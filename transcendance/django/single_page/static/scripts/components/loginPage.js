import { initializeFormListeners } from "../services/authService.js";
import { address } from "../utils/constants.js";

export function renderLoginPage() {
    if (window.location.pathname !== '/login') {
        history.pushState({ page: 'login' }, 'Login', '/login');
    }
    document.body.innerHTML = getLoginPageHtml();
    initializeFormListeners();
    document.querySelector('.login-form__signup a').addEventListener('click', switchLoginSignupForm);
    document.querySelector('.signup-form__cancel').addEventListener('click', switchLoginSignupForm);
    document.getElementById('btn-oauth').addEventListener('click', () => {
        window.location.href = "https://api.intra.42.fr/oauth/authorize?client_id=u-s4t2ud-44e84abb8e03d12d49b46f696a8f77ac97f795feaf74f2be6f54a69b18718c29&redirect_uri=https%3A%2F%2F"+ address +"%3A8443%2Fauth%2Foauth%2Fcallback%2F&response_type=code";
    });
}

function switchLoginSignupForm(event) {
    event.preventDefault();
    const loginForm = document.querySelector('.login-form');
    const signupForm = document.querySelector('.signup-form');
    const error_message = document.querySelector('.form__error-message');

    if (error_message)
        error_message.remove();
  
    if (loginForm.classList.contains('active')) {
        loginForm.classList.remove('active');
        loginForm.style.display = 'none';
        signupForm.style.display = 'flex';
        signupForm.classList.add('active');
    } else {
        signupForm.classList.remove('active');
        signupForm.style.display = 'none';
        loginForm.style.display = 'flex';
        loginForm.classList.add('active');
    }
}

/*
---------------------------- HTML CONTENT ----------------------------
*/
function getLoginPageHtml() {
    return /*html*/`
        <main class="welcome-grid">
            ${getBrandingHtml()}
            <section class="welcome">
                <div class="welcome__text">
                    <h1 class="welcome__heading">Welcome to Pong-Duck</h1>
                    <p class="welcome__storytelling">Quack into action with 'Pong-Duck'! This isn't your usual Pong game - it's Pong with a twist, where ducks paddle in a splash of fun. Dive into a pond of excitement, where every hit is a quack-up! Ready for some fowl play? Wing it to victory in 'Pong-Duck', where the fun never ducks out. Let the games begin!!</p>
                </div>
                <img class="welcome__image" src="./static/images/duck_bat.png" alt="duck holding a baseball bat">
            </section>
            ${getFormContainerHtml()}
        </main>
        `;
}

export function getBrandingHtml() {
    return /*html*/`
        <div class="branding">
            <img class="branding__logo" src="./static/images/logo.png" alt="logo">
            <h2 class="branding__text">Ft_Pong</h2>
        </div> 
    `
}

function getFormContainerHtml() {
    return /*html*/`
        <section class="form-container">
            ${getLoginFormHtml()}
            ${getSignupFormHtml()}
        </section>
    `;
}

function getLoginFormHtml() {
    return /*html*/`
        <form action="#" class="login-form active">
            <button type="button" id="btn-oauth" class="button button--login" aria-label="Authenticate using 42 OAuth">42Authentication</button>
            <p class="login-form__delimitation">or</p>
            <div class="login-form__input-container">
                <div class="form-field">
                    <label for="log_username" class="form-field__label">Username</label>
                    <input type="text" required name="username" id="log_username" class="form-field__input" autocomplete="off" placeholder="AmandineDu38">
                </div>
                <div class="form-field">
                    <label for="log_password" class="form-field__label">Password</label>
                    <input type="password" required name="password" id="log_password" autocomplete="off" class="form-field__input" placeholder="********" minlength="8">
                </div>
            </div>
            <button class="button button--login" aria-label="Log in to your account">Login</button>
            <p class="login-form__signup">
                No account? Signup <a class="login-form__cta" href="#" aria-label="Sign up for a new account">here</a>
            </p>
        </form>
    `;
}

function getSignupFormHtml() {
    return /*html*/`
        <form action="#" class="signup-form">
            <div class="form-field2">
                <input required type="text" id="username" name="username" autocomplete="off" class="form-field2__input" placeholder="&#8203;">
                <label for="username" class="form-field2__label">Username</label>
            </div> 
            <div class="form-field2">
                <input required type="email" id="email" name="mail" autocomplete="off" class="form-field2__input" placeholder="&#8203;">
                <label class="form-field2__label" for="email">Email</label>
            </div> 
            <div class="form-field2">
                <input required type="password" id="password" name="password" autocomplete="off" class="form-field2__input" minlength="8" placeholder="&#8203;">
                <label class="form-field2__label" for="password">Password</label>
            </div> 
            <div class="form-field2">
                <input required type="password" id="confirm_password" name="confirm_password" autocomplete="off" class="form-field2__input" minlength="8" placeholder="&#8203;">
                <label for="confirm_password" class="form-field2__label">Confirm Password</label>
            </div> 
            <button class="button button--login" aria-label="Create account">Create Account</button>
            <a href="#" class="signup-form__cancel" aria-label="Come back to login page">Cancel</a>
        </form> 
    `;
}