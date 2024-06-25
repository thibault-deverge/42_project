from django.urls import path
from . import views

urlpatterns = [
    path('update_cover_photo/', views.CoverPhotoUpdateView.as_view(), name='update_cover_photo'),
    path('update_avatar/', views.AvatarUpdateView.as_view(), name='update_avatar'),
    path('update_username/', views.UsernameUpdateView.as_view(), name='update_username'),
    path('update_quote/', views.QuoteUpdateView.as_view(), name='update_quote'),
    path('user_profile/', views.UserProfileView.as_view(), name='user_profile'),
    path('<str:username>/', views.UserProfileDetailView.as_view(), name='user_profile_detail'),
    path('get_friends/<str:username>/', views.FriendListView.as_view(), name='friend_list'),
    path('add_friend/<str:username>/', views.AddFriendView.as_view(), name='add_friend'),
    path('remove_friend/<str:username>/', views.RemoveFriendView.as_view(), name='remove_friend'),
]