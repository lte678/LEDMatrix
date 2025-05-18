#ifndef MATRIXIFACE_COMMANDPARSER_H
#define MATRIXIFACE_COMMANDPARSER_H

#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <utility>
#include <vector>
#include <memory>

#include "MatrixManager.h"
#include "property/Property.h"
#include "Commands/Command.h"
#include "Commands/ListCommand.h"
#include "Commands/StartCommand.h"
#include "Commands/StopCommand.h"
#include "Commands/PauseCommand.h"
#include "Commands/SetCommand.h"
#include "Commands/AppsCommand.h"
#include "Commands/UnpauseCommand.h"
#include "Commands/ResetCommand.h"

//class MatrixManager;

class CommandParser {
private:
    PropertyInterface m_PropTree;
    MatrixManager *m_Matrix;
    std::vector<std::unique_ptr<Command>> m_Commands;

    void registerCommand(std::unique_ptr<Command> comm) { m_Commands.push_back(std::move(comm)); }
public:
    CommandParser(MatrixManager *matrix);

    std::string parse(char *command);
};

#endif
