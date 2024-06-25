#include "../../includes/Server.hpp"

void Server::handle_user_command(Client* client, std::string& message)
{
	std::string new_username = extract_next_parameter(message, ' ');

	if (new_username.empty())
	{
		std::string err_msg = find_and_replace(ERR_NEEDMOREPARAMS, "command", "USER");
		send(client->get_socket(), err_msg.c_str(), err_msg.length(), 0);
		return;
	}

	client->set_username(new_username);
}

bool Server::is_username_already_taken(const std::string& new_username)
{
	for (size_t i = 0; i < _clients.size(); ++i)
	{
		if (_clients[i]->get_username() == new_username)
			return true;
	}
	return false;
}
