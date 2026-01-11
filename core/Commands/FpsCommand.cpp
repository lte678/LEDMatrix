//
// Created by Leon on 08/05/2025.
//

#include "FpsCommand.h"

#include <iomanip>
#include <sstream>

std::string FpsCommand::execute(std::vector<char *> params) {
    std::stringstream response;
    response << std::fixed << std::setprecision(1) << m_Matrix->getFps();
    return response.str();
}