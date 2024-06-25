import { navigate, globalSocket } from "../router.js";
import {getInQueue} from "../services/gameService.js";
import { put_loader_navbar, del_loader_navbar } from "./NavBar.js";

export function renderGamePage() {
    if (window.location.pathname !== '/game') {
        history.pushState({ page: 'game' }, 'game', '/game');
    }
    const gameHtml = getGamePageHtml();
    document.body.insertAdjacentHTML('beforeend', gameHtml);
    addEventBtn();
    const isInQueue = getInQueue()
    isInQueue.then(data => {
        if (data)
        {
            if (data.queue === "MATCH")
                WaitingMatch();
            else
                WaitingTournament();
        }
    })
}

function getGamePageHtml() {
    return /*html*/`
        <main>
            <div class="GameModeSelection">
                <h1 class="GameModeSelection_text double-border">Game Mode Selection</h1>
            </div>
            <div class="gameBtnContainer">
                <button id="localBtn" class="gamebutton"><div class="btnText"><p class="btnTitle">LOCAL</p><p class="btnDescription">1 vs 1</p></div></button>
                <button id="iaBtn" class="gamebutton"><div class="btnText">VS IA<p class="btnDescription">1 vs IA</p></div></button>
                <button id="onlineBtn" class="gamebutton"><div class="loader"></div><div id="onlineBtnFilter" class="filterGray"><div class="btnText">ONLINE<p id="descOnline" class="btnDescription">Click to join queue</p></div></div></button>
                <button id="tournamentBtn" class="gamebutton"><div class="loader"></div><div id="tournamentBtnFilter" class="filterGray"><div class="btnText">TOURNAMENT<p id="descTournament" class="btnDescription">Click to join tournament queue</p></div></div></button>
            </div>
        </main>`;
}

function addEventBtn() {
    const localBtn = document.querySelector("#localBtn");
    const iaBtn = document.querySelector("#iaBtn");
    const onlineBtn = document.querySelector("#onlineBtnFilter");
    const tournamentBtn = document.querySelector("#tournamentBtnFilter");
    const descOnline = document.getElementById('descOnline');
    const descTournament = document.getElementById('descTournament');

    function callNavigate(event, path) {
        event.preventDefault();
        navigate(path);
    }
    localBtn.addEventListener("click", (event) => {
        callNavigate(event, "/game/local")
    })
    iaBtn.addEventListener("click", (event) => {
        callNavigate(event, "/game/ia")
    })
    onlineBtn.addEventListener("click", (event) => {
        if (onlineBtn.classList.contains("queue")) {
            globalSocket.send(JSON.stringify({
                'message': "LEAVE MATCH"
            }));
        }
        else {
            globalSocket.send(JSON.stringify({
                'message': "SEARCH MATCH"
            }));
        }
    })
    tournamentBtn.addEventListener("click", (event) => {
        if (tournamentBtn.classList.contains("queue")) {
            globalSocket.send(JSON.stringify({
                'message': "LEAVE QUEUE TOURNAMENT"
            }));
        }
        else {
            globalSocket.send(JSON.stringify({
                'message': "SEARCH TOURNAMENT"
            }));
        }
    })
}

export function WaitingMatch()
{
    if (window.location.pathname === "/game")
    {
        const onlineBtn = document.querySelector("#onlineBtnFilter");
        const descOnline = document.getElementById('descOnline');

        onlineBtn.classList.add("queue");
        descOnline.innerText = "Click to leave queue";
    }
    put_loader_navbar();
}

export function WaitingTournament()
{
    if (window.location.pathname === "/game")
    {
        const tournamentBtn = document.querySelector("#tournamentBtnFilter");
        const descTournament = document.getElementById('descTournament');

        tournamentBtn.classList.add("queue");
        descTournament.innerText = "Click to leave tournament queue";
    }
    put_loader_navbar();
}

export function LeaveQueueMatch()
{
    if (window.location.pathname === "/game")
    {
        const onlineBtn = document.querySelector("#onlineBtnFilter");
        const descOnline = document.getElementById('descOnline');

        onlineBtn.classList.remove("queue");
        descOnline.innerText = "Click to join queue";
    }
    del_loader_navbar();
}

export function LeaveQueueTournament()
{
    if (window.location.pathname === "/game")
    {
        const tournamentBtn = document.querySelector("#tournamentBtnFilter");
        const descTournament = document.getElementById('descTournament');

        tournamentBtn.classList.remove("queue");
        descTournament.innerText = "Click to join tournament queue";
    }
    del_loader_navbar();
}