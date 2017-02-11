#ifndef WINDOWSCROLLER_H
#define WINDOWSCROLLER_H

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

#include "PinGUI/GUI_Element.h"
#include "PinGUI/GUI_Elements/Window_Arrow.h"

/**
    When manipulating with sprites, remember,
    Sprite 0 - background sprite
    Sprite 1 - Actual scroll fill

    Collider 0 - collider of fill
**/

class WindowScroller: public GUI_Element
{
    private:
        //Scroller cooperates with arrows - it needs to keep those pointers somewhere
        std::vector<GUI_Element*> _ARROWS;

        //Normal state - vertical or horizontal
        manipulationState _state;

        //Bool to alert the changed state
        bool* _update;

        //Ratio of camera
        float _ratio;

        //Variable for camera
        float _cameraVar;

        //This will call the camera manipulation function for window
        PinGUI::basicPointer _cameraRoll;

        /** Private methods **/
        void checkLimits();

        int calculateScrollerSize(const int& value, int& totalValue);

        void manageScrollerFill(const int& value);
        void calculateRatio(const int& totalValue);

        void onClick() override;
        void manipulatingMod(GUI_Element** manipulatingElement) override;
        bool listenForClick(GUI_Element** manipulatingElement) override;

        void incScroller();
        void decScroller();


    public:
        WindowScroller(manipulationState state, PinGUI::Vector2<float> pos, int value, bool* update);
        ~WindowScroller();

        void createArrows(std::vector<GUI_Element*>* _ELEMENTS);

        void loadScrollMover(int value, int totalValue);

        void setShow(bool state) override;
        void setWritingAvailability(bool state) override;

        void hideScroller();

        void attachScrollerToInput();

        bool checkForWheelMove();

        void modifyArrowPos();

        PinGUI::basicPointer getFuncPointer();

};

#endif // WINDOWSCROLLER_H
