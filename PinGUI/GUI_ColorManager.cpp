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

#include "GUI_ColorManager.h"

SDL_Color GUI_ColorManager::_COLORS[COLOR_NUM];

void GUI_ColorManager::initColors(){

    SDL_Color tmpColor;

    /*************************CLIPBOARDS*************************/
    //Normal color
    tmpColor.r = CLIPBOARD_NORMAL_COLOR_R;
    tmpColor.g = CLIPBOARD_NORMAL_COLOR_G;
    tmpColor.b = CLIPBOARD_NORMAL_COLOR_B;
    tmpColor.a = CLIPBOARD_NORMAL_COLOR_A;
    GUI_ColorManager::changeColor(tmpColor,CLIPBOARD_NCOLOR);

    //Target color
    tmpColor.r = CLIPBOARD_ON_AIM_COLOR_R;
    tmpColor.g = CLIPBOARD_ON_AIM_COLOR_G;
    tmpColor.b = CLIPBOARD_ON_AIM_COLOR_B;
    tmpColor.a = CLIPBOARD_ON_AIM_COLOR_A;
    GUI_ColorManager::changeColor(tmpColor,CLIPBOARD_TCOLOR);

}

void GUI_ColorManager::changeColor(SDL_Color color, colorType type){
    _COLORS[type] = color;
}

SDL_Color GUI_ColorManager::getColor(colorType type){
    return _COLORS[type];
}

