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

#include "GUI_Element.h"

GUI_Element::GUI_Element():
    _collidable(true),
    _show(true),
    _networkedElement(false),
    _allowCropp(true),
    _exist(true)
{

}

GUI_Element::~GUI_Element()
{
    for (std::size_t i = 0; i < _SPRITES.size(); i++){
        delete _SPRITES[i];
    }

    _SPRITES.clear();
}

bool GUI_Element::collide(bool& needUpdate, GUI_Element** manipulatingElement){

    if (_collidable && _show){

        //Checking the collision with the cursor
        if (GUI_CollisionManager::isColliding(GUI_Cursor::getCollider(),_COLLIDERS[0])){

            if (!_aimON){

                turnOnAim();
                needUpdate = true;

                //Every element can modify something else via this function
                onAim();

                return true;
            } else {

                /**
                    Here i listen for click
                */
                //Every element can have its own listenForClick function
                listenForClick(manipulatingElement);

                return true;
            }
        } else if (_aimON){

            turnOffAim();
            needUpdate = true;

            //Every element can modify something else via this function
            onEndAim();
        }
        doAdditionalFunc();
    }
    return false;
}

void GUI_Element::turnOnAim(){

    _aimON = true;
    setWritingAvailability(_aimON);
    Input_Manager::setState(GUI);
}

void GUI_Element::turnOffAim(){

    _aimON = false;
    setWritingAvailability(_aimON);
    Input_Manager::setState(GAME);
}


void GUI_Element::onAim(){

}

void GUI_Element::endManipulatingMod(GUI_Element** manipulatingElement){

    *manipulatingElement = nullptr;
    Input_Manager::setInputState(GAMEINPUT);
    Input_Manager::destroyManipulatingModInfo();
    Input_Manager::setAlreadyClick(false);
    SDL_SetRelativeMouseMode(SDL_FALSE);
}

bool GUI_Element::listenForClick(GUI_Element** manipulatingElement){

    if (!Input_Manager::hasAlreadyClicked()){

        if (Input_Manager::clicked(SDL_BUTTON_LEFT)){

            Input_Manager::setAlreadyClick(true);
            onClick();
            return true;
        }

        return false;
    }
    return false;
}

void GUI_Element::addCollider(float x, float y, int w, int h){
    _COLLIDERS.emplace_back(x,y,w,h);
}

void GUI_Element::addCollider(PinGUI::Rect tmpRect){
    _COLLIDERS.emplace_back(tmpRect);
}

void GUI_Element::addSprite(PinGUI::Rect rect,SDL_Surface* source,SDL_Color color){
    _SPRITES.push_back(new GUI_Sprite(rect,source,color));
}

void GUI_Element::addSprite(PinGUI::Rect rect,SDL_Surface* source){
    _SPRITES.push_back(new GUI_Sprite(rect,source));
}

void GUI_Element::addSprite(int x, int y, SDL_Surface* source){

    PinGUI::Vector2<GUIPos> vect(x,y);
    _SPRITES.push_back(new GUI_Sprite(vect,source));
}


PinGUI::Rect* GUI_Element::getCollider(int pos){
    return &_COLLIDERS[pos].rect;
}

GUIRect* GUI_Element::getGUICollider(int pos){
    return &_COLLIDERS[pos];
}

void GUI_Element::draw(int& pos){

    if (_show){

        for (std::size_t i = 0; i < _SPRITES.size(); i++){

            glBindTexture(GL_TEXTURE_2D,getTexture(i));
            glDrawArrays(GL_TRIANGLES,pos*6,6);
            pos++;
        }
    } else {

        pos += _SPRITES.size();
        return;
    }
}

GLuint GUI_Element::getTexture(int pos){
    return _SPRITES[pos]->getTexture();
}

vboData* GUI_Element::getVBOData(int pos){
    return _SPRITES[pos]->getVBOData();
}

void GUI_Element::loadData(std::vector<vboData>* vboData){
    for (std::size_t i = 0; i < _SPRITES.size(); i++){
        vboData->push_back(*getVBOData(i));
    }
}

