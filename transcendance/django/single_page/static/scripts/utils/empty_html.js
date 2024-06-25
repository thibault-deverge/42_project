export function removeAllHtml() {
    document.body.innerHTML = '';
    document.body.classList.remove("container--with-navbar");
}

export function removeMainHtml() {
    const main = document.querySelector('main');
    if (main) {
        main.parentNode.removeChild(main);
    }
}

export function removeNavbar() {
    document.body.classList.remove("container--with-navbar");
    const navbar = document.querySelector('nav')
    if (navbar) {
        navbar.parentNode.removeChild(navbar);
    }
}