#ifndef BUTTON_H
#define BUTTON_H

/**

    PinGUI

    Copyright (c) 2017 ¼ubomír Barantal <l.pinsius@gmail.com>

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


#include "PinGUI/GUI_Elements/ClipBoard.h"

class Button: public ClipBoard
{
    protected:

        PinGUI::basicPointer _func;

        /**
            Private methods
        **/
        void initSprites(std::string name, clipboardData& data);

    public:
        Button(int x, int y, std::string name, clipboardData data);
        Button(int x, int y, std::string name, PinGUI::basicPointer f, clipboardData data);
        Button(int x, int y, std::string name, PinGUI::basicPointer f, clipboardData data, int maxSize);
        ~Button();

        void onClick() override;

        void onAim() override;

        void onEndAim() override;

        void setWritingAvailability(bool state) override;

        bool listenForClick(GUI_Element** manipulatingElement) override;

};

#endif // BUTTON_H
