#include "IntegerText.h"

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

IntegerText::IntegerText(PinGUI::Vector2<GUIPos> pos, textInfo* info, int* Variable):
    _variable(Variable),
    _last_var(*Variable),
    _tmpInteger(EMPTY_TMP_INPUT),
    _tmpInput(false),
    _negative(false)
{
    reloadString();

    init(text,pos);

    _sprite = std::make_shared<GUI_Sprite>(text,pos,info);
}

IntegerText::~IntegerText()
{
    //dtor
}

void IntegerText::reloadString(){

    std::stringstream tmpString;

    tmpString << _last_var;

    text = tmpString.str();
}

void IntegerText::needUpdate(textInfo* info, bool& update){

    if ((*_variable != _last_var) || changed){

        if (_tmpInput)
            _tmpInteger = std::atoi(text.c_str());

        getNewText(info);

        update = true;

        changed = false;

        return;
    }

    checkPositioned(update);
}

void IntegerText::getNewText(textInfo*& info){

    if (!_tmpInput){

        if (changed && (_tmpInteger != EMPTY_TMP_INPUT)){

            *_variable = _tmpInteger;
            _tmpInteger = EMPTY_TMP_INPUT;
        }

        _last_var = *_variable;

        reloadString();

    } else
        _tmpInput = false;

    _sprite.reset();
    _sprite = std::make_shared<GUI_Sprite>(text,_position,info);

    if (_haveOffsetRect){
        calculateTextPosition();
    }
}

void IntegerText::addChar(char* ch, bool change){

    if ((text[0]==' ' && text.size()==1)){

        text[0] = *ch;
        _tmpInput = true;
        changed = change;

        return;
    }

    _tmpInput = true;
    text += *ch;
    changed  = change;
}

void IntegerText::setChar(char ch, int pos){

    text[pos] = ch;

    *_variable = std::atoi(text.c_str());

    changed = true;
}

void IntegerText::removeChar(){

    if (text.back() == '-' && _negative)
        _negative = false;

    text.pop_back();

    if (text.size()==0)
        text.push_back(' ');

    _tmpInput = true;

    changed = true;
}

float IntegerText::getVariableNum(){
    return _tmpInteger;
}

bool IntegerText::checkCharAddition(char* ch, int& maxValue, int& minValue){

    findNegative();

    if (_negative){

        std::string tmpText(text);
        tmpText.push_back(*ch);

        if (std::atoi(tmpText.c_str()) >= minValue)
            return true;
    } else {
        if ((getVariableNum()*10) + getCharNum(ch) <= maxValue) return true;
    }
    return false;
}

void IntegerText::endInputManipulation(){

    _tmpInput = false;
    changed = true;
}

void IntegerText::turnOnNegative(){
    _negative = true;
}

void IntegerText::findNegative(){

    if (std::atof(text.c_str())<0) _negative = true;
    else _negative = false;
}
