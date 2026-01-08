//
// Created by Leon on 18/05/2021.
//

#pragma once

#include "Command.h"

class ActiveCommand : public Command {
public:
    ActiveCommand(MatrixManager *matrix) : Command("active", matrix) {};
    std::string execute(std::vector<char*> params);
};
