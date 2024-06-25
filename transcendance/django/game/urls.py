from django.urls import path
from . import views

urlpatterns = [
    path('leaderboard/', views.GetLeaderboardAPIView.as_view(), name='games-leaderboard'),
    path('recent-games/', views.RecentGamesAPIView.as_view(), name='recent-games'),
    path('stats/tournament/', views.GetStatsTournamentAPIView.as_view(), name='stats-tournament'),
    path('stats/match/', views.GetStatsMatchAPIView.as_view(), name='stats-match'),
    path('in_queue/', views.GetInQueueAPIView.as_view(), name='in-queue'),
]