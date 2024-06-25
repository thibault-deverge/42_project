import { fetchFriendList } from "../services/friendService.js";
import { setupImagesListeners } from "../services/imageService.js";
import { fetchSurroundingPlayers } from "../services/leaderboardService.js";
import { setuptEditListener } from "../services/profilService.js";
import { fetchRecentGames } from "../services/recentMatchService.js";
import { fetchUserProfile } from "../services/userService.js";
import { attachLeaderboardLinkListeners, attachUserLinkListeners } from "../utils/linksAttach.js";
import { setupRGPDListener } from "../utils/rgpd.js";
import { getLeaderboardElement } from "./leaderboardPage.js";

const IMAGES = {
    DEFAULT_COVERTURE: "/media/cover_photo/default_couverture.jpg",
    DEFAULT_PROFILE: "/media/avatars/default_profil.jpg",
    UPLOAD_ICON: "/static/images/upload_icon.png",
    UPLOAD_ICON_WHITE: "/static/images/upload_icon_white.png",
    EDIT_ICON: "/static/images/edit_icon.png",
    SAVE_ICON: "/static/images/save_icon.png",
    CANCEL_ICON: "/static/images/cancel_icon.png"
}

export async function renderProfilePage() {
    const userData = await fetchUserProfile();
    if (!userData) {
        return;
    }

    const friendList = await fetchFriendList(userData.username);

    const id = userData.id;
    const username = userData.username;
    const quote = userData.quote || "Insert a quote here";
    const avatarUrl = userData.avatar || IMAGES.DEFAULT_PROFILE;
    const coverUrl = userData.cover_photo || IMAGES.DEFAULT_COVERTURE;
    const surroundingPlayers = await fetchSurroundingPlayers(username);

    const recentGames = await fetchRecentGames();
    const userRecentGames = recentGames
                                .filter(game => game.winner.username === username || game.loser.username === username)
                                .slice(0, 4);

    const profileHtml = /*html*/`
    <main class="profile-grid">
        ${getCouvertureSection(coverUrl)}
        ${getUserSection(avatarUrl, username, quote)}
        ${getStatResumeSection(friendList, surroundingPlayers, userRecentGames, username, id)}
        ${getFooter()}
    </main>
    `;
    document.body.insertAdjacentHTML('beforeend', profileHtml);
    setupImagesListeners();
    setuptEditListener();
    setupRGPDListener();
    attachUserLinkListeners();
    attachLeaderboardLinkListeners();
    attachRecentMatchListeners()
}

export function attachRecentMatchListeners() {
    document.querySelectorAll('.recent-match__summary').forEach(element => {
        element.addEventListener('click', function(event) {
            event.stopPropagation();
            const parent = this.closest('.recent-match');
            parent.classList.toggle('recent-match__active');
        });
    });
    document.addEventListener('click', function(event) {
        document.querySelectorAll('.recent-match__active').forEach(element => {
            if (!element.contains(event.target)) {
                element.classList.remove('recent-match__active');
            }
        });
    });
}

/*
---------------------------- HTML CONTENT ----------------------------
*/
function getCouvertureSection(url) {
    return /*html*/`
        <section class="couverture">
            <img class="couverture__picture" src="${url}" alt="couverture picture" />
            <input type="file" id="coverPhotoInput" accept="image/png, image/jpeg" style="display: none;">
            <button class="couverture__button">
                Upload couverture picture
                <img class="couverture__icon" src="${IMAGES.UPLOAD_ICON}" alt="upload icon"/>
            </button>
        </section>
    `;
}

function getUserSection(url, username, quote) {
    return /*html*/`
        <section class="user">
            <div class="user__photo">
                <img src="${url}" alt="profile picture" />
                <input type="file" id="avatarInput" accept="image/png, image/jpeg" style="display: none;">
                <button class="user__button">
                    <img class="couverture__icon" src="${IMAGES.UPLOAD_ICON_WHITE}" alt="upload icon"/>
                </button>
            </div>
            <div class="user__username">
                <p class="user__username-display">${username}</p>
                <div class="user__input-container">
                    <input placeholder="New Username" required type="text" class="user__username-input" id="usernameInput" maxlength='20'>
                    <p class="user__input-error"></p>
                </div>
                <button><img id="editUserBtn" src="${IMAGES.EDIT_ICON}" alt="edit icon"/></button>
                <button><img id="saveUserBtn" src="${IMAGES.SAVE_ICON}" alt="save icon"/></button>
                <button><img id="cancelUserBtn" src="${IMAGES.CANCEL_ICON}" alt="cancel icon"/></button>
            </div>
            <div class="user__quote">
                <p class="user__quote-display">${quote}</p>
                <input placeholder="Small quote" required type="text" class="user__quote-input" id="quoteInput" maxlength='42' size='35'>
                <button><img id="editQuoteBtn" src="${IMAGES.EDIT_ICON}" alt="edic icon"/></button>
                <button><img id="saveQuoteBtn" src="${IMAGES.SAVE_ICON}" alt="save icon"/></button>
                <button><img id="cancelQuoteBtn" src="${IMAGES.CANCEL_ICON}" alt="cancel icon"/></button>
            </div>
        </section>
    `;
}

