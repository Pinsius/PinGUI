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

#include "ArrowBoard.h"

ArrowBoard::ArrowBoard(PinGUI::Rect rect, int* var, int max, std::shared_ptr<GUI_Element> clip):
    _clipBoard(clip),
    _max(max),
    _ratio(1),
    _min(0),
    _storageType(PINGUI_INT)
{
    init();

    //Init pos
    initPosition(rect);

    calculateY(rect.y,rect.h);

    _dataStorage = std::make_shared<ElementDataStorage>(var);
}

ArrowBoard::ArrowBoard(int* var, int max, std::shared_ptr<GUI_Element> clip, int min, int ratio):
    _max(max),
    _min(min),
    _ratio(ratio),
    _clipBoard(clip),
    _storageType(PINGUI_INT)
{
    init();

    _dataStorage = std::make_shared<ElementDataStorage>(var);
}

ArrowBoard::ArrowBoard(PinGUI::Rect rect, float* var, int max, std::shared_ptr<GUI_Element> clip):
    _clipBoard(clip),
    _max(max),
    _ratio(1),
    _min(0),
    _storageType(PINGUI_FLOAT)
{
    init();

    //Init pos
    initPosition(rect);

    calculateY(rect.y,rect.h);

    _dataStorage = std::make_shared<ElementDataStorage>(var);
}

ArrowBoard::ArrowBoard(float* var, int max, std::shared_ptr<GUI_Element> clip, int min, int ratio):
    _max(max),
    _min(min),
    _ratio(ratio),
    _clipBoard(clip),
    _storageType(PINGUI_FLOAT)
{
    init();

    _dataStorage = std::make_shared<ElementDataStorage>(var);
}

void ArrowBoard::init(){

    _collidable = false;

    //Create a network between this and clipboard
    _clipBoard->setNetworking(true);
}

ArrowBoard::~ArrowBoard()
{
    _ARROWS.clear();
}

void ArrowBoard::addArrows(PinGUI::Rect& rect, std::vector<std::shared_ptr<GUI_Element>>& _ELEMENTS, PinGUI::manipulationState state){

    PinGUI::basicPointer f1,f2;
    f1._function = boost::bind(&ArrowBoard::incVar,this);
    f2._function = boost::bind(&ArrowBoard::decVar,this);

    switch (state){

        case PinGUI::HORIZONTAL : {

            rect.y = calculateY(rect.y,_clipBoard->getSprite()->getH());

            rect.x = _clipBoard->getSprite()->getX() - PINGUI_WINDOW_SCROLLER_ARROW_SIDE_W - ARROW_OFFSET;

            auto tmpArrow = std::make_shared<Window_Arrow>(rect,SheetManager::getSurface(BOARD),LEFT,ARROW_ONLY);

            tmpArrow->setClickFunction(f2);
            _ARROWS.push_back(tmpArrow);

            //Second one
            rect.x = (_clipBoard->getSprite()->getX()+_clipBoard->getSprite()->getW()) +  ARROW_OFFSET;

            tmpArrow = std::make_shared<Window_Arrow>(rect,SheetManager::getSurface(BOARD),RIGHT,ARROW_ONLY);
            tmpArrow->setClickFunction(f1);

            _ARROWS.push_back(tmpArrow);

            break;
        }

        case PinGUI::VERTICAL : {

            rect.x = (_clipBoard->getSprite()->getX()+_clipBoard->getSprite()->getW()) +  ARROW_OFFSET;

            float tmpY = rect.y;
            rect.y = calculateY(rect.y,_clipBoard->getSprite()->getH()) + HORIZONTAL_ARROWS_OFFSET;

            auto tmpArrow = std::make_shared<Window_Arrow>(rect,SheetManager::getSurface(BOARD),UP,ARROW_ONLY);
            _ARROWS.push_back(tmpArrow);

            tmpArrow->setClickFunction(f1);

            //Second one
            rect.y = calculateY(tmpY,_clipBoard->getSprite()->getH()) - HORIZONTAL_ARROWS_OFFSET;

            tmpArrow = std::make_shared<Window_Arrow>(rect,SheetManager::getSurface(BOARD),DOWN,ARROW_ONLY);
            _ARROWS.push_back(tmpArrow);

            tmpArrow->setClickFunction(f2);

            break;
        }
    }

    for (std::size_t i = 0; i < _ARROWS.size(); i++){
        _ELEMENTS.push_back(_ARROWS[i]);
        _ARROWS[i]->setNetworking(true);
    }
}

float ArrowBoard::calculateY(float y, int h){

    y = (y + (h/2))-(PINGUI_WINDOW_SCROLLER_ARROW_UPDOWN_H/2);
    return y;
}

float ArrowBoard::calculateX(float x, int w){

    x = x+(ARROW_W+ARROW_OFFSET)+w+ARROW_OFFSET;
    return x;
}

void ArrowBoard::info(){
    std::cout << "Arrowboard element. Address: " << this << std::endl;
}

void ArrowBoard::moveElement(const PinGUI::Vector2<GUIPos>& vect){

    _clipBoard->moveElement(vect);

    for (std::size_t i = 0; i < _ARROWS.size(); i++)
        _ARROWS[i]->moveElement(vect);
}

void ArrowBoard::incVar(){

    switch(_storageType){

        case PINGUI_INT : {

            auto _var = _dataStorage->getInt()->getVar_P();

            if (*_var + _ratio <= _max)
                *_var += _ratio;

            break;
        }
        case PINGUI_FLOAT : {

            auto _var = _dataStorage->getFloat()->getVar_P();

            if (*_var + _ratio <= _max)
                *_var += _ratio;

            break;
        }
    }
}

void ArrowBoard::decVar(){

    switch(_storageType){

        case PINGUI_INT : {

            auto _var = _dataStorage->getInt()->getVar_P();

            if (*_var - _ratio >= _min)
                *_var -= _ratio;

            break;
        }
        case PINGUI_FLOAT : {

            auto _var = _dataStorage->getFloat()->getVar_P();

            if (*_var - _ratio >= _min)
                *_var -= _ratio;

            break;
        }
    }
}

void ArrowBoard::cropElement(PinGUI::Rect& rect){

    GUI_Element::cropElement(rect);
    _clipBoard->cropElement(rect);

    for (std::size_t i = 0; i < _ARROWS.size(); i++)
        _ARROWS[i]->cropElement(rect);
}
