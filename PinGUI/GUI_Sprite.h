#ifndef GUI_SPRITE_H
#define GUI_SPRITE_H

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

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <iostream>
#include <cstring>

#include "ErrorManager.h"
#include "stuff.h"
#include "PinGUI_Vector.hpp"
#include "PinGUI_Rect.hpp"

typedef float GUIPos;

enum vertexPoint{
    topLeft,
    topRight,
    bottomLeft,
    bottomRight
};

enum VBO_UV_UPDATE_MODE{
    U,
    V,
    UV
};

class GUI_Sprite
{
    private:
        GUIRect _rect;
        SDL_Color _color;
        GLuint _textureID;
        vboData _dataPointer;

        /**
            Private methods
        **/
        void createTexture(SDL_Surface* surface);
        void loadTextSprite(const std::string& text, textInfo*& info);

        void initColor();

    public:
        /** Constructors for normal sprites **/
        GUI_Sprite(PinGUI::Rect rect,SDL_Surface* source);
        GUI_Sprite(PinGUI::Vector2<GUIPos> pos, SDL_Surface* source);
        GUI_Sprite(SDL_Surface* source);
        GUI_Sprite(PinGUI::Rect rect,SDL_Surface* source,SDL_Color color);

        /** Constructors for Text sprites - initialized using SDL_TTF **/
        GUI_Sprite(const std::string& text, PinGUI::Vector2<GUIPos> pos,textInfo* info);
        GUI_Sprite(const std::string& text,textInfo* info);

        ~GUI_Sprite();

        void createVBO(VBO_UV_UPDATE_MODE mode = UV);

        void updateColors();
        void updatePositions();
        void updateUVs();
        void updateVerticalUVs();
        void updateHorizontalUVs();

        void changeTexture(SDL_Surface* surface);
        void moveSprite(const PinGUI::Vector2<GUIPos>& vect);


        void offsetToRect(PinGUI::Rect offsetRect);

        /**
            Getters and setters
        **/

        GLuint getTexture(){return _textureID;}

        PinGUI::Rect getCollider(){return _rect.rect;}
        GUIRect getGUIRect();
        GUIRect* getGUIRect_P();

        void addDimensions(int w, int h);

        void setColor(float R, float G, float B);
        void setPos(PinGUI::Vector2<GUIPos> pos);

        float getX();
        void setX(float x);

        float getY();
        void setY(float y);

        int getW(){return _rect.rect.w;}
        void setW(int newW);
        void decW(int num);
        void incW(int num);

        int getH(){return _rect.rect.h;}
        void setH(int newH);
        void decH(int num);

        void setRH(int rh);
        void setRW(int rw);

        void changeColor(SDL_Color tmp);
        void setAlpha(int value);

        vboData* getVBOData();
        void setRect(PinGUI::Rect rect);
};

#endif // GUI_SPRITE_H
