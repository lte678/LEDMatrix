//
// Created by Leon on 04/01/2021.
//

#ifndef MATRIX_RESETCOMMAND_H
#define MATRIX_RESETCOMMAND_H


#include "Command.h"

class ResetCommand : public Command {
public:
    ResetCommand(MatrixManager *matrix) : Command("reset", matrix) {};
    std::string execute(std::vector<char*> params);
};


#endif //MATRIX_RESETCOMMAND_H
