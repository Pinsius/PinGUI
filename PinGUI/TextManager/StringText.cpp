#include "StringText.h"

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

StringText::StringText(PinGUI::Vector2<GUIPos> pos, textInfo* info, std::string* Variable):
    _variable(Variable)
{
    reloadString();

    init(text,pos);

    _sprite = std::make_shared<GUI_Sprite>(text,pos,info);
}

StringText::~StringText()
{
    //dtor
}

void StringText::reloadString(){

    std::stringstream tmpString;

    tmpString.str("");
    tmpString << *_variable;

    text = tmpString.str();
}

void StringText::needUpdate(textInfo* info, bool& update){

    if (changed){

        getNewText(info);

        update = true;

        changed = false;

        return;
    }

    checkPositioned(update);
}

void StringText::getNewText(textInfo*& info){

    reloadString();

    _sprite.reset();
    _sprite = std::make_shared<GUI_Sprite>(text,_position,info);

    if (_haveOffsetRect){
        calculateTextPosition();
    }
}

void StringText::addChar(char* ch, bool change){

    Text::addChar(ch);

    *_variable = text;

    changed = change;
}

void StringText::setChar(char ch, int pos){

    Text::setChar(ch,pos);

    *_variable = text;
}

void StringText::removeChar(){

    Text::removeChar();

    *_variable = text;
}
