#include <iostream>
#include <cstdlib>
#include "parsing.hpp"
#include "Server.hpp"

void Server::signalhandler(int sig)
{
	(void)sig;
	_status = false;
}

void	Server::ft_set_sig(void)
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
	// Parse command line arguments (port number and password)
	int port = parse_arguments(argc, argv);
	if (port == PARSING_ERROR)
		return EXIT_FAILURE;

	try {
		// Setup server then start IRC server
		Server server(argv[2], port);
		server.start_server();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}