import { draw, PLAYER_HEIGHT_RATIO, PLAYER_WIDTH_RATIO } from "./drawPong.js";

export let canvas;
let context;
let game;
let anim;
let game_status;
let particles = [];
let yIa1;
let yIa2;
let intervalId;
const PLAYER_SPEED = 0.015;
const BALL_MAX_SPEED = 0.015;
const BALL_RADIUS_RATIO = 0.01;

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
    if (game.ball.x >= 1 || game.ball.x <= 0)
        game.ball.speed.x = -game.ball.speed.x;
    game.ball.x += game.ball.speed.x;
    game.ball.y += game.ball.speed.y;
}

function iaMove(player, yIa)
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

export function play() {
    iaMove(game.player1, yIa1);
    iaMove(game.player2, yIa2);
    draw(context, canvas, game, particles, 0);
    ballMove();

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
    cancelAnimationFrame(anim);
    game.ball.x = 0.5;
    game.ball.y = 0.5;
    game.player1.y = 0.5 - PLAYER_HEIGHT_RATIO / 2;
    game.player2.y = 0.5 - PLAYER_HEIGHT_RATIO / 2;
    yIa1 = 0.5;
    yIa2 = 0.5;

    if (Math.random() >= 0.5)
        game.ball.speed.x = -0.004;
    else
        game.ball.speed.x = 0.004;    
    game.ball.speed.y = (3 - Math.random() * 6) / 1000;
    game_status = 0;
}

export function stop_demo() {
    if (game_status != 0)
    {
        clearInterval(intervalId)
        cancelAnimationFrame(anim);
        reset();
    }
}

export function initiate_pong() {
    game_status = 0;
    canvas = document.getElementById('demo__game');
    context = canvas.getContext('2d');
    game = {
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
    launch_game();
}

export function launch_game()
{
    stop_demo();
    game_status = 1;
    clearInterval(intervalId);
    intervalId = window.setInterval(function(){
        IAPlayer();
    }, 500);
    play();
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
    {
        while (ballX > 0.025)
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
    if (speedX > 0)
    {
        yIa2 = ballY;
        yIa1 = 0.5;
    }
    else
    {
        yIa1 = ballY;
        yIa2 = 0.5;
    }
}