//
// Created by leon on 07.05.19.
//

#include "MatrixManager.h"

MatrixManager::MatrixManager(int gpioPin)
    : m_Matrix(), m_MatrixData(), m_ResetQueued(), m_DrawPaused(), m_Running(true), m_ActiveApp(),
    m_Brightness("brightness", 150), PropertyInterface("matrix") {

    m_Matrix.freq = WS2811_TARGET_FREQ;
    m_Matrix.dmanum = 10;

    ws2811_channel_t mainChannel = {};
    mainChannel.gpionum = gpioPin;
    mainChannel.count = LED_COUNT;
    mainChannel.invert = 0;
    mainChannel.brightness = 255;
    mainChannel.strip_type = SK6812_STRIP_RGBW;

    ws2811_channel_t unused = {};
    unused.gpionum = 0;
    unused.count = 0;
    unused.invert = 0;
    unused.brightness = 0;

    m_Matrix.channel[0] = mainChannel;
    m_Matrix.channel[1] = unused;

    ws2811_return_t returnVal = ws2811_init(&m_Matrix);
    if(returnVal != WS2811_SUCCESS) {
        perror("Failed to initialize LED matrix");
        exit(1);
    }

    registerProperty(&m_Brightness);
}

void MatrixManager::stopMatrix() {
    clearMatrix();
    renderMatrix();

    ws2811_fini(&m_Matrix);
}

//std::string MatrixManager::command(char *command) {
//   return m_CommandProcessor.parse(command);
//}

//void MatrixManager::setBrightness(int brightness) {
//    m_Brightness = brightness;
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

            currentModule.instance = currentModule.constructor(&m_MatrixData);

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

int MatrixManager::matrixToStrip(int x, int y) {
    x = LED_WIDTH - (x + 1);
    int index = LED_HEIGHT * x;
    if(x % 2 == 0) {
        index += y;
    } else {
        index += (LED_HEIGHT - 1) - y;
    }
    return index;
}

void MatrixManager::clearMatrix() {
    for (auto &column : m_MatrixData) {
        for (auto &cell : column) {
            cell = 0;
        }
    }
}

void MatrixManager::renderMatrix() {
    for (int i = 0; i < LED_WIDTH; i++) {
        for (int j = 0; j < LED_HEIGHT; j++) {
            m_Matrix.channel[0].leds[matrixToStrip(i, j)] = m_MatrixData[i][j].data;
        }
    }

    ws2811_return_t returnVal;
    returnVal = ws2811_render(&m_Matrix);
    if(returnVal != WS2811_SUCCESS) {
        perror("Failed to render image");
    }
}

void MatrixManager::matrixLoop() {
    loadApps("/usr/local/share/matrix/apps/");

    if(m_Modules.empty()) {
        std::cerr << "Failed to load any apps!" << std::endl;
        exit(1);
    }
    std::cout << "Starting matrix draw loop" << std::endl;

    m_ActiveApp = m_Modules.at(0).instance;
    (*m_ActiveApp).initApp();

    int counter = 0;
    clearMatrix();

    while(m_Running) {
        m_Matrix.channel[0].brightness = (unsigned char)(int)m_Brightness; //We can only cast to int, so cast twice

        if(m_ResetQueued) {
            clearMatrix();
            for(const Module &mod : m_Modules) {
                if(mod.instance == m_ActiveApp) {
                    (*m_ActiveApp).initApp();
                }
            }
            counter = 0;
            m_ResetQueued = false;
        }

        if(!m_DrawPaused) {
            (*m_ActiveApp).drawFrame(1.0f / (*m_ActiveApp).getFrameRate());
            counter++;
        }

        renderMatrix();

        usleep(1e6 / (*m_ActiveApp).getFrameRate());
    }

    stopMatrix();
    unloadApps();
}
