import {navigate, startGlobalSocket} from './router.js';
import {checkAuthentication} from "./services/authService.js";

document.addEventListener("DOMContentLoaded", () => {

    const isLoggedIn = checkAuthentication();
    isLoggedIn.then(status => {
        if (status) {
            startGlobalSocket()
        }
        navigate(window.location.pathname);
    })
});

