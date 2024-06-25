import { handleLogout } from "../services/authService.js";
import { navigate } from "../router.js";
import {getInQueue} from "../services/gameService.js";

export function renderNavbar() {
    const existingNavbar = document.querySelector(".navbar");
    const path = window.location.pathname;
    if (!existingNavbar) {
        const navbarHtml = getNavbarHtml();
        document.body.classList.add("container--with-navbar")
        document.body.insertAdjacentHTML('afterbegin', navbarHtml);
        initializeNavbarListeners();
    }
    document.querySelectorAll('.navbar__element').forEach(link => {
        link.classList.remove('active');
    });
    if (path.includes('dashboard'))
        document.querySelector('#homeBtn').classList.add("active");
    else if (path.includes('game'))
        document.querySelector('#gameBtn').classList.add("active");
    else if (path.includes('chat'))
        document.querySelector('#chatBtn').classList.add("active");
    else if (path.includes('statistics'))
        document.querySelector('#statisticsBtn').classList.add("active");
    else if (path.includes('profile'))
        document.querySelector('#profileBtn').classList.add("active");
    const isInQueue = getInQueue()
    isInQueue.then(data => {
        if (data)
            put_loader_navbar();
        else
            del_loader_navbar();
    })
}
function initializeNavbarListeners() {
    const hamburger = document.querySelector('.hamburger');
    const list = document.querySelector('.navbar__list');
    const links = document.querySelectorAll(".navbar__link");
    const btnLogout = document.querySelector(".btnLogout");
    const chatBtn = document.querySelector("#chatBtn");
    const homeBtn = document.querySelectorAll(".homeBtn");
    const gameBtn = document.querySelector("#gameBtn");
    const profileBtn = document.querySelector("#profileBtn");
    const statisticsBtn = document.querySelector("#statisticsBtn");

    function displayMobile() {
        hamburger.classList.toggle('hamburger-active');
        list.classList.toggle('hamburger-active');
    }
    function closeMenu() {
        hamburger.classList.remove('hamburger-active');
        list.classList.remove('hamburger-active');
    }
    function callNavigate(event, path) {
        event.preventDefault();
        navigate(path);
    }
    hamburger.addEventListener("click", displayMobile);
    links.forEach(link => link.addEventListener('click', closeMenu));
    chatBtn.addEventListener("click", (event) => {
        closeMenu();
        callNavigate(event, "/chat");
    })
    homeBtn.forEach(el => {
        el.addEventListener("click", (event) => {
            closeMenu();
            callNavigate(event, "/dashboard");
        })
    })
    gameBtn.addEventListener("click", (event) => {
        closeMenu();
        callNavigate(event, "/game");
    })
    profileBtn.addEventListener("click", (event) => {
        closeMenu();
        callNavigate(event, "/profile");
    })
    statisticsBtn.addEventListener("click", (event) => {
        closeMenu();
        callNavigate(event, "/statistics")
    })
    btnLogout.addEventListener('click', handleLogout);
}

/*
---------------------------- HTML CONTENT ----------------------------
*/
function getNavbarHtml() {
    return /*html*/`
        <nav class="navbar">
            <div class="branding homeBtn">
                <img class="branding__logo" src="/static/images/logo.png" alt="logo">
                <h2 class="branding__text">Ft_Pong</h2>
            </div> 
            <div class="navbar__loader" id="loader_navbar"></div>
            <ul class="navbar__list">
                <li id="homeBtn" class="navbar__element homeBtn">
                    <a href="#" class="navbar__link">Home</a>
                </li>
                <li id="gameBtn" class="navbar__element">
                    <a href="#" class="navbar__link">Play</a>
                </li>
                <li id="chatBtn" class="navbar__element">
                    <a href="#" class="navbar__link">Chat</a>
                </li>
                <li id="statisticsBtn" class="navbar__element">
                    <a href="#" class="navbar__link">Statistics</a>
                </li>
                <li id="profileBtn" class="navbar__element">
                    <a href="#" class="navbar__link">Profile</a>
                </li>
                <li class="navbar__element">
                    <button class="btnLogout">
                        <div class="btnLogout__sign">
                            <svg viewBox="0 0 512 512">
                                <path d="M377.9 105.9L500.7 228.7c7.2 7.2 11.3 17.1 11.3 27.3s-4.1 20.1-11.3 27.3L377.9 406.1c-6.4 6.4-15 9.9-24 9.9c-18.7 0-33.9-15.2-33.9-33.9l0-62.1-128 0c-17.7 0-32-14.3-32-32l0-64c0-17.7 14.3-32 32-32l128 0 0-62.1c0-18.7 15.2-33.9 33.9-33.9c9 0 17.6 3.6 24 9.9zM160 96L96 96c-17.7 0-32 14.3-32 32l0 256c0 17.7 14.3 32 32 32l64 0c17.7 0 32 14.3 32 32s-14.3 32-32 32l-64 0c-53 0-96-43-96-96L0 128C0 75 43 32 96 32l64 0c17.7 0 32 14.3 32 32s-14.3 32-32 32z"></path>
                            </svg>
                        </div>
                        <div class="btnLogout__text">Logout</div>
                    </button>
                </li>
            </ul>
            <div class="hamburger">
                <span class="hamburger__bar"></span>
                <span class="hamburger__bar"></span>
                <span class="hamburger__bar"></span>
            </div>
        </nav>
    `;
}

export function put_loader_navbar(){
    const loader_navbar = document.getElementById('loader_navbar');

    if (loader_navbar != null)
        loader_navbar.classList.add("inQueue");
}

export function del_loader_navbar(){
    const loader_navbar = document.getElementById('loader_navbar');

    if (loader_navbar != null)
        loader_navbar.classList.remove("inQueue");
}