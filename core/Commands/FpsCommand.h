//
// Created by Leon on 18/05/2021.
//

#pragma once

#include "Command.h"

class FpsCommand : public Command {
public:
    FpsCommand(MatrixManager *matrix) : Command("fps", matrix) {};
    std::string execute(std::vector<char*> params);
};
