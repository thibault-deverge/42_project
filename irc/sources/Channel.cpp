#include "Channel.hpp"

Channel::Channel(const std::string& name, Client *ope, const std::string key) : _name(name)
{

	_mode.i = false;
	_mode.t = false;
	_mode.topic = "";
	_mode.key = key;
	_mode.limit = 0;
	_operators.push_back(ope);
	addClient(ope);
}

Channel::~Channel()	{

}

void Channel::msgToChannel(const std::string& msg, int sender_socket)
{
	for (Client_Iterator it = _clients.begin(); it < _clients.end(); ++it)
	{
		if ((*it)->get_socket() != sender_socket)
		{
			send((*it)->get_socket(), msg.c_str(), msg.size(), 0);
		}
	}
}

void Channel::msgToAllChannel(std::string msg)
{
	for (std::vector<Client*>::iterator it = _clients.begin(); it < _clients.end(); ++it)
	{
		send((*it)->get_socket(), msg.c_str(), msg.size(), 0);
	}
}

const std::string	Channel::getName() const {
	return (_name); }

t_mode Channel::getMode() const {
	return (_mode); }

std::string Channel::getKey() const {
	return (_mode.key); }

std::string Channel::getTopic() const {
	return (_mode.topic); }

void	Channel::setTopic(const std::string& new_topic) {
	_mode.topic = new_topic;
}

void	Channel::setMode(Client *client, char mode, long int limit, std::string key)
{
	std::string resp = find_and_replace(CHANGEMODE, "user", client->get_username().c_str());
	resp = find_and_replace(resp, "nick", client->get_nickname().c_str());
	resp = find_and_replace(resp, "channel", _name.c_str());
	std::string resp_arg = find_and_replace(CHANGEMODEARG, "user", client->get_username().c_str());
	resp_arg = find_and_replace(resp_arg, "nick", client->get_nickname().c_str());
	resp_arg = find_and_replace(resp_arg, "channel", _name.c_str());
	if (!isClientOpe(client))
		return;
	if (mode == 'i')
	{
		if (_mode.i)
			resp = find_and_replace(resp, "mode", "-i");
		else
			resp = find_and_replace(resp, "mode", "+i");
		_mode.i = !_mode.i;
		msgToAllChannel(resp);
	}
	else if (mode == 't')
	{
		if (_mode.t)
			resp = find_and_replace(resp, "mode", "-t");
		else
			resp = find_and_replace(resp, "mode", "+t");
		_mode.t = !_mode.t;
		msgToAllChannel(resp);
	}
	else if (mode == 'k')
	{
		if (_mode.key.empty())
		{
			resp_arg = find_and_replace(resp_arg, "mode", "+k");
			resp_arg = find_and_replace(resp_arg, "arg", key.c_str());
			_mode.key = key;
			msgToAllChannel(resp_arg);
		}
		else
		{
			resp = find_and_replace(resp, "mode", "-k");
			_mode.key = "";
			msgToAllChannel(resp);
		}
	}
	else if (mode == 'l')
	{
		if (limit == 0)
		{
			resp = find_and_replace(resp_arg, "mode", "-l");
			msgToAllChannel(resp);
		}
		else
		{
			resp_arg = find_and_replace(resp_arg, "mode", "+l");
			std::stringstream ss;
			ss << limit;
			std::string res = ss.str();
			resp_arg = find_and_replace(resp_arg, "arg", res.c_str());
			msgToAllChannel(resp_arg);
		}
		_mode.limit = limit;
	}
	else if (mode != 'o')
	{
		std::string err = find_and_replace(ERR_UNKNOWNMODE, "char", &mode);
		send(client->get_socket(), err.c_str(), err.size(), 0);
		return;
	}
}

bool Channel::isClientOpe(Client *client) const
{

	if (std::find(_operators.begin(), _operators.end(), client) != _operators.end())
		return (true);
	std::string resp = find_and_replace(ERR_CHANOPRIVSNEEDED, "channel", _name.c_str());
	send(client->get_socket(), resp.c_str(), resp.size(), 0);
	return (false);
}

