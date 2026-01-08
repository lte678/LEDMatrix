#pragma once

#include "CommandParser.h"

#include <thread>
#include <mutex>
#include <sys/socket.h>

class TcpServer {
private:
    int m_SocketFd = -1;
    std::vector<std::thread> clientHandlers;
    std::vector<int> clientFds;
public:
    void listenThread(CommandParser *parser);

    void stop() {
        // Shutdown the listening socket to unblock accept()
        if (m_SocketFd != -1) {
            shutdown(m_SocketFd, SHUT_RDWR);
        }
        
        // Shutdown all client sockets to unblock read() (should be behind mutex)
        for (int fd : clientFds) {
            shutdown(fd, SHUT_RDWR);
        }
    }
};