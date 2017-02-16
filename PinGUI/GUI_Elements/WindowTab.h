#ifndef WINDOWTAB_H
#define WINDOWTAB_H

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
#include "../GUIManager.h"
#include "../SheetManager.h"
#include "../TextManager/Text.h"
#include "../clFunction.hpp"

#define DEFAULT_WINDOWTAB_ALPHA 20
#define ON_COLLIDE_WINDOWTAB_ALPHA 50
#define CHOOSED_WINDOWTAP_ALPHA 5

class WindowTab: public GUI_Element
{
    private:
        //It has its own gui manager(+textmanager)
        GUIManager* _guiManager;

        //Accesing the window´s main tab
        WindowTab** _mainTab;

        //Bool to alert the window
        bool* _tabChange;

        //So tab can acces the tabs title via this
        Text** _tabText;

        PinGUI::basicPointer _function;

        /**
            By default the tabDimensions are set to a Windows dimension
            You can increase it (window will automatically apply a scroller to acces the hidden parts)
            Decreasing it will do nothing ( not recommended )
            x - width
            y - height
        **/
        PinGUI::Vector2<int> _tabDimensions;

        /**
           Private methods
        **/
        void initSprites(PinGUI::Rect& positionRect);

    public:
        WindowTab(){};
        WindowTab(PinGUI::Rect positionRect,WindowTab** mainTab, bool* tabChange);
        WindowTab(TextManager* texter);
        ~WindowTab();

        void render();

        void update();

        bool listenForClick(GUI_Element** manipulatingElement) override;

        void onClick() override;

        void setWritingAvailability(bool state) override;

        void info() override;

        void setMainTab(WindowTab** mainTab );

        void setTabText(Text* text);

        void setRollBackFunction(PinGUI::basicPointer Function);

        //Dimensions manipulation
        void setTabDimensions(PinGUI::Rect& rect);
        void setTabDimensions(PinGUI::Vector2<int> dims);
        void setTabHeight(int height);
        void setTabWidth(int width);
        PinGUI::Vector2<int> getTabDimensions();

        GUIManager* getGUI();


};

#endif // WINDOWTAB_H
