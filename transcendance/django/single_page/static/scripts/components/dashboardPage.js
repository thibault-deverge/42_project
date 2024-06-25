import { initiate_pong } from "../pong/demoGame.js"
import { fetchTopPlayers } from "../services/leaderboardService.js";
import { attachLeaderboardLinkListeners, attachUserLinkListeners } from "../utils/linksAttach.js";

let game_launch = 0;

export async function renderDashboardPage() {
    if (window.location.pathname !== '/dashboard') {
        history.pushState({ page: 'dashboard' }, 'dashboard', '/dashboard');
    }

    const dashboardHtml = getDashboardPageHtml();
    document.body.insertAdjacentHTML('beforeend', dashboardHtml);

    initiate_pong();

    const topPlayers = await fetchTopPlayers();
    updateLeaderboardHtml(topPlayers);
}

function updateLeaderboardHtml(players) {
    const leaderboardContainer = document.querySelector('.leaderboard__container');
    const playersHtml = players.map(player => getLeaderboardElement(player)).join('');
    leaderboardContainer.insertAdjacentHTML('beforeend', playersHtml);
    attachLeaderboardLinkListeners();
    attachUserLinkListeners();
}

function getLeaderboardElement(player) {
    return /*html*/`
        <div class="leaderboard__element">
            <span class="leaderboard__rank">${player.rank}</span>
            <span class="leaderboard__username user-link">${player.username}</span>
            <span class="leaderboard__total-win">${player.num_wins}</span>
        </div>
    `;
}

/*
---------------------------- HTML CONTENT ----------------------------
*/
function getDashboardPageHtml() {
    return /*html*/`
        <main class="dashboard-grid">
            <section class="dashboard-grid__left">
                <h1 class="dashboard__title">Welcome to Pong-Duck</h1>
                <div class="demo__container">
                    <canvas id="demo__game" width="1920px" height="1280px"></canvas>
                </div>
            </section>
            <section class="dashboard-grid__right">
                ${getLeaderboardHtml()}
                ${getRulesHtml()}
            </section>
        </main>
    `;
}

function getLeaderboardHtml() {
    return /*html*/`
        <section class="leaderboard">
            <div class="leaderboard__container leaderboard__container--dashboard">
                <p class="leaderboard__headings leaderboard-link">
                    <span class="leaderboard__title">Leaderboard</span>
                    <svg class="leaderboard__icon" width="22" height="20" viewBox="0 0 22 20">
                        <path d="M0 20V6.66667H6.05V20H0ZM7.975 20V0H14.025V20H7.975ZM15.95 20V8.88889H22V20H15.95Z"/>
                    </svg>
                    <span class="leaderboard__win">Win</span>
                </p>
            </div>
        </section>
    `;
}

function getRulesHtml() {
    return /*html*/`
        <section class="rules">
            <div class="rules__bubble">
                <p class="rules__text">Press 'W' to move up.<br>Press 'S' to move down.<br>The first player to score 3 points wins.</p>
            </div>
            <img class="rules__image" src="./static/images/duck-bubble.png" alt="duck holding a baseball bat.">
        </section>
    `;
}