#include "../../includes/Channel.hpp"
#include "../../includes/Server.hpp"

void	Server::handle_quit_command(Client *client, std::string& message)
{
	(void)message;
	if (!client)
		return;
	for (std::vector<Channel*>::iterator it_chan = _channels.begin(); it_chan != _channels.end();)
	{
		if (*it_chan)
			(*it_chan)->removeClient(client);
		if ((*it_chan) && (*it_chan)->getClients().size() == 0)
		{
			delete (*it_chan);
			it_chan = _channels.erase(it_chan);
		}
		else
			it_chan++;
	}
	std::cout << "Client n*" << client->get_socket() << " disconnect.\n";
	FD_CLR(client->get_socket(), &_main_set);
	remove_client(client->get_socket());
}