void Channel::addOpe(Client *client, Client *newOpe)
{
	if (!isClientOpe(client))
		return;
	if (std::find(_clients.begin(), _clients.end(), newOpe) != _clients.end())
	{
		if (std::find(_operators.begin(), _operators.end(), newOpe) == _operators.end())
		{
			_operators.push_back(newOpe);
			std::string resp = find_and_replace(CHANGEMODEARG, "user", client->get_username().c_str());
			resp = find_and_replace(resp, "nick", client->get_nickname().c_str());
			resp = find_and_replace(resp, "channel", _name.c_str());
			resp = find_and_replace(resp, "mode", "+o");
			resp = find_and_replace(resp, "arg", newOpe->get_nickname().c_str());
			msgToAllChannel(resp);
		}
	}
	else
	{
		std::string err = find_and_replace(ERR_USERNOTINCHANNEL, "nick", newOpe->get_nickname().c_str());
		err = find_and_replace(err, "channel", _name.c_str());
		send(client->get_socket(), err.c_str(), err.size(), 0);
		return;
	}
}

void Channel::removeOpe(Client *client, Client *opeToErase)
{

	if (!isClientOpe(client))
		return;
	if (!isClientOpe(opeToErase))
		return;
	if (std::find(_clients.begin(), _clients.end(), opeToErase) != _clients.end())
	{
		std::vector<Client*>::iterator it = std::find(_operators.begin(), _operators.end(), opeToErase);
		if (it != _operators.end())
		{
			_operators.erase(it);
			std::string resp = find_and_replace(CHANGEMODEARG, "user", client->get_username().c_str());
			resp = find_and_replace(resp, "nick", client->get_nickname().c_str());
			resp = find_and_replace(resp, "channel", _name.c_str());
			resp = find_and_replace(resp, "mode", "-o");
			resp = find_and_replace(resp, "arg", opeToErase->get_nickname().c_str());
			msgToAllChannel(resp);
		}
	}
	else
	{
		std::string err = find_and_replace(ERR_USERNOTINCHANNEL, "nick", opeToErase->get_nickname().c_str());
		err = find_and_replace(err, "channel", _name.c_str());
		send(client->get_socket(), err.c_str(), err.size(), 0);
		return;
	}
}

void Channel::addClient(Client* newCli)
{
	if (std::find(_clients.begin(), _clients.end(), newCli) != _clients.end())
		return;
	if (_mode.i)
	{
		if (std::find(_invited.begin(), _invited.end(), newCli) == _invited.end())
		{
			std::string err = find_and_replace(ERR_INVITEONLYCHAN, "channel", _name.c_str());
			send(newCli->get_socket(), err.c_str(), err.size(), 0);
			return;
		}
	}
	if (_mode.limit != 0 && _mode.limit <= (long int)_clients.size())
	{
		std::string err = find_and_replace(ERR_CHANNELISFULL, "channel", _name.c_str());
		send(newCli->get_socket(), err.c_str(), err.size(), 0);
		return;
	}
	_clients.push_back(newCli);
	std::string resp = find_and_replace(RPL_JOINCHAN, "user", newCli->get_username().c_str());
	resp = find_and_replace(resp, "nick", newCli->get_nickname().c_str());
	resp = find_and_replace(resp, "channel", _name.c_str());
	msgToAllChannel(resp);
	if (_mode.i)
		_invited.erase(std::find(_invited.begin(), _invited.end(), newCli));

	std::string resp_list = find_and_replace(RPL_NAMREPLY, "nick", newCli->get_nickname().c_str());
	resp_list = find_and_replace(resp_list, "channel", _name.c_str());
	for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		std::string full_user;
		if (std::find(_operators.begin(), _operators.end(), (*it)) != _operators.end())
			full_user = "@<nick> <full_user>";
		else
			full_user = "<nick> <full_user>";
		full_user = find_and_replace(full_user, "nick", (*it)->get_nickname().c_str());
		resp_list = find_and_replace(resp_list, "full_user", full_user.c_str());
	}
	resp_list = find_and_replace(resp_list, "full_user", "");
	send(newCli->get_socket(), resp_list.c_str(), resp_list.size(), 0);

	std::string resp_end_lst = find_and_replace(RPL_ENDOFNAMES, "nick", newCli->get_nickname().c_str());
	resp_end_lst = find_and_replace(resp_end_lst, "channel", _name.c_str());
	send(newCli->get_socket(), resp_end_lst.c_str(), resp_end_lst.size(), 0);
}

