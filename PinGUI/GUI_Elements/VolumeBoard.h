#ifndef VOLUMEBOARD_H
#define VOLUMEBOARD_H

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

#define VOLUMEBOARD_MOVER_OFFSET 0
#define VOLUMEBOARD_MOVER_OFFSET_Y -1
#define VOLUMEBOARD_BAR_LENGTH 209

#define VOLUMEBOARD_CLIP_OFFSET_X 220
#define VOLUMEBOARD_CLIP_OFFSET_Y -4

#define VOLUMEBOARD_MOVER_COLLIDER_X 0
#define VOLUMEBOARD_MOVER_COLLIDER_Y -1
#define VOLUMEBOARD_MOVER_COLLIDER_W 0
#define VOLUMEBOARD_MOVER_COLLIDER_H -1
#define VOLUMEBOARD_FILL_OFFSET 1

/**
    Important:
        Sprites : 0 - Background
                  1 - Fill
                  2 - Mover
**/


enum VOLUME_SPRITE{
    VOL_BACKGROUND,
    VOL_FILL,
    VOL_MOVER
};

class VolumeBoard: public GUI_Element
{
    private:
        GUI_Element* _clipBoard;

        int* _var;
        int _lastVar;

        int _max;

        float _ratio;

        bool* _needUpdate;

        /**
            Private methods
        **/
        void calculateRatio();
        void addMover(PinGUI::Rect& tmpRect);
        void addFill(PinGUI::Rect& tmpRect);

        bool needMove();


        void moveMover();
        void moveMover(int distance);
        void checkMover();
        void calculateFill(int& distance);

        int calculatePosition();

        bool listenForClick(GUI_Element** manipulatingElement) override;
        void onClick() override;

        void manipulatingMod(GUI_Element** manipulatingElement);
        void modifyVar();
        void checkForColliderPosition();
    public:
        VolumeBoard(PinGUI::Vector2<GUIPos> pos, int* var, int max, GUI_Element* clip,bool* needUpdate);
        ~VolumeBoard();

        void draw(int& pos);

        void moveElement(const PinGUI::Vector2<GUIPos>& vect) override;
        void cropElement(PinGUI::Rect& rect) override;

        void info() override;

        inline float getDistance(){
            return _SPRITES[VOL_MOVER]->getGUIRect().realRect.getX()-(_SPRITES[VOL_BACKGROUND]->getGUIRect_P()->realRect.x);
        }

};



#endif // VOLUMEBOARD_H
