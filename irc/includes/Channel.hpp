#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include "Client.hpp"
#include "Server.hpp"

class Client;
class Server;

typedef struct	s_mode {
	bool			i;
	bool			t;
	std::string		topic;
	std::string		key;
	long int		limit;
}				t_mode;

class Channel
{
	private:
		typedef std::vector<Client*>::iterator Client_Iterator;

		const std::string			_name;
		t_mode						_mode;
		std::vector<Client*>		_operators;
		std::vector<Client*>		_clients;
		std::vector<Client*>		_invited;

	public:
		Channel(const std::string& name, Client *ope, const std::string key);
		~Channel();
		Channel(const Channel& obj);
		Channel &operator=(const Channel&obj);

//		Utils
		const std::string			getName() const;
		std::vector<Client*>		getClients() const;
		std::vector<Client*>		getOpes() const;
		t_mode						getMode() const;
		std::string					lstMode() const;
		std::string 				getKey() const;
		std::string 				getTopic() const;
		void						msgToChannel(const std::string& msg, int sender_socket);
		void						msgToAllChannel(std::string msg);
		void						setMode(Client *client, char mode, long int limit, std::string key_or_topic);
		void						setTopic(const std::string& new_topic);
		bool						check_if_client_in_channel(Client	*client);
		Client*						find_client_by_nickname(const std::string& nickname);
		void						sendMode(Client *client);

//		Handling operators
		void				addOpe(Client *client, Client *newOpe);
		void				removeOpe(Client *client, Client *opeToErase);
		bool				isClientOpe(Client *client) const;

//		Handling client
		void				addClient(Client *newCli);
		void				removeClient(Client *client);
		void				inviteClient(Client *client, Client *client_invited);

};
