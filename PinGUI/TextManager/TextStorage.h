#ifndef TEXTSTORAGE_H
#define TEXTSTORAGE_H

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

#include "../TextManager/TextManager.h"
#include "../stuff.h"

struct additionalStorage{
    PinGUI::Rect* offsetRect;
    clipboard_type* type;
};

class TextStorage
{
    private:
        //It is holding pointers to texts and also a pointer to the textmanager
        std::vector<Text*> _TEXTS;

        TextManager* texter;

        //Pointer to an additional informations - in case of clipboards, etc.
        additionalStorage* _additionalStorage;

    public:
        TextStorage(TextManager* text);
        ~TextStorage();

        void addText(const std::string& text, int x, int y) ;
        void addText(const std::string& text, int x, int y, int* var);

        void destroyText(int position = 0);

        void addChar(char* ch, int position, int maxValue);
        void removeChar(int position);

        Text* getText(int position = 0);

        std::vector<Text*>* getVector();

        void setAdditionalInfo(PinGUI::Rect* OffsetRect, clipboard_type* Type);

        void proccess(char* ch);
};

#endif // TEXTSTORAGE_H
