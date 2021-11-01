//
// Created by Leon on 03/01/2021.
//

#ifndef MATRIX_SETCOMMAND_H
#define MATRIX_SETCOMMAND_H

#include "Command.h"

class SetCommand : public Command {
public:
    SetCommand(MatrixManager *matrix) : Command("set", matrix) {};
    std::string execute(std::vector<char*> params);
};



#endif //MATRIX_SETCOMMAND_H
