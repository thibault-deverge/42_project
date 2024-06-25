export const PLAYER_HEIGHT_RATIO = 0.13;
export const PLAYER_WIDTH_RATIO = 0.015;
let xAnimation;

export function createExplosion(pos_x, pos_y, size, nb_particle, particles, canvas) {
    for (let i = 0; i < nb_particle; i++) {
        particles.push({
            x: pos_x * canvas.width,
            y: pos_y * canvas.height,
            radius: Math.random() * 3 + 1,
            color: `rgba(${151 + Math.floor(Math.random() * 100)}, ${101 + Math.floor(Math.random() * 150)}, ${34 + Math.floor(Math.random() * 150)}`,
            velocityX: Math.random() * size - size / 2,
            velocityY: Math.random() * size - size / 2,
            op: 1,
            dop: -0.02
        });
        setTimeout(function () {
            particles.pop();
        }, 1800);
    }
}

export function update_particles(particles)
{
    particles.forEach(particle => {
        particle.x += particle.velocityX;
        particle.y += particle.velocityY;
        particle.op += particle.dop
    });
}

function draw_particle(context, particles)
{
    particles.forEach(particle => {
        context.beginPath();
        context.arc(particle.x, particle.y, particle.radius, 0, Math.PI * 2);
        context.fillStyle = `${particle.color}, ${particle.op})`;
        context.fill();
        context.closePath();
    });
}

export function draw(context, canvas, game, particles, score) {
    context.clearRect(0, 0, canvas.width, canvas.height);

    // Draw middle line
    context.strokeStyle = 'rgba(225,225,225,0.5)';
    context.lineWidth = 5;
    context.setLineDash([5,5]);
    context.beginPath();
    context.moveTo(canvas.width / 2, 0);
    context.lineTo(canvas.width / 2, canvas.height);
    context.stroke();

    // Draw players
    context.fillStyle = '#FFD9AD';
    context.fillRect(canvas.width * 0.01, game.player1.y * canvas.height, PLAYER_WIDTH_RATIO * canvas.width, PLAYER_HEIGHT_RATIO * canvas.height);
    context.fillRect(canvas.width - (PLAYER_WIDTH_RATIO * canvas.width + canvas.width * 0.01), game.player2.y * canvas.height, PLAYER_WIDTH_RATIO * canvas.width, PLAYER_HEIGHT_RATIO * canvas.height);
    context.fillStyle = '#DDA15E';
    context.fillRect(canvas.width * 0.01 + 7, game.player1.y * canvas.height + 7, PLAYER_WIDTH_RATIO * canvas.width - 14, PLAYER_HEIGHT_RATIO * canvas.height - 14);
    context.fillRect(canvas.width - (PLAYER_WIDTH_RATIO * canvas.width + canvas.width * 0.01) + 7, game.player2.y * canvas.height + 7, PLAYER_WIDTH_RATIO * canvas.width - 14, PLAYER_HEIGHT_RATIO * canvas.height - 14);

    // Draw ball
    context.beginPath();
    context.fillStyle = '#DDA15E';
    context.arc(game.ball.x * canvas.width, game.ball.y * canvas.height, game.ball.r * canvas.width, 0, Math.PI * 2, false);
    context.fill();
    context.beginPath();
    context.fillStyle = '#FFD9AD';
    context.arc(game.ball.x * canvas.width, game.ball.y * canvas.height, (game.ball.r / 4 * 3) * canvas.width, 0, Math.PI * 2, false);
    context.fill();

    // Draw score
    if (score == 1)
    {
        context.font = "bold 60px Orbitron";
        context.fillStyle = '#DDA15E';
        context.strokeStyle = '#FFD9AD';
        context.textAlign = "center";
        context.setLineDash([0,0]);
        context.strokeText(`-`, canvas.width / 2, 80);
        context.strokeText(game.player1.score, canvas.width / 2 - 80, 80);
        context.strokeText(game.player2.score, canvas.width / 2 + 80, 80);
        context.fillText(`-`, canvas.width / 2, 80);
        context.fillText(game.player1.score, canvas.width / 2 - 80, 80);
        context.fillText(game.player2.score, canvas.width / 2 + 80, 80);
    }
    draw_particle(context, particles);
}

export function resetAnimation()
{
    xAnimation = 0;
}

export function scoreAnimation(context, canvas, game, particles, yAnim) {
    draw(context, canvas, game, particles, 1);
    update_particles(particles);
    let score = game.player1.score + " - " + game.player2.score;
    context.setLineDash([0,0]);
    context.font = "bold 180px Orbitron";
    context.fillStyle = '#DDA15E';
    context.textAlign = "left";
    if (game.player1.score == 1)
    {
        context.fillText(score, canvas.width / 2 - 175, yAnim * canvas.height);
        context.strokeText(score, canvas.width / 2 - 175, yAnim * canvas.height);
    }
    else
    {
        context.fillText(score, canvas.width / 2 - 250, yAnim * canvas.height);
        context.strokeText(score, canvas.width / 2 - 250, yAnim * canvas.height);
    }
    if (yAnim <= 0.51 && yAnim >= 0.49)
        createExplosion(0.5, 0.5, 50, 200, particles, canvas);
}

export function finalAnimation(context, canvas, game, particles, yAnim) {
    let x = canvas.width / 2 - 175;
    let y = canvas.height / 2 + 60;
    draw(context, canvas, game, particles, 1);
    update_particles(particles);
    let score = game.player1.score + " - " + game.player2.score;
    context.font = "bold 180px Orbitron";
    context.fillStyle = '#DDA15E';
    context.textAlign = "left";
    if (game.player1.score != 1)
        x = canvas.width / 2 - 250;
    if (yAnim <= 0.51)
        y = yAnim * canvas.height;
    context.fillText(score, x, y);
    context.strokeText(score, x, y);
    if (yAnim >= 0.49 && yAnim <= 0.51)
        createExplosion(0.5, 0.5, 50, 200, particles, canvas);
    if (yAnim > 0.51)
    {
        xAnimation += 0.015;
        if (xAnimation < canvas.width / 2)
        {
            createExplosion(0.5 + xAnimation, 0.5, 50, 100, particles, canvas);
            createExplosion(0.5 - xAnimation, 0.5, 50, 100, particles, canvas);
        }
    }

}

export function drawBtn(btn, canvas, context) {
    btn.forEach((element) => {
        context.beginPath();
        context.rect(element.x, element.y, element.width, element.height);
        context.fillStyle = 'rgba(44,83,100,0.8)';
        context.fill();
        context.lineWidth = 2;
        context.strokeStyle = '#FFD9AD';
        context.stroke();
        context.closePath();
        context.font = "bold 80px Orbitron";
        context.fillStyle = '#DDA15E';
        context.textAlign = "center";
        context.fillText('START', element.x + element.width / 2, element.y + element.height / 1.35);
        context.setLineDash([0,0]);
        context.strokeText('START', element.x + element.width / 2, element.y + element.height / 1.35);
        context.closePath();
        if (element.selected)
        {
            context.strokeStyle='#DDA15E';
            context.lineWidth = 8;
            context.strokeRect(element.x,element.y,element.width,element.height);
            context.strokeStyle = '#FFD9AD';
            context.lineWidth = 4;
            context.strokeText('START', element.x + element.width / 2, element.y + element.height / 1.35);
        }
    });
}
