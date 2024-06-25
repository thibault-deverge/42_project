from PIL import Image
from django.core.files.images import get_image_dimensions
from django.contrib.auth import get_user_model
from rest_framework import serializers
import re

User = get_user_model()

class UserSignupSerializer(serializers.ModelSerializer):
    confirm_password = serializers.CharField(style={'input_type': 'password'}, write_only=True)
    email = serializers.EmailField(required=True)

    class Meta:
        model = User
        fields = ('username', 'email', 'password', 'confirm_password')
        extra_kwargs = {
            'password': {'write_only': True},
            'confirm_password': {'write_only': True}
        }

    def validate(self, attrs):
        username = attrs.get('username')
        email = attrs.get('email')
        password = attrs.get('password')
        confirm_password = attrs.pop('confirm_password', None)

        if len(User.objects.filter(username=username)) > 20:
            raise serializers.ValidationError("Username have a maximum size of 20 characters.")    
        if not re.match("^[a-zA-Z0-9_]+$", username):
            raise serializers.ValidationError("Username should contains only alphanumerics value and underscore")
        if User.objects.filter(email=email).exists():
            raise serializers.ValidationError("This email is already in use.")
        if password != confirm_password:
            raise serializers.ValidationError("Password and Confirm Password does not match")
        if len(password) < 8:
            raise serializers.ValidationError("Password should be at least 8 characters long")
        if not re.search("[a-zA-Z]", password) or not re.search("[0-9]", password):
            raise serializers.ValidationError("Password must contain at least one letter and one number")

        return attrs

    def create(self, validated_data):
        return User.objects.create_user(**validated_data)