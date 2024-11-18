#pragma once

#include "Command.hpp"

class BOT: public Command {
public:
	BOT(void);
	virtual ~BOT(void);
	virtual void run(Client* client, Channel* channel, std::vector<std::string> params);
};
