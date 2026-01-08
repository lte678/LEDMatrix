//
// Created by Leon on 03/01/2021.
//

#include "StopCommand.h"

#include <sstream>

std::string StopCommand::execute(std::vector<char *> params) {
    std::stringstream response;
    m_Matrix->stopApp();
    return response.str();
}