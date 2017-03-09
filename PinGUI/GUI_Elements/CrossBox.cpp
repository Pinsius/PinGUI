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

#include "CrossBox.h"

CrossBox::CrossBox(int x, int y, bool* var):
    _var(var)
{

    PinGUI::Rect tmp;
    tmp.x = x;
    tmp.y = y;

    initPosition(tmp);

    if (*_var)addSprite(tmp, SheetManager::getSurface(NON_CHECKBOX));
    else addSprite(tmp, SheetManager::getSurface(CHECKBOX));

    tmp.x += CHECKBOX_COLLIDER_X;
    tmp.y += CHECKBOX_COLLIDER_Y;
    tmp.w = _SPRITES[0]->getW()+CHECKBOX_COLLIDER_W;
    tmp.h = _SPRITES[0]->getH()+CHECKBOX_COLLIDER_H;
    addCollider(tmp);
}

CrossBox::~CrossBox()
{
    //dtor
}

void CrossBox::onClick(){

    if (*_var){

        *_var = false;
        _SPRITES[0]->changeTexture(SheetManager::getSurface(CHECKBOX));
    } else {

        *_var = true;
        _SPRITES[0]->changeTexture(SheetManager::getSurface(NON_CHECKBOX));
    }
}

void CrossBox::setWritingAvailability(bool state){

    if (state){
        getSprite()->changeColor(GUI_ColorManager::getColor(CLIPBOARD_TCOLOR));
    } else {
        getSprite()->changeColor(GUI_ColorManager::getColor(CLIPBOARD_NCOLOR));
    }
}

bool CrossBox::listenForClick(GUI_Element** manipulatingElement){
    if (!PinGUI::Input_Manager::hasAlreadyClicked()){

        if (PinGUI::Input_Manager::clicked(SDL_BUTTON_LEFT)){
                onClick();
                return true;
        }
        return false;
    }
    return false;
}

void CrossBox::info(){
    std::cout << "Crossbox element. Address: " << this << std::endl;
}
