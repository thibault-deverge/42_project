from django.contrib.auth import get_user_model
from rest_framework import status
from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework.permissions import IsAuthenticated, AllowAny
from rest_framework.parsers import MultiPartParser, FormParser
from rest_framework.exceptions import NotFound
from .serializers import AvatarUpdateSerializer, CoverPhotoUpdateSerializer, UsernameUpdateSerializer, QuoteUpdateSerializer

User = get_user_model()

# ***** UPDATING INFORMATIONS *****
class CoverPhotoUpdateView(APIView):
    permission_classes = [IsAuthenticated]
    parser_classes = [MultiPartParser, FormParser]

    def post(self, request):
        serializer = CoverPhotoUpdateSerializer(request.user, data=request.data, partial=True)
        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

class AvatarUpdateView(APIView):
    permission_classes = [IsAuthenticated]
    parser_classes = [MultiPartParser, FormParser]

    def post(self, request):
        serializer = AvatarUpdateSerializer(request.user, data=request.data, partial=True)
        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

class UsernameUpdateView(APIView):
    permission_classes = [IsAuthenticated]

    def post(self, request):
        serializer = UsernameUpdateSerializer(request.user, data=request.data, partial=True)
        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

class QuoteUpdateView(APIView):
    permission_classes = [IsAuthenticated]

    def post(self, request):
        serializer = QuoteUpdateSerializer(request.user, data=request.data, partial=True)
        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

# ***** RETRIEVE INFORMATIONS OF USERS *****
class UserProfileView(APIView):
    permission_classes = [IsAuthenticated]

    def get(self, request):
        user = request.user
        data = {
            "id": user.id,
            "username": user.username,
            "email": user.email,
            "avatar": user.avatar.url if user.avatar else None,
            "cover_photo": user.cover_photo.url if user.cover_photo else None,
            "quote": user.quote,
            "isConnected": user.connected
        }
        return Response(data)

class UserProfileDetailView(APIView):
    permission_classes = [AllowAny]

    def get(self, request, username):
        try:
            user = User.objects.get(username=username)
        except User.DoesNotExist:
            raise NotFound(detail="User not found", code=404)
        data = {
            "username": user.username,
            "email": user.email,
            "avatar": user.avatar.url if user.avatar else None,
            "cover_photo": user.cover_photo.url if user.cover_photo else None,
            "quote": user.quote,
            "isConnected": user.connected
        }
        return Response(data)

class FriendListView(APIView):
    permission_classes = [IsAuthenticated]

    def get(self, request, username):
        try:
            user = User.objects.get(username=username)
            friends = user.friends.all()
            friend_list = [{
                "username": friend.username, 
                "avatar": friend.avatar.url if friend.avatar else None,
                "isConnected": friend.connected
                } for friend in friends]
            return Response(friend_list)
        except User.DoesNotExist:
            return Response({"detail": "User not found."}, status=status.HTTP_404_NOT_FOUND)


# ***** ADD/REMOVE USER AS A FRIEND *****
class AddFriendView(APIView):
    permission_classes = [IsAuthenticated]

    def post(self, request, username):
        try:
            user_to_add = User.objects.get(username=username)
            if user_to_add in request.user.friends.all():
                return Response({"detail": "User is already a friend."}, status=status.HTTP_400_BAD_REQUEST)
            request.user.friends.add(user_to_add)
            return Response({"detail": "Friend added successfully."}, status=status.HTTP_200_OK)
        except User.DoesNotExist:
            return Response({"detail": "User not found."}, status=status.HTTP_404_NOT_FOUND)

class RemoveFriendView(APIView):
    permission_classes = [IsAuthenticated]

    def post(self, request, username):
        try:
            user_to_remove = User.objects.get(username=username)
            request.user.friends.remove(user_to_remove)
            return Response({"detail": "Friend removed successfully."}, status=status.HTTP_200_OK)
        except User.DoesNotExist:
            return Response({"detail": "User not found."}, status=status.HTTP_404_NOT_FOUND)