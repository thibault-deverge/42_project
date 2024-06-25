import { isValidForm, displayErrorMsg } from "../utils/validation_input.js";
import {globalSocket, GlobalSocketToNull, navigate, startGlobalSocket } from "../router.js";
import {PATH} from "../utils/constants.js";

/*
------------------------------ Constants -----------------------------
*/
const AUTH_ENDPOINT         = PATH + 'auth';
const HTTP_STATUS_BAD_REQUEST      = 400;
const LOGIN_FORM_SELECTOR   = ".login-form__input-container"
const SIGNUP_FORM_SELECTOR  = ".signup-form:nth-child(even)"

/*
------------------------ Authentication Check ------------------------
*/
export async function checkAuthentication() {
    try {
        const response = await fetch(`${AUTH_ENDPOINT}/check-auth/`);
        const data = await response.json();
        return data.authenticated;
    } catch(error) {
        return false;
    }
}

/*
------------------------------ Form Setup ----------------------------
*/
export function initializeFormListeners() {
    const loginForm = document.querySelector(".login-form");
    const signupForm = document.querySelector(".signup-form");

    loginForm.addEventListener('submit', handleLoginSubmit);
    signupForm.addEventListener('submit', handleSignupSubmit);
}

/*
---------------------------- Login Handle ----------------------------
*/
function handleLoginSubmit(event) {
    event.preventDefault();
    const loginData = {
        'username': document.querySelector('#log_username').value,
        'password': document.querySelector('#log_password').value
    }
    if (isValidForm(loginData, LOGIN_FORM_SELECTOR))
        authenticateUser(loginData);
}

async function authenticateUser(loginData) {
    try {
        const response = await fetch(`${AUTH_ENDPOINT}/login/`, {
            method: 'post',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify(loginData)
        })
        const data = await response.json();
        if (response.status === HTTP_STATUS_BAD_REQUEST)
            displayErrorMsg(data.detail, LOGIN_FORM_SELECTOR);
        else {
            startGlobalSocket()
            history.pushState({ page: 'dashboard' }, 'dashboard', '/dashboard');
            navigate('/dashboard');
        }
    } catch (error) {
        alert("Failed to log in. Please try again.");
    }
}

/*
---------------------------- Signup Handle --------------------------
*/
function handleSignupSubmit(event) {
    event.preventDefault();
    const signupData = {
        'username': document.querySelector('#username').value,
        'email': document.querySelector('#email').value,
        'password': document.querySelector('#password').value,
        'confirm_password': document.querySelector('#confirm_password').value
    };
    if (isValidForm(signupData, SIGNUP_FORM_SELECTOR))
        registerUser(signupData);
}

async function registerUser(signupData) {
    try {
        const response = await fetch(`${AUTH_ENDPOINT}/signup/`, {
            method: 'post',
            headers: { 'Content-Type': 'application/json'},
            body: JSON.stringify(signupData)
        })
        const data = await response.json();
        if (response.status === HTTP_STATUS_BAD_REQUEST) {
            const messageKey = Object.keys(data)[0];
            displayErrorMsg(data[messageKey], SIGNUP_FORM_SELECTOR);
        } else {
            history.pushState({ page: 'login' }, 'Login', '/login');
            navigate('/login');
        }
    } catch (error) {
        alert("Failed to sign up. Please try again.");
    }
}

/*
---------------------------- Logout Handle ---------------------------
*/
export async function handleLogout() {
    try {
        const response = await fetch(`${AUTH_ENDPOINT}/logout/`, {
            method: 'GET',
            headers: { 'Content-Type': 'application/json' },
        });
        if (response.ok) {
            globalSocket.close();
            GlobalSocketToNull();
            history.pushState({ page: 'login' }, 'Login', '/login');
            navigate('/login');
        } else {
            alert("Failed to log out. Please try again.");
        }
    } catch (error) {
        alert("Failed to log out. Please try again.");
    }
}