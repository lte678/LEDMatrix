#pragma once

#include "MatrixManager.h"
#include "TcpServer.h"

#include <thread>
#include <csignal>
#include <iostream>
// Global matrix manager context
extern MatrixManager* g_MatrixManager;
extern TcpServer* g_TcpServer;
extern std::atomic_bool g_ApplicationRunning;

static void exitapp(int exit_code) {
    g_ApplicationRunning = false;
    g_TcpServer->stop();
}