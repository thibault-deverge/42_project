import { getCookie } from "../utils/cookie.js";
import {PATH} from "../utils/constants.js";

const IMG_ENDPOINT = PATH + 'user';
export function setupImagesListeners() {
    const uploadCoverButton = document.querySelector('.couverture__button');
    const uploadAvatarButton = document.querySelector('.user__button');
    const coverPhotoInput = document.getElementById('coverPhotoInput');
    const avatarInput = document.getElementById('avatarInput');

    uploadCoverButton.addEventListener('click', function() {
        coverPhotoInput.click();
    })
    uploadAvatarButton.addEventListener('click', function() {
        avatarInput.click();
    })
    coverPhotoInput.addEventListener('change', function() {
        if (this.files[0])
            uploadImage(this.files[0], `${IMG_ENDPOINT}/update_cover_photo/`, 'cover_photo');
    });
    avatarInput.addEventListener('change', function() {
        if (this.files[0])
            uploadImage(this.files[0], `${IMG_ENDPOINT}/update_avatar/`, 'avatar');
    });
}

async function uploadImage(file, url, field) {
    const csrfToken = getCookie('csrftoken');
    const formData = new FormData();
    formData.append(field, file);

    try {
        const response = await fetch(url, {
            method: 'post',
            headers: {
                'X-CSRFToken': csrfToken,
            },
            body: formData,
            credentials: 'include'
        })
        if (response.ok) {
            let data;
            try {
                data = await response.json();
            } catch (error) {
            }
            updateImage(field, data);
        }
        else {
            const errorResponse = await response.json();
            const errorMessage = Object.values(errorResponse)
                .flat()
                .map(error => error)
                .join('\n');
            alert(`Error to upload image: ${errorMessage}`);
        }
    } catch (error) {
        alert(`Error to upload image: Image too big`);
    }
}

function updateImage(field, data) {
    if (field === 'avatar') {
        document.querySelector('.user__photo img').src = data.avatar;
    } else {
        document.querySelector('.couverture__picture').src = data.cover_photo;
    }
}
