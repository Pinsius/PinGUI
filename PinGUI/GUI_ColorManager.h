#ifndef GUI_COLORMANAGER_H
#define GUI_COLORMANAGER_H

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

#include <SDL2/SDL.h>

#define COLOR_NUM 2

/**
    Defined colors
**/

#define CLIPBOARD_NORMAL_COLOR_R  255;
#define CLIPBOARD_NORMAL_COLOR_G  255;
#define CLIPBOARD_NORMAL_COLOR_B  255;
#define CLIPBOARD_NORMAL_COLOR_A  255;

#define CLIPBOARD_ON_AIM_COLOR_R  200;
#define CLIPBOARD_ON_AIM_COLOR_G  200;
#define CLIPBOARD_ON_AIM_COLOR_B  255;
#define CLIPBOARD_ON_AIM_COLOR_A  255;


enum colorType{
    CLIPBOARD_NCOLOR,
    CLIPBOARD_TCOLOR
};

class GUI_ColorManager{
    private:
        static SDL_Color _COLORS[COLOR_NUM];
    public:
        static void initColors();

        static void changeColor(SDL_Color color, colorType type);

        static SDL_Color getColor(colorType type);
};

#endif // GUI_COLORMANAGER_H
