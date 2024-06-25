import { getCookie } from "../utils/cookie.js";
import {PATH} from "../utils/constants.js";

const BASE_URL = PATH;

export async function attachFriendListener(username, isFriend, images) {
    const friendBtn = document.getElementById("add_friend");
    let friendBtnImg = friendBtn.querySelector('img');

    async function handleFriendClick() {
        if (isFriend) {
            await removeFriend(username);
            friendBtnImg.src = images.ADD_FRIEND;
            isFriend = false;
        } else {
            await addFriend(username);
            friendBtnImg.src = images.REMOVE_FRIEND;
            isFriend = true;
        }
    }
    function updateListener() {
        friendBtn.removeEventListener('click', handleFriendClick);
        friendBtn.addEventListener('click', handleFriendClick);
    }
    updateListener();
}

export async function addFriend(username) {
    try {
        const response = await fetch(`${BASE_URL}user/add_friend/${username}/`, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
                'X-CSRFToken': getCookie('csrftoken')
            },
            credentials: 'include'
        });
        const data = await response.json();
        return data;
    } catch (error) {
        return false;    
    }
}

export async function removeFriend(username) {
    try {
        const response = await fetch(`${BASE_URL}user/remove_friend/${username}/`, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
                'X-CSRFToken': getCookie('csrftoken')
            },
            credentials: 'include'
        });
        const data = await response.json();
        return data;
    } catch (error) {
        return false;    
    }
}

export async function fetchFriendList(username) {
    try {
        const response = await fetch(`${BASE_URL}user/get_friends/${username}/`, {
            method: 'GET',
            headers: {
                'Content-Type': 'application/json',
                'X-CSRFToken': getCookie('csrftoken')
            },
            credentials: 'include'
        });
        const data = await response.json();
        return data;
    } catch (error) {
        return [];    
    }
}