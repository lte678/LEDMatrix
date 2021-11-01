//
// Created by Leon on 03/01/2021.
//

#include "StopCommand.h"

std::string StopCommand::execute(std::vector<char *> params) {
    std::stringstream response;
    m_Matrix->pause();
    m_Matrix->resetApp();
    return response.str();
}