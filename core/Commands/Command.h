//
// Created by Leon on 03/01/2021.
//

#ifndef MATRIX_COMMAND_H
#define MATRIX_COMMAND_H

#include <string>
#include <vector>
#include <sstream>

#include "../MatrixManager.h"
#include "property/Property.h"

class Command {
public:
    explicit Command(std::string _identifier, MatrixManager *matrix) : identifier(std::move(_identifier)), m_Matrix(matrix) {};
    std::string identifier;
    MatrixManager *m_Matrix;
    virtual std::string execute(std::vector<char*> params) = 0;
};

#endif //MATRIX_COMMAND_H