void Channel::removeClient(Client *client)
{
	std::vector<Client*>::iterator it;

	it = std::find(_operators.begin(), _operators.end(), client);
	if (it != _operators.end())
		_operators.erase(it);
	it = std::find(_clients.begin(), _clients.end(), client);
	if (it != _clients.end())
	{
		_clients.erase(it);
		std::string resp = find_and_replace(RPL_QUITCHANNEL, "user", client->get_username().c_str());
		resp = find_and_replace(resp, "nick", client->get_nickname().c_str());
		resp = find_and_replace(resp, "channel", _name.c_str());
		msgToAllChannel(resp);
	}
}

void Channel::inviteClient(Client *client, Client *client_invited)
{
	if (std::find(_clients.begin(), _clients.end(), client) == _clients.end())
	{
		std::string err = find_and_replace(ERR_NOTONCHANNEL, "channel", _name.c_str());
		send(client->get_socket(), err.c_str(), err.size(), 0);
		return;
	}
	if (std::find(_clients.begin(), _clients.end(), client_invited) != _clients.end())
	{
		std::string err = find_and_replace(ERR_USERONCHANNEL, "user", client->get_username().c_str());
		err = find_and_replace(err, "channel", _name.c_str());
		send(client->get_socket(), err.c_str(), err.size(), 0);
		return;
	}
	if (std::find(_invited.begin(), _invited.end(), client_invited) == _invited.end())
		_invited.push_back(client_invited);

	std::string resp = find_and_replace(INVITCHAN, "channel", _name.c_str());
	resp = find_and_replace(resp, "user", client->get_username().c_str());
	resp = find_and_replace(resp, "nick", client->get_nickname().c_str());
	resp = find_and_replace(resp, "invited", client_invited->get_nickname().c_str());
	send(client_invited->get_socket(), resp.c_str(), resp.size(), 0);

	std::string err = find_and_replace(RPL_INVITING, "sender", client->get_nickname().c_str());  
	err = find_and_replace(err, "invited", client_invited->get_nickname().c_str());
	err = find_and_replace(err, "channel", _name.c_str());
	send(client->get_socket(), err.c_str(), err.size(), 0);
	return;
}

std::string Channel::lstMode() const
{
	std::string lstMode;

	lstMode = "+";
	if (_mode.i || _mode.t || !_mode.key.empty() || _mode.limit != 0)
	{
		if (_mode.i)
			lstMode += 'i';
		if (_mode.t)
			lstMode += 't';
		if (!_mode.key.empty())
			lstMode += 'k';
		if (_mode.limit != 0)
			lstMode += 'l';
	}
	return (lstMode);
}

bool Channel::check_if_client_in_channel(Client *client)
{
	if (std::find(_clients.begin(), _clients.end(), client) != _clients.end())
		return true;
	return false;
}

Client* Channel::find_client_by_nickname(const std::string& nickname) {
    for (Client_Iterator it = _clients.begin(); it != _clients.end(); ++it) 
	{
        if (*it && (*it)->get_nickname() == nickname) {
            return *it;
        }
    }
    return 0;
}

void Channel::sendMode(Client *client)
{
	std::string resp_mode = find_and_replace(RPL_MODECHAN, "channel", _name.c_str());
	resp_mode = find_and_replace(resp_mode, "nick", client->get_nickname().c_str());
	resp_mode = find_and_replace(resp_mode, "mode", lstMode().c_str());
	if (!lstMode().empty())
	{
		if (!_mode.key.empty())
			resp_mode = find_and_replace(resp_mode, "arg", (_mode.key + " <arg>").c_str());
		if (_mode.limit != 0)
		{
			std::stringstream ss;
			ss << _mode.limit;
			resp_mode = find_and_replace(resp_mode, "arg", (ss.str() + " <arg>").c_str());
		}
	}
	resp_mode = find_and_replace(resp_mode, "arg", "");
	send(client->get_socket(), resp_mode.c_str(), resp_mode.size(), 0);
}

std::vector<Client *> Channel::getClients() const
{
	return _clients;
}

Channel::Channel(const Channel &obj) : _name(obj._name)
{
	*this = obj;
}

Channel &Channel::operator=(const Channel &obj)
{
	_mode = obj._mode;
	_operators = obj._operators;
	for (std::vector<Client*>::const_iterator it = obj._clients.begin(); it != obj._clients.end(); ++it)
	{
		_clients.push_back(*it);
	}
	_invited = obj._invited;
	return (*this);
}

std::vector<Client *> Channel::getOpes() const
{
	return _operators;
}
