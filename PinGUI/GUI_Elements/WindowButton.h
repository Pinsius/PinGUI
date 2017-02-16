#ifndef WINDOWBUTTON_H
#define WINDOWBUTTON_H

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

#include "../GUI_Elements/Button.h"
#include "../GUI_Elements/Window.h"

class WindowButton: public Button
{
    private:
        Window* _target;
        bool _switchState;

    public:
        WindowButton(int x, int y, std::string name, clipboardData data);
        WindowButton(int x, int y, std::string name, clipboardData data, PinGUI::basicPointer f);
        WindowButton(int x, int y, std::string name, clipboardData data, PinGUI::basicPointer f, int maxSize);
        ~WindowButton();

        void onClick() override;

        void setWindowTarget(Window* target);

        void setState(bool state);

};

#endif // WINDOWBUTTON_H
