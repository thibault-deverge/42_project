#include "../../includes/Server.hpp"

void Server::handle_pass_command(Client* client, std::string& message)
{
	std::string password = extract_next_parameter(message, ' ');

	if (client->get_connected())
	{
		send(client->get_socket(), ERR_ALREADYREGISTRED.c_str(), ERR_ALREADYREGISTRED.length(), 0);
		return ;
	}
	if (!_password.empty() && password.empty())
	{
		std::string err_msg = find_and_replace(ERR_NEEDMOREPARAMS, "command", "PASS");
		send(client->get_socket(), err_msg.c_str(), err_msg.length(), 0);
		client->set_password(false);
		return ;
	}
	else if (!_password.empty() && password.compare(_password))
	{
		send(client->get_socket(), ERR_INCORRECT_PASS.c_str(), ERR_INCORRECT_PASS.length(), 0);
		client->set_password(false);
		return ;
	}

	client->set_password(true);
}
