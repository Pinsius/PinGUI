#ifndef STUFF_H
#define STUFF_H

/**

    PinGUI

    Copyright (c) 2017 Lubomir Barantal <l.pinsius@gmail.com>

    This software is provided 'as-is', without any express or implied
    warranty. In no event will the authors be held liable for any damages
    arising from the use of this software.

    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute it
    freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
       claim that you wrote the original software. If you use this software
       in a product, an acknowledgment in the product documentation would be
       appreciated but is not required.
    2. Altered source versions must be plainly marked as such, and must not be
       misrepresented as being the original software.
    3. This notice may not be removed or altered from any source distribution.

**/
#define BLANK "Blank"

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <memory>

#include "GL_Vertex.h"

class textInfo{
public:
    textInfo(TTF_Font* Font,SDL_Color Color):
        font(Font),
        color(Color)
        {
        }; 

    textInfo(){};

    ~textInfo(){
		TTF_CloseFont(font);
    }

    TTF_Font* font;  
    SDL_Color color;
};

struct vboData{
    PinGUI::Vertex vertices[6];
};

/**
    Class for storing data for VBO´s (normal VBO and instances)
**/
class BufferData{
public:
    std::vector<vboData> vboDATA;
};

/**
    Enum for different clipboards
**/
enum clipboard_type{
    NORMAL,
	ADJUSTABLE,
    INT_ONLY,
    INT_FLOAT,
    UNCLICKABLE
};

enum element_shape{
    ROUNDED,
    RECTANGLED 
};

enum windowElementType
{
	NONE,
	MOVER_ONLY,
	EXIT_ONLY,
	BOTH
};

namespace PinGUI{

    enum gameState{
        GAME,
        GUI
    };

    enum inputState{
        GAMEINPUT,
        WRITINGMOD,
        MANIPULATINGMOD
    };

    enum manipulationState{
        HORIZONTAL,
        VERTICAL,
        WINDOW_MOVING
    };

    struct writingModInfo{
        clipboard_type inputType;
        int max;
        int maxValue;
        int minValue;
        bool negativeInput;
    };

    struct manipulatingModInfo{
		int lastX;
		int lastY;
        manipulationState manipState;
    };
}

#endif // STUFF_H
