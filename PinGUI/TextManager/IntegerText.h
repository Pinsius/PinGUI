#ifndef INTEGERTEXT_H
#define INTEGERTEXT_H

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

#include "Text.h"

class IntegerText: public Text
{
    private:

        //In case of storing variable data
        int* _variable;

        int _last_var;

        bool _tmpInput;

        int _tmpInteger;

        /**
            Private methods
        **/
        void reloadString();

    public:
        IntegerText(PinGUI::Vector2<GUIPos> pos, textInfo* info, int* Variable);
        ~IntegerText();

        void needUpdate(textInfo* info, bool& update) override;

        void getNewText(textInfo*& info) override;

        void addChar(char* ch, bool change = true) override;

        void setChar(char ch, int pos) override;

        void removeChar() override;

        float getVariableNum() override;

        bool checkCharAddition(char* ch, int& maxValue) override;

        void endInputManipulation() override;
};

#endif // INTEGERTEXT_H
