#include "../../includes/Server.hpp"

Client* Server::get_client_by_socket(int socket)
{
    for (size_t i = 0; i < _clients.size(); ++i)
    {
        if (_clients[i] && _clients[i]->get_socket() == socket)
            return _clients[i];
    }
	return NULL;
}

Client* Server::get_client_by_socket_ptr(int socket)
{
	for (size_t i = 0; i < _clients.size(); ++i)
	{
		if (_clients[i] && _clients[i]->get_socket() == socket)
			return (_clients[i]);
	}
	return NULL;
}

void Server::remove_client(int socket)
{
	for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); it++)
    {
        if (*it && (*it)->get_socket() == socket)
        {
            close((*it)->get_socket());
            delete *it;
            _clients.erase(it);
			break;
        }
    }
}

std::string Server::extract_next_parameter(std::string& message, char delimiter) const
{
	size_t end_parameter = message.find(delimiter);
	std::string		tmp;

	if (end_parameter != std::string::npos)
	{
		std::string parameter = message.substr(0, end_parameter);
		size_t erase_len = message.find_first_not_of(delimiter, end_parameter);
		message.erase(0, erase_len);

		return parameter;
	}
	end_parameter = message.find('\r');
	tmp = message.substr(0, end_parameter);
	message.erase(0, end_parameter);
	return tmp;
}

std::string find_and_replace(const std::string &error, const char *find, const char *replace)
{
	if (!find || !replace)
		return error;
	std::string new_error = error;
	std::string find_str(static_cast<std::string>("<") + static_cast<std::string>(find) + static_cast<std::string>(">"));
	new_error.replace(error.find(find_str), find_str.size(), replace);
	return (new_error);
}

const std::string get_current_date() {
    std::time_t now = std::time(0);
    std::tm *ltm = std::localtime(&now);

    std::ostringstream oss;
    oss << 1900 + ltm->tm_year << '-'
        << 1 + ltm->tm_mon << '-'
        << ltm->tm_mday << ' '
        << ltm->tm_hour << ':'
        << ltm->tm_min << ':'
        << ltm->tm_sec;

    return oss.str();
}

std::vector<Channel*>::iterator Server::find_channel_iterator(const std::string &channel_name)
{
	for (std::vector<Channel*>::iterator it = _channels.begin(); it != _channels.end(); ++it)
	{
		if ((*it) && !((*it)->getName().compare(channel_name)))
			return it;
	}
	return _channels.end();
}

std::vector<Client*>::iterator Server::find_client_iterator(const std::string &client_name)
{
	for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		if ((*it) && !((*it)->get_nickname().compare(client_name)))
			return it;
	}
	return _clients.end();
}

void Server::msg_to_all_client(const std::string &message)
{
	for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		if (*it)
			send((*it)->get_socket(), message.c_str(), message.size(), 0);
	}
}