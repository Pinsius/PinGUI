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

#include "Text.h"
#include <iostream>

Text::Text(){

}

Text::Text(std::string Text, PinGUI::Vector2<GUIPos> pos, textInfo* info):
    text(Text),
    active(true),
    changed(false),
    positioned(false),
    _haveOffsetRect(false),
    _networkedText(false),
    _show(true),
    _position(pos)
{
    if (text.size()==0)
        text.push_back(' ');

    _sprite = std::make_shared<GUI_Sprite>(text,pos,info);
}

Text::~Text()
{
}

void Text::init(std::string Text, PinGUI::Vector2<GUIPos> pos){
    active = true;
    text = Text;
    changed = false;
    positioned = false;
    _haveOffsetRect = false;
    _networkedText = false;
    _show = true;

    _position = pos;
}

void Text::needUpdate(textInfo* info, bool& update){

    if (changed){

        getNewText(info);

        update = true;
        changed = false;

        return;
    }

    checkPositioned(update);
}

void Text::checkPositioned(bool& update){

    if (positioned){

        positioned = false;

        if (!update)
            update = true;
    }
}

void Text::getNewText(textInfo*& info){

    _sprite.reset();
    _sprite = std::make_shared<GUI_Sprite>(text,_position,info);

    if (_haveOffsetRect){
        calculateTextPosition();
    }
}

void Text::replaceText(std::string newText){

    text = newText;

    changed = true;
}

void Text::addChar(char* ch, bool change){

    if ((text[0]==' ' && text.size()==1)){

        text[0] = *ch;
    } else {

        text += *ch;
    }

    changed  = change;
}

void Text::setChar(char ch, int pos){

    text[pos] = ch;

    changed = true;
}

void Text::removeChar(){

    text.pop_back();

    if (text.size() == 0)
        text.push_back(' ');

    changed = true;
}

void Text::setPos(PinGUI::Vector2<GUIPos> setPos){

    _position.x = setPos.x;
    _position.y = setPos.y;

    _sprite->setPos(_position);

    positioned = true;
}

void Text::calculateTextPosition(){

    GUIPos tmpX = _offsetRect.x + (_offsetRect.w)/2;
	GUIPos tmpY = _offsetRect.y + (_offsetRect.h)/2;

    PinGUI::Vector2<GUIPos> pos(tmpX - (_sprite->getW())/2,tmpY - (_sprite->getH())/2);

    setPos(pos);
}

int Text::getTextSize(){
    if (text[0]==' ' && text.size()==1) return 0;
    else return text.size();
}

bool Text::isEmpty(){
    return text.size()==0;
}

bool Text::isChanged(){
    return changed;
}

void Text::moveText(const PinGUI::Vector2<GUIPos>& vect, bool croppedMovement){

    _sprite->moveSprite(vect);
    _position += vect;

    _offsetRect.addPos(vect);

    positioned = true;
}

void Text::moveTo(PinGUI::Vector2<GUIPos> vect){
    vect -= _position;

    moveText(vect);
}

void Text::normalizeText(const PinGUI::Vector2<GUIPos>& vect){

    if (!_haveOffsetRect){

        //Have to store the oldPosition because the position will be modified in moveTo function
        PinGUI::Vector2<GUIPos> oldPosition(_position);

        moveTo(vect);

        //Flip Y
        oldPosition.y *= -1;
        moveText(oldPosition);
    }
}

void Text::setOffsetRect(PinGUI::Rect offsetRect){

    _offsetRect = offsetRect;
    _haveOffsetRect = true;

    calculateTextPosition();
}

bool Text::isNetworked(){
    return _networkedText;
}

void Text::setNetworked(bool state){
    _networkedText = state;
}

bool Text::getShow(){
    return _show;
}

void Text::setShow(bool state){
    _show = state;
}

PinGUI::Vector2<GUIPos> Text::getPos(){
    return _position;
}

PinGUI::Vector2<GUIPos>* Text::getPos_P(){
    return &_position;
}

std::shared_ptr<GUI_Sprite> Text::getSprite(){
    return _sprite;
}

bool Text::isActive(){
    return active;
}

GUIPos Text::getX(){
    return _position.x;
}

GUIPos Text::getY(){
    return _position.y;
}

std::string Text::getString(){
    return text;
}

void Text::setActive(bool state){
    active = state;
}

vboData Text::getVBOData(){
    return *(_sprite->getVBOData());
}

bool Text::isPositioned(){
    return positioned;
}

bool Text::isZero(){
    return text[0]=='0';
}

float Text::getCharNum(char* ch){
    return ((*ch)-48.0f);
}

bool Text::canAcceptNegativeInput(){
    if (text[0]==' ' && text.size()==1)
        return true;
    else return false;
}
