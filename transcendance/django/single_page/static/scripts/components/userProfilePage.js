import { navigate } from "../router.js";
import { attachFriendListener, fetchFriendList } from "../services/friendService.js";
import { fetchSurroundingPlayers } from "../services/leaderboardService.js";
import { fetchRecentGames } from "../services/recentMatchService.js";
import { fetchUserProfile, fetchUserProfileByUsername } from "../services/userService.js";
import { attachLeaderboardLinkListeners, attachUserLinkListeners } from "../utils/linksAttach.js";
import { render404Page } from "./404Page.js";
import { getMatchesLeaderboard, getRankingLeaderboard } from "./profilePage.js";

const IMAGES = {
    DEFAULT_COVERTURE: "/media/cover_photo/default_couverture.jpg",
    DEFAULT_PROFILE: "/media/avatars/default_profil.jpg",
    ADD_FRIEND: "/static/images/add_friend_icon.png",
    REMOVE_FRIEND: "/static/images/remove_friend_icon.png"
}

export async function renderUserProfilePage() {
    const ownData = await fetchUserProfile();
    const usernamePath = window.location.pathname.split('/')[2];
    const userData = await fetchUserProfileByUsername(usernamePath);
    if (!userData) {
        render404Page();
        return;
    }
    if (ownData.username === userData.username) {
        navigate("/profile");
        return;
    }
    const id = userData.id;
    const name = userData.username;
    const quote = userData.quote || "This user does not have a quote";
    const avatarUrl = userData.avatar || IMAGES.DEFAULT_PROFILE;
    const coverUrl = userData.cover_photo || IMAGES.DEFAULT_COVERTURE;
    const ownFriendList = await fetchFriendList(ownData.username);
    const userFriendList = await fetchFriendList(name);
    const isFriend = ownFriendList.some(friend => friend.username === name);
    const surroundingPlayers = await fetchSurroundingPlayers(name);
    const recentGames = await fetchRecentGames();
    const userRecentGames = recentGames
                                .filter(game => game.winner.username === name || game.loser.username === name)
                                .slice(0, 4);
    const userProfileHtml = /*html*/`
        <main class="profile-grid">
            ${getCouvertureSection(coverUrl)}
            ${getUserSection(avatarUrl, name, quote, isFriend)}
            ${getStatResumeSection(userFriendList, surroundingPlayers, userRecentGames, name, id)}
        </main>
    `
    document.body.insertAdjacentHTML('beforeend', userProfileHtml);
    attachUserLinkListeners();
    attachLeaderboardLinkListeners();
    attachFriendListener(name, isFriend, IMAGES);
}

/*
---------------------------- HTML CONTENT ----------------------------
*/
function getCouvertureSection(url) {
    return /*html*/`
        <section class="couverture">
            <img class="couverture__picture" src="${url}" alt="couverture picture" />
        </section>
    `;
}

function getUserSection(url, username, quote, isFriend) {
    return /*html*/`
        <section class="user">
            <div class="user__photo">
                <img src="${url}" alt="profile picture" />
            </div>
            <div class="user__username">
                <p class="user__username-display">${username}</p>
            </div>
            <div class="user__quote">
                <p class="user__quote-display">${quote}</p>
            </div>
            <button class="user__friend-btn" id="add_friend">
                <img src="${isFriend ? IMAGES.REMOVE_FRIEND : IMAGES.ADD_FRIEND}" 
                alt="${isFriend ? "Add Friend button" : "Remove Friend button"}" />
            </button>
        </section>
    `;
}

function getStatResumeSection(friendList, surroundingPlayers, recentGames, username, id) {
    return /*html*/`
        <section class="stat-resume">
            ${getFriendsLeaderboard(friendList)}
            ${getRankingLeaderboard(surroundingPlayers)}
            ${getMatchesLeaderboard(recentGames, username, id)}
        </section>
    `;
}

function getFriendsLeaderboard(friendList) {
    const friendsHtml = friendList
        .map(friend => {
            return /*html*/`
                <div class="leaderboard__element">
                    <img class="leaderboard__photo" src="${friend.avatar || IMAGES.DEFAULT_PROFILE}" alt="username photo" />
                    <span class="leaderboard__username user-link">${friend.username}</span>
                </div>
            `})
        .join('');

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