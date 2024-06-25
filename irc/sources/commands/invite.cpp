#include "../../includes/Channel.hpp"
#include "../../includes/Server.hpp"

void	Server::handle_invite_command(Client* client, std::string& message)
{
    std::string invitee_nickname    = extract_next_parameter(message, ' ');
    std::string channel_name        = extract_next_parameter(message, '\r');

	Channel     *channel            = find_channel(channel_name);
    if (!channel)
    {
        std::string error = find_and_replace(ERR_NOSUCHCHANNEL, "channel", channel_name.c_str());
		send(client->get_socket(), error.c_str(), error.size(), 0);
        return;
    }

    t_mode channel_mode = channel->getMode();
    if (!channel_mode.i && !channel->isClientOpe(client))
        return;

    Client_Iterator invitee_it = find_client_iterator(invitee_nickname);
    if (!(*invitee_it))
    {
        std::string err = find_and_replace(ERR_NOSUCHNICK, "pseudo", invitee_nickname.c_str());
        send(client->get_socket(), err.c_str(), err.size(), 0);
        return;
    }

	channel->inviteClient(client, (*invitee_it));
}

