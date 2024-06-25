#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <exception>
#include <sstream>
#include <cstring>
#include <cstdio>
#include <ctime>
#include <cerrno>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <fcntl.h>
#include "Client.hpp"
#include "error.hpp"
#include "Channel.hpp"
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>

class Channel;
class Client;

class Server
{
	private:
		typedef void (Server::*CommandHandler)(Client*, std::string&);
		typedef std::map<std::string, CommandHandler>::iterator Map_Iterator;
		typedef std::vector<Channel*>::iterator					Channel_Iterator;
		typedef std::vector<Client*>::iterator 					Client_Iterator;

		std::map<std::string, CommandHandler>	_commandHandler;
		std::vector<Channel*>					_channels;
		std::vector<Client*>					_clients;
		struct sockaddr_in						_server_addr;
		std::string								_password;
		int										_port;
		int										_socket;
		fd_set 									_main_set;
		static bool								_status;

		// Setup Server
		void   		set_socket_non_blocking_mode(int socket) const;
		void    	bind_and_listen() const;

    	// Handle connections
    	int			accept_new_connection();
    	void    	handle_existing_connection(int client_socket);
    	void		process_message(Client* client, std::string& message);
		void		connect_to_server(Client *client);

		// Commands
		void		handle_pass_command(Client* client, std::string& message);
		void		handle_nick_command(Client* client, std::string& message);
		bool		is_nickname_already_taken(const std::string& new_nickname) const;
		void 		handle_user_command(Client* client, std::string& message);
		bool 		is_username_already_taken(const std::string& new_username);
		void		handle_quit_command(Client* client, std::string& message);
		void		handle_mode_command(Client* client, std::string& message);
		void		handle_who_command(Client* client, std::string& message);
		void		handle_join_command(Client* client, std::string& message);
		void 		verify_key_join(Client* client, Channel* channel, std::string& message);
		bool		is_valid_channel_name(const std::string& channel_name) const;
		Channel*	find_channel(const std::string& channel_name);
		void		handle_privmsg_command(Client* client, std::string& message);
		void		handle_topic_command(Client *client, std::string& message);
		void		handle_kick_command(Client *client, std::string& message);
		void		handle_part_command(Client* client, std::string& message);
		void		handle_invite_command(Client* client, std::string& message);

		// Helper functions
		Client*				get_client_by_socket(int socket);
		Client*				get_client_by_socket_ptr(int socket);
		void				remove_client(int socket);
        std::string			extract_next_parameter(std::string& message, char delimiter) const;
		Channel_Iterator 	find_channel_iterator(const std::string &channel_name);
		Client_Iterator		find_client_iterator(const std::string &client_name);
		void				msg_to_all_client(const std::string &message);
		void				ft_set_sig(void);
		static void			signalhandler(int sig);


	public:
		Server(const std::string& password, int port);
		~Server();

		int start_server();
};