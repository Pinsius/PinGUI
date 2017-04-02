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

#include "WindowExit.h"
#include <iostream>

WindowExit::WindowExit(PinGUI::Rect positionRect, GUI_Element* windowElement):
    _windowElement(windowElement)
{
    initPosition(positionRect);

    positionRect.x += positionRect.w + WINDOW_EXIT_X_OFFSET;
    positionRect.y -= WINDOW_EXIT_Y_OFFSET;

    //Background sprite
    addSprite(positionRect,SheetManager::getSurface(BOARD));

    getSprite()->setW(WINDOW_EXIT_W_AREA);
    getSprite()->setH(WINDOW_EXIT_H_AREA);

    getSprite()->setAlpha(0);
    getSprite()->setColor(255,20,20);

    addCollider(getSprite()->getCollider());

    //Now creating the sprite for the 'X' button
    addSprite(positionRect,SheetManager::getSurface(WINDOW_EXITBUTTON));

    //Also need to offsetTheRect
    getSprite(1)->offsetToRect(getSprite()->getCollider());
}

WindowExit::~WindowExit()
{
    //dtor
}

void WindowExit::setWritingAvailability(bool state){

    if (state){
        getSprite()->setAlpha(255);
    } else {
        getSprite()->setAlpha(0);
    }
}

void WindowExit::onClick(){

    PinGUI::Input_Manager::turnOnTMPState();
    _windowElement->setShow(false);
}

void WindowExit::info(){
    std::cout << "WindowExit. Address: " << this << std::endl;
}
