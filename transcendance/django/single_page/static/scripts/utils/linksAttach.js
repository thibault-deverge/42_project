import { navigate } from "../router.js";

export function attachUserLinkListeners() {
    const userLinks = document.querySelectorAll('.user-link');

    userLinks.forEach(link => {
        link.addEventListener('click', function(event) {
            const username = this.textContent.trim();
            if (username) {
                event.preventDefault();
                navigate(`/profile/${username}`)
            }
        })
    })
}

export function attachLeaderboardLinkListeners() {
    const leaderboardLinks = document.querySelectorAll('.leaderboard-link');

    leaderboardLinks.forEach(link => {
        link.addEventListener('click', function(event) {
            navigate(`/leaderboard`);
        })
    })
}
