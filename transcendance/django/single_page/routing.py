from django.urls import re_path
from single_page import consumers

websocket_urlpatterns = [
    re_path("wss/global", consumers.MatchMakingConsumer.as_asgi()),
]
