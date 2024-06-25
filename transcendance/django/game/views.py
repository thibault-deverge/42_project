from rest_framework import status
from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework.permissions import IsAuthenticated
from .models import GameModel
from django.http import Http404, HttpResponse
from authentication.models import CustomUser
from django.db.models import Count, Q, Sum
from blockchain.apps import getStats

class GetInQueueAPIView(APIView):
    permission_classes = [IsAuthenticated]

    def get(self, request, *args, **kwargs):
        user = CustomUser.objects.get(id=request.user.id)
        if user.queue_match:
            return Response({"queue": "MATCH"}, status=status.HTTP_200_OK)
        elif user.queue_tournament:
            return Response({"queue": "TOURNAMENT"}, status=status.HTTP_200_OK)
        else:
            return HttpResponse(status=204)
class GetLeaderboardAPIView(APIView):
    permission_classes = [IsAuthenticated]

    def get(self, request, *args, **kwargs):
        leaderboard = CustomUser.objects.annotate(num_wins=Count('winner')).order_by('-num_wins')
        limit = request.query_params.get('limit', None)
        if not leaderboard.exists():
            raise Http404("No GameModel matches the given query.")
        if limit:
            try:
                limit = int(limit)
                leaderboard = leaderboard[:limit]
            except ValueError:
                return Response({"error": "Invalid limit value"}, status=status.HTTP_400_BAD_REQUEST)

        if not leaderboard.exists():
            raise Http404("No GameModel matches the given query.")
        leaderboard_data = [
            {
                "rank": index + 1,
                "username": user.username,
                "num_wins": user.num_wins
            } for index, user in enumerate(leaderboard)
        ]
        return Response(leaderboard_data, status=status.HTTP_200_OK)

class RecentGamesAPIView(APIView):
    permission_classes = [IsAuthenticated]
    def get(self, request):
        games = GameModel.objects.all().order_by('-date')
        games_data = []
        for game in games:
            game_data = {
                'id': game.id,
                'winner': {
                    'username': game.winner.username,
                    'id': game.winner.id
                },
                'loser': {
                    'username': game.loser.username,
                    'id': game.loser.id
                },
                'score_winner': game.score_winner,
                'score_loser': game.score_loser,
                'ball_hit': game.ball_hit,
                'score_order': game.score_order,
                'date': game.date
            }
            games_data.append(game_data)
        return Response(games_data, status=status.HTTP_200_OK)

class GetStatsTournamentAPIView(APIView):
    permission_classes = [IsAuthenticated]
    def get(self, request, *args, **kwargs):
        stats = getStats(request.user.id)
        if stats is not None:
            data = {"Tournaments_played": stats[0],
                    "Tournaments_won": stats[1],
                    "Games_played": stats[2],
                    "Games_won": stats[3],
                    "Points": stats[4],
                    "First_loser": stats[5],
                    "Final_reach": stats[6],
            }
            return Response(data, status=status.HTTP_200_OK)
        else:
            return HttpResponse(status=204)

class GetStatsMatchAPIView(APIView):
    permission_classes = [IsAuthenticated]

    def get(self, request, *args, **kwargs):
        current_user = request.user
        total_games = current_user.winner.count() + current_user.loser.count()
        if total_games > 0:
            total_wins = current_user.winner.count()
            total_ball_hits = GameModel.objects.filter(
                Q(loser=current_user) | Q(winner=current_user)
            ).aggregate(total_hits=Sum('ball_hit'))['total_hits']

            games_lose = GameModel.objects.filter(loser=current_user)
            total_points_scored = total_wins * 3
            if len(games_lose) > 0:
                total_points_scored += games_lose.aggregate(score_loser=Sum('score_loser'))['score_loser']

            context = {
                'total_wins': total_wins,
                'total_games': total_games,
                'total_ball_hits': total_ball_hits,
                'total_points_scored': total_points_scored
            }
            return Response(context, status=status.HTTP_200_OK)
        else:
            return HttpResponse(status=204)