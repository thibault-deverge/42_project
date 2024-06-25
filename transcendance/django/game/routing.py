from django.urls import path
from game import consumers

websocket_urlpatterns = [
    path("wss/match/online/<str:id_game>", consumers.MatchConsumer.as_asgi()),
    path("wss/tournament/online/<str:id_game>", consumers.MatchConsumer.as_asgi()),
    path("wss/private_match/online/<str:id_game>", consumers.MatchConsumer.as_asgi())
]