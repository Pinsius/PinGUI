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


#include "ClipBoard.h"
#include <iostream>


ClipBoard::ClipBoard()
{
 _aimON = false;
}

ClipBoard::ClipBoard(PinGUI::Vector2<GUIPos> position, int maxSize, clipboard_type type, clipboardData data, element_shape shape):
    _type(type),
    _shape(shape)
{

    initClipBoard(maxSize,data,position);

    initText();
}

ClipBoard::ClipBoard(PinGUI::Vector2<GUIPos> position, int maxSize, clipboard_type type, clipboardData data, int* var, element_shape shape):
    _type(type),
    _shape(shape)
{

    initClipBoard(maxSize,data,position);

    initText(var);
}

void ClipBoard::init(PinGUI::Vector2<GUIPos> position, int maxSize, clipboardData data, clipboard_type type, element_shape shape){

    _type = type;
    _shape = shape;

    initClipBoard(maxSize,data,position);

    initText();
}

ClipBoard::~ClipBoard()
{
    delete _textStorage;
}


void ClipBoard::initClipBoard(int& maxSize, clipboardData& data, PinGUI::Vector2<GUIPos>& position){

    _position = position;

    _aimON = false;

    //Calculating the maximum size(max numbers of chars(or ints)
    setMaxSize(maxSize);

    //creating tmp variables to represent my width and height
    int tmp_width,tmp_height;

    //Calculating the width and height of the clipboard
    fakeInputText(tmp_width,tmp_height,data);

    //Creating the GUI sprite (the whole sprite of the clipboard)
    SDL_Surface* tmpSurface;

    if (_shape == ROUNDED){

        tmpSurface = SheetManager::createClipBoard(tmp_width,tmp_height);
    } else if (_shape == RECTANGLED){

        tmpSurface = SheetManager::createRectangle(tmp_width,tmp_height,BOARD,BORDER_LINE);
    }

    addSprite(getSpriteRect(tmp_width,tmp_height,position),
              tmpSurface,
              GUI_ColorManager::getColor(CLIPBOARD_NCOLOR));

    //Creation of textStorage unit
    _textStorage = new TextStorage(data.texter);
}

void ClipBoard::initText(){

    if (_type==INT_ONLY||_type==UNCLICKABLE)
        _textStorage->addText(" ",100,100);
    else
        _textStorage->addText(" ",100,100);

    _textStorage->getText(0)->setOffsetRect(*(getCollider()));
    _textStorage->getText(0)->calculateTextPosition();
    _textStorage->getText(0)->setNetworked(true);

    _textStorage->setAdditionalInfo(getCollider(),&_type);

    //Here i initialize also the collidable state
    if (_type==UNCLICKABLE)
        setCollidable(false);
}

void ClipBoard::initText(int* var){

    std::stringstream tmp;
    tmp.str("");
    tmp << *var;

     _textStorage->addText("",100,100,var);
    _textStorage->getText(0)->setOffsetRect(*(getCollider()));
    _textStorage->getText(0)->calculateTextPosition();
    _textStorage->getText(0)->setNetworked(true);

    _textStorage->setAdditionalInfo(getCollider(),&_type);

    //Here i initialize also the collidable state
    if (_type==UNCLICKABLE)
        setCollidable(false);
}

void ClipBoard::calculateMaxSize(){

    //Temporary copy
    int tmp = _maxValue;
    _maxSize = 0;

    //Here i count the maximum num of digits
    while(tmp!=0){
        _maxSize++;
        tmp = tmp/10;
    }
}

void ClipBoard::setMaxSize(int& maxSize){

    if (_type==INT_ONLY||_type==UNCLICKABLE){

        _maxValue = maxSize;
        calculateMaxSize();
    } else {

        _maxSize = maxSize;
    }
}

PinGUI::Rect ClipBoard::getSpriteRect(const GUIPos& tmp_width, const GUIPos& tmp_height, const PinGUI::Vector2<GUIPos> position){
    PinGUI::Rect tmp;

     //Now have to modify the collision rect
    tmp.x = position.x+CLIPBOARD_COLLIDER_X;
    tmp.y = position.y+CLIPBOARD_COLLIDER_Y;
    tmp.w = tmp_width;

    if (_shape==ROUNDED)
        tmp.w += CLIPBOARD_COLLIDER_W;

    tmp.h = tmp_height+CLIPBOARD_COLLIDER_H;

    addCollider(tmp);

    //Setting up the rectangle
    tmp.x = position.x;
    tmp.y = position.y;
    tmp.w = tmp_width;
    tmp.h = tmp_height;

    return tmp;
}

