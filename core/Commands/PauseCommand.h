//
// Created by Leon on 03/01/2021.
//

#ifndef MATRIX_PAUSECOMMAND_H
#define MATRIX_PAUSECOMMAND_H

#include "Command.h"

class PauseCommand : public Command {
public:
    PauseCommand(MatrixManager *matrix) : Command("pause", matrix) {};
    std::string execute(std::vector<char*> params);
};


#endif //MATRIX_PAUSECOMMAND_H