GUI_Sprite* GUI_Element::getSprite(int pos){

    if (pos!=-1)
        return _SPRITES[pos];
    else if (pos==-1 && _SPRITES.size()>0 )
        return _SPRITES.back();
    else
        ErrorManager::systemError("Trying to: GUI_Element getSprite a non existing sprite");
}

void GUI_Element::setCollider(PinGUI::Rect rect,int pos){
    _COLLIDERS[pos] = rect;
}

void GUI_Element::moveElement(const PinGUI::Vector2<GUIPos>& vect){

    for (std::size_t i = 0; i < _SPRITES.size(); i++){
        _SPRITES[i]->moveSprite(vect);
    }

    for (std::size_t i = 0; i < _COLLIDERS.size(); i++){
        moveCollider(_COLLIDERS[i],vect);
    }
    _position += vect;
}

void GUI_Element::moveTo(PinGUI::Vector2<GUIPos> vect){
    vect -= _position;

    moveElement(vect);
}

void GUI_Element::normalizeElement(const PinGUI::Vector2<GUIPos>& vect){

    //Have to store the oldPosition because the position will be modified in moveTo function
    PinGUI::Vector2<GUIPos> oldPosition(_position);

    moveTo(vect);

    //Flip Y
    oldPosition.y *= -1;
    moveElement(oldPosition);
}

void GUI_Element::moveCollider(GUIRect& rect,const PinGUI::Vector2<GUIPos>& vect){
    rect.addPos(vect);
}

void GUI_Element::moveCollider(PinGUI::Rect& rect,const PinGUI::Vector2<GUIPos>& vect){
    rect.addPos(vect);
}

void GUI_Element::info(){
    std::cout << "Undefined element. Address: " << this << std::endl;
}

void GUI_Element::setShow(bool state){

    _show = state;
}

bool GUI_Element::getShow(){
    return _show;
}

void GUI_Element::deleteSprite(int pos){
    delete _SPRITES[pos];
    _SPRITES.erase(_SPRITES.begin()+pos);
}

void GUI_Element::deleteCollider(int pos){
    _COLLIDERS.erase(_COLLIDERS.begin()+pos);
}

elementType GUI_Element::getElementType(){
    return BLANK;
}

void GUI_Element::setX(float x){

    for (std::size_t i = 0; i < _SPRITES.size(); i++)
        _SPRITES[i]->setX(x);
    for (std::size_t i = 0; i < _COLLIDERS.size(); i++)
        _COLLIDERS[i].rect.x = x;

    _position.x = x;
}

void GUI_Element::setY(float y){

    for (std::size_t i = 0; i < _SPRITES.size(); i++)
        _SPRITES[i]->setY(y);
    for (std::size_t i = 0; i < _COLLIDERS.size(); i++)
        _COLLIDERS[i].rect.y = y;

    _position.y = y;
}

float GUI_Element::getY(){
    return 0;
}

float GUI_Element::getX(){
    return 0;
}

void GUI_Element::setNetworking(bool state){
    _networkedElement = state;
}

bool GUI_Element::getNetworking(){
    return _networkedElement;
}

float GUI_Element::getTopPoint(int pos){
    return getSprite(pos)->getY() + getSprite(pos)->getH();
}

void GUI_Element::initPosition(const PinGUI::Rect& rect){
    _position.x = rect.x;
    _position.y = rect.y;
}

PinGUI::Vector2<GUIPos> GUI_Element::getPositionVector(){
    return _position;
}

PinGUI::Vector2<GUIPos>* GUI_Element::getPositionVector_P(){
    return &_position;
}

void GUI_Element::cropElement(PinGUI::Rect& rect){

    for (std::size_t i = 0; i <_SPRITES.size(); i++){

        CropManager::cropSprite(_SPRITES[i],rect);
    }

    for (std::size_t i = 0; i < _COLLIDERS.size(); i++){

        CropManager::cropRect(rect,_COLLIDERS[i]);
    }
}

bool GUI_Element::getCollidable(){
    return _collidable;
}

void GUI_Element::setAllowCrop(bool state){
    _allowCropp = state;
}

bool GUI_Element::isAllowedCrop(){
    return _allowCropp;
}

void GUI_Element::setExist(bool state){
    _exist = state;
}

bool GUI_Element::exist(){
    return _exist;
}
