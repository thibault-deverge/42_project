import { createExplosion, update_particles, draw, scoreAnimation, resetAnimation, finalAnimation, drawBtn, PLAYER_HEIGHT_RATIO, PLAYER_WIDTH_RATIO } from "./drawPong.js";
import { ftMouseMove, ftmouseUp } from "./control.js";

export let canvas;
let context;
let game;
let anim;
let game_status; // 0 = no game, 1 = game on, 2 = game pause, 3 = final animation time
let btn;
let btnW;
let btnS;
let btnUp;
let btnDown;
let particles = [];
let yAnim;
let yIa;
let intervalId;
const PLAYER_SPEED = 0.015;
const BALL_MAX_SPEED = 0.015;
const BALL_RADIUS_RATIO = 0.01;

export function changeGameStatus(val) {
    game_status = val;
}

export function getGameStatus() {
    return game_status;
}

function scored(player) {
    clearInterval(intervalId);
    createExplosion(game.ball.x, game.ball.y, 50, 200, particles, canvas);
    reset();
    resetAnimation();
    
    if (player == game.player1) {
        game.player2.score++;
    } else {
        game.player1.score++;
    }
    yAnim = 0;
    if (game.player1.score == 3 || game.player2.score == 3)
    {
        game_status = 3;
        playFinalAnimation(context, canvas, game, particles);
    }
    else
    {
        game_status = 3;
        playScoreAnimation();
    }
}

function playFinalAnimation() {
    yAnim += 0.012;
    finalAnimation(context, canvas, game, particles, yAnim);
    if (yAnim < 1.1)
        anim = requestAnimationFrame(function() {
            playFinalAnimation(context, canvas, game, particles, yAnim);
        })
    else
    {
        cancelAnimationFrame(anim);
        stop();
    }
}

function playScoreAnimation() {
    yAnim += 0.012;
    scoreAnimation(context, canvas, game, particles, yAnim)
    if (yAnim < 1.1)
        anim = requestAnimationFrame(function() {
            playScoreAnimation(context, canvas, game, particles, anim)
        })
    else
    {
        game_status = 1;
        intervalId = window.setInterval(function(){
            IAPlayer();
        }, 1000);
        play();
    }
}

function changeDirection(playerPosition, y) {
    let impact = y - playerPosition - (PLAYER_HEIGHT_RATIO) / 2;
    let ratio = 80 / ((PLAYER_HEIGHT_RATIO) / 2);
    game.ball.speed.y = Math.round(impact * ratio / 10) / 1000;
}

function collide(x, y) {
    if ((x - game.ball.r) <= 0.01 + PLAYER_WIDTH_RATIO  && (x - game.ball.r) >= 0.01
        && (((y + game.ball.r) <= (game.player1.y) + (PLAYER_HEIGHT_RATIO) && (y + game.ball.r) >= (game.player1.y) )
        || (y - game.ball.r) <= (game.player1.y) + (PLAYER_HEIGHT_RATIO) && (y - game.ball.r) >= (game.player1.y)))
    {
        if (game.ball.speed.x < 0)
        {
            game.ball.speed.x *= -1;
            changeDirection(game.player1.y, y);
        }
        if (Math.abs(game.ball.speed.x) * 1.1 > BALL_MAX_SPEED)
            game.ball.speed.x = BALL_MAX_SPEED;
        else
            game.ball.speed.x *= 1.1;
        return 1;
    }
    else if ((x + game.ball.r) >= 1 - (PLAYER_WIDTH_RATIO + 0.01) && (x + game.ball.r) <= 1 - 0.01
        && (((y + game.ball.r) <= (game.player2.y) + (PLAYER_HEIGHT_RATIO) && (y + game.ball.r) >= (game.player2.y) )
        || (y - game.ball.r) <= (game.player2.y) + (PLAYER_HEIGHT_RATIO) && (y - game.ball.r) >= (game.player2.y)))
    {
        if (game.ball.speed.x > 0)
        {
            game.ball.speed.x *= -1;
            changeDirection((game.player2.y), y);

        }
        if (Math.abs(game.ball.speed.x) * 1.1 > BALL_MAX_SPEED)
            game.ball.speed.x = -BALL_MAX_SPEED;
        else
            game.ball.speed.x *= 1.1;
        return 1;
    }
    return 0;
}

function check_collide(begin_x, begin_y, end_x, end_y){
    let collided = 0;
    let steps = Math.abs(end_x - begin_x);
    if (steps < Math.abs(end_y - begin_y))
        steps = Math.abs(end_y - begin_y)
    let dx = Math.abs(end_x - begin_x) / steps;
    let dy = Math.abs(end_y - begin_y) / steps;
    let i = 0;
    let x = begin_x;
    let y = begin_y;
    while (i < steps && collided == 0)
    {
        collided = collide(x, y);
        x += dx;
        y += dy;
        i++;
    }
}

