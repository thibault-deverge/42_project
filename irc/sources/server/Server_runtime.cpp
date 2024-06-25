#include "../../includes/Server.hpp"

int Server::start_server()
{
    fd_set  temp_set;
    int     max_fd_so_far = _socket + 1;

    while (_status)
    {
        temp_set = _main_set;

        if (select(max_fd_so_far, &temp_set, 0, 0, 0) == -1)
        {
			if (!_status)
				break;
            perror("error:");
            throw std::runtime_error(ERR_SELECT);
        }

        for (int i = 0; i <= max_fd_so_far; ++i)
		{
            if (FD_ISSET(i, &temp_set))
            {
                if (i == _socket)
                {
                    int client_socket = accept_new_connection();
                    FD_SET(client_socket, &_main_set);
                    if (client_socket + 1 > max_fd_so_far)
                        max_fd_so_far = client_socket + 1;
                }
                else
                    handle_existing_connection(i);
            }
        }
    }
    return 0;
}

int Server::accept_new_connection()
{
    struct sockaddr_in  client_address;
    socklen_t           client_address_len = sizeof(client_address);
    int                 client_socket;

    client_socket = accept(_socket, (struct sockaddr*)&client_address, &client_address_len);
    if (client_socket == -1)
		throw std::runtime_error(ERR_ACCEPT);
	std::cout << "New connection on socket n*" << client_socket << "." << std::endl;
    set_socket_non_blocking_mode(client_socket);
    Client *client = new Client(client_socket);
    _clients.push_back(client);
    return client_socket;
}

void Server::handle_existing_connection(int client_socket)
{
	char		buffer[2000];
	int			n_bytes;
	std::string	incoming_data;
	std::string	single_msg;
	std::string	incomplete_msg;

	n_bytes = recv(client_socket, buffer, sizeof(buffer), 0);
	if (n_bytes > 0)
	{
		Client* client = get_client_by_socket(client_socket);
		buffer[n_bytes] = 0;
		incoming_data = buffer;
		incomplete_msg = client->get_message();

		if (!incomplete_msg.empty())
		{
			client->clear_buffer();
			incoming_data = incomplete_msg + incoming_data;
		}
		while (incoming_data.find("\r\n") != std::string::npos)
		{
			single_msg = incoming_data.substr(0, incoming_data.find("\r\n"));
			incoming_data = incoming_data.erase(0, incoming_data.find("\r\n") + 2);
			if (single_msg.length() > 512)
				send(client_socket, ERR_MSG_TOO_LONG.c_str(), ERR_MSG_TOO_LONG.length(), 0);
			else
			{
				process_message(client, single_msg);
				if (!client)
					return;
			}
		}
		if (!incoming_data.empty())
			client->append_data(incoming_data);
	}
	else if (n_bytes <= 0)
	{
		std::string str;
		handle_quit_command(get_client_by_socket(client_socket), str);
	}
}

void Server::process_message(Client* client, std::string& message)
{
	std::string command = extract_next_parameter(message, ' ');

	if (!client)
		return;
	Map_Iterator it = _commandHandler.find(command);
    if (it != _commandHandler.end())
    {
        CommandHandler handler = it->second;
        (this->*handler)(client, message);
		if (command == "QUIT")
			return;
		if (!client->get_connected() && client->get_password() && !client->get_nickname().empty() && !client->get_username().empty())
			connect_to_server(client);
    }
    else
    {
		if (command == "WHO" || command == "CAP")
			return;
		std::string error_msg = find_and_replace(ERR_UNKNOWNCOMMAND, "command", command.c_str());
		send(client->get_socket(), error_msg.c_str(), error_msg.length(), 0);
		client->clear_complete_message();
    }
}

void Server::connect_to_server(Client *client)
{
	if (!client)
		return;
	client->set_connected(true);

	std::string welcome = find_and_replace(RPL_WELCOME, "nick", client->get_nickname().c_str());
	welcome = find_and_replace(welcome, "nick", client->get_nickname().c_str());
	welcome = find_and_replace(welcome, "user", client->get_username().c_str());
	welcome = find_and_replace(welcome, "host", "127.0.0.1");
	send(client->get_socket(), welcome.c_str(), welcome.size(), 0);

	std::string host = find_and_replace(RPL_YOURHOST, "nick", client->get_nickname().c_str());
	send(client->get_socket(), host.c_str(), host.size(), 0);

	std::string date = get_current_date();
	std::string created = find_and_replace(RPL_CREATED, "nick", client->get_nickname().c_str());
	created = find_and_replace(created, "date", date.c_str());
	send(client->get_socket(), created.c_str(), created.size(), 0);

	std::string myinfo = find_and_replace(RPL_MYINFO, "nick", client->get_nickname().c_str());
	myinfo = find_and_replace(myinfo, "available user modes", "");
	myinfo = find_and_replace(myinfo, "available channel modes", "");
	send(client->get_socket(), myinfo.c_str(), myinfo.size(), 0);
}