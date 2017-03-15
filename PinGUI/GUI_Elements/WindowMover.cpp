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

#include "WindowMover.h"

WindowMover::WindowMover(PinGUI::Rect tmpRect, bool* windowUpdate)
{
    initPosition(tmpRect);

    _windowUpdate = windowUpdate;

    //I add a sprite and a collider, i choose any surface because i want it to have 100% transparency - if you want to change it you need to change the SURFACE by yourself
    addSprite(tmpRect,SheetManager::getSurface(BOARD));

    getSprite()->setW(tmpRect.w);
    getSprite()->setH(tmpRect.h);

    addCollider(tmpRect);

    getSprite()->setAlpha(0);
}

WindowMover::~WindowMover()
{
    //dtor
}

void WindowMover::manipulatingMod(manip_Element manipulatingElement){

    if (!PinGUI::Input_Manager::isKeyPressed(SDL_BUTTON_LEFT)){

        endManipulatingMod(manipulatingElement);
        optionCollider();

        return;
    }
}

void WindowMover::onClick(){

    //Setting the input state
    PinGUI::Input_Manager::setInputState(MANIPULATINGMOD);
    PinGUI::Input_Manager::setState(GUI);
    PinGUI::Input_Manager::createManipulatingModInfo(getSprite()->getX(),getSprite()->getY(),WINDOW_MOVING);
    PinGUI::Input_Manager::initManipulation(getSprite(),_windowUpdate);
}

bool WindowMover::listenForClick(manip_Element manipulatingElement){

    if (!PinGUI::Input_Manager::hasAlreadyClicked()){

        if (PinGUI::Input_Manager::isKeyPressed(SDL_BUTTON_LEFT)){

            PinGUI::Input_Manager::setAlreadyClick(true);
            onClick();

            manipulatingElement = this;
        }
        return true;
    } return false;
}

void WindowMover::optionCollider(){
    setCollider(getSprite()->getCollider());
}

void WindowMover::info(){
    std::cout << "WindowMover element. Address: " << this << std::endl;
}
