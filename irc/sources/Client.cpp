#include "../includes/Client.hpp"

Client::Client(int socket)
    : _password(false), _connected(false), _socket(socket) {
	_channels.clear();
}

Client::~Client()
{

}

bool Client::operator==(const Client &obj)
{
	if (_socket == obj._socket && _nickname == obj._nickname && _username == obj._username)
		return (true);
	return (false);
}

void Client::append_data(std::string data)
{
	_msg_buffer += data;
}

bool Client::is_complete_data() const
{
    size_t end_pos = _msg_buffer.find("\r\n");
    if (end_pos != std::string::npos)
        return true;
    return false;
}

std::string Client::extract_complete_message()
{
    size_t end_msg = _msg_buffer.find("\r\n");

    if (end_msg != std::string::npos)
    {
		std::stringstream iss(_msg_buffer);
        std::string complete_msg;
        std::getline(iss, complete_msg, '\n');
        _msg_buffer.erase(0, end_msg + 2);
        return complete_msg;
    }
    return "";
}

void Client::clear_complete_message()
{
    // Return position of '\r\n'
    size_t end_msg = _msg_buffer.find("\r\n");

    if (end_msg != std::string::npos)
        _msg_buffer.erase(0, end_msg + 2);
}

int Client::get_socket() const { return _socket; }
std::string Client::get_username() const { return _username; }
std::string Client::get_nickname() const { return _nickname; }
bool Client::get_connected() const { return _connected; }
bool Client::get_password() const { return _password; }

void Client::set_nickname(const std::string& new_nickname)
{
    _nickname = new_nickname;
}

void Client::set_username(const std::string &new_username)
{
	_username = new_username;
}

void Client::set_connected(const bool connected_status)
{
	_connected = connected_status;
}

void Client::set_password(const bool password_status)
{
	_password = password_status;
}

std::string Client::get_message() const
{
	return (_msg_buffer);
}

void		Client::clear_buffer()
{
	_msg_buffer = "";
}

Client::Client(const Client &obj)
{
	*this = obj;
}

Client &Client::operator=(const Client &obj)
{
	if (&obj != this)
	{
		_msg_buffer = obj._msg_buffer;
		_socket = obj._socket;
		_nickname = obj._nickname;
		_username = obj._username;
		_connected = obj._connected;
		_password = obj._password;
		for (std::vector<Channel*>::const_iterator it = obj._channels.begin(); it != obj._channels.end(); ++it)
		{
			_channels.push_back(*it);
		}
	}
	return (*this);
}
