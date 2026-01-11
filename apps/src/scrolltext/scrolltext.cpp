//
// Created by leon on 15.07.18.
//

#include "scrolltext.h"

ScrollTextApp::ScrollTextApp(matrix_t *inMatrix) : MatrixApp(inMatrix, "scrolltext"),
    m_ScrollSpeed("scrollspeed", 8),
    m_ScrollText("scrolltext", "LEON IS AWESOME"),
    m_Spaces("spaces", 5) {

    registerProperty(&m_ScrollSpeed);
    registerProperty(&m_ScrollText);
    registerProperty(&m_Spaces);
}

void ScrollTextApp::initApp() {
    charWidth = getCharacter('X').width;
    charHeight = getCharacter('X').height;
    stringWidth = (int)((m_Spaces + m_ScrollText.length()) * charWidth);
    scrollText = (u_char*)malloc(stringWidth * charHeight * sizeof(u_char));

    std::string displayString = std::string(m_Spaces,' ') + (std::string)m_ScrollText;
    for(int i = 0; i < (int)displayString.length(); i++) {
        Character currentChar = getCharacter(displayString.at(i));
        for(int y = 0; y < charHeight; y++) {
            for(int x = 0; x < charWidth; x++) {
                scrollText[i * charWidth + x + stringWidth * y] = currentChar.data[x + charWidth * y];
                //std::cout << currentChar.data[x + charWidth * y];
            }
        }
    }
}

void ScrollTextApp::drawFrame(float dt) {
    clearMatrix(m_Matrix);

    int ypos = 5;
    for(int y = 0; y < charHeight; y++) {
        for(int x = 0; x < LED_WIDTH; x++) {
            int xIndex = (scrollIndex + x) % stringWidth;
            if(scrollText[xIndex + stringWidth * y] != 0) {
                (*m_Matrix)[x][y + ypos].g = 200;
                (*m_Matrix)[x][y + ypos].b = 200;
            }
        }
    }

    scrollIndexCounter += dt * m_ScrollSpeed;
    if(scrollIndexCounter > 1.0f) {
        scrollIndexCounter--;
        scrollIndex++;
    }
}

Character ScrollTextApp::getCharacter(char character) {
    Character returnChar;

    returnChar.character = character;
    int xMin = fontUbuntuCharSet.chars[character].x - 1;
    int yMin = fontUbuntuCharSet.chars[character].y + 1;
    int xMax = xMin + fontUbuntuCharSet.charWidth;
    int yMax = yMin + fontUbuntuCharSet.charBaseHeight - 1;

    returnChar.width = xMax - xMin;
    returnChar.height = yMax - yMin;

    returnChar.data = (u_char*)malloc(returnChar.width * returnChar.height);

    for(int y = 0; y < returnChar.height; y++) {
        for(int x = 0; x < returnChar.width; x++) {
            /*
            if((int)fontUbuntuBitmap[fontUbuntuCharSet.bitmapWidth * (y) + x] == 255) {
                std::cout << "*";
            } else {
                std::cout << " ";
            }
            */
            returnChar.data[returnChar.width * y + x] = fontUbuntuBitmap[fontUbuntuCharSet.bitmapWidth * ((returnChar.height - (y + 1)) + yMin) + (x + xMin)];
        }
        //std::cout << std::endl;
    }



    return returnChar;
}
