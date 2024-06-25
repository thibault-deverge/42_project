from django.urls import path
from . import views

urlpatterns = [
    path('signup/', views.SignupAPIView.as_view(), name='signup'),
    path('login/', views.LoginAPIView.as_view(), name='login'),
    path('logout/', views.LogoutAPIView.as_view(), name='logout'),
    path('check-auth/', views.CheckAuthAPIView.as_view(), name='check_auth'),
    path('get-user/', views.GetuserAPIView.as_view(), name='get-user'),
    path('delete-user/', views.DeleteUserAPIView.as_view(), name='delete-user'),
    path('oauth/callback/', views.OAuthCallbackView.as_view(), name='oauth_callback'),
]