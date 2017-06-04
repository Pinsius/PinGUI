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
#include <memory>

#include "../GUI_Sprite.h"

#define EMPTY_TMP_INPUT -1

class Text
{
protected:
    std::shared_ptr<GUI_Sprite> _sprite;

    PinGUI::Vector2<GUIPos> _position;

    std::string text;

    bool active;

    bool changed;

    bool positioned;

    bool _networkedText;

    bool _show;

    //In case of offseting to some rect
    PinGUI::Rect _offsetRect;

    bool _haveOffsetRect;

    /**
        Private methods
    **/

    void checkPositioned(bool& update);

    void init(std::string Text, PinGUI::Vector2<GUIPos> pos);

    float getCharNum(char* ch);

public:
    Text();
    Text(std::string Text, PinGUI::Vector2<GUIPos> pos, textInfo* info);
    ~Text();

    virtual void needUpdate(textInfo* info, bool& update);

    //For creating a new copy
    virtual void getNewText(textInfo*& info);

    virtual void addChar(char* ch, bool change = true);

    virtual void setChar(char ch, int pos);

    virtual void removeChar();

	virtual float getVariableNum() { return 0.0f; }

    virtual bool checkCharAddition(char* ch, int& maxValue, int& minValue){return true;}

    virtual bool isZero();

    virtual void endInputManipulation(){};

    virtual void turnOnNegative() {};

    void normalizeText(const PinGUI::Vector2<GUIPos>& vect);

    void adaptToClipBoard();

    void moveText(const PinGUI::Vector2<GUIPos>& vect, bool croppedMovement = false);

    void moveTo(PinGUI::Vector2<GUIPos> vect);

    void replaceText(std::string newText);

    std::shared_ptr<GUI_Sprite> getSprite();

    bool canAcceptNegativeInput();

    bool isActive();

    GUIPos getX();

    GUIPos getY();

    std::string getString();

    void setActive(bool state);

    vboData getVBOData();

    bool isPositioned();

    PinGUI::Vector2<GUIPos> getPos();

    PinGUI::Vector2<GUIPos>* getPos_P();

    void setPos(PinGUI::Vector2<GUIPos> setPos);

    void setOffsetRect(PinGUI::Rect offsetRect);

    void calculateTextPosition();

    bool isNetworked();

    void setNetworked(bool state);

    int getTextSize();

    bool isEmpty();

    bool isChanged();

    bool getShow();

    void setShow(bool state);
};

#endif // TEXT_H
