const ERR_USERNAME_MSG          = "Username must contain only letters, numbers, and underscores.";
const ERR_PASSWORD_MSG          = "Password must be at least 8 characters long and include letter and numbers.";
const ERR_CONFIRM_PASSWORD_MSG  = "Passwords do not match.";

export function isValidUsername(username) {
    const regex = /^[A-Za-z0-9_]+$/;
    return regex.test(username);
}

export function isValidPassword(password) {
    const regex = /^(?=.*[A-Za-z])(?=.*\d)[A-Za-z\d?\/,.?!-_]{8,}$/;
    return regex.test(password);
}

export function isValidForm(data, htmlLocation) {
    if (data.username && !isValidUsername(data.username)) {
        displayErrorMsg(ERR_USERNAME_MSG, htmlLocation);
        return false;
    }
    if (data.password && !isValidPassword(data.password)) {
        displayErrorMsg(ERR_PASSWORD_MSG, htmlLocation);
        return false;
    }
    if (data.confirmPassword && data.password !== data.confirmPassword) {
        displayErrorMsg(ERR_CONFIRM_PASSWORD_MSG, htmlLocation);
        return false;
    } 
    return true;
}

export function displayErrorMsg(message, selector) {
    const   location = document.querySelector(selector);
    let     error_element = location.querySelector('.form__error-message');

    if (!error_element) {
        error_element = document.createElement('p');
        error_element.classList.add("form__error-message");
        location.insertAdjacentElement('beforeEnd', error_element);
    }

    error_element.textContent = message;
}