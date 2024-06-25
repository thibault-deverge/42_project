from django.test import TestCase
from . import apps
from contextlib import redirect_stdout

class MyFunctionTestCase(TestCase):

    def test_my_function(self):
        tournament = {
            "first_demi": {
                "player1": {
                    "id": 160,
                    "score":3
                },
                "player2": {
                    "id": 150,
                    "score": 1
                },
				"ball_hit" : 12
            },
            "second_demi": {
                "player1": {
                    "id": 170,
                    "score": 3
                },
                "player2": {
                    "id": 180,
                    "score": 2
                },
				"ball_hit" : 12
            },
            "final": {
                "player1": {
                    "id": 170,
                    "score": 3
                },
                "player2": {
                    "id": 160,
                    "score": 2
                },
				"ball_hit" : 12
            }
        }
        with open('test.txt', 'w') as f:
            with redirect_stdout(f):
                tournoi = apps.createNewTournament()
                apps.setAll(tournoi, tournament)
                print(apps.getStats(160), "\n")
