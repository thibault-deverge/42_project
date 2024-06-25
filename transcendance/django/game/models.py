import uuid
from django.db import models
from authentication.models import CustomUser
from django.contrib.postgres.fields import ArrayField

class GameModel(models.Model):
    id = models.UUIDField(primary_key=True, default=uuid.uuid4, editable=False)
    score_loser = models.IntegerField(default=0)
    score_winner = models.IntegerField(default=0)
    loser = models.ForeignKey(CustomUser, related_name='loser', null=True, blank=True, on_delete=models.CASCADE)
    winner = models.ForeignKey(CustomUser, related_name='winner', null=True, blank=True, on_delete=models.CASCADE)
    ball_hit = models.IntegerField(default=0)
    score_order = ArrayField(models.CharField(max_length=255), blank=True, null=True)
    date = models.DateTimeField(auto_now_add=True)