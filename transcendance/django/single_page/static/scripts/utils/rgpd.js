import { getCookie } from "./cookie.js";
import { navigate, globalSocket, GlobalSocketToNull, startGlobalSocket } from "../router.js";
import {PATH} from "./constants.js";
import {fetchUserProfile} from "../services/userService.js";

export function setupRGPDListener() {
    const deleteButton = document.querySelector(".footer__button");
    const downloadButton = document.querySelector(".button-download-data");

    deleteButton.addEventListener('click', deleteUser);
    downloadButton.addEventListener('click', downloadUserData);

}

async function deleteUser() {
    if (confirm('Are you sure you want to delete your account? This action cannot be undone.')) {
        try {
            globalSocket.close();
            GlobalSocketToNull();
            const response = await fetch(PATH + 'auth/delete-user/', {
                method: 'DELETE',
                headers: {
                    'Content-Type': 'application/json',
                    'X-CSRFToken': getCookie("csrftoken")
                },
                credentials: 'include',
            });
            if (response.ok) {
                alert('Your account has been successfully deleted.');
                navigate('/login');
            } else {
                const errorData = await response.json();
                alert(`Failed to delete account: ${errorData.detail || 'Unknown error'}`);
            }
        } catch (error) {
            alert('An error occurred while deleting your account. Please try again.');
            startGlobalSocket();
        }
    }
}

async function downloadUserData() {
    const userData = await fetchUserProfile();
    if (userData) {
        const userDataStr = JSON.stringify(userData, null, 2);
        const blob = new Blob([userDataStr], { type: 'application/json' });
        const url = URL.createObjectURL(blob);
        const a = document.createElement('a');
        a.href = url;
        a.download = 'user_data.json';
        document.body.appendChild(a);
        a.click();
        document.body.removeChild(a);
    } else {
        alert('Failed to download user data.');
    }
}