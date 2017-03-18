#ifndef SCROLLER_H
#define SCROLLER_H

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
#include <boost/bind.hpp>

#include "../GUI_Elements/Window_Arrow.h"

#define WINDOW_SCROLLER_ARROW_MOVEMENT 7

#define SCROLLING_NORMALIZE 0.3

struct scrollNormalizer{

    int _PLUS;
    int _MINUS;
    int _RATIO;
};

class Scroller: public GUI_Element
{
    protected:

        //Scroller cooperates with arrows - it needs to keep those pointers somewhere
        std::vector<std::shared_ptr<Window_Arrow>> _ARROWS;

        //Bool to alert the changed state
        bool* _update;

        //Ratio of camera
        int _ratio;

        //Maximum possible scroll
        int _max;

        //This will call the camera manipulation function for window
        PinGUI::scrollFuncPointer _cameraRoll;

        //Keep track of addition/dec of var
        int _oldPos;

        int _oldDiff;

        //NORMALIZER
        scrollNormalizer _NORMALIZER;

        /** Private methods **/
        virtual void initNormalizer(const int& totalValue, const int& numOfPixels);

        virtual int useNormalizer(CHANGER change, int diff){};

        virtual void createArrows(std::vector<std::shared_ptr<GUI_Element>>* _ELEMENTS){};

        virtual void modifyArrowPos(){} ;

        virtual void checkLimits(){};

        virtual int calculateScrollerSize(const int& value, int& totalValue){};

        virtual void manageScrollerFill(const int& value){};

        virtual void calculateRatio(const int& totalValue){};

        virtual void decide(){};

        virtual void initOldPos(){};

        virtual void incScroller(){};

        virtual void decScroller(){};

        virtual void moveOldPos(const PinGUI::Vector2<GUIPos>& vect){};

        virtual int getDiff(){};

        void manageFunctionality();

    public:
        Scroller(PinGUI::Vector2<GUIPos> pos, bool* update);
        virtual ~Scroller() = 0;

        void setShow(bool state) override;

        void setWritingAvailability(bool state) override;

        void moveElement(const PinGUI::Vector2<GUIPos>& vect) override;

        void manipulatingMod(manip_Element manipulatingElement) override;

        bool listenForClick(manip_Element manipulatingElement) override;

        void info() override;

        void loadScrollMover(int value, int totalValue);

        void hideScroller();

        void attachScrollerToInput();

        void checkForWheelMove();

        PinGUI::scrollFuncPointer getFuncPointer();
        void setCamRollFunction(PinGUI::scrollFuncPointer f);
};

#endif // SCROLLER_H
