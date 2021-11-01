//
// Created by Leon on 03/01/2021.
//

#ifndef MATRIX_STOPCOMMAND_H
#define MATRIX_STOPCOMMAND_H

#include "Command.h"

class StopCommand : public Command {
public:
    StopCommand(MatrixManager *matrix) : Command("stop", matrix) {};
    std::string execute(std::vector<char*> params);
};


#endif //MATRIX_STOPCOMMAND_H
