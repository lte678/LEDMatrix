//
// Created by Leon on 03/01/2021.
//

#ifndef MATRIX_COMMAND_H
#define MATRIX_COMMAND_H

#include <string>
#include <vector>

class Command {
public:
    explicit Command(std::string _identifier) : identifier(std::move(_identifier)) {};
    std::string identifier;
    virtual std::string execute(std::vector<char*> params) = 0;
};

#endif //MATRIX_COMMAND_H
