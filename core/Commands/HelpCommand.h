//
// Created by Leon on 08/05/2025.
//

#pragma once

#include "Command.h"

class CommandParser;

class HelpCommand : public Command {
private:
    CommandParser *m_CommandParser;
public:
    HelpCommand(CommandParser *parser) : Command("help"), m_CommandParser(parser) {};
    std::string execute(std::vector<char*> params) override;
};
