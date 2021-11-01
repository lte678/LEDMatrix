//
// Created by Leon on 04/01/2021.
//

#include "ResetCommand.h"

std::string ResetCommand::execute(std::vector<char *> params) {
    std::stringstream response;
    m_Matrix->resetApp();
    return response.str();
}