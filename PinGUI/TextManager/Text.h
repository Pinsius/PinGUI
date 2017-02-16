#ifndef TEXT_H
#define TEXT_H

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

#include <sstream>
#include <cstdlib>

#include "../GUI_Sprite.h"

    class Text
    {
    private:
        GUI_Sprite* _sprite;

        PinGUI::Vector2<GUIPos> _position;

        std::string text;

        bool active;

        bool changed;

        bool positioned;

        bool _networkedText;

        bool _show;

        //In case of storing variable data
        int* variable;
        int last_var;

        //In case of offseting to some rect
        PinGUI::Rect _offsetRect;
        bool _haveOffsetRect;

    public:

        Text(std::string Text, PinGUI::Vector2<GUIPos> pos, textInfo* info);
        Text(std::string Text, PinGUI::Vector2<GUIPos> pos, textInfo* info, int* Variable);
        ~Text();

        void normalizeText(const PinGUI::Vector2<GUIPos>& vect);

        void adaptToClipBoard();

        void moveText(const PinGUI::Vector2<GUIPos>& vect, bool croppedMovement = false);

        void moveTo(PinGUI::Vector2<GUIPos> vect);

        void needUpdate(textInfo* info, bool& update);

        //For creating a new copy
        void getNewText(textInfo*& info);

        void replaceText(std::string newText);

        GUI_Sprite* getSprite(){return _sprite;}

        bool isActive(){return active;}

        GUIPos getX(){return _position.x;}

        GUIPos getY(){return _position.y;}

        int* getVar(){return variable;}

        PinGUI::Vector2<GUIPos> getPos();

        PinGUI::Vector2<GUIPos>* getPos_P();

        std::string getString(){return text;}

        void setPos(PinGUI::Vector2<GUIPos> setPos);

        void setOffsetRect(PinGUI::Rect offsetRect);

        void setActive(bool state){active = state;}

        void addChar(char* ch);
        void setChar(char ch, int pos);
        void removeChar();

        vboData getVBOData(){return *_sprite->getVBOData();}

        void calculateTextPosition();

        bool isPositioned(){return positioned;}

        bool isNetworked();
        void setNetworked(bool state);

        int getTextSize();

        int getNumericalText();

        int getVariableNum();

        bool haveNum();

        bool isZero();

        bool isEmpty();

        bool isChanged();

        bool getShow();
        void setShow(bool state);
    };


#endif // TEXT_H
