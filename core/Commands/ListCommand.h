//
// Created by Leon on 03/01/2021.
//

#ifndef MATRIX_LISTCOMMAND_H
#define MATRIX_LISTCOMMAND_H

#include "Command.h"
#include "../MatrixManager.h"

class ListCommand : public Command {
private:
    MatrixManager *m_Matrix;
public:
    ListCommand(MatrixManager *matrix) : Command("list"), m_Matrix(matrix) {};
    std::string execute(std::vector<char*> params);
    static void printProperties(PropertyInterface *propertyInterface, std::ostream &printStream, unsigned int depth = 0);
};


#endif //MATRIX_LISTCOMMAND_H
