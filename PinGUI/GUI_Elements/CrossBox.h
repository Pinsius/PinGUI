#ifndef CROSSBOX_H
#define CROSSBOX_H

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

#include <iostream>

#include "../GUI_Element.h"

#define CHECKBOX_COLLIDER_X 1
#define CHECKBOX_COLLIDER_Y 1
#define CHECKBOX_COLLIDER_W -1
#define CHECKBOX_COLLIDER_H -1

class CrossBox: public GUI_Element
{
    private:

        bool* _var;

        bool _last_var;

        /**
            Private methods
        **/
        void onClick() override;

        void setWritingAvailability(bool state) override;

        bool hasChanged();

        void change();
    public:
        CrossBox(int x, int y, bool* var);
        ~CrossBox();

        void info() override;

        void update() override;
};

#endif // CROSSBOX_H
