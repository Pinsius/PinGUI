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

ClipBoard::ClipBoard(PinGUI::Vector2<GUIPos> position,
					 int maxSize,
					 clipboard_type type,
					 clipboardData data,
					 unsigned int maxSizeOfAdjustText,
					 element_shape shape,
					 bool delegated):
    _type(type),
    _shape(shape),
    _negativeInput(true),
    _exitAtEnter(true)
{

	if (!delegated) {

		initClipBoard(maxSize,data,position);

		initText(_maxSize, maxSizeOfAdjustText);
	}
}

ClipBoard::ClipBoard(PinGUI::Vector2<GUIPos> position,
					 int width,
					 int maxSize,
					 clipboard_type type,
					 clipboardData data,
					 unsigned int maxSizeOfAdjustText,
					 element_shape shape):
    ClipBoard(position,maxSize,type,data,maxSizeOfAdjustText,shape,true)
{
    initClipBoard(maxSize,data,position,width);

    initText(_maxSize, maxSizeOfAdjustText);
}

ClipBoard::ClipBoard(PinGUI::Vector2<GUIPos> position, int maxSize, clipboard_type type, clipboardData data, int* var, bool negativeInput, element_shape shape):
	ClipBoard(position, maxSize, type, data, 0, shape, true)
{
	_negativeInput = negativeInput;

    initClipBoard(maxSize,data,position);

    initText(var);
}

ClipBoard::ClipBoard(PinGUI::Vector2<GUIPos> position, int maxSize, clipboard_type type, clipboardData data, std::string* var, element_shape shape):
	ClipBoard(position, maxSize, type, data, 0, shape, true)
{
    initClipBoard(maxSize,data,position);

    initText(var);
}

ClipBoard::ClipBoard(PinGUI::Vector2<GUIPos> position, int maxSize, clipboard_type type, clipboardData data, float* var, bool negativeInput, element_shape shape):
	ClipBoard(position, maxSize, type, data, 0, shape, true)
{
	_negativeInput = negativeInput;

    initClipBoard(maxSize,data,position);

    initText(var);
}

void ClipBoard::init(PinGUI::Vector2<GUIPos> position, int maxSize, clipboardData data, clipboard_type type, element_shape shape){

    _type = type;
    _shape = shape;

    _exitAtEnter = true;

    initClipBoard(maxSize,data,position);

    initText();
}

ClipBoard::~ClipBoard()
{
	if (containsText())
		_textStorage->destroyStorage();
}

void ClipBoard::initClipBoard(int& maxSize, clipboardData& data, PinGUI::Vector2<GUIPos>& position, int width){

    _minValue = 0;

    _position = position;

    _aimON = false;

    //Calculating the maximum size(max numbers of chars(or ints)
    setMaxSize(maxSize);

    //creating tmp variables to represent my width and height
    int tmp_width,tmp_height;

    //Calculating the width and height of the clipboard
    fakeInputText(tmp_width,tmp_height,data);

    //Check if I need to have fixed clipboard width
    if (width != 0)
        tmp_width = width;

    //Creating the GUI sprite (the whole sprite of the clipboard)
    SDL_Surface* tmpSurface;

    if (_shape == ROUNDED){

        tmpSurface = SheetManager::createClipboard(tmp_width,tmp_height);
    } else if (_shape == RECTANGLED){

        tmpSurface = SheetManager::createRectangle(tmp_width,tmp_height,BOARD,BORDER_LINE);
    }

    addSprite(getSpriteRect(tmp_width,tmp_height,position),
              tmpSurface,
              GUI_ColorManager::getColor(CLIPBOARD_NCOLOR));

    //Creation of textStorage unit
    _textStorage = std::make_shared<TextStorage>(data.texter);
}

void ClipBoard::initText(unsigned int sizeOfAdjustText, unsigned int maxSizeOfAdjustText){

	if (_type != ADJUSTABLE) {
		_textStorage->addText(" ",100,100);
	}
	else {
		_textStorage->addAdjustableText(" ", 100, 100, sizeOfAdjustText, maxSizeOfAdjustText);
	}

	initStorage();
}

void ClipBoard::initText(int* var){

    _textStorage->addText(100,100,var);

    initStorage();
}

void ClipBoard::initText(float* var){

    _textStorage->addText(100,100,var);

    initStorage();
}

void ClipBoard::initText(std::string* var){

    _textStorage->addText(100,100,var);

    initStorage();
}

