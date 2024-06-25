#include "../../includes/Channel.hpp"
#include "../../includes/Server.hpp"

void	Server::handle_mode_command(Client *client, std::string& message)
{
	if (!client->get_connected())
	{
		send(client->get_socket(), ERR_NOTREGISTERED.c_str(), ERR_NOTREGISTERED.length(), 0);
		return ;
	}
	std::string name_channel    = extract_next_parameter(message, ' ');
	Channel     *channel        = find_channel(name_channel);

	if (name_channel.empty())
	{
		std::string error_msg = find_and_replace(ERR_NEEDMOREPARAMS, "command", "MODE");
		send(client->get_socket(), error_msg.c_str(), error_msg.length(), 0);
	}
	else if (channel)
	{
		std::string mod = extract_next_parameter(message, ' ');
		if (mod.empty())
			channel->sendMode(client);
		else
		{
			if (mod[0] == '+' && mod.size() > 1)
			{
				for (unsigned long i = 1; i < mod.size(); ++i)
				{
					if (mod[i] == 'i' && !channel->getMode().i)
						channel->setMode(client, 'i', 0, "");
					else if (mod[i] == 't' && !channel->getMode().t)
						channel->setMode(client, 't', 0, "");
					else if (mod[i] == 'k' && channel->getMode().key.empty())
					{
						std::string key = extract_next_parameter(message, ' ');
						if (key.empty())
						{
							std::string error_key = find_and_replace(KEY_MODE_ERROR, "nick", client->get_nickname().c_str());
							error_key = find_and_replace(error_key, "channel", channel->getName().c_str());
							send(client->get_socket(), error_key.c_str(), error_key.length(), 0);
						}
						else
							channel->setMode(client, 'k', 0, key);
					}
					else if (mod[i] == 'o')
					{
						std::string new_ope = extract_next_parameter(message, ' ');
						if (new_ope.empty())
						{
							std::string error_op = find_and_replace(OP_MODE_ERROR, "nick", client->get_nickname().c_str());
							error_op = find_and_replace(error_op, "channel", channel->getName().c_str());
							send(client->get_socket(), error_op.c_str(), error_op.length(), 0);
						}
						else
						{
							std::vector<Client *> lst_client = channel->getClients();
							for (std::vector<Client *>::iterator it = lst_client.begin(); it != lst_client.end(); ++it)
							{
								if ((*it)->get_nickname() == new_ope)
								{
									channel->addOpe(client, (*it));
									break;
								}
								std::string usernotinchan = find_and_replace(ERR_USERNOTINCHANNEL, "nick", new_ope.c_str());
								usernotinchan = find_and_replace(usernotinchan, "channel", channel->getName().c_str());
								send(client->get_socket(), usernotinchan.c_str(), usernotinchan.length(), 0);
							}
						}
					}
					else if (mod[i] == 'l')
					{
						std::string limit = extract_next_parameter(message, ' ');
						if (limit.empty())
						{
							std::string error_lim = find_and_replace(LIMIT_MODE_ERROR, "nick", client->get_nickname().c_str());
							error_lim = find_and_replace(error_lim, "channel", channel->getName().c_str());
							send(client->get_socket(), error_lim.c_str(), error_lim.length(), 0);
						}
						else
						{
							long int lim = std::strtol(limit.c_str(), NULL, 10);
							if (!(lim == 0 && channel->getMode().limit == 0))
								channel->setMode(client, 'l', lim, "");
						}
					}
				}
			}
			else if (mod[0] == '-' && mod.size() > 1)
			{
				for (unsigned long i = 1; i < mod.size(); ++i)
				{
					if (mod[i] == 'i' && channel->getMode().i)
						channel->setMode(client, 'i', 0, "");
					else if (mod[i] == 't' && channel->getMode().t)
						channel->setMode(client, 't', 0, "");
					else if (mod[i] == 'k' && !channel->getMode().key.empty())
					{
						std::string key = extract_next_parameter(message, ' ');
						if (key.empty())
						{
							std::string error_key = find_and_replace(KEY_MODE_ERROR, "nick", client->get_nickname().c_str());
							error_key = find_and_replace(error_key, "channel", channel->getName().c_str());
							send(client->get_socket(), error_key.c_str(), error_key.length(), 0);
						}
						else
							channel->setMode(client, 'k', 0, "");
					}
					else if (mod[i] == 'o')
					{
						std::string old_ope = extract_next_parameter(message, ' ');
						if (old_ope.empty())
						{
							std::string error_op = find_and_replace(OP_MODE_ERROR, "nick", client->get_nickname().c_str());
							error_op = find_and_replace(error_op, "channel", channel->getName().c_str());
							send(client->get_socket(), error_op.c_str(), error_op.length(), 0);
						}
						else
						{
							std::vector<Client *> lst_opes = channel->getOpes();
							for (std::vector<Client *>::iterator it = lst_opes.begin(); it != lst_opes.end(); ++it)
							{
								if ((*it)->get_nickname() == old_ope)
								{
									channel->removeOpe(client, (*it));
									break;
								}
								std::string usernotinchan = find_and_replace(ERR_USERNOTINCHANNEL, "nick", old_ope.c_str());
								usernotinchan = find_and_replace(usernotinchan, "channel", channel->getName().c_str());
								send(client->get_socket(), usernotinchan.c_str(), usernotinchan.length(), 0);
							}
						}
					}
					else if (mod[i] == 'l' && channel->getMode().limit != 0)
						channel->setMode(client, 'l', 0, "");
				}
			}
		}
	}
	else
	{
		std::string error_msg = find_and_replace(ERR_NOSUCHNICK, "pseudo", name_channel.c_str());
		send(client->get_socket(), error_msg.c_str(), error_msg.length(), 0);
	}
}