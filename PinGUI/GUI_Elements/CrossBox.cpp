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
    _var(var),
    _last_var(*_var)
{
    PinGUI::Rect tmp;
    tmp.x = x;
    tmp.y = y;

    initPosition(tmp);

    if (*_var)
        addSprite(tmp, SheetManager::getSurface(NON_CHECKBOX));
    else
        addSprite(tmp, SheetManager::getSurface(CHECKBOX));

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

    _last_var = *_var;
}

void CrossBox::setWritingAvailability(bool state){

    if (state){
        getSprite()->changeColor(GUI_ColorManager::getColor(CLIPBOARD_TCOLOR));
    } else {
        getSprite()->changeColor(GUI_ColorManager::getColor(CLIPBOARD_NCOLOR));
    }
}

void CrossBox::info(){
    std::cout << "Crossbox element. Address: " << this << std::endl;
}

bool CrossBox::hasChanged(){
    return (_last_var!=*_var);
}

void CrossBox::update(){

    if (hasChanged())
        change();
}

void CrossBox::change(){
    _last_var = *_var;

    switch(_last_var){

        case true : {
            _SPRITES[0]->changeTexture(SheetManager::getSurface(NON_CHECKBOX));
            break;
        }
        case false : {
            _SPRITES[0]->changeTexture(SheetManager::getSurface(CHECKBOX));
            break;
        }
    }
}
