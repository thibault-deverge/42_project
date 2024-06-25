import { initiate_pong } from "../pong/localPong.js"

export function renderVersusLocalGamePage() {
    if (window.location.pathname !== '/game/local') {
        history.pushState({ page: 'game/local' }, 'game/local', '/game/local');
    }
    const localGameHtml = getLocalGamePageHtml();
    document.body.insertAdjacentHTML('beforeend', localGameHtml);
    initiate_pong(0);
}

export function renderIAGamePage() {
    if (window.location.pathname !== '/game/ia') {
        history.pushState({ page: 'game/ia' }, 'game/ia', '/game/ia');
    }
    const localGameHtml = getIAGamePageHtml();
    document.body.insertAdjacentHTML('afterbegin', localGameHtml);
    initiate_pong(1);
}

function getLocalGamePageHtml() {
    return /*html*/`
        <main id="mainGame">
            <div id="gameContainer">
                <div id="leftCol">
                    <p class="playerName">Player 1</p>
                    <div class="btnDiv">
                        <button id="btnW" class="btnKeyboard">W</button>
                        <button id="btnS" class="btnKeyboard">S</button>
                    </div>
                </div>
                <canvas id="board" width="1920px" height="1280px"></canvas>
                <div id="rightCol">
                    <p class="playerName">Player 2</p>
                    <div class="btnDiv">
                        <button id="btnUp" class="btnKeyboard">↑</button>
                        <button id="btnDown" class="btnKeyboard">↓</button>
                    </div>
                </div>
            </div>
        </main>`;
}

function getIAGamePageHtml() {
    return /*html*/`
        <main id="mainGame">
            <div id="gameContainer">
                <div id="leftCol">
                    <p class="playerName">You</p>
                    <div class="btnDiv">
                        <button id="btnW" class="btnKeyboard">W</button>
                        <button id="btnS" class="btnKeyboard">S</button>
                    </div>
                </div>
                <canvas id="board" width="1920px" height="1280px"></canvas>
                <div id="rightCol">
                    <p class="playerName">IA</p>
                </div>
            </div>
        </main>`;
}