function ballMove() {
    if (game.ball.y + game.ball.r >= 1 && game.ball.speed.y > 0)
        game.ball.speed.y *= -1;
    else if (game.ball.y - game.ball.r <= 0 && game.ball.speed.y < 0)
        game.ball.speed.y *= -1;
    check_collide(game.ball.x, game.ball.y, game.ball.x + game.ball.speed.x, game.ball.y + game.ball.speed.y);
    if (game.ball.x >= 1) {
        scored(game.player2);
    } else if (game.ball.x <= 0){
        scored(game.player1);
    }
    game.ball.x += game.ball.speed.x;
    game.ball.y += game.ball.speed.y;
}


function playerMove(player)
{
    if (player.up && !player.down)
    {
        player.y -= PLAYER_SPEED;
        if (player.y < 0)
            player.y = 0;
    }
    if (player.down && !player.up)
        player.y += PLAYER_SPEED;
        if (player.y > 1 - PLAYER_HEIGHT_RATIO)
            player.y = 1 - PLAYER_HEIGHT_RATIO;
}

function iaMove(player)
{
    if (player.y > yIa - (PLAYER_HEIGHT_RATIO / 2))
    {
        player.y -= PLAYER_SPEED;
        if (player.y < 0)
            player.y = 0;
    }
    if (player.y < yIa - (PLAYER_HEIGHT_RATIO / 2))
    {
        player.y += PLAYER_SPEED;
        if (player.y > 1 - PLAYER_HEIGHT_RATIO)
            player.y = 1 - PLAYER_HEIGHT_RATIO;
    }
}

function pause() {
    game_status = 2;
}

function unpause() {
    game_status = 1;
    play();
}

export function play() {
    playerMove(game.player1);
    if (game.type == 0)
        playerMove(game.player2);
    else if (game.type == 1)
        iaMove(game.player2);
    draw(context, canvas, game, particles, 1);
    ballMove();
    update_particles(particles);

    if (game_status == 1)
        anim = requestAnimationFrame(play);
    else if (game_status == 2)
    {
        context.fillStyle = 'rgba(0,0,0,0.35)';
        context.fillRect(0, 0, canvas.width, canvas.height);
        context.font = "bold 300px Orbitron";
        context.textAlign = "center";
        context.fillText("Pause", canvas.width / 2, canvas.height / 2);
    }
}

function reset() {
    game.ball.x = 0.5;
    game.ball.y = 0.5;
    game.player1.y = 0.5 - PLAYER_HEIGHT_RATIO / 2;
    game.player2.y = 0.5 - PLAYER_HEIGHT_RATIO / 2;
    game.player1.up = 0;
    game.player2.up = 0;
    game.player1.down = 0;
    game.player2.down = 0;
    yIa = 0.5;

    if (Math.random() >= 0.5)
        game.ball.speed.x = -0.004;
    else
        game.ball.speed.x = 0.004;    
    game.ball.speed.y = (3 - Math.random() * 6) / 1000;
}

export function stop() {
    if (game_status != 0)
    {
        clearInterval(intervalId)
        cancelAnimationFrame(anim);
        reset();
        game.player1.score = 0;
        game.player2.score = 0;
        draw(context, canvas, game, particles, 1);
        game_status = 0;
        canvas.addEventListener('mousemove', function(evt){
            ftMouseMove(evt, canvas, btn);
        }, false);
        canvas.addEventListener('mouseup', function(evt){
            ftmouseUp(evt, canvas, btn);
        }, false);
        loopMenu();    
    }
}

function pressKey(event) {
    const keyCode = event.keyCode;

    if (keyCode == 87)
        game.player1.up = 1
    else if (keyCode == 83)
        game.player1.down = 1
    else if (keyCode == 38)
        game.player2.up = 1
    else if (keyCode == 40)
        game.player2.down = 1
    else if (keyCode == 27)
    {
        if (game_status == 1)
            pause();
        else if (game_status == 2)
            unpause();
    }
    else if (keyCode == 69)
    {
        if (game.ball.r == BALL_RADIUS_RATIO)
        {
            game.ball.r /= 2;
            createExplosion(game.ball.x, game.ball.y, 5, 10, particles, canvas);
            setTimeout(function () {
                game.ball.r = BALL_RADIUS_RATIO;
            }, 2000);
        }
    }
    else if (keyCode == 70)
    {
        if (game.ball.r == BALL_RADIUS_RATIO)
        {
            game.ball.r *= 2;
            createExplosion(game.ball.x, game.ball.y, 5, 10, particles, canvas);
            setTimeout(function () {
                game.ball.r = BALL_RADIUS_RATIO;
            }, 2000);
        }
    }
}

