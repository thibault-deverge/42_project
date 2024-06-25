import ui from "./ui.js"
import { blocked_list, socket, defineBlockedList, initSocket, connected_user, removeUserConnected, addUserConnected, pushBlockedList, rmBlockedList, } from "../services/chatService.js"
// -------- TEMPORARY --------


export function identify(username){
	initSocket();
    socket.onopen = function (e){
        socket.send(JSON.stringify({'message' : username,'type' : "identify"}));
    }

    socket.onmessage = function (e) {
		let data = JSON.parse(e.data);
        if (data.type == "new_connection"){
			if (connected_user.includes(data.name)){
				addUserConnected(data.name);
				socket.send(JSON.stringify({'type' : "update", 'send_to' : data['sender']}));
				return ;
			}
			addUserConnected(data.name);
            ui.recvMsg(data, false, blocked_list);
            ui.addUserToSearchList(data.name, blocked_list);
            socket.send(JSON.stringify({'type' : "update", 'send_to' : data['sender']}));
        }
        if(data.type == "disconnection"){
			removeUserConnected(data.name);
			if (connected_user.includes(data.name))
				return ;
            ui.recvMsg(data, false, blocked_list);
            ui.removeUserFromSearchList(data.name);
        }

		if (data.type == "PRIVATE GAME ROOM DOESN'T EXIST")
			alert("Invitation has already expired !")

        if (data.type == "new_message")
            ui.recvMsg(data, false, blocked_list);
        if (data.type == "new_message_whisper"){
            ui.recvMsg(data, true, blocked_list);
		}
        if (data.type == "update"){
			if (connected_user.includes(data.name)){
				addUserConnected(data.name);
				return ;
			}
			addUserConnected(data.name);
            ui.addUserToSearchList(data.name, blocked_list);
		}
		if (data.type == "invite private game"){
			if (blocked_list != null)
				if (blocked_list.includes(username))
					return;
			ui.recvInvite(data)
		}
        if (data.type == "blockedList")
            defineBlockedList(data["blockedList"]);
		if (data.type == "self_new_message")
			ui.self_sendMsg(data["message"], 0, null);
		if (data.type == "self_new_message_whisper")
			ui.self_sendMsg(data["message"], true, data["whisper_to"]);
		if (data.type == "self_blockUser"){
			if (blocked_list != null)
				pushBlockedList(data.name);
			else
				defineBlockedList(Array(data.name))
			const userElement = document.querySelectorAll(".user-list__element");
			userElement.forEach(element =>{
				if (element.querySelector("#"+data.name) != null){
					element.querySelector('.block-btn').firstChild.src = '/static/images/unblock_icon.png';
				}
			});
		}
		if (data.type == "self_unblockUser"){
			rmBlockedList(data.name);
			const userElement = document.querySelectorAll(".user-list__element");
			userElement.forEach(element =>{
				if (element.querySelector("#"+data.name) != null)
					element.querySelector('.block-btn').firstChild.src = '/static/images/block_icon.png';
			});
		}
		if (data.type == "connect_private_match") {
			navigate(PATH + "private_match/online/" + data.id_game)
		}
    }
}
