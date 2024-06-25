import { PATH } from "../utils/constants.js";
import { getCookie } from "../utils/cookie.js";

const LEADERBOARD_ENDPOINT = `${PATH}/game/leaderboard/`;

export async function fetchLeaderboard() {
    try {
        const response = await fetch(LEADERBOARD_ENDPOINT, {
            method: 'GET',
            headers: {
                'Content-Type': 'application/json',
                'X-CSRFToken': getCookie('csrftoken'),
            },
            credentials: 'include',
        })
        return await response.json();
    } catch (error) {
        return [];
    }
}

export async function fetchTopPlayers(limit = 4) {
    try {
        const response = await fetch(`${LEADERBOARD_ENDPOINT}?limit=${limit}`, {
            method: 'GET',
            headers: {
                'Content-Type': 'application/json',
                'X-CSRFToken': getCookie('csrftoken'),
            },
            credentials: 'include',
        });
        return await response.json();
    } catch (error) {
        return [];
    }
}

export async function fetchSurroundingPlayers(username) {
    const leaderboardData = await fetchLeaderboard();
    const userIndex = leaderboardData.findIndex(user => user.username === username);

    if (userIndex === -1)
        return [];
    const start = Math.max(0, userIndex - 2);
    const end = Math.min(leaderboardData.length, userIndex + 2);
    return leaderboardData.slice(start, end);
}