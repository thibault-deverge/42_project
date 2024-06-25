#include "../includes/Bot.hpp"

bool Bot::_status = true;

/* ***** CONSTRUCTOR/DESTRUCTOR ***** */
Bot::Bot(int port, const std::string& nickname, const std::string& password)
    : _port(port), _nickname(nickname), _password(password), _connected(false)
{
    _sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(_sockfd == -1)
        throw std::runtime_error(ERR_SOCKET);

    bzero(&_servaddr, sizeof(_servaddr));
	_servaddr.sin_family = AF_INET;
	_servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	_servaddr.sin_port = htons(_port);

	if (connect(_sockfd, reinterpret_cast<struct sockaddr*>(&_servaddr), sizeof(_servaddr)) == -1)
        throw std::runtime_error(ERR_CONNECT);

    _authentication = "PASS " + _password + "\r\n";
    _authentication += "NICK " + _nickname + "\r\n";
    _authentication += "USER " + _nickname + "\r\n";

    _welcome = find_and_replace(MSG_AUTHENTICATION, "nick", _nickname.c_str());
    _welcome = find_and_replace(_welcome, "nick", _nickname.c_str());
    _welcome = find_and_replace(_welcome, "user", _nickname.c_str());

    // User choices
    _user_choices.push_back("rock");
    _user_choices.push_back("paper");
    _user_choices.push_back("scissors");

    // All choices including 'black hole' for the bot
    _all_choices.push_back("rock");
    _all_choices.push_back("paper");
    _all_choices.push_back("scissors");
    _all_choices.push_back("black hole");

    srand(static_cast<unsigned int>(time(NULL)));
	send(_sockfd, _authentication.c_str(), _authentication.size(), 0);
}

Bot::~Bot()
{
    close(_sockfd);
}

/* ***** Main function ***** */

void    Bot::run_bot()
{
    char buf[1024];
	std::string incoming_data;
	std::string single_msg;

    while (_status)
	{
		int n_bytes = recv(_sockfd, &buf, 1024, 0);
		if (n_bytes <= 0)
			return;
		buf[n_bytes] = 0;

		incoming_data = buf;
		while (incoming_data.find("\r\n") != std::string::npos)
		{
			single_msg = incoming_data.substr(0, incoming_data.find("\r\n"));
 			incoming_data = incoming_data.erase(0, incoming_data.find("\r\n") + 2);

			if (_connected)
			{
				if (test_path_regex(regex_pat, single_msg.c_str()))
				{
					std::string raw_msg = single_msg;
					std::string sender = get_sender_nickname(raw_msg);
					size_t find;

					find = raw_msg.find(':', 1);
					if (find != std::string::npos)
					{
						std::string msg = raw_msg.substr(find + 1);
						process_message(msg, sender);
					}
				}
			}
			else if (!single_msg.compare(_welcome))
				_connected = true;
			else if (!single_msg.empty())
			{
				//std::cout << single_msg << std::endl;
				throw std::runtime_error(ERR_AUTHENTICATION);
			}
		}
	}
}

void    Bot::process_message(std::string& message, const std::string& sender)
{
    std::string user_choice;

    for (size_t i = 0; i < message.size(); ++i)
        user_choice += tolower(message[i]);

    if (std::find(_user_choices.begin(), _user_choices.end(), user_choice) == _user_choices.end()) 
    {
        std::string invalid_choice_msg = "PRIVMSG " + sender + RPL_INVALID_CHOICE;
        send(_sockfd, invalid_choice_msg.c_str(), invalid_choice_msg.size(), 0);
        return;
    } 

    std::string bot_choice = _all_choices[rand() % 4];

    std::string result;
    if (user_choice == bot_choice) 
        result = "It's a draw, lol!";
    else if (check_game(user_choice, bot_choice)) 
        result = "You win but you're playing 2vs1 with the luck s*cker!";
    else
        result = "You lose motherf*cker!";

    std::string response = "PRIVMSG " + sender + " :You chose " + user_choice + ", I chose " + bot_choice + ". " + result + "\r\n";
    send(_sockfd, response.c_str(), response.size(), 0);
}

bool    Bot::check_game(const std::string& user_choice, const std::string& bot_choice)
{
    if (user_choice == "rock" && bot_choice == "scissors")
        return true;
    if (user_choice == "paper" && bot_choice == "rock")
        return true;
    if (user_choice == "scissors" && bot_choice == "paper")
        return true;
    return false;
}

std::string Bot::get_sender_nickname(const std::string& message)
{
    size_t end_of_nickname = message.find('!');

    std::string nickname = message.substr(1, end_of_nickname - 1);
    return nickname;
}