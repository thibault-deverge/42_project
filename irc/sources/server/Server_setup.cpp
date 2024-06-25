#include "../../includes/Server.hpp"

bool Server::_status = true;

Server::Server(const std::string& password, int port)
    : _password(password), _port(port)
{
    // Creating a socket for the server
	this->ft_set_sig();
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket == -1)
	{
		throw std::runtime_error(ERR_SOCKET);
	}

	// Allow to run programm on same port without interruptions
	int optval = 1;
	if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0) {
		throw std::runtime_error("setsockopt failed");
	}
    
    // Initializing server address structure
    std::memset((&_server_addr), 0, sizeof(_server_addr));
    _server_addr.sin_family = AF_INET;
    _server_addr.sin_port = htons(_port);
    _server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	FD_ZERO(&_main_set);
	FD_SET(_socket, &_main_set);

    set_socket_non_blocking_mode(_socket);
    bind_and_listen();

    // Initialize map for command handlers
    _commandHandler["QUIT"] = &Server::handle_quit_command;
    _commandHandler["PASS"] = &Server::handle_pass_command;
    _commandHandler["USER"] = &Server::handle_user_command;
    _commandHandler["NICK"] = &Server::handle_nick_command;
    _commandHandler["JOIN"] = &Server::handle_join_command;
    _commandHandler["MODE"] = &Server::handle_mode_command;
    _commandHandler["PRIVMSG"] = &Server::handle_privmsg_command;
    _commandHandler["TOPIC"] = &Server::handle_topic_command;
    _commandHandler["KICK"] = &Server::handle_kick_command;
    _commandHandler["INVITE"] = &Server::handle_invite_command;
    _commandHandler["PART"] = &Server::handle_part_command;
}


Server::~Server()
{
	for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		close((*it)->get_socket());
		delete (*it);
	}

	for (std::vector<Channel*>::iterator it = _channels.begin(); it != _channels.end(); it++)
		delete *it;

	close(_socket);
}

void Server::set_socket_non_blocking_mode(int socket) const
{
    if (fcntl(socket, F_SETFL, O_NONBLOCK) == -1)
    {
        close(socket);
        throw std::runtime_error(ERR_FCNTL_SET);
    }
}

void Server::bind_and_listen() const
{
    // Binding the server socket to the server address
    if (bind(_socket, (const sockaddr*)&_server_addr, sizeof(_server_addr)) == -1)
    {
        close(_socket);
        throw std::runtime_error(ERR_BIND);
    }

    // Setting the server socket in listen mode to maximum number of connections possible (SOMAXCONN)
    if (listen(_socket, SOMAXCONN) == -1)
    {
        close(_socket);
        throw std::runtime_error(ERR_LISTEN);
    }
}