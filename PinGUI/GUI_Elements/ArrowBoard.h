#ifndef ARROWBOARD_H
#define ARROWBOARD_H

/**

    PinGUI

    Copyright (c) 2017 ¼ubomír Barantal <l.pinsius@gmail.com>

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


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <boost/bind.hpp>

#include "../GUI_Elements/ClipBoard.h"
#include "../GUI_Elements/Window_Arrow.h"
#include "../SheetManager.h"

#define ARROW_OFFSET 3
#define HORIZONTAL_ARROWS_OFFSET 4

#define ARROWBOARD_COLLIDER_X 2
#define ARROWBOARD_COLLIDER_Y 2
#define ARROWBOARD_COLLIDER_W -4,5
#define ARROWBOARD_COLLIDER_H -3

class ArrowBoard: public GUI_Element
{
    private:

        std::shared_ptr<GUI_Element> _clipBoard;

        std::vector<std::shared_ptr<GUI_Element>> _ARROWS;

        int* _var;

        int _max;
        int _min;

        int _ratio;

        /**
        Private methods
        **/
        float calculateY(float y, int h);
        float calculateX(float x, int w);

        void incVar();
        void decVar();

    public:
        ArrowBoard(PinGUI::Rect rect, int* var, int max, std::shared_ptr<GUI_Element> clip);
        ArrowBoard(int* var, int max, std::shared_ptr<GUI_Element> clip, int min = 0, int ratio = 1);
        ~ArrowBoard();

        void addArrows(PinGUI::Rect& rect, std::vector<std::shared_ptr<GUI_Element>>& _ELEMENTS, PinGUI::manipulationState state = PinGUI::VERTICAL);

        void info() override;

        void moveElement(const PinGUI::Vector2<GUIPos>& vect) override;

        void cropElement(PinGUI::Rect& rect) override;

};

#endif // ARROWBOARD_H
