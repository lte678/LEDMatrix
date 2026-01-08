//
// Created by Leon on 04/01/2021.
//

#include "AppsCommand.h"

#include <sstream>

std::string AppsCommand::execute(std::vector<char *> params) {
    std::stringstream response;
    std::vector<std::string> apps = m_Matrix->getAppNames();
    for(const std::string& app : apps) {
        response << " - " << app << std::endl;
    }
    return response.str();
}