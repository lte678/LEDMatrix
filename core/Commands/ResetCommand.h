//
// Created by Leon on 04/01/2021.
//

#ifndef MATRIX_RESETCOMMAND_H
#define MATRIX_RESETCOMMAND_H


#include "Command.h"
#include "../MatrixManager.h"

class ResetCommand : public Command {
private:
    MatrixManager *m_Matrix;
public:
    ResetCommand(MatrixManager *matrix) : Command("reset"), m_Matrix(matrix) {};
    std::string execute(std::vector<char*> params);
};


#endif //MATRIX_RESETCOMMAND_H
