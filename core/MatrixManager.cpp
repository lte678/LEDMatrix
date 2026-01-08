//
// Created by leon on 07.05.19.
//

#include "MatrixManager.h"
#include "Globals.h"

#include <iostream>
#include <unistd.h>


MatrixManager::MatrixManager(std::unique_ptr<Matrix> display, std::string appPath)
    : m_Display(std::move(display)), m_AppPath(appPath), m_Canvas(), m_FreezeFrame(), m_FadeIn(1.0f),
    m_ResetQueued(), m_DrawPaused(), m_ActiveApp(), m_Brightness("brightness", 150), m_CrossfadeTime("crossfade", 0.2), PropertyInterface("matrix") {

    registerProperty(&m_Brightness);
    registerProperty(&m_CrossfadeTime);

    if (!m_Display->init()) {
        perror("Failed to initialize display");
        exitapp(1);
        return;
    }
}

void MatrixManager::stopMatrix() {
    clearMatrix();
    m_Display->render(m_Canvas);
    m_Display->shutdown();
}

//std::string MatrixManager::command(char *command) {
//   return m_CommandProcessor.parse(command);
//}

//Dieser Codeabschnitt wurde mit (wahrscheinlci0jh) >0,5 Promille geschrieben (um 02:00 morgens)
void MatrixManager::loadApps(const std::string &moduleDir) {
    std::string modulePrefix = "app";
    std::string moduleSuffix = ".so";

    DIR *moduleDirHandle;
    dirent *moduleFileHandle;
    std::vector<std::string> moduleFullNames;

    if((moduleDirHandle = opendir(moduleDir.c_str())) != nullptr) {
        while((moduleFileHandle = readdir(moduleDirHandle)) != nullptr) {
            if(std::string(moduleFileHandle->d_name).compare(0,modulePrefix.length(),modulePrefix) == 0) {
                //std::cout << module->d_name << std::endl;
                moduleFullNames.emplace_back(std::string(moduleFileHandle->d_name));
            }
        }
    } else {
        std::cerr << "Could not open module directory!" << std::endl;
    }

    for(const std::string &moduleName : moduleFullNames) {
        void* moduleHandle = dlopen((moduleDir + moduleName).c_str(), RTLD_NOW);
        if(moduleHandle == nullptr) {
            std::cerr << "Failed to load " << moduleName << std::endl;
            std::cerr << dlerror() << std::endl;
        } else {
            Module currentModule;
            currentModule.name = moduleName.substr(modulePrefix.length(), (moduleName.length() - modulePrefix.length()) - moduleSuffix.length());
            currentModule.modulePointer = moduleHandle;

            currentModule.constructor = (MatrixApp::createApp*) dlsym(moduleHandle, "create");
            currentModule.destructor = (MatrixApp::destroyApp*) dlsym(moduleHandle, "destroy");

            currentModule.instance = currentModule.constructor(&m_Canvas);

            registerPropTree(currentModule.instance);

            m_Modules.push_back(currentModule);
        }
    }
}
//Und hier ist der Spass zu Ende :(

void MatrixManager::unloadApps() {
    for(const Module &currentModule : m_Modules) {
        currentModule.destructor(currentModule.instance);
        dlclose(currentModule.modulePointer);
    }
}

/*
int MatrixManager::getModuleIndex(std::string appName) {
    for(int i = 0; i < m_Modules.size(); i++) {
        if(m_Modules.at(i).name == appName) {
            return i;
        }
    }
    return -1;
}
*/

void MatrixManager::setApp(std::string appName) {
    for(const Module &mod : m_Modules) {
        if(mod.name == appName) m_ActiveApp = mod.instance;
        (*m_ActiveApp).initApp();
    }

    matrix_t blendedFrame;
    blend_frames(blendedFrame, m_FadeIn, m_FreezeFrame, m_Canvas);
    copy_frame(m_FreezeFrame, blendedFrame);
    clearMatrix();
    m_FadeIn = 0.0f;
}

bool MatrixManager::hasApp(std::string appName) const {
    for(const Module &mod : m_Modules) {
        if(mod.name == appName) return true;
    }
    return false;
}

std::vector<std::string> MatrixManager::getAppNames() const {
    std::vector<std::string> appNames;

    for(const Module &mod : m_Modules) {
        appNames.push_back(mod.name);
    }

    return appNames;
}

void MatrixManager::clearMatrix() {
    for (auto &column : m_Canvas) {
        for (auto &cell : column) {
            cell = 0;
        }
    }
}

void MatrixManager::matrixLoop() {
    loadApps(m_AppPath);

    if(m_Modules.empty()) {
        std::cerr << "Failed to load any apps at " << m_AppPath << std::endl;
        exitapp(1);
        return;
    }
    std::cout << "Starting matrix draw loop" << std::endl;

    m_ActiveApp = m_Modules.at(0).instance;
    (*m_ActiveApp).initApp();

    clearMatrix();

    matrix_t blendedFrame;
    float frameTime;
    while(g_ApplicationRunning) {
        m_Display->setBrightness((uint8_t)m_Brightness.getValue());

        
        if(m_ResetQueued) {
            clearMatrix();
            for(const Module &mod : m_Modules) {
                if(mod.instance == m_ActiveApp) {
                    (*m_ActiveApp).initApp();
                }
            }
            m_ResetQueued = false;
        }
        
        frameTime = 1.0f / (*m_ActiveApp).getFrameRate();
        if(!m_DrawPaused) {
            (*m_ActiveApp).drawFrame(frameTime);
            m_FadeIn = std::min(1.0f, m_FadeIn + frameTime/m_CrossfadeTime.getValue());
        }

        blend_frames(blendedFrame, m_FadeIn, m_FreezeFrame, m_Canvas);
        m_Display->render(blendedFrame);
        usleep(1e6 * frameTime);
    }

    stopMatrix();
    unloadApps();
}
