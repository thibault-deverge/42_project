#include "../../includes/Channel.hpp"
#include "../../includes/Server.hpp"

void	Server::handle_who_command(Client *client, std::string& message)
{
	if (!client->get_connected())
	{
		send(client->get_socket(), ERR_NOTREGISTERED.c_str(), ERR_NOTREGISTERED.length(), 0);
		return ;
	}
	std::string name_channel    = extract_next_parameter(message, ' ');
	Channel     *channel        = find_channel(name_channel);

	if (name_channel.empty())
	{
		std::string error_msg = find_and_replace(ERR_NEEDMOREPARAMS, "command", "WHO");
		send(client->get_socket(), error_msg.c_str(), error_msg.length(), 0);
	}
	else if (channel)
		channel->sendMode(client);
	else
	{
		std::string error_msg = find_and_replace(ERR_NOSUCHNICK, "pseudo", name_channel.c_str());
		send(client->get_socket(), error_msg.c_str(), error_msg.length(), 0);
	}
}