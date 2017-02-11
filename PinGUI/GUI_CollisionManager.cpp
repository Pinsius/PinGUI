#ifndef GUI_COLLISIONMANAGER_CPP
#define GUI_COLLISIONMANAGER_CPP


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

#include "SDL.h"
#include <iostream>
#include "PinGUI_Rect.hpp"

/**
    In this file are going to be defined different types of collisions in GUIManager created by Pins 2016
**/

namespace GUI_CollisionManager{
    static bool colliding;

    /**
        Use this function for static objects
    **/
    //Function for handling the rectangular collision check between gui elements and cursor
    static bool isColliding(PinGUI::Rect collider1, PinGUI::Rect collider2){
        if (collider1.x < collider2.x + collider2.w && collider1.x  + collider1.w > collider2.x && collider1.y < collider2.y + collider2.h && collider1.y + collider1.h > collider2.y){
            return true;
        } return false;
    }

    //Function for handling the rectangular collision check between gui elements and cursor
    static bool isColliding(PinGUI::Rect collider1, GUIRect collider2){
        if (collider1.x < collider2.rect.x + collider2.rect.w && collider1.x  + collider1.w > collider2.rect.x && collider1.y < collider2.rect.y + collider2.rect.h && collider1.y + collider1.h > collider2.rect.y){
            return true;
        } return false;
    }

    //Normal listener for click
    static bool clicked(SDL_Event* e){
        switch(e->type){
            case SDL_MOUSEBUTTONDOWN : {
                if (e->button.button==SDL_BUTTON_LEFT){
                        return true;
                }
            }
        }
        return false;
    }
}

#endif //GUI_COLLISIONMANAGER_CPP
