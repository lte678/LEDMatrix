#include <memory>
#include <thread>
#include <unistd.h>
#include <signal.h>
#include <cstring>

#include "MatrixDefines.h"
#include "socketThreads.h"
//#include "matrixThread.h"
#include "HardwareMatrix.h"
#include "MatrixManager.h"
#include "CommandParser.h"
#include "ServiceUtils.h"

std::thread socketListenerThread;

MatrixManager* g_MatrixManager;

void termSocketListener() {
    socketThreadRunning = false;
    closeConnections();
    socketListenerThread.join();
}

void termHandler(int signum, siginfo_t *info, void *ptr) {
    if(g_MatrixManager) {
        (*g_MatrixManager).stop();
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

    g_MatrixManager = new MatrixManager(
        std::make_unique<HardwareMatrix>(GPIO_PIN)
    );

    CommandParser commandParser(g_MatrixManager);

    catchSigterm();

    socketListenerThread = std::thread(&socketListener, &commandParser);
    (*g_MatrixManager).matrixLoop();

    termSocketListener();
    return EXIT_SUCCESS;
}