function getStatResumeSection(friendList, surroundingPlayers, userRecentGames, username, id) {
    return /*html*/`
        <section class="stat-resume">
            ${getFriendsLeaderboard(friendList)}
            ${getRankingLeaderboard(surroundingPlayers)}
            ${getMatchesLeaderboard(userRecentGames, username, id)}
        </section>
    `;
}

function getFriendsLeaderboard(friendList) {
    const friendsHtml = friendList.map(friend => {
        return /*html*/`
            <div class="leaderboard__element">
                <img class="leaderboard__photo" src="${friend.avatar || IMAGES.DEFAULT_PROFILE}" alt="username photo" />
                <span class="leaderboard__username user-link">${friend.username}</span>
                ${getIsConnectedHtml(friend.isConnected)}
            </div>
        `}).join('');

    return /*html*/`
        <section class="leaderboard leaderboard--profile">
            <div class="leaderboard__container">
                <p class="leaderboard__headings">
                    <span class="leaderboard__title">Friend's List</span>
                </p>
                ${friendsHtml}
            </div>
        </section>
    `;
}

function getIsConnectedHtml(isConnected) {    
    if (isConnected)
        return /*html*/`<div class="leaderboard__connect-status"></div>`
    else
        return "";
}

export function getRankingLeaderboard(surroundingPlayers) {
    return /*html*/`
        <section class="leaderboard leaderboard--profile">
            <div class="leaderboard__container">
                <p class="leaderboard__headings leaderboard-link">
                    <span class="leaderboard__title">Leaderboard</span>
                    ${leaderboardIconSvg()}
                    <span class="leaderboard__win">Win</span>
                </p>
                ${surroundingPlayers.map(player => getLeaderboardElement(player)).join('')}
            </div>
        </section>
    `;
}

export function getMatchesLeaderboard(userRecentGames, username, id) {
    return /*html*/`
        <section class="leaderboard leaderboard--profile">
            <div class="leaderboard__container">
                <p class="leaderboard__headings">
                    <span class="leaderboard__title">Recent's Matches</span>
                </p>
                ${userRecentGames.map(game => getRecentMatchElement(game, username, id)).join('')}
            </div>
        </section>
    `;
}

function getRecentMatchElement(game, username, id) {
    const isWin = game.winner.username === username ? true : false;
    const userScore = isWin ? game.score_winner : game.score_loser;
    const otherScore = isWin ? game.score_loser : game.score_winner;

    return /*html*/`
        <div class="leaderboard__element recent-match">
            <div class="recent-match__summary">
                <div class="leaderboard__color ${isWin ? "leaderboard__color--win" : "leaderboard__color--lose"}"></div>
                <span class="leaderboard__username user-link">${isWin ? game.loser.username : game.winner.username}</span>
                <span class="leaderboard__result">${userScore} : ${otherScore}</span>
            </div>
            <div class="recent-match__expand">
                <p><span>Date:</span> ${new Date(game.date).toLocaleDateString()}</p>
                <p><span>Number of ball hits:</span> ${game.ball_hit}</p>
                <div class="recent-match-chart">
                    ${getRecentScoreChart(game.score_order, id)}
                </div>
            </div>
        </div>
    `;
}

function getRecentScoreChart(score_order, id) {
    let counter = 0;

    let scoreHtml = score_order.map(point => {
        const isWin = point == id ? 'win' : 'lose';
        counter++;

        return /*html*/`
            <div class="recent-match-chart__element">
                <p>${counter}</p>
                <div class="recent-match-chart__${isWin}"></div> 
            </div>
        `
    }).join("");
    return scoreHtml;
}

function leaderboardIconSvg() {
    return /*html*/`
        <svg class="leaderboard__icon" width="22" height="20" viewBox="0 0 22 20">
            <path d="M0 20V6.66667H6.05V20H0ZM7.975 20V0H14.025V20H7.975ZM15.95 20V8.88889H22V20H15.95Z"/>
        </svg>
    `;
}

function getFooter() {
    return /*html*/`
        <footer class="footer">
            <button class="footer__button">
                <svg viewBox="0 0 448 512" class="svgIcon"><path d="M135.2 17.7L128 32H32C14.3 32 0 46.3 0 64S14.3 96 32 96H416c17.7 0 32-14.3 32-32s-14.3-32-32-32H320l-7.2-14.3C307.4 6.8 296.3 0 284.2 0H163.8c-12.1 0-23.2 6.8-28.6 17.7zM416 128H32L53.2 467c1.6 25.3 22.6 45 47.9 45H346.9c25.3 0 46.3-19.7 47.9-45L416 128z"></path></svg>
            </button>
            <button class="button button-download-data">Download My Data</button>
        </footer>
    `;
}