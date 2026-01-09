//
// Created by leon on 15.07.18.
//

#ifndef MATRIXIFACE_SCROLLTEXT_H
#define MATRIXIFACE_SCROLLTEXT_H


#include "MatrixApp.h"
#include "MatrixDefines.h"

#include <cstdlib>
#include "ubuntufont.h"

#define CHARACTER_TRIM 1 //Amount to trim characters, since there is a lot of white space

struct Character {
    char character;
    int width;
    int height;
    u_char* data;

    ~Character() { free(data); }
};

class ScrollTextApp : public MatrixApp {
public:
    ScrollTextApp(matrix_t *inMatrix);
    ~ScrollTextApp() { if (scrollText != nullptr) free(scrollText); }

    void initApp() override;
    void drawFrame(float dt) override;
private:
    Character getCharacter(char character);
    int scrollIndex = 0;
    float scrollIndexCounter = 0.0f;
    u_char* scrollText;

    int charWidth, charHeight;
    int stringWidth;

    FloatProperty m_ScrollSpeed;
    TextProperty m_ScrollText;
    IntProperty m_Spaces;
};


extern "C" MatrixApp* create(matrix_t *inMatrix) {
    return new ScrollTextApp(inMatrix);
}

extern "C" void destroy(MatrixApp* app) {
    delete app;
}


#endif //MATRIXIFACE_SCROLLTEXT_H
