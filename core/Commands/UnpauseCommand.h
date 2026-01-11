//
// Created by Leon on 04/01/2021.
//

#ifndef MATRIX_UNPAUSECOMMAND_H
#define MATRIX_UNPAUSECOMMAND_H

#include "Command.h"
#include "../MatrixManager.h"

class UnpauseCommand : public Command {
private:
    MatrixManager *m_Matrix;
public:
    UnpauseCommand(MatrixManager *matrix) : Command("unpause"), m_Matrix(matrix) {};
    std::string execute(std::vector<char*> params);
};


#endif //MATRIX_UNPAUSECOMMAND_H
