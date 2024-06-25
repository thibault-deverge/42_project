import {PATH} from "../utils/constants.js";

export async function getGameID() {
    try {
        let ApiPath = PATH + `game/id/`;
        const response = await fetch(ApiPath);
        if (response.ok) {
            const data = await response.json();
            return data
        }
        else
            return false
    } catch(error) {
        return false;
    }
}

export async function getGameUser() {
    try {
        let ApiPath = PATH + `game/user/`;
        const response = await fetch(ApiPath);
        if (response.ok) {
            const data = await response.json();
            return data
        }
        else
            return false
    } catch(error) {
        return false;
    }
}

export async function getGameUserWinner() {
    try {
        let ApiPath = PATH + `game/user_winner/`;
        const response = await fetch(ApiPath);
        if (response.ok) {
            const data = await response.json();
            return data
        }
        else
            return false
    } catch(error) {
        return false;
    }
}

export async function getGameUserInQueue() {
    try {
        let ApiPath = PATH + `game/user_in_queue/`;
        const response = await fetch(ApiPath);
        if (response.ok) {
            const data = await response.json();
            return data
        }
        else
            return false
    } catch(error) {
        return false;
    }
}

export async function getLeaderboard() {
    try {
        let ApiPath = PATH + `game/leaderboard/`;
        const response = await fetch(ApiPath);
        if (response.ok) {
            const data = await response.json();
            return data
        }
        else
            return false
    } catch(error) {
        return false;
    }
}

export async function getStatsMatch() {
    try {
        let ApiPath = PATH + `game/stats/match/`;
        const response = await fetch(ApiPath);
        if (response.ok) {
            const data = await response.json();
            return data
        }
        else
            return false
    } catch(error) {
        return false;
    }
}

export async function getStatsTournament() {
    try {
        let ApiPath = PATH + `game/stats/tournament/`;
        const response = await fetch(ApiPath);
        if (response.ok) {
            const data = await response.json();
            return data
        }
        else
            return false
    } catch(error) {
        return false;
    }
}

export async function getInQueue() {
    try {
        let ApiPath = PATH + `game/in_queue/`;
        const response = await fetch(ApiPath);
        if (response.ok) {
            const data = await response.json();
            return data
        }
        else
            return false
    } catch(error) {
        return false;
    }
}
