import { initiate_pong } from "../pong/onlinePong.js"

export function renderOnlineGameMatchPage() {
    const onlineGameMatchHtml = getOnlineGameMatchPageHtml();
    document.body.insertAdjacentHTML('afterbegin', onlineGameMatchHtml);
    initiate_pong();
}

function getOnlineGameMatchPageHtml() {
    return /*html*/`
        <main id="mainGame">
            <div id="gameContainer">
                <div id="leftCol">
                    <p class="playerName" id="player1Name">Player 1</p>
                    <div class="btnDiv" id="divBtn">
                        <button id="btnW" class="btnKeyboard">W</button>
                        <button id="btnS" class="btnKeyboard">S</button>
                    </div>
                </div>
                <canvas id="board" width="1920px" height="1280px"></canvas>
                <div id="rightCol">
                    <p class="playerName" id="player2Name">Player 2</p>
                </div>
            </div>
        </main>`;
}