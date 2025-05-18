//
// Created by leon on 10.07.18.
//

#ifndef MATRIXIFACE_SOCKETTHREADS_H
#define MATRIXIFACE_SOCKETTHREADS_H

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <cstdio>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <thread>
#include <atomic>
#include <string.h>
#include <mutex>

#include "CommandParser.h"

//TODO: Move this crap into a class
//We cant use an incomplete type in a header file, so we need to at least move it to a source file
#define MATRIXPORT 8252

std::atomic_bool socketThreadRunning(true);
std::vector<int> clients;
char const *ackMessage = "ack;";

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

// Forward declaration as a temporary solution
/*class MatrixManager {
public:
    std::string command(char *command);
};
 */

void closeConnections() {
    for(int clientfd : clients) {
        close(clientfd);
    }
}


void clientConnection(int index, CommandParser *parser) {
    char buffer[256];
    char command[256];
    std::string commandResponse;
    std::cout << "Connection opened" << buffer << std::endl;
    bool closeConnection = false;
    while(!closeConnection) {
        bzero(buffer, sizeof(buffer));
        read(clients.at(index), buffer, sizeof(buffer) - 1); //Minus 1 to avoid overriding the null terminator

        if(strcmp(buffer, "") != 0) {
            char* token;
            char* bufferPointer = buffer;
            while(true) {
                token = strsep(&bufferPointer, ";");
                strcat(command, token);
                if(bufferPointer == nullptr) {
                    break;
                }
                std::cout << "Received: " << command << std::endl;

                // We dont want any threads modifying parameters simultaneously!
                commandResponse = parser->parse(command);

                if(!commandResponse.empty()) {
                    commandResponse += ";";
                }

                send(clients.at(index), commandResponse.c_str(), strlen(commandResponse.c_str()), 0);
                send(clients.at(index), ackMessage, strlen(ackMessage), 0);

                *command = '\0';
            }
        } else {
            std::cout << "Connection closed" << buffer << std::endl;
            closeConnection = true;
        }
    }
    close(clients.at(index));
}

void socketListener(CommandParser *parser) {
    std::vector<std::thread> clientHandlers;
    int socketfd; //socket file descriptor
    sockaddr_in serverAddress, clientAddress; //Host and client addresses

    serverAddress.sin_family = AF_INET; //An internet connection
    serverAddress.sin_addr.s_addr = INADDR_ANY; //Set to host address
    serverAddress.sin_port = htons(MATRIXPORT);
    memset(&serverAddress.sin_zero, 0, sizeof(serverAddress.sin_zero));

    if((socketfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }

    int flags = fcntl(socketfd, F_GETFL);
    fcntl(socketfd, F_SETFL, flags | O_NONBLOCK);

    //if(setsockopt(serverHandle, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))

    if(bind(socketfd, (struct sockaddr*) &serverAddress, sizeof(serverAddress)) == -1) {
        perror("Failed to bind socket");
        exit(EXIT_FAILURE);
    }

    std::cout << "Matrix Server started on port " << MATRIXPORT << std::endl;

    //Wait for traffic on the socket, allow up to 5 backlogged connections
    if(listen(socketfd, 5) == -1) {
        perror("Cannot listen on socket");
        exit(EXIT_FAILURE);
    }

    while(socketThreadRunning) {
        int addressLength = sizeof(sockaddr_in);
        int clientFD = accept(socketfd, (struct sockaddr*) &clientAddress, (socklen_t*) &addressLength);

        if(clientFD == -1) {
            if(errno == EWOULDBLOCK) {
                usleep(1e5); // No inbound connections, just wait for a bit
            } else {
                perror("Error while accepting connection");
                exit(EXIT_FAILURE);
            }
        } else {
            clients.emplace_back(clientFD);
            clientHandlers.emplace_back(std::thread(clientConnection, clients.size() - 1, parser));
        }
    }
}
#pragma clang diagnostic pop

#endif
