//
// Created by Leon on 04/01/2021.
//

#ifndef MATRIX_APPSCOMMAND_H
#define MATRIX_APPSCOMMAND_H

#include "Command.h"

class AppsCommand : public Command {
public:
    AppsCommand(MatrixManager *matrix) : Command("apps", matrix) {};
    std::string execute(std::vector<char*> params);
};


#endif //MATRIX_APPSCOMMAND_H
