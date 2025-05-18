//
// Created by leon on 07.05.19.
//

#ifndef MATRIX_CORE_MATRIXMANAGER_H
#define MATRIX_CORE_MATRIXMANAGER_H


#include <iostream>
#include <atomic>
#include <dlfcn.h>
#include <dirent.h>
#include <mutex>

#include "property/Property.h"
#include "MatrixDefines.h"
//#include "CommandParser.h"
#include "MatrixApp.h"

class MatrixManager : public PropertyInterface {
//TODO: Look at scope of member functions (private/public)
public:
    explicit MatrixManager(int gpioPin);
    //~MatrixManager();

    void loadApps(const std::string &moduleDir);

    void stop() { m_Running = false; };
    void resetApp() { m_ResetQueued = true; };
    void pause() { m_DrawPaused = true; };
    void unpause() { m_DrawPaused = false; };

    void setApp(std::string appName);
    bool hasApp(std::string appName) const;
    std::vector<std::string> getAppNames() const;


    std::string command(char *command);

    //void setBrightness(int brightness);

    void matrixLoop();

    //int getModuleIndex(char* name);
private:
    void stopMatrix();
    void unloadApps();
    void renderMatrix();
    void clearMatrix();
    static int matrixToStrip(int x, int y);

private:
    struct Module {
        std::string name;
        void* modulePointer;
        MatrixApp::createApp* constructor;
        MatrixApp::destroyApp* destructor;

        MatrixApp* instance;
    };

    ws2811_t m_Matrix;
    matrix_t m_MatrixData;

    std::vector<Module> m_Modules;

    // All values that are modifiable from other threads
    std::atomic<bool> m_ResetQueued;
    std::atomic<bool> m_DrawPaused;
    std::atomic<bool> m_Running;
    std::mutex m_BrightnessLock;
    std::atomic<MatrixApp*> m_ActiveApp;

    IntProperty m_Brightness;
};


#endif //MATRIX_CORE_MATRIXMANAGER_H
