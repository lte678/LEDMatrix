//
// Created by leon on 20.05.19.
//

#include "CommandParser.h"

#include "Commands/ListCommand.h"
#include "Commands/StartCommand.h"
#include "Commands/StopCommand.h"
#include "Commands/PauseCommand.h"
#include "Commands/SetCommand.h"
#include "Commands/AppsCommand.h"
#include "Commands/UnpauseCommand.h"
#include "Commands/ResetCommand.h"
#include "Commands/ActiveCommand.h"
#include "Commands/FpsCommand.h"
#include "Commands/HelpCommand.h"

#include <cstring>
#include <memory>

CommandParser::CommandParser(MatrixManager *matrix) : m_PropTree("root"), m_Matrix(matrix) {
    m_PropTree.registerPropTree(matrix);
    registerCommand(std::make_unique<ListCommand>(matrix));
    registerCommand(std::make_unique<StartCommand>(matrix));
    registerCommand(std::make_unique<StopCommand>(matrix));
    registerCommand(std::make_unique<PauseCommand>(matrix));
    registerCommand(std::make_unique<SetCommand>(matrix));
    registerCommand(std::make_unique<AppsCommand>(matrix));
    registerCommand(std::make_unique<ActiveCommand>(matrix));
    registerCommand(std::make_unique<UnpauseCommand>(matrix));
    registerCommand(std::make_unique<ResetCommand>(matrix));
    registerCommand(std::make_unique<FpsCommand>(matrix));
    registerCommand(std::make_unique<HelpCommand>(this));
}

std::string CommandParser::parse(char* command) {
    // Extract all tokens from the command string
    std::vector<char*> tokens;
    char* token;
    while(true) {
        token = strsep(&command, "%");
        if(token == nullptr)
            break;
        tokens.push_back(token);
    }

    // Iterate over all registered commands to find a match
    std::string response;
    bool commandExecuted = false;
    for(const std::unique_ptr<Command>& cmd : m_Commands) {
        if(strcmp(tokens.at(0), cmd->identifier.c_str()) == 0) {
            // Matching command found
            response = cmd->execute(tokens);
            commandExecuted = true;
        }
    }

    if(!commandExecuted) {
        // No matching command was found!
        response = "[Error] Invalid command!";
    }

    // Return the command output
    return response;
}

std::vector<std::string> CommandParser::getCommandList() const {
    std::vector<std::string> commandList;
    for (const auto& cmd : m_Commands) {
        commandList.push_back(cmd->identifier);
    }
    return commandList;
}