void ClipBoard::initStorage(){

    _textStorage->getText(0)->setOffsetRect(*(getCollider()));
    _textStorage->getText(0)->calculateTextPosition();
    _textStorage->getText(0)->setNetworked(true);
    _textStorage->setAdditionalInfo(&_type);

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

    switch (_type){

        case INT_ONLY :
        case UNCLICKABLE : {

            _maxValue = maxSize;

            calculateMaxSize();

            if (_negativeInput)
                _maxSize++;

            break;
        }
        case INT_FLOAT : {

            _maxValue = maxSize;

            calculateMaxSize();
            _maxSize += FLOAT_TEXT_PRECISION + 1;

            if (_negativeInput)
                _maxSize++;

            break;
        }
        default : {
            _maxSize = maxSize;
        }
    }
}

PinGUI::Rect ClipBoard::getSpriteRect(const int& tmp_width, const int& tmp_height, const PinGUI::Vector2<GUIPos> position){

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
    PinGUI::Input_Manager::setInputState(PinGUI::WRITINGMOD);

    //Saving the text of my clipboard to be the one that is manipulated
    PinGUI::Input_Manager::setManipulatedText(_textStorage);

    //Creating mod info
    PinGUI::writingModInfo tmp;

    if (_type!=NORMAL)
        tmp.maxValue = _maxValue;

    tmp.inputType = _type;

	if (_type != ADJUSTABLE)
		tmp.max = _maxSize;
	else
		tmp.max = std::static_pointer_cast<AdjustableText>(_textStorage->getText())->getMaxRealTextSize();

    tmp.minValue = _minValue;
    tmp.negativeInput = _negativeInput;

    PinGUI::Input_Manager::setWritingModInfo(tmp);
	_textStorage->getText()->startInputManipulation();
}

void ClipBoard::manipulatingMod(manip_Element manipulatingElement){

    bool tmp = false;

    if (pressedEnter()){

		/*
		This can be applied as a functor to be called for getting the input
		It calls a function with 1 string parameter  after user uses ENTER
		*/
        _func.exec(_textStorage->getText()->getString());


        if (_exitAtEnter)
            tmp = true;
        else
            PinGUI::Input_Manager::clearEnterKey();

    } else if (pressedESC()){

        tmp = true;
    }

	//Exit from the writing mode
    if (tmp){

        manipulatingElement = nullptr;

        SDL_ShowCursor(SDL_ENABLE);
        PinGUI::Input_Manager::setInputState(PinGUI::GAMEINPUT);
        PinGUI::Input_Manager::setAlreadyClick(false);

        _textStorage->getText()->endInputManipulation();

        return;
    }
}

bool ClipBoard::pressedEnter(){
    return (PinGUI::Input_Manager::isKeyPressed(SDLK_RETURN)||PinGUI::Input_Manager::isKeyPressed(SDLK_KP_ENTER));
}

bool ClipBoard::pressedESC(){
    return (PinGUI::Input_Manager::isKeyPressed(SDLK_ESCAPE));
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

    for (unsigned int i = 0; i < _maxSize; i++)
        tmpString+='O';

    std::shared_ptr<GUI_Sprite> tmpSprite = std::make_shared<GUI_Sprite>(tmpString,data.texter->getTextInfo());

    width = tmpSprite->getW() + CLIPBOARD_WIDTH_OFFSET;
    height = tmpSprite->getH() + CLIPBOARD_HEIGHT_OFFSET;

    _widthPerChar = tmpSprite->getW()/_maxSize;
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

	GUI_Element::moveElement(vect);

	if (_textStorage && containsText())
	  _textStorage->getText()->moveText(vect);
}

bool ClipBoard::listenForClick(manip_Element manipulatingElement){

    if (!PinGUI::Input_Manager::hasAlreadyClicked()){

        if (PinGUI::Input_Manager::clicked(SDL_BUTTON_LEFT)){

            PinGUI::Input_Manager::setAlreadyClick(true);
            onClick();

            manipulatingElement = this;

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

	//Destroy the text if it exist(ofc it will exist everytime but to be absolute sure)
	if (_textStorage->getText(0))
	{
		_textStorage->getText(0)->replaceText(text);
		_textStorage->getText(0)->setOffsetRect(collider);
		_textStorage->getText(0)->calculateTextPosition();
	}
}

void ClipBoard::setShow(bool state){

	if (_textStorage && containsText())
	{
		_textStorage->getText(0)->setShow(state);
	}
	_show = state;
}

void ClipBoard::cropElement(PinGUI::Rect& rect){

    GUI_Element::cropElement(rect);

	if (containsText())
		CropManager::cropSprite(_textStorage->getText()->getSprite().get(),rect);
}

void ClipBoard::setMinValue(int minV){
    _minValue = minV;
}

void ClipBoard::setEnterFunc(PinGUI::stringFuncPointer f){
    _func = f;
}

void ClipBoard::clearClipBoard(){
    setClipboardText(" ");
}

void ClipBoard::setExitAtEnter(bool state){
    _exitAtEnter = state;
}

bool ClipBoard::containsText() {
	return (_textStorage && _textStorage->getVector()->size() > 0);
}