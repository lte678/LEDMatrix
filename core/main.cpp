#include <thread>
#include <unistd.h>
#include <signal.h>
#include <cstring>

#include "TcpServer.h"
#include "MatrixManager.h"
#include "CommandParser.h"
#include "ServiceUtils.h"
#include "Globals.h"
#ifdef USE_SOFTWARE_MATRIX
#include "SoftwareMatrix.h"
#else
#include "MatrixDefines.h"
#include "HardwareMatrix.h"
#endif

std::thread socketListenerThread;


void termHandler(int signum, siginfo_t *info, void *ptr) {
    exitapp(1);
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

    std::string appPath = "/usr/local/share/matrix/apps/";
    if(argc > 1) {
        appPath = argv[1];
    }

#ifdef USE_SOFTWARE_MATRIX
    auto matrix = std::make_unique<SoftwareMatrix>();
#else
    auto matrix = std::make_unique<HardwareMatrix>(GPIO_PIN);
#endif
    g_MatrixManager = new MatrixManager(std::move(matrix), appPath);

    CommandParser commandParser(g_MatrixManager);

    catchSigterm();

    g_TcpServer = new TcpServer();
    std::thread tcpServerThread = std::thread([&](){ g_TcpServer->listenThread(&commandParser); });
    g_MatrixManager->matrixLoop();

    tcpServerThread.join();
    return EXIT_SUCCESS;
}



