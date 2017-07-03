#include "FloatText.h"

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

#include <iomanip>
#include <cstdlib>

FloatText::FloatText(PinGUI::Vector2<GUIPos> pos, textInfo* info, float* Variable):
    _variable(Variable),
    _last_var(*Variable),
    _tmpInput(false),
    _negative(false),
    _tmpFloat(EMPTY_TMP_INPUT)
{
    _construct.numOfFloatingNums = 0;
    _construct.pointNum = 0;
    _construct.baseInt = static_cast<int>((*Variable));

    reloadString();

    init(text,pos);

    _sprite = std::make_shared<GUI_Sprite>(text,pos,info);
}

FloatText::~FloatText()
{
    //dtor
}

void FloatText::reloadString(){

    std::stringstream tmpString;

    tmpString << std::fixed << std::setprecision(FLOAT_TEXT_PRECISION) << *_variable;

    text = tmpString.str();
}

void FloatText::needUpdate(textInfo* info, bool& update){

    if ((*_variable != _last_var) || changed){

        if (_tmpInput)
            _tmpFloat = float(std::atof(text.c_str()));

        getNewText(info);

        update = true;

        changed = false;

        return;
    }

    checkPositioned(update);
}

void FloatText::getNewText(textInfo*& info){

    if (!_tmpInput){

        if (changed && (_tmpFloat != EMPTY_TMP_INPUT)){

            *_variable = _tmpFloat;
            _tmpFloat = EMPTY_TMP_INPUT;
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

bool FloatText::findPoint(){

    reachedPoint = false;

    for (std::size_t i = 0; i < text.size(); i++){

        if (!reachedPoint){
            if (text[i]=='.'){

                return true;
            }
        }
    }

    return false;
}

void FloatText::addChar(char* ch, bool change){

    if ((text[0]==' ' && text.size()==1) && *ch != '.'){

        text[0] = *ch;
        _tmpInput = true;
        changed = change;

        return;
    }

    _tmpInput = true;
    text += *ch;

    changed  = change;
}

void FloatText::setChar(char ch, int pos){

    text[pos] = ch;

    *_variable = float(std::atof(text.c_str()));

    changed = true;
}

void FloatText::removeChar(){

    if (text.back() == '-' && _negative)
        _negative = false;
    text.pop_back();

    if (text.size()==0)
        text.push_back(' ');

    _tmpInput = true;

    changed = true;
}

float FloatText::getVariableNum(){
    return _tmpFloat;
}

float FloatText::calculateAddition(char*& ch){

    unsigned int pointNum = 0;
    bool point = false;
    float divider = 10.0f;

    for (std::size_t i = 0; i < text.size(); i++){

         if (!point){

            if (isPoint(&text[i]))
                point = true;

            continue;
         } else {

            pointNum++;
         }
    }

    for (std::size_t i = 0; i < pointNum; i++)
        divider *= 10.0f;

    if (point){

        return (getCharNum(ch) / divider);
    } else {

        return (((float(std::atof(text.c_str())*10)) + getCharNum(ch)) - float(std::atof(text.c_str())));
    }
}

bool FloatText::checkCharAddition(char* ch, int& maxValue, int& minValue){

    findNegative();

    if (isPoint(ch)){

        return (!findPoint());
    }

    if (_negative){

        std::string tmpText(text);
        tmpText.push_back(*ch);

        if (std::atof(tmpText.c_str()) < minValue)
            return false;

    } else {

        if (((std::atof(text.c_str()) + calculateAddition(ch) ) > maxValue))
            return false;
    }

    if (canWritePoint())
        return true;
    else return false;
}

bool FloatText::canWritePoint(){

    int pointNum = 0;
    bool point = false;

    for (std::size_t i = 0; i < text.size(); i++){

         if (!point){

            if (isPoint(&text[i]))
                point = true;

            continue;
         } else {

            pointNum++;
         }
    }

    pointNum++;

    if ((pointNum <= FLOAT_TEXT_PRECISION))
        return true;
    else
        return false;
}

bool FloatText::isPoint(char* ch){
    return (*ch == '.');
}

void FloatText::endInputManipulation(){

    _tmpInput = false;

    changed = true;
}

void FloatText::turnOnNegative(){
    _negative = true;
}

void FloatText::findNegative(){

    if (std::atof(text.c_str())<0) _negative = true;
    else _negative = false;
}
