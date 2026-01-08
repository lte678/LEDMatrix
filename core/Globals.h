#pragma once

#include "MatrixManager.h"

// Global matrix manager context
extern MatrixManager* g_MatrixManager;

static void exitapp(int exit_code) {
    if(g_MatrixManager) {
        (*g_MatrixManager).stop();
    }
}