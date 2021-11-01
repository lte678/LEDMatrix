//
// Created by Leon on 03/01/2021.
//

#include "ListCommand.h"

std::string ListCommand::execute(std::vector<char *> params) {
    std::stringstream response;
    printProperties(m_Matrix, response, 0);
    return response.str();
}

void ListCommand::printProperties(PropertyInterface* propertyInterface, std::ostream &printStream, unsigned int depth) {
    if(depth > 10) {
        printStream << "[Error] Max tree depth reached!" << std::endl;
        return;
    }

    std::string spacing(depth * 4, ' ');

    printStream << spacing << propertyInterface->getID() << std::endl;

    for(const std::string &id : propertyInterface->getProperties()) {
        printStream << spacing << "    -" << id << ": " << propertyInterface->getProperty(id) << std::endl;
    }

    for(PropertyInterface *interface : propertyInterface->getPropertyTrees()) {
        printProperties(interface, printStream, depth + 1);
    }
}
