import os
import requests
from urllib.request import urlopen
from django.core.files.base import ContentFile
from django.contrib.auth import authenticate, login, logout, get_user_model
from django.shortcuts import redirect
from rest_framework import status
from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework.permissions import AllowAny, IsAuthenticated
from rest_framework.exceptions import NotAuthenticated
from .serializers import UserSignupSerializer
from django.http import HttpResponseRedirect

User = get_user_model()

class SignupAPIView(APIView):
    permission_classes = [AllowAny]

    def post(self, request):
        serializer = UserSignupSerializer(data=request.data)
        if serializer.is_valid():
            user = serializer.save()
            response_data = {
                "username": user.username,
                "email": user.email
            }
            return Response(response_data, status=status.HTTP_201_CREATED)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

class LoginAPIView(APIView):
    permission_classes = [AllowAny]

    def post(self, request, *args, **kwargs):
        username = request.data.get('username')
        password = request.data.get('password')

        user = authenticate(request, username=username, password=password)
        if user is not None:
            login(request, user)
            return Response({'detail': 'login successful'}, status=status.HTTP_200_OK)
        return Response({'detail': 'Invalid username or password'}, status=status.HTTP_400_BAD_REQUEST)

class LogoutAPIView(APIView):
    permission_classes = [IsAuthenticated]

    def get(self, request):
        logout(request)
        return Response(status=status.HTTP_204_NO_CONTENT)

class CheckAuthAPIView(APIView):
    permission_classes = [IsAuthenticated]

    def get(self, request):
        return Response({"authenticated": True}, status=status.HTTP_200_OK)

    def handle_exception(self, exc):
        if isinstance(exc, NotAuthenticated):
            return Response({"authenticated": False}, status=status.HTTP_200_OK)
        return super().handle_exception(exc)
class getComputerPath(APIView):
    permission_classes = [AllowAny]

    def get(self, request):
        address = os.environ.get("ALLOWED_HOST")
        return Response({"address": address}, status=status.HTTP_200_OK)
class GetuserAPIView(APIView):
    permission_classes = [IsAuthenticated]

    def get(self, request):
        user = request.user
        session_id = request.session.session_key

        response_data = {
            "username": user.username,
            "email": user.email,
            "session_id": session_id
        }
        return Response(response_data, status=status.HTTP_200_OK)

class DeleteUserAPIView(APIView):
    permission_classes = [IsAuthenticated]

    def delete(self, request):
        user = request.user
        user.delete()
        return Response(status=status.HTTP_204_NO_CONTENT)

class OAuthCallbackView(APIView):
    permission_classes = [AllowAny]

    def get(self, request):
        code = request.GET.get('code')
        if not code:
            return HttpResponseRedirect("https://" + os.environ.get("ALLOWED_HOST") + ":8443")
        
        token_url = 'https://api.intra.42.fr/oauth/token'
        client_id = os.environ.get('CLIENT_API_ID')
        client_secret = os.environ.get('SECRET_API_KEY')
        HOST = os.environ.get('ALLOWED_HOST')
        redirect_uri =  "https://" + HOST + ":8443/auth/oauth/callback/"

        data = {
            'grant_type': 'authorization_code',
            'client_id': client_id,
            'client_secret': client_secret,
            'code': code,
            'redirect_uri': redirect_uri,
        }

        response = requests.post(token_url, data=data)
        if response.status_code != 200:
            return HttpResponseRedirect("https://" + os.environ.get("ALLOWED_HOST") + ":8443")
        
        access_token = response.json().get('access_token')

        user_info_url = 'https://api.intra.42.fr/v2/me'
        headers = {'Authorization': f'Bearer {access_token}'}
        user_info_response = requests.get(user_info_url, headers=headers)

        if user_info_response.status_code != 200:
            return HttpResponseRedirect("https://" + os.environ.get("ALLOWED_HOST") + ":8443")
        
        user_info = user_info_response.json()

        username = user_info['login']
        email = user_info.get('email', f'${username}@42.fr')
        user_id = user_info['id']

        detailed_user_info_url = f'https://api.intra.42.fr/v2/users/{user_id}'
        detailed_user_info_response = requests.get(detailed_user_info_url, headers=headers)

        if detailed_user_info_response.status_code != 200:
            logger.error('Failed to fetch detailed user info: %s', detailed_user_info_response.text)
            return HttpResponseRedirect("https://" + os.environ.get("ALLOWED_HOST") + ":8443")

        detailed_user_info = detailed_user_info_response.json()
        avatar_url = detailed_user_info.get('image', {}).get('versions', {}).get('medium')

        base_username = username
        counter = 1
        while User.objects.filter(username=username).exists():
            username = f'{base_username}{counter}'

        user, created = User.objects.get_or_create(email=email, defaults={'username': username})
        if created:
            user.set_unusable_password()
            user.save()

        if user.avatar and 'default_profil.jpg' in user.avatar.url:
            if avatar_url:
                avatar_response = urlopen(avatar_url)
                avatar_content = avatar_response.read()
                user.avatar.save(f'{username}_avatar.jpg', ContentFile(avatar_content))

        login(request, user)
        return redirect('/')