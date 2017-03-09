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

#include "GUI_Cursor.h"
#include <iostream>

PinGUI::Rect GUI_Cursor::_collisionRect;

GUI_Cursor::GUI_Cursor()
{
    _collisionRect.w = CURSOR_WIDTH;
    _collisionRect.h = CURSOR_HEIGHT;
    _collisionRect.x = 0;
    _collisionRect.y = 0;
}

GUI_Cursor::~GUI_Cursor()
{

}

void GUI_Cursor::updateCursor(){

    int x,y;

    SDL_GetMouseState(&x,&y);
    _collisionRect.x = x;
    _collisionRect.y = y;

    _collisionRect.y = PinGUI::Input_Manager::_screenHeight - _collisionRect.y;
}


PinGUI::Rect GUI_Cursor::getCollider(){
    return _collisionRect;
}

int GUI_Cursor::getX(){
    return _collisionRect.x;
}

int GUI_Cursor::getY(){
    return _collisionRect.y;
}
