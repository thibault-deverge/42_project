from django.views.generic import TemplateView
from django.conf import settings
from django.conf.urls.static import static
from django.urls import path, include, re_path

urlpatterns = [
    # Extension path
    path('__reload__/', include('django_browser_reload.urls')),

    path('auth/', include('authentication.urls')),
    path('user/', include('user.urls')),
    path('game/', include('game.urls')),
    re_path(r'^.*$', TemplateView.as_view(template_name='single_page/index.html'), name='home'),
	path('tournament/', include('blockchain.urls')),
] + static(settings.MEDIA_URL, document_root=settings.MEDIA_ROOT)
