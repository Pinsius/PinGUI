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

#include "Window_Arrow.h"

Window_Arrow::Window_Arrow(PinGUI::Rect tmpRect,SDL_Surface* surface,orientation orient, arrowCollider colliderType):
    _arrowCollider(colliderType)
{
    initPosition(tmpRect);

    _collidable = true;

    _networkedElement = true;

    //The background
    if (colliderType==WHOLE_RECT) addSprite(tmpRect,surface);

    //Arrow surface
    addSprite(tmpRect,chooseRightDirect(orient));

    createCollider(tmpRect,colliderType,orient);

    if ((orient == UP || orient == DOWN)&& colliderType==WHOLE_RECT)
        getSprite(-1)->setY(getSprite(-1)->getY()-BASIC_ARROW_Y_OFFSET);
}


Window_Arrow::~Window_Arrow()
{
    //dtor
}

void Window_Arrow::createCollider(PinGUI::Rect& tmpRect, arrowCollider& colliderType, orientation& orient){

    switch(colliderType){

        case WHOLE_RECT : {

            getSprite(-1)->offsetToRect(tmpRect);
            setUpBackgroundSprite(tmpRect);
            break;
        }
        case ARROW_ONLY : {

            tmpRect.y += 1;
            if (orient==UP || orient==DOWN) {
                tmpRect.w = PINGUI_WINDOW_SCROLLER_ARROW_UPDOWN_W;
                tmpRect.h = PINGUI_WINDOW_SCROLLER_ARROW_UPDOWN_H-1;
            } else {
                tmpRect.w = PINGUI_WINDOW_SCROLLER_ARROW_SIDE_W;
                tmpRect.h = PINGUI_WINDOW_SCROLLER_ARROW_SIDE_H-1;
            }
            break;
        }
    }
    addCollider(tmpRect);
}

SDL_Surface* Window_Arrow::chooseRightDirect(orientation& orient){

   switch(orient){

        case UP : return SheetManager::getSurface(WINDOW_ARROW_UP);
        case DOWN : return SheetManager::getSurface(WINDOW_ARROW_DOWN);
        case LEFT : return SheetManager::getSurface(WINDOW_ARROW_LEFT);
        case RIGHT : return SheetManager::getSurface(WINDOW_ARROW_RIGHT);
   }
}

void Window_Arrow::setUpBackgroundSprite(const PinGUI::Rect& tmpRect){

    getSprite()->setX(tmpRect.x);
    getSprite()->setY(tmpRect.y);
    getSprite()->setW(tmpRect.w);
    getSprite()->setH(tmpRect.h);
    getSprite()->setColor(40,40,40);
    getSprite()->setAlpha(0);
}

void Window_Arrow::setWritingAvailability(bool state){

    if (_arrowCollider==WHOLE_RECT) highlightRect(state);
    else highlightArrow(state);
}

void Window_Arrow::highlightRect(const bool& state){

    if (state){
        getSprite()->setAlpha(255);
    } else {
        getSprite()->setAlpha(0);
    }
}

void Window_Arrow::highlightArrow(const bool& state){

    if (state){
        getSprite()->setColor(100,100,150);
    } else {
        getSprite()->setColor(255,255,255);
    }
}

void Window_Arrow::setClickFunction(PinGUI::basicPointer method){
    _clFunction = method;
}

void Window_Arrow::onClick(){
    _clFunction.exec();
}
