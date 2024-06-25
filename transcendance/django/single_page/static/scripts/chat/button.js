import ui from "./ui.js"
import { whisper_buffer, blocked_list, socket, defineWhisperBuffer, defineBlockedList, pushBlockedList, rmBlockedList } from "../services/chatService.js"
import {globalSocket} from "../router.js";

function sendMsg(){
    const messageInput = document.getElementById('messageInput');
    const message = messageInput.value;
    const chat_general = document.querySelector('.chat__general');
    let avatarPath = `/static/images/default_profil.jpg`;
    if (whisper_buffer[0] === "/" && whisper_buffer[1] === "w"){
        let whisper_to = whisper_buffer.split(" ")[1];
        if (message === "")
            return ;
		let chatWhisper = ui.getChatBoxes(whisper_to);
        let htmlMessage = /*html*/`
            <li class="chat__user-msg">
                <img src="${avatarPath}" alt="avatar"/>
                <p>You: ${message}</p>
            </li>
        `;
        socket.send(JSON.stringify({'message' : message, 'whisper_to' : whisper_to, 'type' : "new_message_whisper"}));
		socket.send(JSON.stringify({'message' : message, 'whisper_to' : whisper_to, 'type' : "self_new_message_whisper"}));
        chatWhisper.insertAdjacentHTML('beforeend', htmlMessage);
        chat_general.scrollTop = chat_general.scrollHeight;
        messageInput.value = '';
    }
    else if (message.trim() !== '') {
        socket.send(JSON.stringify({ 'type': 'new_message', 'message': message }));
        socket.send(JSON.stringify({'message' : message, 'type' : "self_new_message"}));
        let htmlMessage = /*html*/`
            <li class="chat__user-msg">
                <img src="${avatarPath}" alt="avatar"/>
                <p>You: ${message}</p>
            </li>
        `;
        chat_general.insertAdjacentHTML('beforeend', htmlMessage);
        chat_general.scrollTop = chat_general.scrollHeight;
        messageInput.value = '';
    }
}

function blockButton(username){
	const userElement = document.querySelectorAll(".user-list__element");
	let icon = null;
    userElement.forEach(element =>{
		if (element.querySelector("#"+username) != null)
			icon = element.querySelector('.block-btn').firstChild;
	});
    if (blocked_list != null){
        if (blocked_list.includes(username)){
            socket.send(JSON.stringify({'message' : username, 'type' : "unblockUser"}));
            socket.send(JSON.stringify({'name' : username,'type' : "self_unblockUser"}));
            rmBlockedList(username);
			icon.src = '/static/images/block_icon.png';
            return ;
        }
    }
    else
        defineBlockedList(Array(username))
    pushBlockedList(username);
    socket.send(JSON.stringify({'name' : username, 'type' : "self_blockUser"}));
    socket.send(JSON.stringify({'message' : username, 'type' : "blockUser"}));
	icon.src = '/static/images/unblock_icon.png';
}

function whisperButton(username){
    let user_elem = document.querySelector("#"+username).parentNode;
    if (!user_elem.classList.contains("user-list__whisper-list"))
        user_elem.classList.add("user-list__whisper-list");
    defineWhisperBuffer("/w "+username+" ");
    ui.getChatBoxes(username);
    ui.showDiscussion(username);
}

function sendInvite(username){
	//handle globalSocket
    alert("Invitation sent !")
	socket.send(JSON.stringify({'name' : username, 'type' : "invite private game"}));
}

export default {
	sendMsg,
	blockButton,
	whisperButton,
	sendInvite,
}
