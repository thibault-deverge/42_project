import {socket} from "../services/chatService.js";

export function recvMsg(data, isWhisper, blocked_list){
	let username = data['name'];
    if (blocked_list != null)
        if (blocked_list.includes(username))
            return;
    let message = data['message'];
    let avatarPath = `/static/images/default_profil.jpg`;
    let addedClass = "";
    if (isWhisper)
        addedClass = "chat__whisper-msg";
    let htmlMessage = /*html*/`
            <li class="chat__other-msg ${addedClass}">
                <img class="user-link" src="${avatarPath}" alt="avatar"/>
                <p>${username}: ${message}</p>
            </li>
        `;
    let chatToUpdate = document.querySelector(".chat__general");
    if (chatToUpdate != null)
    {
        if (isWhisper){
            chatToUpdate = getChatBoxes(username);
            let user_elem = document.querySelector("#"+username).parentNode;
            if (!user_elem.classList.contains("user-list__whisper-list"))
                user_elem.classList.add("user-list__whisper-list");
        }
        chatToUpdate.insertAdjacentHTML('beforeend', htmlMessage);
        chatToUpdate.scrollTop = chatToUpdate.scrollHeight;
    }
}

export function self_sendMsg(message, isWhisper, whisper_to){
    let chat_general = document.querySelector(".chat__general");
    let avatarPath = `/static/images/default_profil.jpg`;
    let addedClass = "";
    if (isWhisper)
        addedClass = "chat__whisper-msg";
    let htmlMessage = /*html*/`
            <li class="chat__user-msg ${addedClass}">
                <img src="${avatarPath}" alt="avatar"/>
                <p>You: ${message}</p>
            </li>
        `;
    if (!isWhisper){
        chat_general.insertAdjacentHTML('beforeend', htmlMessage);
        chat_general.scrollTop = chat_general.scrollHeight;
    }
    else{
        let chatList = getChatBoxes(whisper_to);
        let user_elem = document.querySelector("#"+whisper_to).parentNode;
        if (!user_elem.classList.contains("user-list__whisper-list"))
            user_elem.classList.add("user-list__whisper-list");
        chatList.insertAdjacentHTML('beforeend', htmlMessage);
        chatList.scrollTop = chatList.scrollHeight;
    }
}

export function getChatBoxes(username){
    let chat_list = document.querySelectorAll(".chat__list");
    let ret = null;
    chat_list.forEach(element =>{
        if (element.id == username){
            ret = element;
            return;
        }
    });
    if (ret != null)
        return ret;
    if (ret == null){
        let htmlChat = `<ul class="chat__list" id="${username}"></ul>`;
        document.querySelector(".chat__msg-box").insertAdjacentHTML('beforebegin', htmlChat);
		getChatBoxes(username).style.display = "none";
    }
    return getChatBoxes(username);
}

export function addUserToSearchList(username, blocked_list){
    const userList = document.querySelector('.user-list');
    const avatarPath = '/static/images/default_profil.jpg';
    const whisperIconPath = '/static/images/private_msg_icon.png';
    let blockIconPath = '/static/images/block_icon.png';
	if (blocked_list != null)
        if (blocked_list.includes(username))
            blockIconPath = '/static/images/unblock_icon.png';
    const inviteGameIconPath = '/static/images/game_icon.png';
    if (document.getElementById(username))
        return;
    const userElementHtml = /*html*/`
        <div class="user-list__element">
            <img class="user-list__image" src="${avatarPath}" alt="profil image"/>
            <p class="user-list__username user-link" id="${username}">${username}</p>
            <button class="chat-user-btn whisper-btn"><img src="${whisperIconPath}" alt="whisper button" /></button>
            <button class="chat-user-btn block-btn"><img src="${blockIconPath}" alt="block user button" /></button>
            <button class="chat-user-btn inviteGame-btn"><img src="${inviteGameIconPath}" alt="invite game button" /></button>
        </div>
    `;
    userList.insertAdjacentHTML('beforeend', userElementHtml);
}

export function removeUserFromSearchList(username){
    const userElement = document.querySelectorAll(".user-list__element");
    userElement.forEach(element =>{
        if (element.querySelector("#"+username) != null)
            element.remove()
    })
}

export function showDiscussion(username){
	let chatList = document.querySelectorAll(".chat__list");
	chatList.forEach(element => {
		if (element.id == username)
			element.style.display = "flex";
		else
			element.style.display = "none";
	});
}

function handleInvite(id){
    socket.send(JSON.stringify({'id_game' : id, 'type' : "accept private game"}));
}

export function recvInvite(data){
    let avatarPath = `/static/images/default_profil.jpg`;
	let chat_general = document.querySelector(".chat__general");
    let htmlMessage = /*html*/`
            <li class="chat__other-invite">
                <p>${data.name}: <button class="button button--invite">ACCEPT INVITE</button></p>
            </li>
        `;
	chat_general.insertAdjacentHTML('beforeend', htmlMessage);
	chat_general.scrollTop = chat_general.scrollHeight;
    let allButton =  document.querySelectorAll(".button--invite")
    allButton.forEach(element => {
        element.addEventListener("click", function(evt) { handleInvite(data.id_game); })
    })
}

export default {
	recvMsg,
	self_sendMsg,
	addUserToSearchList,
	removeUserFromSearchList,
	showDiscussion,
	getChatBoxes,
	recvInvite,
}
