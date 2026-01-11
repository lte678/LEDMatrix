//
// Created by leon on 07.05.19.
//

#ifndef MATRIX_CORE_MATRIXMANAGER_H
#define MATRIX_CORE_MATRIXMANAGER_H


#include <atomic>
#include <dlfcn.h>
#include <dirent.h>
#include <mutex>
#include <memory>

#include "property/Property.h"
#include "MatrixDefines.h"
#include "Matrix.h"
#include "MatrixApp.h"
#include "FpsCounter.h"


class MatrixManager : public PropertyInterface {
//TODO: Look at scope of member functions (private/public)
public:
    MatrixManager(std::unique_ptr<Matrix> display, std::string appPath);
    //~MatrixManager();

    void loadApps(const std::string &moduleDir);

    void pause() { m_DrawPaused = true; };
    void unpause() { m_DrawPaused = false; };
    
    void resetApp() { m_ResetQueued = true; };
    void setApp(std::string appName);
    bool hasApp(std::string appName) const;
    std::string getRunningApp() const;
    void stopApp();
    std::vector<std::string> getAppNames() const;

    float getFps() const { return m_FpsCounter.get_fps(); }

    void matrixLoop();

private:
    void stopMatrix();
    void unloadApps();
    void clearMatrix();

private:
    struct Module {
        std::string name;
        void* modulePointer;
        MatrixApp::createApp* constructor;
        MatrixApp::destroyApp* destructor;

        MatrixApp* instance;
    };

    std::unique_ptr<Matrix> m_Display;
    matrix_t m_Canvas;
    matrix_t m_FreezeFrame;
    float m_FadeIn;

    std::string m_AppPath;
    std::vector<Module> m_Modules;

    // All values that are modifiable from other threads
    std::atomic<bool> m_ResetQueued;
    std::atomic<bool> m_DrawPaused;
    std::mutex m_BrightnessLock;
    std::atomic<MatrixApp*> m_ActiveApp;
    FpsCounter m_FpsCounter;

    IntProperty m_Brightness;
    FloatProperty m_CrossfadeTime;
};

#endif //MATRIX_CORE_MATRIXMANAGER_H
