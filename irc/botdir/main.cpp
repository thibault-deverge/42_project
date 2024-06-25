#include "../includes/Bot.hpp"

void Bot::signalhandler(int sig)
{
	(void)sig;
	_status = false;
}

void	Bot::ft_set_sig(void)
{
	struct sigaction	sa;

	sa.sa_handler = signalhandler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		exit(0);
}

int main(int argc, char **argv)
{
	int port = parse_arguments(argc, argv);
	if (port == PARSING_ERROR)
		return (EXIT_FAILURE);

	try {
		Bot bot(port, argv[2], argv[3]);

		bot.ft_set_sig();
		bot.run_bot();
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}