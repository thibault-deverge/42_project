#include "../../includes/Channel.hpp"
#include "../../includes/Server.hpp"

void	Server::handle_kick_command(Client *client, std::string& message)
{
    if (!client->get_connected())
	{
		send(client->get_socket(), ERR_NOTREGISTERED.c_str(), ERR_NOTREGISTERED.length(), 0);
		return ;
	}

	std::string name_channel    = extract_next_parameter(message, ' ');
    std::string user_to_kick    = extract_next_parameter(message, ' ');
    std::string comment         = extract_next_parameter(message, '\r');

	Channel     *channel        = find_channel(name_channel);
    if (!channel)
    {
        std::string error = find_and_replace(ERR_NOSUCHCHANNEL, "channel", name_channel.c_str());
		send(client->get_socket(), error.c_str(), error.size(), 0);
        return;
    }

    if (!channel->check_if_client_in_channel(client))
    {
        std::string err = find_and_replace(ERR_NOTONCHANNEL, "channel", name_channel.c_str());
        send(client->get_socket(), err.c_str(), err.size(), 0);
        return;
    }

    Client* target_client = channel->find_client_by_nickname(user_to_kick);
    if (!target_client)
    {
        std::string error = find_and_replace(ERR_USERNOTINCHANNEL, "nick", user_to_kick.c_str());
        error = find_and_replace(error, "channel", name_channel.c_str());
        send(client->get_socket(), error.c_str(), error.size(), 0);
        return;
    }

    if (!channel->isClientOpe(client))
        return;

    std::string rsp = find_and_replace(RPL_KICK, "nick", client->get_nickname().c_str());
    rsp = find_and_replace(rsp, "user", client->get_username().c_str());
    rsp = find_and_replace(rsp, "channel", name_channel.c_str());
    rsp = find_and_replace(rsp, "user_kick", user_to_kick.c_str());
    if (!comment.empty())
        rsp = find_and_replace(rsp, "comment", comment.c_str());
    else
        rsp = find_and_replace(rsp, "comment", user_to_kick.c_str());

    channel->msgToAllChannel(rsp);
    channel->removeClient(target_client);

    if (channel->getClients().size() == 0)
    {
        for (Channel_Iterator it = _channels.begin(); it != _channels.end(); it++)
        {
            if (*it == channel)
            {
                delete(*it);
                _channels.erase(it);
                break;
            }
        }
    }
}