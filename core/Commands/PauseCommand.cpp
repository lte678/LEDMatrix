//
// Created by Leon on 03/01/2021.
//

#include "PauseCommand.h"

#include <sstream>

std::string PauseCommand::execute(std::vector<char *> params) {
    std::stringstream response;
    m_Matrix->pause();
    return response.str();
}