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

#include "Scroller.h"


Scroller::Scroller(PinGUI::Vector2<GUIPos> pos, bool* update):
    _update(update),
    _oldDiff(0)
{
    _position = pos;
}

Scroller::~Scroller()
{
    for (std::size_t i = 0; i < _ARROWS.size(); i++){
        delete _ARROWS[i];
        _ARROWS[i] = nullptr;
    }
}

void Scroller::loadScrollMover(int value, int totalValue){
    int diff = totalValue - value;

    PinGUI::Rect tmpRect;
    tmpRect.x = _ARROWS[1]->getSprite()->getX();
    tmpRect.y = _ARROWS[1]->getSprite()->getY();

    addSprite(tmpRect,SheetManager::getSurface(WINDOW_SCROLLER_FILL));

    manageScrollerFill(calculateScrollerSize(value,totalValue));
    addCollider(getSprite(1)->getCollider());

    initOldPos();

    _collidable = true;
    *_update = true;

    _oldDiff = 0;

    calculateRatio(totalValue - value);

     // In case the realSize was not big enough to load the scroller
    if (_ratio<=0){

        ErrorManager::infoLog("PINGUI err.1","Scroller was unable to be loaded due to a incorrect ratio");
        _show = false;
        _collidable = false;
    }
}

void Scroller::hideScroller(){

    //Need to delete the actual sprite and collider
    if (_SPRITES.size()>1) deleteSprite(1);
    if (_COLLIDERS.size()>0){

        deleteCollider(0);
    }

    *_update = true;
    setShow(false);
}

void Scroller::setWritingAvailability(bool state){

    if (state){
        getSprite(1)->setColor(200,200,200);
    } else {
        getSprite(1)->setColor(255,255,255);
    }

}

void Scroller::attachScrollerToInput(){

    PinGUI::basicPointer f;
    f._function = boost::bind(&Scroller::checkForWheelMove,this);

    Input_Manager::setWheeledInfo(getSprite(1),_update,f);
}

void Scroller::checkForWheelMove(){

    checkLimits();
    decide();
    _COLLIDERS[0] = getSprite(1)->getCollider();
}

void Scroller::manipulatingMod(GUI_Element** manipulatingElement){

    if (!Input_Manager::isKeyPressed(SDL_BUTTON_LEFT)){

        endManipulatingMod(manipulatingElement);
        checkLimits();

    } else if (*_update){

        checkLimits();
        decide();
    }

    _COLLIDERS[0] = getSprite(1)->getCollider();
}

bool Scroller::listenForClick(GUI_Element** manipulatingElement){
    if (!Input_Manager::hasAlreadyClicked()){

        if (Input_Manager::isKeyPressed(SDL_BUTTON_LEFT)){

            Input_Manager::setAlreadyClick(true);
            onClick();
            *manipulatingElement = this;

        }

        return true;
    }

    return false;
}

PinGUI::scrollFuncPointer Scroller::getFuncPointer(){

    return _cameraRoll;
}

void Scroller::setShow(bool state){

    _show = state;
    for (std::size_t i = 0; i < _ARROWS.size(); i++){

        _ARROWS[i]->setShow(state);
    }
}

void Scroller::setCamRollFunction(PinGUI::scrollFuncPointer f){
    _cameraRoll = f;
}

void Scroller::manageFunctionality(){

    checkLimits();

    _COLLIDERS[0].rect.y = getSprite(1)->getY();
    _COLLIDERS[0].rect.x = getSprite(1)->getX();

    decide();
    *_update = true;
}

void Scroller::moveElement(const PinGUI::Vector2<GUIPos>& vect){

    moveOldPos(vect);
    GUI_Element::moveElement(vect);

    for (std::size_t i = 0; i < _ARROWS.size(); i++)
        _ARROWS[i]->moveElement(vect);
}

void Scroller::initNormalizer(const int& totalValue, const int& numOfPixels){

    _NORMALIZER._PLUS = totalValue - (_ratio * numOfPixels);
    _NORMALIZER._MINUS = 0;

     if (_NORMALIZER._PLUS==0)
        _NORMALIZER._PLUS++;

    _NORMALIZER._RATIO = numOfPixels/_NORMALIZER._PLUS;
}
