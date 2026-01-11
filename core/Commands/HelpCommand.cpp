//
// Created by Leon on 08/05/2025.
//

#include "HelpCommand.h"
#include "../CommandParser.h"
#include <sstream>

std::string HelpCommand::execute(std::vector<char *> params) {
    std::stringstream response;
    response << "Available commands:\n";
    
    std::vector<std::string> commands = m_CommandParser->getCommandList();
    for (const auto& cmd : commands) {
        response << "  - " << cmd << "\n";
    }
    
    return response.str();
}
