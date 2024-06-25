#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <cstring>
#include <sstream>
#include <arpa/inet.h>
#include <cstdlib>
#include <ctime>
#include <regex.h>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <signal.h>

static const std::string ERROR_NB_ARGUMENTS     = "Usage error: ./bot <port> <name> <password> required";
static const std::string ERROR_PORT_VALIDITY    = "Error: Invalid port format, must be an integer";
static const std::string ERROR_PORT_RANGE       = "Error: Port number must be in the range [1084-49151]";
static const std::string ERROR_PASSWORD         = "Error: Password length must be 4-12 characters";
static const std::string ERR_SOCKET             = "Error: Socket creation failed.";
static const std::string ERR_CONNECT            = "Error: Connection to server failed.";
static const std::string ERR_AUTHENTICATION     = "Error: Authentication to server failed.\n";
static const std::string MSG_AUTHENTICATION     = ":IRC 001 <nick> :Welcome to the Internet Relay Network <nick>!~<user>@127.0.0.1";
static const std::string RPL_INVALID_CHOICE     = " :Please choose rock, paper, or scissors.\r\n";
static const char *regex_pat                    = "^\\:.+\\!.+\\@127\\.0\\.0\\.1\\ PRIVMSG";

static const int PARSING_ERROR = -1;
static const int MIN_PORT = 1084;
static const int MAX_PORT = 49151;



class Bot 
{
    private:
        std::vector<std::string>   _user_choices;
        std::vector<std::string>   _all_choices;
        struct sockaddr_in         _servaddr;
        int                        _port;
        int                        _sockfd;
        std::string                _nickname;
        std::string                _password;
        std::string                _authentication;
        std::string                _welcome;
		bool					   _connected;
		static bool				   _status;

        std::string get_sender_nickname(const std::string& message);
        void        process_message(std::string& message, const std::string& sender);
        bool        check_game(const std::string& user_choice, const std::string& bot_choice);
		static void	signalhandler(int sig);

    public:
        Bot(int port, const std::string& nickname, const std::string& password);
        ~Bot();

		void	ft_set_sig(void);
        void	run_bot();
};

int         parse_arguments(int argc, char **argv);
int         parse_port(const std::string& port_str);
bool        parse_password(const std::string& password);
std::string find_and_replace(const std::string &error, const char *find, const char *replace);
bool	    test_path_regex(const char *pat, const char *str);
