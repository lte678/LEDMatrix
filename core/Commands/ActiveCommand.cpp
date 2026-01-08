//
// Created by Leon on 08/05/2025.
//

#include "ActiveCommand.h"

#include <sstream>

std::string ActiveCommand::execute(std::vector<char *> params) {
    std::stringstream response;
    response << m_Matrix->getRunningApp();
    return response.str();
}