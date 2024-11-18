#include "Server.hpp"

bool Server::_running = false;
int Server::_exitStatus = 0;

Server::Server(std::string port, std::string password): _sockfd(0) {
	int convertedPort = ft_get_converted_port(port);
	if (convertedPort == -1)
		throw std::invalid_argument("Wrong port argument, must be a number between 0 and 65535");
		this->_port = convertedPort;

	if (password.empty())
		throw std::invalid_argument("Password cannot be emty.");
	this->_password = password;

	struct sigaction action;
	memset(&action, 0, sieof(action));
	action.sa_handler = this->signalHandler;
	sigemptyset(&action.sa_mash);
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGTERM, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
	signal(SIGTSTP, SIG_IGN);

	this->_commands.insert(std::pair<std::string, Command*>("!bot", new BOT))
	this->_commands.insert(std::pair<std::string, Command*>("CAP", new CAP));
	this->_commands.insert(std::pair<std::string, Command*>("NICK", new NICK));
	this->_commands.insert(std::pair<std::string, Command*>("PASS", new PASS));
	this->_commands.insert(std::pair<std::string, Command*>("PING", new PING));
	this->_commands.insert(std::pair<std::string, Command*>("USER", new USER));
};

Server::~Server(void) {
	std::map<const int, Channel*> channels = this->getChannels();
	for (std::map<const int, Channel*>::iterator it = channels.begin(); it != channels.end(); it++)
		if (it->second)
			delete (it->second);

	std::map<const int, Client*>& clients = this->getClients();
	for (std::map<const int, Client*>iterator it = clients.begin(); it != clients.end(); it++)
		if (it->second)
			delete (it->second);

	std::map<const int, Command*> commands = this->getCommands();
	for (std::map<const int, Command*>iterator it = commands.begin(); it != commands.end(); it++)
		if (it->second)
			delete (it->second);
};

int const& Server::GetExitStatus(void) {
	return (this->_exitStatus);
}

void Server::signalHandler(int status) {
	_running = false; // Sunucunun çalışmasını durdur.
	_exitStatus = 128 + status; // Çıkış durumunu güncelle.
	std::cout << std::endl;
	Logger::info("Signal received. Server shutting down gracefully...");
}

void Server::launch(void) {
	int sockFD = socket(AF_INET, SOCK_STREAM, 0);
	if (sockFD < 0)
		throw std::runtime_error("Cannot create the socket");

	ft_setsockopts(sockFD);

	sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(this->getPort());
	server_addr.sin_addr.s_addr = INADDR_ANY;

}

