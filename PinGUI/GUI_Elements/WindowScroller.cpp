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

#include "WindowScroller.h"


WindowScroller::WindowScroller(manipulationState state, PinGUI::Vector2<float> pos, int value, bool* update):
    _update(update),
    _state(state)
{
    _position = pos;

    PinGUI::Rect tmpRect;
    tmpRect.initPos(pos);

    addSprite(tmpRect,SheetManager::createWindowScroller(value,_state));

    _collidable = false;
}

WindowScroller::~WindowScroller()
{
    for (std::size_t i = 0; i < _ARROWS.size(); i++){
        delete _ARROWS[i];
        _ARROWS[i] = nullptr;
    }
}

void WindowScroller::createArrows(std::vector<GUI_Element*>* _ELEMENTS){
    PinGUI::Rect tmpRect;
    tmpRect.w = WINDOW_ARROW_W;
    tmpRect.h = WINDOW_ARROW_H;

    int a;

    //_ELEMENTS->push_back(this);

    switch(_state){

        case VERTICAL : {
            tmpRect.x = getSprite()->getX()+PINGUI_WINDOW_LINE_W;
            tmpRect.y = getSprite()->getY()+PINGUI_WINDOW_LINE_H;

            //Down arrow
            _ARROWS.push_back(new Window_Arrow(tmpRect,SheetManager::getSurface(BOARD),DOWN));

            //Up arrow
            tmpRect.y = getSprite()->getY()+getSprite()->getH()-tmpRect.h;
            _ARROWS.push_back(new Window_Arrow(tmpRect,SheetManager::getSurface(BOARD),UP));

            break;
        }
       case HORIZONTAL : {

            tmpRect.x = getSprite()->getX()+PINGUI_WINDOW_LINE_W;
            tmpRect.y = getSprite()->getY() +PINGUI_WINDOW_LINE_H;

            //Right arrow
            _ARROWS.push_back(new Window_Arrow(tmpRect,SheetManager::getSurface(BOARD),LEFT));

            //Left arrow
            tmpRect.x +=  getSprite()->getW() - WINDOW_ARROW_W;
            _ARROWS.push_back(new Window_Arrow(tmpRect,SheetManager::getSurface(BOARD),RIGHT));

            break;
       }
    }

    for (std::size_t i = 0; i < _ARROWS.size(); i++) _ELEMENTS->push_back(_ARROWS[i]);
}

void WindowScroller::setShow(bool state){
    _show = state;
    for (std::size_t i = 0; i < _ARROWS.size(); i++){
        _ARROWS[i]->setShow(state);
    }
}

void WindowScroller::loadScrollMover(int value, int totalValue){
    int diff = totalValue - value;

    PinGUI::Rect tmpRect;
    tmpRect.x = _ARROWS[1]->getSprite()->getX();
    tmpRect.y = _ARROWS[1]->getSprite()->getY();


    addSprite(tmpRect,SheetManager::getSurface(WINDOW_SCROLLER_FILL));

    manageScrollerFill(calculateScrollerSize(value,totalValue));
    addCollider(getSprite(1)->getCollider());
    _collidable = true;
    *_update = true;

    calculateRatio(totalValue - value);

}

void WindowScroller::calculateRatio(const int& totalValue){
    int numOfManipulationPixels;

    switch (_state){

        case VERTICAL : {

            numOfManipulationPixels = getSprite(1)->getY() - (_ARROWS[0]->getSprite()->getY() + _ARROWS[0]->getSprite()->getH());
            break;
        }
        case HORIZONTAL : {

            numOfManipulationPixels = (getSprite(1)->getX() + getSprite(1)->getW())- _ARROWS[0]->getSprite()->getX() ;
            break;
        }
    }

    _ratio = static_cast<float>(totalValue)/numOfManipulationPixels;
}

void WindowScroller::manageScrollerFill(const int& value){
    switch (_state){
        case VERTICAL : {

            getSprite(1)->setH(value);
            getSprite(1)->setW(PINGUI_WINDOW_DEFAULT_SCROLLER_W - (PINGUI_WINDOW_LINE_W*2));
            getSprite(1)->setY(_ARROWS[1]->getSprite()->getY() - getSprite(1)->getH());
            return;
        }
        case HORIZONTAL : {

            getSprite(1)->setW(value);
            getSprite(1)->setH(PINGUI_WINDOW_DEFAULT_SCROLLER_H - (PINGUI_WINDOW_LINE_H*2));
            getSprite(1)->setX((_ARROWS[0]->getSprite()->getX()+_ARROWS[0]->getSprite()->getW()));
            return;
        }
    }
}

