//
// Created by Leon on 03/01/2021.
//

#ifndef MATRIX_STARTCOMMAND_H
#define MATRIX_STARTCOMMAND_H

#include "Command.h"

class StartCommand : public Command {
public:
    StartCommand(MatrixManager *matrix) : Command("start", matrix) {};
    std::string execute(std::vector<char*> params);
};


#endif //MATRIX_STARTCOMMAND_H
