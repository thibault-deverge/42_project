from rest_framework import serializers
from .models import GameModel

class GameSerializer(serializers.ModelSerializer):
    class Meta:
        model = GameModel
        fields = '__all__'