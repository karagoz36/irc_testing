#include "utils.hpp"
#include "Server.hpp"

int	main(int ac, char **av) {
	if (argc != 3) {
		Logger::error("Bad number of arguments, ./ircserv [PORT] [PASSWORD]");
		return (1);
	}

	std::string port = argv[1];
	std::string password = argv[2];

	try {
		srand(static_cast<unsigned int>(time(NULL)));
		Server IRC_Server = Server(port, password);
		IRC_Server.launch();
		return (IRC_Server.getExitStatus());
	} catch (std::exception const& err) {
		Logger::error(err.what());
		return (1);
	};

	return (0);
};
