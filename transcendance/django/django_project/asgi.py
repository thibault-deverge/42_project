"""
ASGI config for django_project project.

It exposes the ASGI callable as a module-level variable named ``application``.

For more information on this file, see
https://docs.djangoproject.com/en/5.0/howto/deployment/asgi/
"""

import os

from django.core.asgi import get_asgi_application

from channels.auth import AuthMiddlewareStack
from channels.routing import ProtocolTypeRouter, URLRouter
from channels.security.websocket import AllowedHostsOriginValidator

asgi_apps = get_asgi_application()

from chat.routing import websocket_urlpatterns as websocket_urlpatterns_chat
from game.routing import websocket_urlpatterns as websocket_urlpatterns_game
from single_page.routing import websocket_urlpatterns as websocket_urlpatterns_single_page

os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'django_project.settings')

application = ProtocolTypeRouter(
    {
        "http": asgi_apps,
        "websocket": AllowedHostsOriginValidator(AuthMiddlewareStack(URLRouter(websocket_urlpatterns_chat + websocket_urlpatterns_game + websocket_urlpatterns_single_page))),
    }
)