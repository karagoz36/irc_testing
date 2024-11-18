#pragma once

#include <string>
#include <signal.h>
#include <cstring>
#include <poll.h>
#include <sstream>
#include <map>
#include <vector>
#include <ctime>

#include "Client.hpp"
#include "Channel.hpp"
#include "utils.hpp"

#include "BOT.hpp"
#include "CAP.hpp"
#include "NICK.hpp"
#include "PASS.hpp"
#include "PING.hpp"

#define MAX_CLIENTS 100
#define BUFFER_SIZE 1024

class Command;

class Servers {
private:
	int			_sockfd;
	int			_port;
	std::string	_password;
	static bool	_running;
	static int	_exitStatus;

	std::map<const int, Channel*>	_channels;
	std::map<const int, Client*>	_clients;
	std::map<std::string, Command*>	_commands;

public:
	Server(std::String port, std::string password);
	~Server(void);

	void addChannel(Channel* channel);
	void addClient(Client* client);
	void rmChannel(int channelId);
	void rmClient(int clientId);

	int const& getSockFD(void);
	int const& getPort(void);
	std::string const& getPassword(void);
	bool const& isRunning(void);
	int const& getExitStatus(void);
	std::map<const int, Channel*>& getChannels(void);
	std::map<const int, Client*>& getClients(void);
	std::map<std::string, Command*>& getCommands(void);

	Channel* getChannelById(int channelId);
	Client* getClientById(int clientId);
	Client* getClientByNickName(std::string nickname);
	Command* getCommandByName(std::string name);
	Channel* getChannelByName(std::string name);

	static void signalHandler(int status);

	void launch(void);
	void sendMessage(std::string message);
};

void Server::signalHandler(int status) {
	_running = false; // Sunucunun çalışmasını durdur.
	_exitStatus = 128 + status; // Çıkış durumunu güncelle.
	std::cout << std::endl;
	Logger::info("Signal received. Server shutting down gracefully...");
}


# include "Command.hpp"
