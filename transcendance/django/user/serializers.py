from PIL import Image
from django.contrib.auth import get_user_model
from rest_framework import serializers

User = get_user_model()
class AvatarUpdateSerializer(serializers.ModelSerializer):
    class Meta:
        model = User
        fields = ['avatar']

    def validate_avatar(self, value):
        img = Image.open(value)
        if img.height > 800 or img.width > 800:
            raise serializers.ValidationError("Avatar must be no larger than 800x800 pixels")
        if not img.format.lower() in ['jpeg', 'png']:
            raise serializers.ValidationError("Avatar must be a JPEG or PNG file")
        return value

class CoverPhotoUpdateSerializer(serializers.ModelSerializer):
    class Meta:
        model = User
        fields = ['cover_photo']

    def validate_cover_photo(self, value):
        img = Image.open(value)
        if not img.format.lower() in ['jpeg', 'png']:
            raise serializers.ValidationError("Cover photo must be a JPEG or PNG file")
        return value

class UsernameUpdateSerializer(serializers.ModelSerializer):
    class Meta:
        model = User
        fields = ['username']
    
    def validate_username(self, value):
        if len(value) > 20:
            raise serializers.ValidationError("Username have a maximum size of 20 characters.")    
        return value

class QuoteUpdateSerializer(serializers.ModelSerializer):
    class Meta:
        model = User
        fields = ['quote']
    
    def validate_quote(self, value):
        if len(value) > 42:
            raise serializers.ValidationError("Quote have a maximum size of 42 characters.")    
        return value