#include "../../includes/Server.hpp"

void Server::handle_join_command(Client* client, std::string& message)
{
	if (!client->get_connected())
	{
		send(client->get_socket(), ERR_NOTREGISTERED.c_str(), ERR_NOTREGISTERED.length(), 0);
		return ;
	}
    std::string name_channel    = extract_next_parameter(message, ' ');
    Channel     *channel        = find_channel(name_channel);

	if (channel)
    {
        if (channel->getKey().empty())
		{
			channel->addClient(client);
			client->_channels.push_back(channel);
		}
        else
			verify_key_join(client, channel, message);
    }
    else
    {
        std::string key = extract_next_parameter(message, ' ');

        if (is_valid_channel_name(name_channel))
		{
			Channel *new_channel = new Channel(name_channel, client, key);
			_channels.push_back(new_channel);
			client->_channels.push_back(new_channel);
		}
        else
        {
            std::string error_msg = find_and_replace(ERR_NOSUCHCHANNEL, "channel", name_channel.c_str());
            send(client->get_socket(), error_msg.c_str(), error_msg.length(), 0);
        }
    }
}

void Server::verify_key_join(Client* client, Channel* channel, std::string& message)
{
    std::string key_parameter = extract_next_parameter(message, ' ');

    if (key_parameter != channel->getKey())
    {
        std::string error_msg = find_and_replace(ERR_BADCHANNELKEY, "canal", channel->getName().c_str());
        send(client->get_socket(), error_msg.c_str(), error_msg.length(), 0);
    }
    else
	{
		channel->addClient(client);
		client->_channels.push_back(channel);
	}
}

Channel* Server::find_channel(const std::string& channel_name)
{
    for (size_t i = 0; i < _channels.size(); ++i)
    {
        if (_channels[i]->getName() == channel_name)
            return _channels[i];
    }
    return 0;
}

bool Server::is_valid_channel_name(const std::string& channel_name) const
{
    size_t name_len = channel_name.length();

    if (channel_name[0] != '#' || name_len > 200)
        return false;

    for (size_t i = 1; i < name_len; ++i)
    {
        if (channel_name[i] == ' ' || channel_name[i] == 7)
            return false;
    }
    return true;
}