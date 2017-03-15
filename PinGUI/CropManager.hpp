#ifndef CROPMANAGER_HPP
#define CROPMANAGER_HPP

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

#include <memory>

#include "GUI_Sprite.h"
#include "PinGUI_Rect.hpp"
#include "GUI_CollisionManager.cpp"
#include "clFunction.hpp"
#include "GL_Vertex.h"

#define NORMALIZE_CONSTANT 1

enum orientation
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class CropManager{

    private :

        static int _cropVar;

        static int _cropSize;

        static PinGUI::Rect _lastCropRect;


        /**
            COLLIDER RECTANGLES
        **/

        //Normal checking
        static void repairRect(int& var, const int& maxVar);

        static bool doCropping(PinGUI::Rect& cropRect, GUIRect& dstRect);

        static void cropHorizontally(PinGUI::Rect& cropRect, GUIRect& dstRect);

        static void cropVertically(PinGUI::Rect& cropRect, GUIRect& dstRect);

        static void finishCropping(int& targetVar, int& maxVar);

        /**
            SPRITES
        **/

        static void changeUV(orientation orient, vboData* dataPointer, PinGUI::Vector2<float> percentage);

        static void cropSpriteVertically(GUI_Sprite*& sprite, PinGUI::Rect& cropRect);

        static void cropSpriteHorizontally(GUI_Sprite*& sprite, PinGUI::Rect& cropRect);

    public :

        //Cropping GUIRectangles
        static void cropRect(PinGUI::Rect cropRect, GUIRect& dstRect);

        /** CROPPING SPRITES **/
        static void cropSprite(GUI_Sprite* sprite, PinGUI::Rect cropRect);

};
#endif // CROPMANAGER_HPP
