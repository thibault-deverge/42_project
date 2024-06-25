import { draw, scoreAnimation, finalAnimation, createExplosion, resetAnimation, PLAYER_HEIGHT_RATIO } from "./drawPong.js";
import { WSS_PATH } from "../utils/constants.js";

export let gameSocket = null;
export function GameSocketToNull()
{
    gameSocket = null;
}

let canvas;
let context
let particles = [];
let yAnim;
let anim;
let lastPosBall;
let emptyGame = {
    "ball": {
        "x": 0.5,
        "y": 0.5,
        "r": 0.01,
        "speed": {
            "x": 0.5,
            "y": 0.5,
        }
    },
    "player1": {
        "name": "player1",
        "y": 0.5 - PLAYER_HEIGHT_RATIO / 2,
        "score": 0,
    },
    "player2": {
        "name": "player2",
        "y": 0.5 - PLAYER_HEIGHT_RATIO / 2,
        "score": 0,
    }
}

export function pressKeyOnline(event) {
    let move = {
        "type": "update",
        "message": {
            "event": "PRESS",
            "move": event.keyCode,
        }
    }
    gameSocket.send(JSON.stringify(move));
}

export function releaseKeyOnline(event) {
    let move = {
        "type": "update",
        "message": {
            "event": "RELEASE",
            "move": event.keyCode,
        }
    }
    gameSocket.send(JSON.stringify(move));
}

function pressBtn(keyCode) {
    let move = {
        "type": "update",
        "message": {
            "event": "PRESS",
            "move": keyCode,
        }
    }
    gameSocket.send(JSON.stringify(move));
}

function releaseBtn(keyCode) {
    let move = {
        "type": "update",
        "message": {
            "event": "RELEASE",
            "move": keyCode,
        }
    }
    gameSocket.send(JSON.stringify(move));
}

export function initiate_pong() {
    canvas = document.getElementById('board');
    context = canvas.getContext('2d');

    let pathname = window.location.pathname
    gameSocket = new WebSocket(WSS_PATH + pathname);
    document.addEventListener("keydown", pressKeyOnline);
    document.addEventListener("keyup", releaseKeyOnline);

    let btnW = document.getElementById('btnW');
    let btnS = document.getElementById('btnS');
    btnW.addEventListener("touchstart", function(evt) { pressBtn(87); }, { passive: true });
    btnW.addEventListener("mousedown", function(evt) { pressBtn(87); });
    btnS.addEventListener("touchstart", function(evt) { pressBtn(83); }, { passive: true });
    btnS.addEventListener("mousedown", function(evt) { pressBtn(83); });
    btnW.addEventListener("touchend", function(evt) { releaseBtn(87); });
    btnW.addEventListener("mouseup", function(evt) { releaseBtn(87); });
    btnS.addEventListener("touchend", function(evt) { releaseBtn(83); });
    btnS.addEventListener("mouseup", function(evt) { releaseBtn(83); });

    gameSocket.onmessage = function (e) {
        let data = JSON.parse(e.data);
        let event = data.event;

        if (event === "START")
        {
            document.getElementById('player1Name').textContent = data["game"].player1.name;
            document.getElementById('player2Name').textContent = data["game"].player2.name;
        }
        else if (event === "GAME")
        {
            document.getElementById('player1Name').textContent = data["game"].player1.name;
            document.getElementById('player2Name').textContent = data["game"].player2.name;
            draw(context, canvas, data["game"], particles, 1);
            lastPosBall = {x: data["game"].ball.x, y: data["game"].ball.y};
        }
        else if (event === "TIMER")
        {
            draw(context, canvas, emptyGame, particles, 1);
            Timer(data, context);
        }
        else if (event === "SCORE")
        {
            yAnim = 0;
            resetAnimation();
            createExplosion(lastPosBall.x, lastPosBall.y, 50, 200, particles, canvas);
            if (data["game"].player1.score == 3 || data["game"].player2.score == 3)
                playFinalAnimation(context, canvas, data["game"], particles);
            else
                playScoreAnimation(context, canvas, data["game"], particles);
        }
        else if (event === 'SPECTATOR')
            Spectator();
    }
}

function playScoreAnimation(context, canvas, game, particles) {
    yAnim += 0.012;
    scoreAnimation(context, canvas, game, particles, yAnim)
    if (yAnim < 1.1)
    {
        anim = requestAnimationFrame(function() {
            playScoreAnimation(context, canvas, game, particles, anim)
        })
    }
    else
        cancelAnimationFrame(anim);
}

function playFinalAnimation(context, canvas, game, particles)
{
    yAnim += 0.012;
    finalAnimation(context, canvas, game, particles, yAnim);

    if (yAnim < 1.7)
    {
        anim = requestAnimationFrame(function() {
            playFinalAnimation(context, canvas, game, particles, yAnim);
        })
    }
    else
    {
        cancelAnimationFrame(anim);
        if (game.player1.score == 3)
            endMessage(context, "You Win !");
        else
            endMessage(context, "You Loose !");
    }
}

function Timer(data, context)
{
    context.fillStyle = 'rgba(0,0,0,0.35)';
    context.fillRect(0, 0, canvas.width, canvas.height);
    context.font = "bold 300px Orbitron";
    context.textAlign = "center";
    context.fillText(data["SEC"], canvas.width / 2, canvas.height / 2);
}

function endMessage(context, msg)
{
    context.fillStyle = 'rgba(0,0,0,0.35)';
    context.fillRect(0, 0, canvas.width, canvas.height);
    context.font = "bold 280px Orbitron";
    context.textAlign = "center";
    context.fillText(msg, canvas.width / 2, canvas.height / 2);
}

function Score(data, particles)
{
    draw_particle(context, particles);
    createExplosion(game.ball.x, game.ball.y, 5, 10, particles, canvas);
    return ;
}

function Spectator()
{
    alert("You are in spectator mode");
    document.getElementById('divBtn').classList.add("invisible");
}