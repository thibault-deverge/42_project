#include "../../includes/Server.hpp"

void split_recipient(std::string recipient, std::vector<std::string> &recipients);

void Server::handle_privmsg_command(Client *client, std::string &message)
{
	if (!client->get_connected())
	{
		send(client->get_socket(), ERR_NOTREGISTERED.c_str(), ERR_NOTREGISTERED.length(), 0);
		return ;
	}
	std::string recipient = extract_next_parameter(message, ' ');
	if (recipient.empty())
	{
		std::string error = find_and_replace(ERR_NORECIPIENT, "command", "PRIVMSG");
		send(client->get_socket(), error.c_str(), error.size(), 0);
		return ;
	}
	if (message.empty())
	{
		send(client->get_socket(), ERR_NOTEXTTOSEND.c_str(), ERR_NOTEXTTOSEND.size(), 0);
		return ;
	}
	std::vector<std::string> recipients;
	split_recipient(recipient, recipients);
	std::string message_to_send = message;
	if (message_to_send[0] == ':')
	{
		message_to_send = message_to_send.substr(1, message_to_send.size() - 1);
	}
	else
		message_to_send = message_to_send = extract_next_parameter(message, ' ');
	for (std::vector<std::string>::iterator it = recipients.begin(); it != recipients.end(); ++it)
	{
		std::string final_message = find_and_replace(RPL_PRIVMSG, "nick", client->get_nickname().c_str());
		final_message = find_and_replace(final_message, "user", client->get_username().c_str());
		final_message = find_and_replace(final_message, "recipient", it->c_str());
		final_message = find_and_replace(final_message, "message", message_to_send.c_str());
		std::vector<Channel*>::iterator it_channel = find_channel_iterator(*it);
		std::vector<Client*>::iterator it_client = find_client_iterator(*it);
		if (it_channel != _channels.end())
		{
			if ((*it_channel)->check_if_client_in_channel(client))
			{
				(*it_channel)->msgToChannel(final_message, client->get_socket());
			}
			else
			{
				std::string error = find_and_replace(ERR_NOSUCHNICK, "channel", (*it_channel)->getName().c_str());
				send(client->get_socket(), error.c_str(), error.size(), 0);
			}
		}
		else if (it_client != _clients.end())
		{
			send((*it_client)->get_socket(), final_message.c_str(), final_message.size(), 0);
		}
		else
		{
			std::string error = find_and_replace(ERR_NOSUCHNICK, "pseudo", it->c_str());
			send(client->get_socket(), error.c_str(), error.size(), 0);
		}
	}
}

void split_recipient(std::string recipient, std::vector<std::string> &recipients)
{
	if (recipient[recipient.size() - 1] == ',')
		recipient = recipient.substr(0, recipient.size() - 1);
	while (!recipient.empty())
	{
		size_t delimiter = recipient.find(',');
		std::string new_recipient = recipient.substr(0, delimiter);
		if (delimiter != std::string::npos)
			recipient.erase(0, delimiter + 1);
		else
			recipient.erase(0, delimiter);
		if (std::find(recipients.begin(), recipients.end(), new_recipient) == recipients.end())
			recipients.push_back(new_recipient);
	}
}
