import { renderLoginPage } from "./components/loginPage.js";
import { renderDashboardPage } from "./components/dashboardPage.js";
import { renderNavbar } from "./components/NavBar.js";
import { renderChatPage } from "./components/chatPage.js";
import { renderGamePage, WaitingMatch, WaitingTournament, LeaveQueueMatch, LeaveQueueTournament} from "./components/gamePage.js";
import { renderVersusLocalGamePage, renderIAGamePage } from "./components/localGamePage.js";
import { renderProfilePage } from "./components/profilePage.js";
import { renderUserProfilePage } from "./components/userProfilePage.js";
import { renderOnlineGameMatchPage } from "./components/OnlineGameMatchPage.js";
import { renderStatisticsPage } from "./components/statisticsPage.js";
import { render404Page } from "./components/404Page.js";
import { renderLeaderboardPage } from "./components/leaderboardPage.js";
import { checkAuthentication } from "./services/authService.js";
import { removeAllHtml, removeMainHtml } from "./utils/empty_html.js";
import { leaveChat } from "./services/chatService.js";
import { gameSocket, GameSocketToNull, pressKeyOnline, releaseKeyOnline } from "./pong/onlinePong.js";
import { PATH, WSS_PATH } from "./utils/constants.js";

const routes = {
    '/login': renderLoginPage,
    '/': renderDashboardPage,
    '/dashboard': renderDashboardPage,
    '/404notfound': render404Page,
    '/chat': renderChatPage,
    '/game': renderGamePage,
    '/game/local': renderVersusLocalGamePage,
    '/game/ia': renderIAGamePage,
    '/profile': renderProfilePage,
    '/leaderboard': renderLeaderboardPage,
    '/statistics': renderStatisticsPage,
}

const dynamicRoutes = {
    match: {
        regex: /^\/match\/online\/[\dA-Za-z]{5}\/?$/, // Accepte /game/<gameId>
    },
    tournament: {
        regex: /^\/tournament\/online\/[\dA-Za-z]{5}\/?$/, // Accepte /game/<gameId>
    },
    profile: {
        regex: /^\/profile\/([^\/]+)\/?$/,
    },
    private_match: {
        regex: /^\/private_match\/online\/[\dA-Za-z]{5}\/?$/, // Accepte /game/<gameId>
    },
};

const findDynamicRoute = (path) => {
        const match = path.match(dynamicRoutes.match.regex);
        if (match) {
            return renderOnlineGameMatchPage
        }
        const tournament = path.match(dynamicRoutes.tournament.regex)
        if (tournament){
            return renderOnlineGameMatchPage
        }
        const profile = path.match((dynamicRoutes.profile.regex))
        if (profile) {
            return renderUserProfilePage;
        }
        const private_match = path.match((dynamicRoutes.private_match.regex))
        if (private_match) {
            return renderOnlineGameMatchPage;
        }
    return null;
};

export function navigate(path) {
    if (window.location.pathname !== path) {
        if (window.location.pathname === '/chat')
			leaveChat();
		history.pushState({ page: `${path}`}, '', path);
    }
    routeChange();
}

async function routeChange() {
    let path = window.location.pathname;
    const isLoggedIn = await checkAuthentication();
    if (!isLoggedIn) {
        history.replaceState({ page: '/login' }, 'Login', '/login');
        removeAllHtml();
        renderLoginPage();
    }
    else if (isLoggedIn && path === '/login') {
        history.replaceState({ page: '/dashboard' }, 'Dashboard', '/dashboard');
        removeMainHtml();
        renderNavbar();
        renderDashboardPage();
    }
    else {
        const routeHandler = routes[path] || findDynamicRoute(path);
        removeMainHtml();
        renderNavbar();
        if (!findDynamicRoute(path) && gameSocket)
            gameSocket.close();
            GameSocketToNull();
            document.removeEventListener("keydown", pressKeyOnline);
            document.removeEventListener("keyup", releaseKeyOnline);
        if (routeHandler)
            routeHandler();
        else {
            removeAllHtml();
            render404Page();
        }
    }
}

window.addEventListener('popstate', routeChange);

export let globalSocket = null;

export function GlobalSocketToNull()
{
    globalSocket = null;
}

export function startGlobalSocket()
{
    globalSocket = new WebSocket(WSS_PATH +"/global")
        globalSocket.onmessage = function (e) {
            let data = JSON.parse(e.data);
            let event = data.event;
            const EventHandler = events[event];
            if (EventHandler)
                EventHandler(data)
        }
}

const events = {
    'WAITING MATCH': WaitingMatch,
    'WAITING TOURNAMENT': WaitingTournament,
    'LEAVE QUEUE MATCH': LeaveQueueMatch,
    'LEAVE QUEUE TOURNAMENT': LeaveQueueTournament,
    'CONNECT MATCH': ConnectMatch,
    'CONNECT TOURNAMENT': ConnectTournament,
    'NEXT MATCH': NextMatch,
    'FINISHED': Finished,
}

function ConnectMatch(data)
{
    LeaveQueueMatch();
    navigate(PATH + "match/online/" + data.id_game)
}

function ConnectTournament(data)
{
    LeaveQueueTournament();
    navigate(PATH + "tournament/online/" + data.id_game)
}

function popupNextMatch(match_status, name1, name2)
{
    let popup = `
    <div class="popup" id="idPopup">
        <span class="titlePopup">MATCH ANNOUNCEMENT</span>
        <p class="popupDescription"><span id="name1">`+ name1 +`</span> VS <span id="name2">`+ name2 +`</span></p><p class="popupDescription">`+ match_status +`</p>
    </div>
    `
    document.body.insertAdjacentHTML('beforeend', popup);
    setTimeout(function () {
        if (document.contains(document.getElementById("idPopup"))) {
            document.getElementById("idPopup").remove();
        }
    }, 3000);

}

function NextMatch(data)
{
    popupNextMatch(data["match_status"], data["match_infos"][0], data["match_infos"][1]);
}

function Finished(data)
{
    globalSocket.send(JSON.stringify({
            'message': "LEAVE QUEUE"
    }));
}
