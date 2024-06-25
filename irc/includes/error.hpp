#pragma once

#include <string>

/*
***** PARSING ERROR *****
*/
static const std::string ERROR_NB_ARGUMENTS = "Usage error: ./ircserv <port> <password> required";
static const std::string ERROR_PORT_VALIDITY = "Error: Invalid port format, must be an integer";
static const std::string ERROR_PORT_RANGE = "Error: Port number must be in the range [1084-49151]";
static const std::string ERROR_PASSWORD = "Error: Password length must be 4-12 characters";

/*
***** SYSCALL ERROR *****
*/
static const std::string ERR_SOCKET = "Error: Socket creation failed.";
static const std::string ERR_SELECT = "Error: Select system call failed.\n";
static const std::string ERR_FCNTL_SET = "Error: Unable to set flags with fcntl().";
static const std::string ERR_BIND = "Error: Binding server address to socket failed.";
static const std::string ERR_LISTEN = "Error: Listen operation on server socket failed.";
static const std::string ERR_ACCEPT = "Error: Accepting a new client connection failed.";

/*
***** CLIENT ERROR *****
*/
static const std::string ERR_MSG_TOO_LONG = ":IRC 300 : Message too long (512 characters max)\r\n";
static const std::string ERR_INCORRECT_PASS = ":IRC 400 : The Password is incorrect\r\n";
static const std::string ERR_NOSUCHNICK = ":IRC 401 : <pseudo> :No such nick/channel\r\n";
static const std::string ERR_NOSUCHCHANNEL = ":IRC 403 : <channel> : No such channel\r\n";
static const std::string ERR_NORECIPIENT = ":IRC 411 : No recipient given (<command>)\r\n";
static const std::string ERR_NOTEXTTOSEND = ":IRC 412 : No text to send\r\n";
static const std::string ERR_UNKNOWNCOMMAND = ":IRC 421 : <command> : Unknown command\r\n";
static const std::string ERR_NONICKNAMEGIVEN = ":IRC 431 : No nickname given\r\n";
static const std::string ERR_ERRONEUSNICKNAME = ":IRC 432 : <pseudo> : Erroneus nickname\r\n";
static const std::string ERR_NICKNAMEINUSE = ":IRC 433 * <nick> :Nickname is already in use.\r\n";
static const std::string ERR_USERNOTINCHANNEL = ":IRC 441 : <nick> <channel> :They aren't on that channel\r\n";
static const std::string ERR_NOTONCHANNEL = ":IRC 442 : <channel> :You're not on that channel\r\n";
static const std::string ERR_USERONCHANNEL = ":IRC 443 : <user> <channel> :is already on channel\r\n";
static const std::string ERR_NOTREGISTERED = ":IRC 451 :You have not registered\r\n";
static const std::string ERR_NEEDMOREPARAMS = ":IRC 461 : <command> :Not enough parameters\r\n";
static const std::string ERR_ALREADYREGISTRED = ":IRC 462 : You may not reregister\r\n";
static const std::string ERR_CHANNELISFULL = ":IRC 471 : <channel> :Cannot join channel (+l)\r\n";
static const std::string ERR_UNKNOWNMODE = ":IRC 472 : <char> :is unknown mode char to me\r\n";
static const std::string ERR_INVITEONLYCHAN = ":IRC 473 : <channel> :Cannot join channel (+i)\r\n";
static const std::string ERR_BADCHANNELKEY = ":IRC 475 : <canal> : Cannot join channel (+k)\r\n";
static const std::string ERR_CHANOPRIVSNEEDED = ":IRC 482 : <channel> :You're not channel operator\r\n";

/*
***** CLIENT RESPONSE
*/
static const std::string RPL_WELCOME = ":IRC 001 <nick> :Welcome to the Internet Relay Network <nick>!~<user>@<host>\r\n";
static const std::string RPL_YOURHOST = ":IRC 002 <nick> :Your host is IRC, running version 2.0\r\n";
static const std::string RPL_CREATED = ":IRC 003 <nick> :This server was created <date>\r\n";
static const std::string RPL_MYINFO = ":IRC 004 <nick> :IRC 1.0 <available user modes> <available channel modes>\r\n";
static const std::string RPL_PRIVMSG = ":<nick>!<user>@127.0.0.1 PRIVMSG <recipient> :<message>\r\n";
static const std::string RPL_NOTOPIC = ":IRC 331 <nick> <canal> :No topic is set\r\n";
static const std::string RPL_TOPIC = ":IRC 332 <nick> <canal> <topic>\r\n"; 
static const std::string RPL_NICK = ":<nick>!~<user>@127.0.0.1 NICK :<new_nick>\r\n";
static const std::string CHANGEMODEARG = ":<nick>!~<user>@127.0.0.1 MODE <channel> <mode> <arg>\r\n";
static const std::string CHANGEMODE = ":<nick>!~<user>@127.0.0.1 MODE <channel> :<mode>\r\n";
static const std::string KEY_MODE_ERROR = ":IRC 696 <nick> <channel> k * :You must specify a parameter for the key mode. Syntax: <key>.\r\n";
static const std::string LIMIT_MODE_ERROR = ":IRC 696 <nick> <channel> l * :You must specify a parameter for the limit mode. Syntax: <limit>.\r\n";
static const std::string OP_MODE_ERROR = ":IRC 696 <nick> <channel> o * :You must specify a parameter for the op mode. Syntax: <nick>.\r\n";
static const std::string RPL_JOINCHAN = ":<nick>!~<user>@127.0.0.1 JOIN :<channel>\r\n";
static const std::string RPL_MODECHAN = ":IRC 324 <nick> <channel> <mode> <arg>\r\n";
static const std::string RPL_NAMREPLY = ":IRC 353 <nick> = <channel> :<full_user>\r\n";
static const std::string RPL_ENDOFNAMES = ":IRC 366 <nick> <channel> :End of /NAMES list.\r\n";
static const std::string RPL_TOPIC_CHANGE = ":<nick>!~<user>@127.0.0.1 TOPIC <channel> <topic>\r\n";
static const std::string RPL_KICK = ":<nick>!~<user>@127.0.0.1 KICK <channel> <user_kick> <comment>\r\n";
static const std::string RPL_PART = ":<nick>!~<user>@127.0.0.1 PART <channel> :Leaving\r\n";
static const std::string RPL_INVITING = ":IRC 341 <sender> <invited> :<channel>\r\n";
static const std::string INVITCHAN = ":<nick>!~<user>@127.0.0.1 INVITE <invited> :<channel>\r\n";
static const std::string RPL_QUITCHANNEL = ":<nick>!~<user> QUIT :Quit: Leaving the channel <channel>\r\n";

std::string find_and_replace(const std::string &error, const char *find, const char *replace);
const std::string get_current_date();