import { navigate } from "../router.js";
import { removeAllHtml } from "../utils/empty_html.js";

const page404Variants = {
    1: get404PageHtml1,
    2: get404PageHtml2,
    3: get404PageHtml3,
    4: get404PageHtml4
};

export function render404Page() {
    removeAllHtml();
    const randomPageNumber = Math.floor(Math.random() * 4) + 1;
    if (window.location.pathname !== '/404notfound') {
        history.pushState({ page: '404notfound' }, '404notfound', '/404notfound');
    }
    document.body.classList.remove("container--with-navbar");
    const page404Html = page404Variants[randomPageNumber]();
    document.body.insertAdjacentHTML('beforeend', page404Html);
    if (document.querySelector("#rickRollAudio"))
        initializeRickRoll404Behavior();
}

function initializeRickRoll404Behavior() {
    const lyrics = [
        "Never gonna give you up",
        "Never gonna let you down",
        "Never gonna run around and desert you",
        "Never gonna make you cry",
        "Never gonna say goodbye",
        "Never gonna tell a lie and hurt you",
        "ok......😥"
    ];
    let clickCount = 0;
    const button = document.querySelector('.page404__link');
    const audioPlayer = document.getElementById('rickRollAudio');
    document.body.addEventListener('click', () => {
        audioPlayer.play();
    }, { once: true });
    button.addEventListener('click', function(event) {
        event.preventDefault();
        if (clickCount < lyrics.length) {
            button.style.position = 'absolute';
            button.style.left = `${Math.random() * (window.innerWidth - button.offsetWidth)}px`;
            button.style.top = `${Math.random() * (window.innerHeight - button.offsetHeight)}px`;

            button.textContent = lyrics[clickCount];
            clickCount++;
        } else {
            audioPlayer.pause();
            removeAllHtml();
            navigate('/')
        }
    });
}

/*
---------------------------- HTML CONTENT ----------------------------
*/
function get404PageHtml1() {
    return /*html*/`
        <div class="page404">
            <div class="page404__container-gif">
                <img class="page404__gif" src="./static/images/404_1.gif" alt="">
                <div class="page404__container-text">
                    <h1 class="page404__code">404</h1>
                    <h2 class="page404__title">Dude! Where's my page?</h2>
                    <p class="page404__paragraph">The page you are looking for might have been removed, had its name changed, or is temporarily unavailable. But seriously, we have no idea where it is!</p>
                    <a href="/" class="button page404__link">HomePage</a>
                </div>
            </div>
        </div>
    `;
}

function get404PageHtml2() {
    return /*html*/`
        <div class="page404">
            <div class="page404__container-gif">
                <iframe class="page404__gif" width="760" height="315" src="https://www.youtube.com/embed/0jm6K25L2uI?autoplay=1&mute=1" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture;" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>
                <div class="page404__container-text">
                    <h1 class="page404__code">404 error</h1>
                    <h2 class="page404__title">Oops, We're in a Bit of a Pickle!</h2>
                    <p class="page404__paragraph">We couldn't find the page you were looking for. It may have vanished into thin air or perhaps never existed! But worry not — to make it up to you, here's a captivating Konbini short about Xavier Niel. Sit back, relax, and enjoy!</p>
                    <a href="/" class="button page404__link">HomePage</a>
                </div>
            </div>
        </div>
    `;
}

function get404PageHtml3() {
    return /*html*/`
        <div class="page404">
            <div class="page404__container-gif">
                <img class="page404__gif" src="./static/images/404_2.gif" alt="confused girl">
                <div class="page404__container-text">
                    <h1 class="page404__code">404 error</h1>
                    <h2 class="page404__title">Hey, what are you trying to do here?</h2>
                    <p class="page404__paragraph">It looks like you've wandered off the map! The page you're looking for isn't here, but don't worry. We've all been a bit lost at times. Why not head back home and try a fresh start?</p>
                    <a href="/" class="button page404__link">Take me home</a>
                </div>
            </div>
        </div>
    `;
}

function get404PageHtml4() {
    return /*html*/`
        <div class="page404">
            <div class="page404__container-gif">
                <img class="page404__gif page404__gif--rickroll" src="./static/images/404_3.gif" alt="rickroll gif">
                <div class="page404__container-text">
                    <h1 class="page404__code">404 error</h1>
                    <h2 class="page404__title">Hey, You seem lost!</h2>
                    <p class="page404__paragraph">Seems like we couldn't find the page you were looking for. But wait, don't give up...</p>
                    <a href="/" class="button page404__link">Take me home</a>
                    <audio id="rickRollAudio" src="./static/media/rickroll.mp3" type="audio/mp3" autoplay loop></audio>
                </div>
            </div>
        </div>
    `;
}