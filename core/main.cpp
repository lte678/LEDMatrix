#include <iostream>
#include <thread>
#include <unistd.h>
#include <signal.h>
#include <cstring>

#include "MatrixDefines.h"
#include "socketThreads.h"
//#include "matrixThread.h"
#include "MatrixManager.h"
#include "CommandParser.h"
#include "ServiceUtils.h"

std::thread socketListenerThread;

MatrixManager* g_Matrix;

void termSocketListener() {
    socketThreadRunning = false;
    closeConnections();
    socketListenerThread.join();
}

void termHandler(int signum, siginfo_t *info, void *ptr) {
    if(g_Matrix) {
        (*g_Matrix).stop();
    }
}

void catchSigterm() {
    static struct sigaction _sigact;
    memset(&_sigact, 0, sizeof(_sigact));
    _sigact.sa_sigaction = termHandler;
    _sigact.sa_flags = SA_SIGINFO;

    sigaction(SIGTERM, &_sigact, nullptr); //Interrupt with service stop
    sigaction(SIGINT, &_sigact, nullptr); //Interrupt with ctrl-c

}

int main(int argc, char *argv[]) {
    if(serviceRunning()) {
        printf("Service already running!\n");
        return EXIT_FAILURE;
    }

    g_Matrix = new MatrixManager(GPIO_PIN);

    CommandParser commandParser(g_Matrix);

    catchSigterm();

    socketListenerThread = std::thread(&socketListener, &commandParser);
    (*g_Matrix).matrixLoop();

    termSocketListener();
    return EXIT_SUCCESS;
}