function releaseKey(event) {
    const keyCode = event.keyCode;

    if (keyCode == 87)
        game.player1.up = 0
    else if (keyCode == 83)
        game.player1.down = 0
    if (keyCode == 38)
        game.player2.up = 0
    else if (keyCode == 40)
        game.player2.down = 0
}

function setEventPlayer1() {
    btnW = document.getElementById('btnW');
    btnS = document.getElementById('btnS');
    btnW.addEventListener("touchstart", function(evt) { game.player1.up = 1 }, { passive: true });
    btnW.addEventListener("mousedown", function(evt) { game.player1.up = 1 });
    btnS.addEventListener("touchstart", function(evt) { game.player1.down = 1 }, { passive: true });
    btnS.addEventListener("mousedown", function(evt) { game.player1.down = 1 });
    btnW.addEventListener("touchend", function(evt) { game.player1.up = 0 });
    btnW.addEventListener("mouseup", function(evt) { game.player1.up = 0 });
    btnS.addEventListener("touchend", function(evt) { game.player1.down = 0 });
    btnS.addEventListener("mouseup", function(evt) { game.player1.down = 0 });
    document.addEventListener( "keydown", pressKey);
    document.addEventListener( "keyup", releaseKey);
}


function setEventPlayer2() {
    btnUp = document.getElementById('btnUp');
    btnDown = document.getElementById('btnDown');
    btnUp.addEventListener("touchstart", function(evt) { game.player2.up = 1 }, { passive: true });
    btnUp.addEventListener("mousedown", function(evt) { game.player2.up = 1 });
    btnDown.addEventListener("touchstart", function(evt) { game.player2.down = 1 }, { passive: true });
    btnDown.addEventListener("mousedown", function(evt) { game.player2.down = 1 });
    btnUp.addEventListener("touchend", function(evt) { game.player2.up = 0 });
    btnUp.addEventListener("mouseup", function(evt) { game.player2.up = 0 });
    btnDown.addEventListener("touchend", function(evt) { game.player2.down = 0 });
    btnDown.addEventListener("mouseup", function(evt) { game.player2.down = 0 });          
}

export function initiate_pong(type) {
    game_status = 0;
    canvas = document.getElementById('board');
    context = canvas.getContext('2d');
    game = {
        type : type,
        player1: {
            score: 0,
            up: 0,
            down: 0,
        },
        player2: {
            score: 0,
            up: 0,
            down: 0,
        },
        ball: {
            r: BALL_RADIUS_RATIO,
            speed: {}
        }
    };
    reset();
    setEventPlayer1();
    if (type == 0)
        setEventPlayer2();
    drawMenu();
    canvas.addEventListener('mousemove', function(evt){
        ftMouseMove(evt, canvas, btn);
    }, false);
    canvas.addEventListener('mouseup', function(evt){
        ftmouseUp(evt, canvas, btn);
    }, false);
    loopMenu();
}

export function launch_game()
{
    canvas.removeEventListener('mousemove', ftMouseMove, false);
    canvas.removeEventListener('mouseup', ftmouseUp, false);
    stop();
    game_status = 1;
    intervalId = window.setInterval(function(){
        IAPlayer();
    }, 1000);
    play();
}

function drawMenu()
{
    btn = [{
            x: canvas.width / 2 - (canvas.width * 0.2 / 2),
            y: canvas.height / 2 - (canvas.height * 0.1 / 2),
            width: canvas.width * 0.2,
            height: canvas.height * 0.1,
            selected: 0,
    }];
}

function loopMenu() {
    context.clearRect(0, 0, canvas.width, canvas.height);
    drawBtn(btn, canvas, context);
    if (game_status == 0)
        anim = requestAnimationFrame(loopMenu);
}

async function IAPlayer()
{
    let ballX = game.ball.x;
    let ballY = game.ball.y;
    let speedY = game.ball.speed.y;
    let speedX = game.ball.speed.x;

    if (speedX > 0)
    {
        while (ballX < 0.975)
        {
            ballX += speedX;
            if (ballY + 0.01 >= 1 && speedY > 0)
                speedY = -speedY;
            else if (ballY - 0.01 <= 0 && speedY < 0)
                speedY = -speedY;
            ballY += speedY;
        }
        ballY -= 0.06;
        ballY += Math.random() * 0.1;
    }
    else
        ballY = 0.5;
    yIa = ballY;
}