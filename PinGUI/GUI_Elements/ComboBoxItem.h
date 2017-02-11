#ifndef COMBOBOXITEM_H
#define COMBOBOXITEM_H

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


#include "PinGUI/GUI_Elements/ClipBoard.h"

class ComboBoxItem: public ClipBoard
{
    private:

        ComboBoxItem** _mainComboBoxItem;

        //Callback function
        PinGUI::basicPointer _function;

        int _option;

    public:
        ComboBoxItem(PinGUI::Vector2<GUIPos> position,
                     std::string itemText,
                     ComboBoxItem** mainComboBoxItem,
                     PinGUI::basicPointer functionP,
                     int maxSize,
                     clipboardData& data);

        ~ComboBoxItem();

        void onClick() override;

        bool listenForClick(GUI_Element** manipulatingElement) override;

        void cropElement(PinGUI::Rect& rect) override;

        void setOption(int opt);
        int getOption(void);
};

#endif // COMBOBOXITEM_H
