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

#include "TextStorage.h"
#include <iostream>


TextStorage::TextStorage(std::shared_ptr<TextManager> text):
    _additionalStorage(nullptr),
    _texter(text)
{
}

TextStorage::~TextStorage()
{
    for (auto&& txt : _TEXTS){

        txt->setActive(false);
    }

    _TEXTS.clear();
}

void TextStorage::destroyStorage()
{
	for (std::size_t i = 0; i < _TEXTS.size(); i++)
	{
		_TEXTS[i]->setActive(false);
	}
	_TEXTS.clear();
}

void TextStorage::addAdjustableText(const std::string& text, GUIPos x, GUIPos y, unsigned int size, unsigned int maxSize) {
	_TEXTS.push_back(_texter->writeAdjustableText(text, x, y, size, maxSize));
}

void TextStorage::addText(const std::string& text, GUIPos x, GUIPos y){

	 _TEXTS.push_back(_texter->writeText(text,x,y));
}

void TextStorage::addText(GUIPos x, GUIPos y, int* var){
    _TEXTS.push_back(_texter->writeText(x,y,var));
}

void TextStorage::addText(GUIPos x, GUIPos y, float* var){
    _TEXTS.push_back(_texter->writeText(x,y,var));
}

void TextStorage::addText(GUIPos x, GUIPos y, std::string* var){
    _TEXTS.push_back(_texter->writeText(x,y,var));
}

void TextStorage::destroyText(int position){

    _TEXTS[position]->setActive(false);
    _TEXTS.erase(_TEXTS.begin()+ position);
}

void TextStorage::addChar(char* ch, int position, PinGUI::writingModInfo& info){

    switch (*(_additionalStorage->type)){
		case ADJUSTABLE :
        case NORMAL : {

            _TEXTS[position]->addChar(ch);
            break;
        }
        case INT_ONLY : {

            handleIntegerInput(ch,position,info);
            break;
        }
        case INT_FLOAT : {

            handleFloatInput(ch,position,info);
            break;
        }
    }
}

void TextStorage::handleIntegerInput(char*& ch, int& position, PinGUI::writingModInfo& info){

    if (info.negativeInput && checkNegativeInput(ch,position)){
        _TEXTS[position]->turnOnNegative();
        return;
    }

    //In case that the clipboard contains a variable
    if ( isdigit(*ch) && _TEXTS[position]->checkCharAddition(ch,info.maxValue,info.minValue) ){

        _TEXTS[position]->addChar(ch);

        return;
    }
}

void TextStorage::handleFloatInput(char*& ch, int& position, PinGUI::writingModInfo& info){

    if (info.negativeInput && checkNegativeInput(ch,position)){
        _TEXTS[position]->turnOnNegative();
        return;
    }

    //In case that the clipboard contains a variable
    if ( isFloatInput(ch) && _TEXTS[position]->checkCharAddition(ch,info.maxValue,info.minValue) ){

        _TEXTS[position]->addChar(ch);

        return;
    }
}

bool TextStorage::checkNegativeInput(char*& ch, int& position){


    if (isNegativeInput(ch))
        if (_TEXTS[position]->canAcceptNegativeInput()){

            _TEXTS[position]->addChar(ch);
            return true;
        }

    return false;
}

bool TextStorage::isFloatInput(char*& ch){

    if (isdigit(*ch) || (*ch == '.')) return true;
    else return false;
}

bool TextStorage::isNegativeInput(char*& ch){

    if ((*ch == '-')) return true;
    else return false;
}

void TextStorage::removeChar(int position){

    _TEXTS[position]->removeChar();
}

std::shared_ptr<Text> TextStorage::getText(int position){

    if (_TEXTS.size() > 0)
        return _TEXTS[position];
    else
        return nullptr;
}

void TextStorage::setAdditionalInfo(clipboard_type* Type){

    _additionalStorage = std::make_shared<additionalStorage>(Type);
}

std::vector<std::shared_ptr<Text>>* TextStorage::getVector(){
    return &_TEXTS;
}

void TextStorage::setShow(bool state){

    for (auto&& txt : _TEXTS){

        txt->setShow(state);
    }
}

std::shared_ptr<TextManager> TextStorage::getTextManager(){
    return _texter;
}
