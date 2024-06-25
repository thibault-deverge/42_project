#include "../../includes/Server.hpp"
#include "../../includes/Client.hpp"

static std::string  create_response_nick(Client* client, const std::string& new_nickname);
static bool         is_valid_nickname(const std::string& new_nickname);

void Server::handle_nick_command(Client* client, std::string& message)
{
    std::string new_nickname = extract_next_parameter(message, ' ');

    // Handle errors of NICK
    if (new_nickname.empty())
	{
		send(client->get_socket(), ERR_NONICKNAMEGIVEN.c_str(), ERR_NONICKNAMEGIVEN.length(), 0);
		return;
	}
	else if (!is_valid_nickname(new_nickname))
	{
		std::string err_msg = find_and_replace(ERR_ERRONEUSNICKNAME, "pseudo", new_nickname.c_str());
		send(client->get_socket(), err_msg.c_str(), err_msg.size(), 0);
		return;
	}
    else if (new_nickname == client->get_nickname() || is_nickname_already_taken(new_nickname))
    {
        std::string err_msg = find_and_replace(ERR_NICKNAMEINUSE, "nick", new_nickname.c_str());
        send(client->get_socket(), err_msg.c_str(), err_msg.length(), 0);
		return;
    }

	std::string old_nickname = client->get_nickname();
    client->set_nickname(new_nickname);
	if (!old_nickname.empty())
	{
		std::string rpl_nick = create_response_nick(client, old_nickname);
		msg_to_all_client(rpl_nick);
	}
}

bool Server::is_nickname_already_taken(const std::string& new_nickname) const
{
    for (size_t i = 0; i < _clients.size(); ++i)
    {
        if (_clients[i] && _clients[i]->get_nickname() == new_nickname)
            return true;
    }
    return false;
}

static std::string create_response_nick(Client* client, const std::string& old_nickname)
{
    std::string rpl_nick = find_and_replace(RPL_NICK, "nick", old_nickname.c_str());
    rpl_nick = find_and_replace(rpl_nick, "user", client->get_username().c_str());
    rpl_nick = find_and_replace(rpl_nick, "new_nick", client->get_nickname().c_str());

    return rpl_nick;
}

static bool is_valid_nickname(const std::string& new_nickname)
{
    if (new_nickname.length() > 9)
        return false;

    for (size_t i = 0; i < new_nickname.length(); i++)
    {
		if (!isalnum(new_nickname[i]) && new_nickname[i] != '_' && new_nickname[i] != ':')
		    return false;
	}
    return true;
}