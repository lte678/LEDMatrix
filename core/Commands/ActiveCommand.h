//
// Created by Leon on 18/05/2021.
//

#pragma once

#include "Command.h"
#include "../MatrixManager.h"

class ActiveCommand : public Command {
private:
    MatrixManager *m_Matrix;
public:
    ActiveCommand(MatrixManager *matrix) : Command("active"), m_Matrix(matrix) {};
    std::string execute(std::vector<char*> params);
};
