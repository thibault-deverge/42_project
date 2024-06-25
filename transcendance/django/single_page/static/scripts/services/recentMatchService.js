import { PATH } from "../utils/constants.js";
import { getCookie } from "../utils/cookie.js";

const RECENT_GAMES_ENDPOINT = `${PATH}game/recent-games/`;

export async function fetchRecentGames() {
    try {
        const response = await fetch(RECENT_GAMES_ENDPOINT, {
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
