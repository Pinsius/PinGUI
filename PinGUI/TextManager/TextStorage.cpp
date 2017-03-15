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
    _additionalStorage(nullptr)
{
    texter = text;
}

TextStorage::~TextStorage()
{
    for (auto&& txt : _TEXTS){

        txt->setActive(false);
    }

    _TEXTS.clear();
}

void TextStorage::addText(const std::string& text, int x, int y){
    _TEXTS.push_back(texter->writeText(text,x,y));
}

void TextStorage::addText(const std::string& text, int x, int y, int* var){
    _TEXTS.push_back(texter->writeText(text,x,y,var));
}

void TextStorage::destroyText(int position){

    _TEXTS[position]->setActive(false);
    _TEXTS.erase(_TEXTS.begin()+ position);
}

void TextStorage::addChar(char* ch, int position, int maxValue){

    if (*(_additionalStorage->type)==INT_ONLY){
        if (_TEXTS[position]->haveNum()){

            //In case that the clipboard contains a variable
            if ((_TEXTS[position]->getVariableNum()*10) + (*ch-48)<=maxValue){
                if (_TEXTS[position]->isZero()){
                  _TEXTS[position]->removeChar();
                }
                _TEXTS[position]->addChar(ch);
                return;
            }
        } else {

            //In case of normal clipboard with int text
            if (_TEXTS[position]->isZero()){
                _TEXTS[position]->removeChar();
            }
            _TEXTS[position]->addChar(ch);
        }
    } else {
        //Normal text clipboard
        _TEXTS[position]->addChar(ch);
    }
}

void TextStorage::removeChar(int position){

    if (*(_additionalStorage->type)==INT_ONLY){

        if (_TEXTS[position]->getTextSize()==1)
            _TEXTS[position]->setChar('0',0);
        else
            _TEXTS[position]->removeChar();
    } else {

        _TEXTS[position]->removeChar();
    }
}

std::shared_ptr<Text> TextStorage::getText(int position){

    if (_TEXTS.size() > 0)
        return _TEXTS[position];
    else
        return nullptr;

}

void TextStorage::setAdditionalInfo(PinGUI::Rect* OffsetRect, clipboard_type* Type){

    _additionalStorage.reset();

    _additionalStorage = std::make_shared<additionalStorage>(OffsetRect,Type);
}

std::vector<std::shared_ptr<Text>>* TextStorage::getVector(){
    return &_TEXTS;
}

void TextStorage::setShow(bool state){

    for (auto&& txt : _TEXTS){

        txt->setShow(state);
    }
}
