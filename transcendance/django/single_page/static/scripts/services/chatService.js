import btn from "../chat/button.js"
import {WSS_PATH} from "../utils/constants.js";

export let whisper_buffer = "";
export let blocked_list = null;
export let socket = null;
export let connected_user = [];
let searchBoxWhisper = false;
let searchBoxTrigger = new KeyboardEvent('keyup', {
	key: 'Enter',
	keyCode: 13,
	bubbles: true
  });

export function initSocket(){
	socket = new WebSocket( WSS_PATH + "/chat");
}

export function addUserConnected(username){
	connected_user.push(username);
}

export function removeUserConnected(username){
	let index = connected_user.indexOf(username);
	if (index !== -1)
		connected_user.splice(index,1);
}

export function resetConnectedUser(){
	connected_user = [];
}

export function defineWhisperBuffer(text){
	whisper_buffer = text;
}

export function rmBlockedList(name){
	let index = blocked_list.indexOf(name);
	if (index !== -1)
		blocked_list.splice(index, 1);
}

export function pushBlockedList(name){
	blocked_list.push(name);
}

export function defineBlockedList(list){
	blocked_list = list;
}

export function leaveChat(){
    socket.send(JSON.stringify({'type' : "deco"}));
	if (socket != null)
		socket.close();
	resetConnectedUser();
}

export function addEventListenerToElement(element, event, handler) {
    if (element) {
        element.addEventListener(event, handler);
    }
}

export function initializeChatListeners() {
    const elements = {
        publicChatBtn: document.getElementById("chatnav__public-category"),
        privateChatBtn: document.getElementById("chatnav__private-category"),
        sendMessageBtn: document.querySelector("#sendButton"),
        userList: document.querySelector(".user-list"),
    };
    const inputs = {
        searchInput: document.querySelector(".chatnav__search-input"),
        chatInput: document.querySelector("#messageInput")
    }
    addEventListenerToElement(elements.userList, 'click', handleUserButton)
    addEventListenerToElement(elements.publicChatBtn, 'click', handleShowPublicChat);
    addEventListenerToElement(elements.privateChatBtn, 'click', handleShowPrivateChat);
    addEventListenerToElement(elements.sendMessageBtn, 'click', handleSendMessage);
    addEventListenerToElement(inputs.chatInput, 'keydown', handleSendMessageInput)
    addEventListenerToElement(inputs.searchInput, 'keyup', handleSearchInput)
}


/*
******** EVENT HANDLER **********
*/

function handleUserButton(event){
    let username = event.target.parentNode.parentNode.querySelector(".user-list__username");
	if (username)
		username = username.id;
	else
		return ;
    if (event.target.alt == "whisper button") {
        btn.whisperButton(username);
		handleShowPrivateChat(null);
    } else if (event.target.alt == "block user button") {
        btn.blockButton(username)
    } else if (event.target.alt == "invite game button") {
        btn.sendInvite(username)
    }
}

function handleShowPublicChat(event) {
    let chat_general = document.querySelector(".chat__general");
    let allChatList = document.querySelectorAll(".chat__list");
	document.getElementById('chatnav__public-category').style.backgroundColor = "#d68c45";
	document.getElementById('chatnav__private-category').style.backgroundColor = "#384454";
    allChatList.forEach(element =>{
        element.style.display = "none";
    });
    chat_general.style.display = "flex";
    defineWhisperBuffer("");
    chat_general.scrollTop = chat_general.scrollHeight;
    searchBoxWhisper = false;
    document.querySelector(".chatnav__search-input").dispatchEvent(searchBoxTrigger);
}

function handleShowPrivateChat(event) {
	document.getElementById('chatnav__public-category').style.backgroundColor = "#384454";
	document.getElementById('chatnav__private-category').style.backgroundColor = "#d68c45";
    let allUser = document.querySelectorAll(".user-list__element");
    allUser.forEach(element => {
        if (!element.classList.contains("user-list__whisper-list"))
            element.style.display = "none";
    });
    searchBoxWhisper = true;
    document.querySelector(".chatnav__search-input").dispatchEvent(searchBoxTrigger);
}

function handleSearchInput(event){
    let value = document.querySelector('.chatnav__search-input').value;
    let users = document.querySelectorAll('.user-list__element');
    if (searchBoxWhisper)
        users = document.querySelectorAll('.user-list__whisper-list')
    if (value.length == 0){
        for (let i = 0; i < users.length; i++)
            users[i].style.display = "inherit";
        return ;
    }
    users.forEach(element =>{
        let username = element.querySelector(".user-list__username").id;
        if (username.substring(0, value.length) != value)
            element.style.display = "none";
        else
            element.style.display = "flex";
    });
}

function handleSendMessage(event) {
    btn.sendMsg();
}

function handleSendMessageInput(event) {
    if (event.key == 'Enter'){
        btn.sendMsg();
    }
}
