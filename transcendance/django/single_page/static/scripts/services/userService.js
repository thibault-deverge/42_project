import { navigate } from "../router.js";
import {PATH} from "../utils/constants.js";

const BASE_URL = PATH;

export async function getOwnUser() {
    try {
        const response = await fetch(`${BASE_URL}auth/get-user/`);
        const data = await response.json();
		return data;
    } catch(error) {
        return false;
    }
}

export async function fetchUserProfile() {
    try {
        const response = await fetch(`${BASE_URL}user/user_profile/`, {
            method: 'GET',
            headers: {
                'Content-Type': 'application/json',
            },
            credentials: 'include'
        });
        const data = await response.json();
        return data;
    } catch (error) {
        return null;
    }
}

export async function fetchUserProfileByUsername(username) {
    try {
        const response = await fetch(`${BASE_URL}user/${username}/`, {
            method: 'GET',
            headers: {
                'Content-Type': 'application/json',
            },
            credentials: 'include'
        });
        if (!response.ok) {
            if (response.status === 404)
                return null;
        }
        const data = await response.json();
        return data;
    } catch (error) {
        return null;
    }
}