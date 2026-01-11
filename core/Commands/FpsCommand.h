//
// Created by Leon on 18/05/2021.
//

#pragma once

#include "Command.h"
#include "../MatrixManager.h"

class FpsCommand : public Command {
private:
    MatrixManager *m_Matrix;
public:
    FpsCommand(MatrixManager *matrix) : Command("fps"), m_Matrix(matrix) {};
    std::string execute(std::vector<char*> params);
};
