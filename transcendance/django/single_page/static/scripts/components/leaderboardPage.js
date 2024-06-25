import { fetchLeaderboard } from "../services/leaderboardService.js";
import { attachUserLinkListeners } from "../utils/linksAttach.js";

export async function renderLeaderboardPage() {
    const leaderboardData = await fetchLeaderboard();

    const leaderboardHtml = `
        <main class="leaderboard-layout">
            ${getLeaderboardSection(leaderboardData)}
        </main>
    `;
    document.body.insertAdjacentHTML('beforeend', leaderboardHtml);

    attachUserLinkListeners();
}

/*
---------------------------- HTML CONTENT ----------------------------
*/
function getLeaderboardSection(data) {
    return `
        <section class="leaderboard leaderboard--full">
            <div class="leaderboard__container leaderboard__container--full">
                ${getLeaderboardHeadings()}
                ${data.map(player => getLeaderboardElement(player)).join('')}
            </div>
        </section>
    `;
}

function getLeaderboardHeadings() {
    return `
        <p class="leaderboard__headings">
            <span class="leaderboard__title">Leaderboard</span>
            ${leaderboardIconSvg()}
            <span class="leaderboard__win">Win</span>
        </p>
    `;
}

export function getLeaderboardElement(player) {
    let rank = 1;

    return `
        <div class="leaderboard__element">
            <span class="leaderboard__rank">${player.rank}</span>
            <span class="leaderboard__username user-link">${player.username}</span>
            <span class="leaderboard__total-win">${player.num_wins}</span>
        </div>
    `;
}

function leaderboardIconSvg() {
    return `
        <svg class="leaderboard__icon" width="22" height="20" viewBox="0 0 22 20">
            <path d="M0 20V6.66667H6.05V20H0ZM7.975 20V0H14.025V20H7.975ZM15.95 20V8.88889H22V20H15.95Z"/>
        </svg>
    `;
}