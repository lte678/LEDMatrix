//
// Created by Leon on 03/01/2021.
//

#include "StartCommand.h"

std::string StartCommand::execute(std::vector<char *> params) {
    std::stringstream response;
    if(params.size() != 2) {
        response << "[Error] Incorrect number of parameters.";
        return response.str();
    }

    if(m_Matrix->hasApp(params.at(1))) {
        m_Matrix->resetApp();
        m_Matrix->setApp(params.at(1));
        m_Matrix->unpause();
    } else {
        response << "[Error] App " <<  std::string(params.at(1))  << " not loaded.";
    }
    return response.str();
}
