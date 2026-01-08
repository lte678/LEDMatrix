//
// Created by leon on 10.07.18.
//

#include "TcpServer.h"

#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <cstdio>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <thread>
#include <string.h>

#include "CommandParser.h"
#include "Globals.h"

constexpr int MATRIXPORT = 8252;
constexpr const char *ACK_MESSAGE = "ack;";


void clientConnection(int fd, CommandParser *parser) {
    char buffer[256];
    char command[256];
    std::string commandResponse;
    std::cout << "Connection opened" << buffer << std::endl;
    
    bool closeConnection = false;
    while(!closeConnection) {
        bzero(buffer, sizeof(buffer));
        read(fd, buffer, sizeof(buffer) - 1); //Minus 1 to avoid overriding the null terminator
        
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

                send(fd, commandResponse.c_str(), strlen(commandResponse.c_str()), 0);
                send(fd, ACK_MESSAGE, strlen(ACK_MESSAGE), 0);

                *command = '\0';
            }
        } else {
            closeConnection = true;
        }
    }
    close(fd);
    std::cout << "Connection closed" << buffer << std::endl;
}

void TcpServer::listenThread(CommandParser *parser) {
    sockaddr_in serverAddress, clientAddress; //Host and client addresses

    serverAddress.sin_family = AF_INET; //An internet connection
    serverAddress.sin_addr.s_addr = INADDR_ANY; //Set to host address
    serverAddress.sin_port = htons(MATRIXPORT);
    memset(&serverAddress.sin_zero, 0, sizeof(serverAddress.sin_zero));

    if((m_SocketFd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Failed to create socket");
        exitapp(EXIT_FAILURE);
        return;
    }

    
    const int enable = 1;
    if(setsockopt(m_SocketFd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) < 0) {
        perror("Failed to set socket opt");
        exitapp(EXIT_FAILURE);
        return;
    }
    
    if(bind(m_SocketFd, (struct sockaddr*) &serverAddress, sizeof(serverAddress)) == -1) {
        perror("Failed to bind socket");
        exitapp(EXIT_FAILURE);
        return;
    }

    std::cout << "Matrix Server started on port " << MATRIXPORT << std::endl;

    //Wait for traffic on the socket, allow up to 5 backlogged connections
    if(listen(m_SocketFd, 5) == -1) {
        perror("Cannot listen on socket");
        exitapp(EXIT_FAILURE);
        return;
    }

    while(g_ApplicationRunning) {
        int addressLength = sizeof(sockaddr_in);
        int clientFd = accept(m_SocketFd, (struct sockaddr*) &clientAddress, (socklen_t*) &addressLength);

        if(clientFd == -1) {
            if(errno != EINTR && errno != ECONNABORTED && errno != EINVAL) {
                perror("Error while accepting connection");
                exitapp(EXIT_FAILURE);
                return;
            }
        } else {
            clientFds.emplace_back(clientFd);
            clientHandlers.emplace_back(std::thread(clientConnection, clientFd, parser));
        }
    }

    close(m_SocketFd);

    // The client handlers must be joined here to avoid them being terminated in an uncontrolled manner.
    for(auto& clientConn : clientHandlers) {
        clientConn.join();
    }
}
