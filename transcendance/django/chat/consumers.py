import json

from channels.generic.websocket import AsyncWebsocketConsumer
from authentication.models import *
from channels.db import database_sync_to_async
from asgiref.sync import sync_to_async
from authentication.models import CustomUser
from game.game import all_private_room, private_game
from single_page.consumers import random_id
import asyncio

def create_msg(sender ,msg):
    data = {
            'sender': sender,
            'message': msg,
        }
    data = json.dumps(data)
    return data

def add_info(data, key, value):
    updated = json.loads(data)
    updated[key] = value
    updated = json.dumps(updated)
    return updated

def rm_info(data, key):
    updated = json.loads(data)
    updated.pop(key, None)
    updated = json.dumps(updated)
    return updated


private_queue = {}

class ChatConsumer(AsyncWebsocketConsumer):
    async def connect(self):
        self.name = None
        self.user = None
        self.room_group_name = {}
        await self.channel_layer.group_add("chat", self.channel_name)
        await self.accept()
        u = await sync_to_async(CustomUser.objects.get)(id=self.scope['user'].id)
        u.connected_chat += 1
        await sync_to_async(u.save)()

    async def disconnect(self, close_code):
        if (self.name == None):
            return
        await database_sync_to_async(self.user.save)()
        await self.channel_layer.group_discard("chat", self.channel_name)
        await self.channel_layer.group_discard(self.name, self.channel_name)
        u = await sync_to_async(CustomUser.objects.get)(id=self.scope['user'].id)
        u.connected_chat -= 1
        await sync_to_async(u.save)()
        if u.connected_chat == 0:
            room_to_delete = []
            for room_key, room_value in private_queue.items():
                if self.scope["user"].id in room_value:
                    room_to_delete.append(room_key)
            for room in room_to_delete:
                del private_queue[room]
        else:
            for room_key, room_value in self.room_group_name.items():
                await self.channel_layer.group_discard(self.name, room_value)


    async def receive(self, text_data):
        self_request = ["self_new_message", "self_new_message_whisper", "self_blockUser", "self_unblockUser"]
        check = json.loads(text_data)
        if (self.name == None and check['type'] != "identify"):
            return
        updated_data = add_info(text_data, 'sender', self.channel_name)
        if check['type'] == "update":
            await self.handle_update(check,updated_data)
        elif check['type'] == "new_message":
            await self.handle_message(updated_data)
        elif check['type'] == "new_message_whisper":
            await self.handle_whisper(check, updated_data)
        elif check['type'] == 'identify':
            await self.handle_identify(check)
        elif check['type'] == 'blockUser':
            await self.handle_blockUser(check)
        elif check['type'] == 'unblockUser':
            await self.handle_unblockUser(check)
        elif check['type'] == 'invite private game':
            await self.handle_invite_private_game(check)
        elif check['type'] == 'accept private game':
            await self.handle_accept_private_game(check)
        elif check['type'] == 'deco':
            await self.handle_deco()
        for elem in self_request:
            if check['type'] == elem:
                await self.handle_self_new_message(updated_data)

    async def handle_deco(self):
        msg = create_msg(self.channel_name, "has disconnected !")
        msg = add_info(msg, 'type', "disconnection")
        msg = add_info(msg, 'name', self.name)
        await self.channel_layer.group_send(
            "chat",
            {
                "type": "chat.message",
                "message": msg,
            },
        )

    async def handle_update(self,check,updated_data):
        updated_data = add_info(updated_data, 'name', self.name)
        updated_data = rm_info(updated_data, 'sender')
        await self.channel_layer.send(
            check['send_to'],
            {
                'type': 'update',
                "message": updated_data,
            }
        )

    async def handle_message(self, updated_data):
        updated_data = add_info(updated_data, 'name', self.name)
        await self.channel_layer.group_send(
            "chat",
            {
                "type": "chat.message",
                "message": updated_data,
            },
        )

    async def handle_whisper(self, check, updated_data):
        try:
            user = await database_sync_to_async(CustomUser.objects.get)(username=check['whisper_to'])
            updated_data = add_info(updated_data, 'name', self.name)
            await self.channel_layer.group_send(
                user.username,
                {
                    "type": "whisper",
                    "message": updated_data,
                },
            )
        except:
            print("Invalid username !")

    async def handle_identify(self, check):
        self.user = await database_sync_to_async(CustomUser.objects.get)(username=check['message'])
        self.name = self.user.username
        await self.channel_layer.group_add(self.name, self.channel_name)
        await database_sync_to_async(self.user.save)()
        payload = {
            "type" : "blockedList",
            "blockedList" : await self.user.get_blocked_list(),
        }
        payload = json.dumps(payload)
        await self.channel_layer.send(
            self.channel_name,
            {
                'type': 'identify',
                "message": payload,
            }
        )
        msg = create_msg(self.channel_name, "has connected !")
        msg = add_info(msg, 'type', "new_connection")
        msg = add_info(msg, 'name', self.name)
        await self.channel_layer.group_send(
            "chat",
            {
                "type": "chat.message",
                "message": msg,
            }
        )

    async def handle_blockUser(self, check):
        await self.user.block_user(check['message'])

    async def handle_unblockUser(self, check):
        await self.user.unblock_user(check['message'])

    async def handle_self_new_message(self, updated_data):
        await self.channel_layer.group_send(
            self.name,
            {
                "type": "to_self",
                "message": updated_data,
            },
        )

    async def handle_invite_private_game(self, check):
        for room_key, room_value in private_queue.items():
            if self.scope["user"].id in room_value and check['name'] in room_value:
                check["id_game"] = room_key
                await self.channel_layer.group_send(
                    check['name'],
                    {
                        "type": "send_message_all",
                        "message": json.dumps(check),
                    },
                )
                return
        rid = random_id()
        while rid in private_queue or rid in all_private_room:
            rid = random_id()
        self.room_group_name[rid] = ('room_%s_queue' % rid)
        await self.channel_layer.group_add(self.room_group_name[rid], self.channel_name)
        private_queue[rid] = [self.scope["user"].id]
        private_queue[rid].append(check['name'])
        check["id_game"] = rid
        await self.channel_layer.group_send(
            check['name'],
            {
                "type": "send_message_all",
                "message": json.dumps(check),
            },
        )

    async def handle_accept_private_game(self, check):
        if check['id_game'] in private_queue:
            self.room_group_name[check['id_game']] = ('room_%s_queue' % check['id_game'])
            all_private_room[check['id_game']] = {}
            all_private_room[check['id_game']][private_queue[check['id_game']][0]] = {
                "up": 0,
                "down": 0,
            }
            all_private_room[check['id_game']][self.scope['user'].id] = {
                "up": 0,
                "down": 0,
            }
            await self.channel_layer.group_add(self.room_group_name[check['id_game']], self.channel_name)
            msg = create_msg(self.channel_name, "CONNECT PRIVATE GAME")
            msg = add_info(msg, "id_game", check['id_game'])
            msg = add_info(msg, 'type', "connect_private_match")
            await self.channel_layer.group_send(self.room_group_name[check['id_game']], {
                'type': 'send_message_all',
                "message": msg,
            })
            player_1 = await sync_to_async(CustomUser.objects.get)(id=private_queue[check['id_game']][0])
            player_2 = await sync_to_async(CustomUser.objects.get)(id=self.scope['user'].id)
            asyncio.create_task(private_game(check['id_game'], private_queue[check['id_game']][0], self.scope['user'].id, player_1.username, player_2.username))
            if check['id_game'] in private_queue:
                del private_queue[check['id_game']]

        else:
            await self.channel_layer.send(
                self.channel_name,
                {
                    'type': 'identify',
                    'message': json.dumps({"type": "PRIVATE GAME ROOM DOESN'T EXIST"})
                }
            )


    async def identify(self, event):
        await self.send(text_data=event["message"])

    async def chat_message(self, event):
        data_dict = json.loads(event["message"])
        myself = self.channel_name
        sent_by = data_dict['sender']
        if data_dict['name'] == self.name:
            return
        if sent_by != myself:
            await self.send(text_data=event["message"])

    async def whisper(self, event):
        data_dict = json.loads(event["message"])
        myself = self.channel_name
        sent_by = data_dict['sender']
        data_dict.pop("sender", None)
        data_dict.pop("whisper_to", None)
        data_dict = json.dumps(data_dict)
        if sent_by != myself:
            await self.send(text_data=data_dict)

    async def update(self, event):
        message_data = json.loads(event["message"])
        if message_data['name'] == self.name:
            return
        message_data.pop("send_to", None)
        message_data = json.dumps(message_data)
        await self.send(text_data=message_data)

    async def to_self(self, event):
        data = json.loads(event["message"])
        if (data['sender'] != self.channel_name):
            await self.send(text_data=event["message"])

    async def send_message_all(self, event):
        await self.send(text_data=event["message"])
