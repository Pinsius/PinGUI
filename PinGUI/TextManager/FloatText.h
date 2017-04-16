#ifndef FLOATTEXT_H
#define FLOATTEXT_H

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

#include <string>

#include "Text.h"

#define FLOAT_TEXT_PRECISION 3

struct floatTextConstruction{

    int baseInt;
    long pointNum;
    int numOfFloatingNums;
};

class FloatText: public Text
{
    private:

        //In case of storing variable data
        float* _variable;

        float _last_var;

        bool reachedPoint;

        bool _tmpInput;

        float _tmpFloat;

        floatTextConstruction _construct;

        /**
            Private methods
        **/
        void reloadString();

        bool findPoint();

        bool isPoint(char* ch);

        bool canWritePoint();

        float calculateAddition(char*& ch);

    public:
        FloatText(PinGUI::Vector2<GUIPos> pos, textInfo* info, float* Variable);
        ~FloatText();

        void needUpdate(textInfo* info, bool& update) override;

        void getNewText(textInfo*& info) override;

        void addChar(char* ch, bool change = true) override;

        void setChar(char ch, int pos) override;

        void removeChar() override;

        float getVariableNum() override;

        bool checkCharAddition(char* ch, int& maxValue) override;

        void endInputManipulation() override;
};

#endif // FLOATTEXT_H
