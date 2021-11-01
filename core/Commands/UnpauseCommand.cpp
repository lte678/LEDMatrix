//
// Created by Leon on 04/01/2021.
//

#include "UnpauseCommand.h"

std::string UnpauseCommand::execute(std::vector<char *> params) {
    std::stringstream response;
    m_Matrix->unpause();
    return response.str();
}