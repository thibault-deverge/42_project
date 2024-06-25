import { identify } from "../chat/chat.js";
import { initializeChatListeners, socket, resetConnectedUser } from "../services/chatService.js";
import { getOwnUser } from "../services/userService.js";

export function renderChatPage() {
    if (window.location.pathname !== '/chat') {
        history.pushState({ page: 'chat' }, 'chat', '/chat');
    }
    const chatHtml = getChatPageHtml();
    document.body.insertAdjacentHTML('beforeend', chatHtml);
	initializeChatListeners();
	if (socket != null){
		if(socket.readyState == 1){
			socket.close();
			resetConnectedUser();
		}
	}
	getOwnUser()
		.then(data => {
			identify(data.username);
		})
}

function getChatPageHtml() {
    return /*html*/ `
        <main class="chat-grid">
                <nav class="chatnav">
                    <div class="chatnav__categories">
                        <div class="chatnav__categories-item" id="chatnav__public-category">
                            <button class="chatnav__btn">Public Chat</button>
                        </div>
                        <div class="chatnav__categories-item" id="chatnav__private-category">
                            <button class="chatnav__btn">Private Chat</button>
                        </div>
                    </div>
                    <div class="chatnav__searchbar">
                        <svg class="icon" aria-hidden="true" viewBox="0 0 24 24"><g><path d="M21.53 20.47l-3.66-3.66C19.195 15.24 20 13.214 20 11c0-4.97-4.03-9-9-9s-9 4.03-9 9 4.03 9 9 9c2.215 0 4.24-.804 5.808-2.13l3.66 3.66c.147.146.34.22.53.22s.385-.073.53-.22c.295-.293.295-.767.002-1.06zM3.5 11c0-4.135 3.365-7.5 7.5-7.5s7.5 3.365 7.5 7.5-3.365 7.5-7.5 7.5-7.5-3.365-7.5-7.5z"></path></g></svg>
                        <input placeholder="Search" type="search" class="chatnav__search-input">
                    </div>
                    <div class="user-list"></div>
                </nav>
                <section class="chat">
                    <ul class="chat__list chat__general">
                    </ul>
                    <div class="chat__msg-box">
                        <input required="" placeholder="Type here..." type="text" maxlength="255" id="messageInput" />
                        <button id="sendButton">
                            <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 664 663">
                                <path fill="none" d="M646.293 331.888L17.7538 17.6187L155.245 331.888M646.293 331.888L17.753 646.157L155.245 331.888M646.293 331.888L318.735 330.228L155.245 331.888"></path>
                                <path stroke-linejoin="round" stroke-linecap="round" stroke-width="33.67" stroke="#6c6c6c" d="M646.293 331.888L17.7538 17.6187L155.245 331.888M646.293 331.888L17.753 646.157L155.245 331.888M646.293 331.888L318.735 330.228L155.245 331.888" ></path>
                            </svg>
                        </button>
                  </div>
                </section>
        </main>
    `
}
