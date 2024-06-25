import { getStatsMatch, getStatsTournament } from "../services/gameService.js";
import { fetchRecentGames } from "../services/recentMatchService.js";
import { fetchUserProfile } from "../services/userService.js";
import { attachUserLinkListeners } from "../utils/linksAttach.js";
import { attachRecentMatchListeners, getMatchesLeaderboard } from "./profilePage.js";

export async function renderStatisticsPage() {
    const userData = await fetchUserProfile();
    const games = await fetchRecentGames();
    const recentGames = games.filter(game => game.winner.username === userData.username || game.loser.username === userData.username);
    const statsTournament = await getStatsTournament()
    const statsMatches = await getStatsMatch()
    const statisticsGameHtml = getStatisticsPageHtml(recentGames, userData.username, statsTournament, statsMatches, userData.id);

    document.body.insertAdjacentHTML('beforeend', statisticsGameHtml);
    if (statsMatches)
        StatsMatches(statsMatches)
    if (statsTournament)
        StatsTournaments(statsTournament)
    attachUserLinkListeners();
    attachRecentMatchListeners()
}

function getStatisticsPageHtml(recentGames, username, statsTournament, statsMatches, id) {
    return /*html*/`
        <main class="statistic-grid">
            <div class="statistics-container">
                <section class="stats">
                    <div class="stats__matches">
                        ${GetStatsMatches(statsMatches)}
                    </div>
                    <div class="stats__tournaments">
                        ${GetStatsTournaments(statsTournament)}
                    </div>
                </section>
                ${getMatchesLeaderboard(recentGames, username, id)}
            </div>
        </main>`;
}

function GetStatsMatches(statsMatches) {
    const WinRate = Math.round(statsMatches.total_wins / statsMatches.total_games * 100);
    const AveragePoint = Math.round(statsMatches.total_ball_hits / statsMatches.total_games);
    const TotalPointsScored = statsMatches.total_points_scored;
    if (statsMatches)
        return /*html*/`
        <div class="chart-container" style="position: relative;">
            <canvas class="pieChart" id="StatsMatches"></canvas>
        </div>
        <div class="otherStats">
            <p>Win Rate : ${WinRate}%</p>
            <p>Avg Ball Hits : ${AveragePoint}</p>
            <p>Total Pts Scored : ${TotalPointsScored}</p>
        </div>`
    else
         return /*html*/` <p>No Match DATA</p>`
}

function StatsMatches(statsMatches) {

        const matches_won = statsMatches.total_wins;
        const matches_lost = statsMatches.total_games - statsMatches.total_wins;
        let ctx = document.getElementById("StatsMatches").getContext("2d")
    
        const data = {
            labels: [
                'Win',
                'Lose',
            ],
            datasets: [{
                label: 'Match Data',

                data: [matches_won, matches_lost],
                backgroundColor: [
                    'rgb(38, 158, 38)',
                    'rgb(215, 38, 61)'
                ],
                hoverOffset: 4,
            }]
        };
        const config = {
            type: 'pie',
            data: data,
            options: {
                responsive: true,
                maintainAspectRatio: true,
                plugins:{
                    legend: {
                        labels: {
                            color: "white",
                            font: {
                                size: 13
                            },
                            boxWidth: 10,
                        }
                    }
                }
            }
        };
        let ChartStatsMatches = new Chart(ctx, config);
}

function GetStatsTournaments(statsTournament) {
    const WinRate = Math.round(statsTournament.Tournaments_won / statsTournament.Tournaments_played * 100);
    const AveragePoint = Math.round(statsTournament.total_ball_hits / statsTournament.Tournaments_played);
    const TotalPointsScored = statsTournament.Points;
    if (statsTournament)
        return /*html*/`
        <div class="chart-container">
            <canvas class="pieChart" id="StatsTournaments"></canvas>
        </div>
        <div class="otherStats">
            <p>Win Rate : ${WinRate}%</p>
            <p>Avg Ball Hits : ${AveragePoint}</p>
            <p>Total Pts Scored : ${TotalPointsScored}</p>
        </div>`
    else
         return /*html*/` <p>No Match DATA</p>`
}

function StatsTournaments(statsTournament) {
    const tournament_won = statsTournament.Tournaments_won;
    const final_reach = statsTournament.Final_reach;
    const first_loser = statsTournament.First_loser;
    let ctx = document.getElementById("StatsTournaments").getContext("2d")
    const data = {
        labels: [
            'Win',
            'Finalist',
            'SemiFinalist',
        ],
        datasets: [{
            label: 'Tournament Data',
            data: [tournament_won, final_reach, first_loser],
            backgroundColor: [
              'rgb(38, 158, 38)',
              'rgb(250, 166, 255)',
              'rgb(215, 38, 61)'
            ],
            hoverOffset: 4
      }]
    };
   const config = {
      type: 'pie',
      data: data,
      options: {
          responsive: true,
          maintainAspectRatio: true,
          plugins:{
            legend: {
                labels: {
                    color: "white",
                    font: {
                        size: 13
                        },
                        boxWidth: 10,
                    }
                }
            }
        }
      }
    let ChartStatsMatches = new Chart(ctx, config);
}