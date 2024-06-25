#include "../../includes/Channel.hpp"
#include "../../includes/Server.hpp"

void	Server::handle_part_command(Client *client, std::string& message)
{
    if (!client->get_connected())
	{
		send(client->get_socket(), ERR_NOTREGISTERED.c_str(), ERR_NOTREGISTERED.length(), 0);
		return ;
	}

	std::string name_channel    = extract_next_parameter(message, ' ');

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

    std::string reply = find_and_replace(RPL_PART, "nick", client->get_nickname().c_str());
    reply = find_and_replace(reply, "user", client->get_username().c_str());
    reply = find_and_replace(reply, "channel", name_channel.c_str());

    channel->msgToAllChannel(reply);
    channel->removeClient(client);

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