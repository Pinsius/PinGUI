#ifndef WINDOW_ARROW_H
#define WINDOW_ARROW_H

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

#define BASIC_ARROW_Y_OFFSET 2

#define WINDOW_ARROW_WIDTH 11
#define WINDOW_ARROW_HEIGHT 11

enum arrowCollider{
    WHOLE_RECT,
    ARROW_ONLY
};

class Window_Arrow: public GUI_Element
{
    private:

        //Collider type
        arrowCollider _arrowCollider;

        //Callback function that is called onClick
        PinGUI::basicPointer _clFunction;

        /**
            Private methods
        **/
        SDL_Surface* chooseRightDirect(orientation& orient);

        void setUpBackgroundSprite(const PinGUI::Rect& tmpRect);

        void highlightRect(const bool& state);

        void highlightArrow(const bool& state);

        void createCollider(PinGUI::Rect& tmpRect, arrowCollider& colliderType, orientation& orient);

    public:
        Window_Arrow(PinGUI::Rect tmpRect, SDL_Surface* surface, orientation orient, arrowCollider colliderType = WHOLE_RECT);
         ~Window_Arrow();

        void setWritingAvailability(bool state) override;

        void onClick() override;

        void setClickFunction(PinGUI::basicPointer method);

};

#endif // WINDOW_ARROW_H
