#ifndef WINDOWMOVER_H
#define WINDOWMOVER_H

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

#include "../GUI_Element.h"

/**
    This element contains a sprite with transparency at 100%
    It is used for moving the window
**/


class WindowMover: public GUI_Element
{
private:
        bool* _windowUpdate;

        /**
            Private methods
        **/

        void optionCollider();

public:
        WindowMover(PinGUI::Rect tmpRect, bool* windowUpdate);
        ~WindowMover();

        void onClick() override;

        void manipulatingMod(GUI_Element** manipulatingElement) override;

        bool listenForClick(GUI_Element** manipulatingElement) override ;

        void info() override;

        void modifyWindow();
};

#endif // WINDOWMOVER_H