void ClipBoard::onClick(){

    SDL_ShowCursor(SDL_DISABLE);
    //Setting the input state
    PinGUI::Input_Manager::setInputState(WRITINGMOD);

    //Saving the text of my clipboard to be the one that is manipulated
    PinGUI::Input_Manager::setManipulatedText(_textStorage);

    //Creating mod info
    writingModInfo tmp;

    if (_type==NORMAL)
        tmp.intOnly = false;
    else {

        tmp.intOnly = true;
        tmp.maxValue = _maxValue;
    }
    tmp.max = _maxSize;

    PinGUI::Input_Manager::setWritingModInfo(tmp);
}

void ClipBoard::manipulatingMod(GUI_Element** manipulatingElement){

    if (PinGUI::Input_Manager::isKeyPressed(SDLK_ESCAPE)||PinGUI::Input_Manager::isKeyPressed(SDLK_RETURN)){

        *manipulatingElement = nullptr;
        SDL_ShowCursor(SDL_ENABLE);
        PinGUI::Input_Manager::setInputState(GAMEINPUT);
        PinGUI::Input_Manager::setAlreadyClick(false);
        return;
    }
}

void ClipBoard::setWritingAvailability(bool state){

    if (state){
        getSprite()->changeColor(GUI_ColorManager::getColor(CLIPBOARD_TCOLOR));
    } else {
        getSprite()->changeColor(GUI_ColorManager::getColor(CLIPBOARD_NCOLOR));
    }
}

bool ClipBoard::changed(){

    return _textStorage->getText(0)->isChanged();
}

void ClipBoard::info(){
    std::cout << "Clipboard element. Address: " << this << std::endl;
}

void ClipBoard::fakeInputText(int& width, int& height, const clipboardData& data){

    std::string tmpString;

    for (int i = 0; i < _maxSize; i++)
        tmpString+='O';

    GUI_Sprite* tmpSprite = new GUI_Sprite(tmpString,data.texter->getTextInfo());

    width = tmpSprite->getW() + CLIPBOARD_WIDTH_OFFSET;
    height = tmpSprite->getH() + CLIPBOARD_HEIGHT_OFFSET;

    delete tmpSprite;
}

void ClipBoard::normalizeElement(const PinGUI::Vector2<GUIPos>& vect){

    //Have to store the oldPosition because the position will be modified in moveTo function
    PinGUI::Vector2<GUIPos> oldPosition(_position);

    moveTo(vect);

    //Flip Y
    oldPosition.y *= -1;

    moveElement(oldPosition);
}

void ClipBoard::moveElement(const PinGUI::Vector2<GUIPos>& vect){

    for (std::size_t i = 0; i < _SPRITES.size(); i++){
        _SPRITES[i]->moveSprite(vect);
    }

    for (std::size_t i = 0; i < _COLLIDERS.size(); i++){
        moveCollider(_COLLIDERS[i],vect);
    }

    _position += vect;

    _textStorage->getText()->moveText(vect);
}

bool ClipBoard::listenForClick(GUI_Element** manipulatingElement){

    if (!PinGUI::Input_Manager::hasAlreadyClicked()){

        if (PinGUI::Input_Manager::clicked(SDL_BUTTON_LEFT)){

            PinGUI::Input_Manager::setAlreadyClick(true);
            onClick();
            *manipulatingElement = this;

            return true;
        }

        return false;
    }
    return false;
}

void ClipBoard::setClipboardText(std::string text){

    setClipboardText(text,*(getCollider()));
}

void ClipBoard::setClipboardText(std::string text, PinGUI::Rect collider){

    //Destroy the text if it exist(ofc it will exist everytime
    if (_textStorage->getText())
        _textStorage->destroyText();

    _textStorage->addText(text,_position.x,_position.y);

    _textStorage->getText(0)->setOffsetRect(collider);
    _textStorage->getText(0)->calculateTextPosition();
    _textStorage->getText(0)->setNetworked(true);

    _textStorage->setAdditionalInfo(getCollider(),&_type);
}

void ClipBoard::setShow(bool state){
    _show = state;
    _textStorage->getText(0)->setShow(state);
}

void ClipBoard::cropElement(PinGUI::Rect& rect){

    GUI_Element::cropElement(rect);

    CropManager::cropSprite(_textStorage->getText()->getSprite(),rect);
}
