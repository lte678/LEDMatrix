//
// Created by Leon on 03/01/2021.
//

#include "SetCommand.h"

std::string SetCommand::execute(std::vector<char *> params) {
    std::stringstream response;
    if(params.size() != 3) {
        response << "[Error] Usage: set tree.subtree.property value" << std::endl;
    } else {
        std::istringstream property(params.at(1));
        std::string subprop;
        std::vector<std::string> subprops;
        while(std::getline(property, subprop, '.')) {
            subprops.push_back(subprop);
        }

        PropertyInterface* current = m_Matrix;
        // Enter the root id... or not, I dont care
        if(subprops.at(0) == m_Matrix->getID()) {
            subprops.erase(subprops.begin());
        }

        for(int i = 0; i < subprops.size() - 1 && current; i++) {
            current = current->getPropertyTree(subprops.at(i));
        }

        if(current && current->hasProperty(subprops.back())) {
            if(current->setProperty(subprops.back(), params.at(2))) {
                response << "Value set to " << current->getProperty(subprops.back()) << std::endl;
            } else {
                response << "[Error] Failed to set property. Is the value valid?" << std::endl;
            }
        } else {
            response << "[Error] Property not found" << std::endl;
        }
    }
    return response.str();
}