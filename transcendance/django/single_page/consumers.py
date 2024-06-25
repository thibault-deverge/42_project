import json
from channels.generic.websocket import AsyncWebsocketConsumer
from asgiref.sync import sync_to_async
import asyncio
from django.utils.crypto import get_random_string
from game.models import GameModel
from game.game import game, all_room, add_info, create_msg, timer, POINT_TO_WIN
from authentication.models import CustomUser
from blockchain.apps import createNewTournament, setAll

def random_id():
    return get_random_string(5, 'qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM0123456789')

queue_match = {}
queue_tournament = {}

class MatchMakingConsumer(AsyncWebsocketConsumer):
    async def connect(self):
        self.room_user = 'room_%s_queue' % self.scope['user'].id
        await self.channel_layer.group_add(self.room_user, self.channel_name)
        self.room_name = None
        await self.accept()
        u = await sync_to_async(CustomUser.objects.get)(id=self.scope['user'].id)
        u.connected += 1
        await sync_to_async(u.save)()


    async def disconnect(self, close_code):
        u = await sync_to_async(CustomUser.objects.get)(id=self.scope['user'].id)
        await self.channel_layer.group_discard(self.room_user, self.channel_name)
        u.connected -= 1
        await sync_to_async(u.save)()
        if u.connected == 0:
            await self.leave_queue()

    async def leave_queue(self):
        for room_key, room_value in queue_match.items():
            if self.scope["user"].id in room_value:
                queue_match[room_key].remove(self.scope["user"].id)
                u = await sync_to_async(CustomUser.objects.get)(id=self.scope['user'].id)
                u.queue_match = False
                await sync_to_async(u.save)()
        for room_key, room_value in queue_tournament.items():
            if self.scope["user"].id in room_value:
                queue_tournament[room_key].remove(self.scope["user"].id)
                u = await sync_to_async(CustomUser.objects.get)(id=self.scope['user'].id)
                u.queue_tournament = False
                await sync_to_async(u.save)()
        if self.room_name is not None:
            await self.channel_layer.group_discard(self.room_group_name, self.channel_name)
            self.room_name = None

    async def receive(self, text_data):
        response = json.loads(text_data)
        response = response.get('message')
        if response == 'SEARCH MATCH':
            await self.search_match()
        elif response == 'LEAVE MATCH':
            await self.leave_match()
        elif response == 'SEARCH TOURNAMENT':
            await self.search_tournament()
        elif response == 'LEAVE QUEUE TOURNAMENT':
            await self.leave_queue_tournament()
        elif response == 'LEAVE QUEUE':
            await self.leave_queue()


        ######### MATCH PART ########

    async def search_match(self):
        for room_key, room_value in all_room.items():
            if self.scope["user"].id in room_value:
                if len(room_value) > 2:
                    msg = create_msg(self.channel_name, "CONNECT TOURNAMENT")
                    msg = add_info(msg, "id_game", room_key)
                    await self.channel_layer.group_send(self.room_user, {
                        'type': 'send_message_all',
                        "message": msg,
                    })
                else:
                    msg = create_msg(self.channel_name, "CONNECT MATCH")
                    msg = add_info(msg, "id_game", room_key)
                    await self.channel_layer.group_send(self.room_user, {
                        'type': 'send_message_all',
                        "message": msg,
                    })
                return
        if self.room_name is not None:
            if self.room_name in queue_match:
                return
        await self.leave_queue_tournament()
        await self.match_making_1v1()

    async def leave_match(self):
        for room_key, room_value in queue_match.items():
            if self.scope["user"].id in room_value:
                queue_match[room_key].remove(self.scope["user"].id)
                u = await sync_to_async(CustomUser.objects.get)(id=self.scope['user'].id)
                u.queue_match = False
                await sync_to_async(u.save)()
                msg = create_msg(self.channel_name, "LEAVE QUEUE MATCH")
                await self.channel_layer.group_send(self.room_user, {
                    'type': 'send_message_all',
                    "message": msg,
                })
        if self.room_name is not None:
            await self.channel_layer.group_discard(self.room_group_name, self.channel_name)
            self.room_name = None

    async def match_making_1v1(self):
        if queue_match:
            for room_key, room_value in queue_match.items():
                room_value.append(self.scope["user"].id)
                self.room_name = room_key
                self.room_group_name = 'room_%s_queue' % self.room_name
                await self.channel_layer.group_add(self.room_group_name, self.channel_name)
                if len(room_value) == 2:
                    del queue_match[room_key]
                    await self.match_starting(self.room_name, room_value)
                    return
        else:
            rid = random_id()
            while rid in queue_match or rid in queue_tournament or rid in all_room:
                rid = random_id()
            self.room_name = rid
            self.room_group_name = 'room_%s_queue' % self.room_name
            await self.channel_layer.group_add(self.room_group_name, self.channel_name)
            queue_match[rid] = [self.scope["user"].id]
        u = await sync_to_async(CustomUser.objects.get)(id=self.scope['user'].id)
        u.queue_match = True
        await sync_to_async(u.save)()
        msg = create_msg(self.channel_name, "WAITING MATCH")
        await self.channel_layer.group_send(self.room_user, {
            'type': 'send_message_all',
            "message": msg,
        })

    async def match_starting(self, id, players):
        all_room[id] = {}
        all_room[id][players[0]] = {
            "up": 0,
            "down": 0,
            }
        all_room[id][players[1]] = {
            "up": 0,
            "down": 0,
            }
        msg = create_msg(self.channel_name, "CONNECT MATCH")
        msg = add_info(msg, "id_game", id)
        await self.channel_layer.group_send(self.room_group_name, {
            'type': 'send_message_all',
            "message": msg,
        })
        asyncio.create_task(self.match(id, players))

    async def match(self, id,  players):
        player_1 = await sync_to_async(CustomUser.objects.get)(id=players[0])
        player_2 = await sync_to_async(CustomUser.objects.get)(id=players[1])
        player_1.queue_match = False

        await sync_to_async(player_1.save)()
        match = await game(id, players[0], players[1], player_1.username, player_2.username)
        if match["player1"]["score"] == POINT_TO_WIN:
            winner = await sync_to_async(CustomUser.objects.get)(id=players[0])
            loser = await sync_to_async(CustomUser.objects.get)(id=players[1])
            score_loser = match["player2"]["score"]
        else:
            winner = await sync_to_async(CustomUser.objects.get)(id=players[1])
            loser = await sync_to_async(CustomUser.objects.get)(id=players[0])
            score_loser = match["player1"]["score"]
        score_winner = POINT_TO_WIN
        g = await sync_to_async(GameModel)(winner=winner, loser=loser, score_winner=score_winner, score_loser=score_loser, ball_hit=match["statistic"]["ball_hit"], score_order=match["statistic"]["score_order"])
        await sync_to_async(g.save)()
        del all_room[id]
        msg = create_msg(self.channel_name, "FINISHED")
        await self.channel_layer.group_send(self.room_group_name, {
            'type': 'send_message_all',
            "message": msg,
        })

        ######### Tournament PART ########

    async def search_tournament(self):
        for room_key, room_value in all_room.items():
            if self.scope["user"].id in room_value:
                if len(room_value) > 2:
                    msg = create_msg(self.channel_name, "CONNECT TOURNAMENT")
                    msg = add_info(msg, "id_game", room_key)
                    await self.channel_layer.group_send(self.room_user, {
                        'type': 'send_message_all',
                        "message": msg,
                    })
                else:
                    msg = create_msg(self.channel_name, "CONNECT MATCH")
                    msg = add_info(msg, "id_game", room_key)
                    await self.channel_layer.group_send(self.room_user, {
                        'type': 'send_message_all',
                        "message": msg,
                    })
                return
        if self.room_name is not None:
            if self.room_name in queue_tournament:
                msg = create_msg(self.channel_name, "ALREADY IN QUEUE")
                await self.channel_layer.group_send(self.room_user, {
                    'type': 'send_message_all',
                    "message": msg,
                })
                return
        await self.leave_match()
        await self.match_making_tournament()

    async def leave_queue_tournament(self):
        for room_key, room_value in queue_tournament.items():
            if self.scope["user"].id in room_value:
                queue_tournament[room_key].remove(self.scope["user"].id)
                u = await sync_to_async(CustomUser.objects.get)(id=self.scope['user'].id)
                u.queue_tournament = False
                await sync_to_async(u.save)()
                msg = create_msg(self.channel_name, "LEAVE QUEUE TOURNAMENT")
                await self.channel_layer.group_send(self.room_user, {
                    'type': 'send_message_all',
                    "message": msg,
                })
        if self.room_name is not None:
            await self.channel_layer.group_discard(self.room_group_name, self.channel_name)
            self.room_name = None


    async def match_making_tournament(self):
        if queue_tournament:
            for room_key, room_value in queue_tournament.items():
                room_value.append(self.scope["user"].id)
                self.room_name = room_key
                self.room_group_name = 'room_%s_queue' % self.room_name
                await self.channel_layer.group_add(self.room_group_name, self.channel_name)
                if len(room_value) == 4:
                    del queue_tournament[room_key]
                    await self.tournament_starting(self.room_name, room_value)
                    return
        else:
            rid = random_id()
            while rid in queue_match or rid in queue_tournament or rid in all_room:
                rid = random_id()
            self.room_name = rid
            self.room_group_name = 'room_%s_queue' % self.room_name
            await self.channel_layer.group_add(self.room_group_name, self.channel_name)
            queue_tournament[rid] = [self.scope["user"].id]
        u = await sync_to_async(CustomUser.objects.get)(id=self.scope['user'].id)
        u.queue_tournament = True
        await sync_to_async(u.save)()
        msg = create_msg(self.channel_name, "WAITING TOURNAMENT")
        await self.channel_layer.group_send(self.room_user, {
            'type': 'send_message_all',
            "message": msg,
        })

    async def tournament_starting(self, id, players):
        all_room[id] = {}
        all_room[id][players[0]] = {
            "up": 0,
            "down": 0,
        }
        all_room[id][players[1]] = {
            "up": 0,
            "down": 0,
        }
        all_room[id][players[2]] = {
            "up": 0,
            "down": 0,
        }
        all_room[id][players[3]] = {
            "up": 0,
            "down": 0,
        }
        msg = create_msg(self.channel_name, "CONNECT TOURNAMENT")
        msg = add_info(msg, "id_game", id)
        await self.channel_layer.group_send(self.room_group_name, {
            'type': 'send_message_all',
            "message": msg,
        })
        asyncio.create_task(self.tournament(id, players))

    async def tournament(self, id, players):
        player_1 = await sync_to_async(CustomUser.objects.get)(id=players[0])
        player_2 = await sync_to_async(CustomUser.objects.get)(id=players[1])
        player_3 = await sync_to_async(CustomUser.objects.get)(id=players[2])
        player_4 = await sync_to_async(CustomUser.objects.get)(id=players[3])

        player_1.queue_tournament = False
        await sync_to_async(player_1.save)()
        player_2.queue_tournament = False
        await sync_to_async(player_2.save)()
        player_3.queue_tournament = False
        await sync_to_async(player_3.save)()

        msg = create_msg(self.channel_name, "NEXT MATCH")
        msg = add_info(msg, "match_status", "first semifinal")
        msg = add_info(msg, "match_infos", [player_1.username, player_2.username])
        await self.channel_layer.group_send(self.room_group_name, {
            'type': 'send_message_all',
            "message": msg,
        })
        semifinal_1 = await game(id, players[0], players[1], player_1.username, player_2.username)
        if semifinal_1["player1"]["score"] == POINT_TO_WIN:
            winner_semifinal1 = players[0]
            winner_semifinal1_name = player_1.username
        else:
            winner_semifinal1 = players[1]
            winner_semifinal1_name = player_2.username
        msg = create_msg(self.channel_name, "NEXT MATCH")
        msg = add_info(msg, "match_status", "second semifinal")
        msg = add_info(msg, "match_infos", [player_3.username, player_4.username])
        await self.channel_layer.group_send(self.room_group_name, {
            'type': 'send_message_all',
            "message": msg,
        })
        semifinal_2 = await game(id, players[2], players[3], player_3.username, player_4.username)
        if semifinal_2["player1"]["score"] == POINT_TO_WIN:
            winner_semifinal2 = players[2]
            winner_semifinal2_name = player_3.username
        else:
            winner_semifinal2 = players[3]
            winner_semifinal2_name = player_4.username
        msg = create_msg(self.channel_name, "NEXT MATCH")
        msg = add_info(msg, "match_status", "final")
        msg = add_info(msg, "match_infos", [winner_semifinal1_name, winner_semifinal2_name])
        await self.channel_layer.group_send(self.room_group_name, {
            'type': 'send_message_all',
            "message": msg,
        })
        await asyncio.sleep(5)
        final = await game(id, winner_semifinal1, winner_semifinal2, winner_semifinal1_name, winner_semifinal2_name)
        data = {
            "first_demi": {
                "player1": {
                    "id": players[0],
                    "score": semifinal_1["player1"]["score"],
                },
                "player2": {
                    "id": players[1],
                    "score": semifinal_2["player2"]["score"],
                },
                "ball_hit": semifinal_1["statistic"]["ball_hit"]
            },
            "second_demi": {
                "player1": {
                    "id": players[2],
                    "score": semifinal_1["player1"]["score"],
                },
                "player2": {
                    "id": players[3],
                    "score": semifinal_1["player2"]["score"],
                },
                "ball_hit": semifinal_2["statistic"]["ball_hit"]
            },
            "final": {
                "player1": {
                    "id": winner_semifinal1,
                    "score": final["player1"]["score"],
                },
                "player2": {
                    "id": winner_semifinal2,
                    "score": final["player2"]["score"],
                },
                "ball_hit": final["statistic"]["ball_hit"]
            }
        }
        tournament = createNewTournament()
        setAll(tournament, data)
        del all_room[id]
        msg = create_msg(self.channel_name, "FINISHED")
        await self.channel_layer.group_send(self.room_group_name, {
            'type': 'send_message_all',
            "message": msg,
        })

        ####### UTILS #######

    async def send_message_all(self, res):
        """ Receive message from room group """
        # Send message to WebSocket
        await self.send(res["message"])
