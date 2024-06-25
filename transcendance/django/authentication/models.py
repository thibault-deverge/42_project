from django.contrib.auth.models import AbstractUser
from django.db import models
from channels.db import database_sync_to_async

import json

class CustomUser(AbstractUser):
    avatar = models.ImageField(upload_to='avatars/', default='/avatars/default_profil.jpg', blank=True)
    cover_photo = models.ImageField(upload_to='cover_photos/', default="/cover_photos/default_couverture.jpg", null=True, blank=True)
    quote = models.CharField(max_length=42, default="Insert a small quote here", null=True, blank=True)
    friends = models.ManyToManyField('self', symmetrical=False, related_name='friend_of', blank=True)
    blockedUser = models.TextField(null=True)
    connected = models.IntegerField(default=0)
    connected_chat = models.IntegerField(default=0)
    queue_tournament = models.BooleanField(default=False)
    queue_match = models.BooleanField(default=False)

    async def get_blocked_list(self):
        if self.blockedUser == None:
            return None
        return json.loads(self.blockedUser)

    async def block_user(self, username):
        list = await self.get_blocked_list()
        if self.username == username:
            return
        if list is None:
            list = [username]
        elif username not in list:
            list.append(username)
        self.blockedUser = json.dumps(list)
        await database_sync_to_async(self.save)()

    async def unblock_user(self, username):
        list = await self.get_blocked_list()
        if list is None:
            return
        if username in list:
            list.remove(username)
            self.blockedUser = json.dumps(list)
            await database_sync_to_async(self.save)()