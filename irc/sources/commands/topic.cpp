#include "../../includes/Channel.hpp"
#include "../../includes/Server.hpp"

void	Server::handle_topic_command(Client *client, std::string& message)
{
    if (!client->get_connected())
	{
		send(client->get_socket(), ERR_NOTREGISTERED.c_str(), ERR_NOTREGISTERED.length(), 0);
		return ;
	}

	std::string channel_name    = extract_next_parameter(message, ' ');
    std::string new_topic       = extract_next_parameter(message, '\r');
	Channel     *channel        = find_channel(channel_name);

    if (!channel)
    {
        std::string error = find_and_replace(ERR_NOSUCHCHANNEL, "channel", channel_name.c_str());
		send(client->get_socket(), error.c_str(), error.size(), 0);
        return;
    }

    if (!channel->check_if_client_in_channel(client))
    {
        std::string err = find_and_replace(ERR_NOTONCHANNEL, "channel", channel_name.c_str());
        send(client->get_socket(), err.c_str(), err.size(), 0);
        return;
    }

    if (new_topic.empty())
    {
        if (channel->getTopic().empty())
        {
            std::string rsp = find_and_replace(RPL_NOTOPIC, "nick", client->get_nickname().c_str());
            rsp = find_and_replace(rsp, "canal", channel_name.c_str()); 
            send(client->get_socket(), rsp.c_str(), rsp.size(), 0);
        }
        else
        {
            std::string rsp = find_and_replace(RPL_TOPIC, "nick", client->get_nickname().c_str());
            rsp = find_and_replace(rsp, "canal", channel_name.c_str());
            rsp = find_and_replace(rsp, "topic", channel->getTopic().c_str());
            send(client->get_socket(), rsp.c_str(), rsp.size(), 0);
        }
        return;
    }

    t_mode channel_mode = channel->getMode();
    if (!channel_mode.t && !channel->isClientOpe(client))
        return;

    channel->setTopic(new_topic);
    std::string rsp = find_and_replace(RPL_TOPIC_CHANGE, "nick", client->get_nickname().c_str());
    rsp = find_and_replace(rsp, "user", client->get_username().c_str());
    rsp = find_and_replace(rsp, "channel", channel_name.c_str());
    rsp = find_and_replace(rsp, "topic", new_topic.c_str());
    channel->msgToAllChannel(rsp);
}