import json
from channels.generic.websocket import AsyncWebsocketConsumer
from .game import all_private_room, all_room

class MatchConsumer(AsyncWebsocketConsumer):

    async def connect(self):
        self.room_name = self.scope["url_route"]["kwargs"]["id_game"]
        self.room_group_name = 'room_%s' % self.room_name
        await self.channel_layer.group_add(self.room_group_name, self.channel_name)
        await self.accept()
        if self.room_name in all_room:
            if self.scope['user'].id not in all_room[self.room_name]:
                await self.send(text_data=json.dumps({"event": "SPECTATOR"}))

    async def disconnect(self, close_code):
        await self.channel_layer.group_discard(self.room_group_name, self.channel_name)

    async def receive(self, text_data):
        response = json.loads(text_data)
        response = response.get('message')
        
        if response["event"] == 'PRESS':
            if self.room_name in all_room:
                if self.scope['user'].id in all_room[self.room_name]:
                    if response["move"] == 87:
                        all_room[self.room_name][self.scope['user'].id]["up"] = 1
                    elif response["move"] == 83:
                        all_room[self.room_name][self.scope['user'].id]["down"] = 1
                else:
                    await self.send(text_data=json.dumps({"event": "SPECTATOR"}))
            elif self.room_name in all_private_room:
                if self.scope['user'].id in all_private_room[self.room_name]:
                    if response["move"] == 87:
                        all_private_room[self.room_name][self.scope['user'].id]["up"] = 1
                    elif response["move"] == 83:
                        all_private_room[self.room_name][self.scope['user'].id]["down"] = 1
                else:
                    await self.send(text_data=json.dumps({"event": "SPECTATOR"}))
        elif response["event"] == 'RELEASE':
            if self.room_name in all_room:
                if self.scope['user'].id in all_room[self.room_name]:
                    if response["move"] == 87:
                        all_room[self.room_name][self.scope['user'].id]["up"] = 0
                    elif response["move"] == 83:
                        all_room[self.room_name][self.scope['user'].id]["down"] = 0
                else:
                    await self.send(text_data=json.dumps({"event": "SPECTATOR"}))
            elif self.room_name in all_private_room:
                if self.scope['user'].id in all_private_room[self.room_name]:
                    if response["move"] == 87:
                        all_private_room[self.room_name][self.scope['user'].id]["up"] = 0
                    elif response["move"] == 83:
                        all_private_room[self.room_name][self.scope['user'].id]["down"] = 0
                else:
                    await self.send(text_data=json.dumps({"event": "SPECTATOR"}))

    async def send_message_all(self, res):
        await self.send(res["message"])


    async def send_game_all(self, res):
        message = res["message"]
        if message["player_2"] == self.scope["user"].id:
            if message["data"]["game"]["player1"]["player"] != "2":
                tmp = message["data"]["game"]["player2"]
                message["data"]["game"]["player2"] = message["data"]["game"]["player1"]
                message["data"]["game"]["player1"] = tmp
                message["data"]["game"]["ball"]["x"] = 1 - message["data"]["game"]["ball"]["x"]
        else:
            if message["data"]["game"]["player1"]["player"] != "1":
                tmp = message["data"]["game"]["player2"]
                message["data"]["game"]["player2"] = message["data"]["game"]["player1"]
                message["data"]["game"]["player1"] = tmp
                message["data"]["game"]["ball"]["x"] = 1 - message["data"]["game"]["ball"]["x"]
        await self.send(json.dumps(message["data"]))


