#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <cctype>
#include <Channel.hpp>

class Server;
class Channel;

class Client 
{
	private:
		std::string     		_msg_buffer;
		std::string				_nickname;
		std::string				_username;
		bool					_password;
		bool					_connected;
		int             		_socket;

	public:
		std::vector<Channel*>	_channels;

		Client(int socket);
		Client(const Client &obj);
		Client &operator=(const Client &obj);
		~Client();
		bool operator==(const Client &obj);

		// Receive message into server
		std::string extract_complete_message();
		void        append_data(std::string data);
		void        clear_complete_message();
		bool        is_complete_data() const;
		void		clear_buffer();

		// Getters
		int					get_socket() const;
		std::string			get_username() const;
		std::string			get_nickname() const;
		std::string			get_message() const;
		bool				get_password() const;
		bool				get_connected()	const;

		// Setters
		void			set_nickname(const std::string& new_nickname);
		void			set_username(const std::string& new_username);
		void			set_password(const bool password_status);
		void			set_connected(const bool connected_status);
};