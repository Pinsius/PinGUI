#ifndef HORIZONTALSCROLLER_H
#define HORIZONTALSCROLLER_H

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

#include "../GUI_Elements/Scroller.h"

#define NORMALIZE_FL 0.09

/**
    When manipulating with sprites, remember,
    Sprite 0 - background sprite
    Sprite 1 - Actual scroll fill

    Collider 0 - collider of fill
**/

class HorizontalScroller: public Scroller
{
    private:

        /** Private methods **/
        int useNormalizer(CHANGER change, int diff) override;

        void checkLimits() override;

        int calculateScrollerSize(const int& value, int& totalValue) override;

        void manageScrollerFill(const int& value) override;

        void calculateRatio(const int& totalValue) override;

        void decide() override;

        void initOldPos() override;

        void incScroller() override;

        void decScroller() override;

        void moveOldPos(const PinGUI::Vector2<GUIPos>& vect) override;

        //This one is from GUI_Element
        void onClick() override;

        int getDiff() override;

    public:
        HorizontalScroller(PinGUI::Vector2<GUIPos> pos, int value, bool* update, std::vector<std::shared_ptr<GUI_Element>>* _ELEMENTS);
        ~HorizontalScroller();

        void createArrows(std::vector<std::shared_ptr<GUI_Element>>* _ELEMENTS) override;

        void modifyArrowPos() override;

        void reloadScroller(int value, int totalValue) override;
};

#endif // HORIZONTALSCROLLER_H
