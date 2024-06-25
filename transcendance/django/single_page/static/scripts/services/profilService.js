import { getCookie } from "../utils/cookie.js";

export function setuptEditListener() {
    const elements = {
        usernameDisplay: document.querySelector(".user__username-display"),
        usernameInput: document.getElementById("usernameInput"),
        editUsernameBtn: document.getElementById("editUserBtn"),
        saveUsernameBtn: document.getElementById("saveUserBtn"),
        cancelUsernameBtn: document.getElementById("cancelUserBtn"),
        quoteDisplay: document.querySelector(".user__quote-display"),
        quoteInput: document.querySelector(".user__quote-input"),
        editQuoteBtn: document.getElementById("editQuoteBtn"),
        saveQuoteBtn: document.getElementById("saveQuoteBtn"),
        cancelQuoteBtn: document.getElementById("cancelQuoteBtn"),
        errorMessage: document.querySelector(".user__input-error"),
    };
    elements.editUsernameBtn.addEventListener('click', () => openEditModeUsername(elements));
    elements.cancelUsernameBtn.addEventListener('click', () => closeEditModeUsername(elements));
    elements.editQuoteBtn.addEventListener('click', () => openEditModeQuote(elements));
    elements.cancelQuoteBtn.addEventListener('click', () => closeEditModeQuote(elements));
    elements.saveUsernameBtn.addEventListener('click', () => updateUsername(elements));
    elements.saveQuoteBtn.addEventListener('click', () => updateQuote(elements));
}

async function updateUsername(elements) {
    const newUsername = elements.usernameInput.value;

    try {
        const response = await fetch('/user/update_username/', {
            method: 'post',
            headers: {
                'Content-type': 'application/json',
                'X-CSRFToken': getCookie('csrftoken')
            },
            body: JSON.stringify({ username: newUsername }),
            credentials: 'include'
        });
        const data = await response.json();
        if (response.ok) {
            elements.usernameDisplay.textContent = newUsername;
            closeEditModeUsername(elements);
        } else {
            elements.errorMessage.textContent = data.username[0] || 'failed to update username';
            elements.errorMessage.style.display = 'block';
        }
    } catch (error) {
    }
}

async function updateQuote(elements) {
    const newQuote = elements.quoteInput.value;

    try {
        const response = await fetch('/user/update_quote/', {
            method: 'post',
            headers: {
                'Content-type': 'application/json',
                'X-CSRFToken': getCookie('csrftoken')
            },
            body: JSON.stringify({ quote: newQuote }),
            credentials: 'include'
        });
        const data = await response.json();
        if (response.ok) {
            elements.quoteDisplay.textContent = newQuote;
            closeEditModeQuote(elements);
        }
    } catch (error) {
    }
}

function openEditModeUsername(elements) {
    elements.usernameDisplay.style.display = 'none';
    elements.editUsernameBtn.style.display = 'none';
    elements.usernameInput.style.display = 'inline';
    elements.saveUsernameBtn.style.display = 'inline';
    elements.cancelUsernameBtn.style.display= 'inline';
}

function openEditModeQuote(elements) {
    elements.quoteDisplay.style.display = 'none';
    elements.editQuoteBtn.style.display = 'none';
    elements.quoteInput.style.display = 'inline';
    elements.saveQuoteBtn.style.display = 'inline';
    elements.cancelQuoteBtn.style.display = 'inline';
}

function closeEditModeQuote(elements) {
    elements.quoteDisplay.style.display = "flex";
    elements.editQuoteBtn.style.display = 'inline';
    elements.quoteInput.style.display = 'none';
    elements.saveQuoteBtn.style.display = 'none';
    elements.cancelQuoteBtn.style.display = 'none';
}

function closeEditModeUsername(elements) {
    elements.usernameDisplay.style.display = 'flex';
    elements.editUsernameBtn.style.display = 'inline';
    elements.usernameInput.value = '';
    elements.usernameInput.style.display = 'none';
    elements.errorMessage.textContent = '';
    elements.errorMessage.style.display = 'none';
    elements.saveUsernameBtn.style.display = 'none';
    elements.cancelUsernameBtn.style.display= 'none';
}