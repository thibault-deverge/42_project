import { getGameStatus, launch_game } from "./localPong.js";

function isInside(x, y, rect) {
    return (x >= rect.x) && (x <= (rect.width + rect.x)) &&
            (y >= rect.y) && (y <= (rect.height + rect.y));
}

export function ftMouseMove(evt, canvas, btn) {
    let x = evt.offsetX * canvas.width / canvas.clientWidth | 0;
    let y = evt.offsetY * canvas.height / canvas.clientHeight | 0;
    if (isInside(x, y, btn[0]))
        btn[0].selected = 1;
    else
        btn[0].selected = 0;
}

export function ftmouseUp(evt, canvas, btn) {
    let x = evt.offsetX * canvas.width / canvas.clientWidth | 0;
    let y = evt.offsetY * canvas.height / canvas.clientHeight | 0;
    if (isInside(x, y, btn[0]) && getGameStatus() == 0)
        launch_game();
}