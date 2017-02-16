#ifndef WINDOWEXIT_H
#define WINDOWEXIT_H

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

/** EXIT BUTTON **/
#define WINDOW_EXIT_X_OFFSET -15
#define WINDOW_EXIT_Y_OFFSET 12

#define WINDOW_EXIT_W_AREA 27
#define WINDOW_EXIT_H_AREA 22

class WindowExit: public GUI_Element
{
    private:
        bool* _windowClose;

    public:
        WindowExit(PinGUI::Rect positionRect, bool* windowClose);
        ~WindowExit();

        void onClick() override;

        void draw(int& pos) override;

        void setWritingAvailability(bool state) override;

};

#endif // WINDOWEXIT_H