int WindowScroller::calculateScrollerSize(const int& value, int& totalValue){
    //Percentage of window viewport
    float windowPercentage = static_cast<float>(value)/static_cast<float>(totalValue);


   //Now need the possible length of scroller fill
   int tmpLength = 0;

   switch(_state){
        case VERTICAL : {

            tmpLength = _ARROWS[1]->getSprite()->getY()-(_ARROWS[0]->getSprite()->getY()+WINDOW_ARROW_H);
            break;
        }
        case HORIZONTAL : {

            tmpLength = _ARROWS[1]->getSprite()->getX()-(_ARROWS[0]->getSprite()->getX()-WINDOW_ARROW_W);
            break;
        }
   }


   return tmpLength*windowPercentage;
}

void WindowScroller::hideScroller(){

    //Need to delete the actual sprite and collider
    if (_SPRITES.size()>1) deleteSprite(1);
    if (_COLLIDERS.size()>0){
        deleteCollider(0);

    }
    *_update = true;
    setShow(false);
}

void WindowScroller::setWritingAvailability(bool state){

    if (state){
        getSprite(1)->setColor(200,200,200);
    } else {
        getSprite(1)->setColor(255,255,255);
    }

}

void WindowScroller::attachScrollerToInput(){

    PinGUI::basicPointer f;

    Input_Manager::setWheeledInfo(getSprite(1),_update,f);
}

bool WindowScroller::checkForWheelMove(){

    if (*_update){
        checkLimits();
        _COLLIDERS[0] = getSprite(1)->getCollider();
        return true;
    }

    return false;

}

void WindowScroller::modifyArrowPos(){
    switch(_state){
        case HORIZONTAL : {

            _ARROWS[1]->setX(getSprite()->getX() + getSprite()->getW() - WINDOW_ARROW_W);
            _ARROWS[1]->getSprite(-1)->offsetToRect(*(_ARROWS[1]->getCollider()));
            break;
        }
    }
}

void WindowScroller::onClick(){

    //Setting the input state
    Input_Manager::setInputState(MANIPULATINGMOD);
    Input_Manager::setState(GUI);
    Input_Manager::createManipulatingModInfo(getSprite(1)->getX(),getSprite(1)->getY(),_state);
    Input_Manager::initManipulation(_SPRITES[1],_update);

}

void WindowScroller::manipulatingMod(GUI_Element** manipulatingElement){

    if (!Input_Manager::isKeyPressed(SDL_BUTTON_LEFT)){

        endManipulatingMod(manipulatingElement);

    } else if (*_update){
        std::cout << "modiofikujem" << std::endl;
        checkLimits();
        _cameraRoll.exec();
    }

    _COLLIDERS[0] = getSprite(1)->getCollider();
}

bool WindowScroller::listenForClick(GUI_Element** manipulatingElement){
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

void WindowScroller::checkLimits(){
    switch(_state){
        case VERTICAL : {

            if (getSprite(1)->getY()<(_ARROWS[0]->getSprite()->getY()+_ARROWS[0]->getSprite()->getH())){
                getSprite(1)->setY(_ARROWS[0]->getSprite()->getY()+_ARROWS[0]->getSprite()->getH());
            } else if (getSprite(1)->getY() + getSprite(1)->getH() > _ARROWS[1]->getSprite()->getY()){
                getSprite(1)->setY(_ARROWS[1]->getSprite()->getY() - getSprite(1)->getH());
            }

            break;
        }
        case HORIZONTAL : {

            if (getSprite(1)->getX()<(_ARROWS[0]->getSprite()->getX()+_ARROWS[0]->getSprite()->getW())){
                getSprite(1)->setX(_ARROWS[0]->getSprite()->getX()+_ARROWS[0]->getSprite()->getW());
            } else if (getSprite(1)->getX() + getSprite(1)->getW() > _ARROWS[1]->getSprite()->getX()){
                getSprite(1)->setX(_ARROWS[1]->getSprite()->getX() - getSprite(1)->getW());
            }

            break;
        }

    }
}

void WindowScroller::incScroller(){
    switch(_state){
        case HORIZONTAL : {

            break;
        }
        case VERTICAL : {

            break;
        }
    }
    _cameraRoll.exec();
}

void WindowScroller::decScroller(){
    switch(_state){
        case HORIZONTAL : {

            break;
        }
        case VERTICAL : {

            break;
        }
    }
    _cameraRoll.exec();
}

PinGUI::basicPointer WindowScroller::getFuncPointer(){
    return _cameraRoll;
}
