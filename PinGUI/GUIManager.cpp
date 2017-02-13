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

#include "GUIManager.h"

GUIManager::GUIManager():
    _needUpdate(false),
    _manipulatingMod(false),
    _manipulatingElement(nullptr),
    _collidingElement(nullptr),
    _moved(false)
{

    _vboMANAGER = new VBO_Manager(100);

    _vboDATA.emplace_back();

    _texter = new TextManager();
}

GUIManager::GUIManager(TextManager* texter):
    _needUpdate(false),
    _manipulatingMod(false),
    _manipulatingElement(nullptr),
    _collidingElement(nullptr),
    _moved(false)
{
    this->_texter = texter;

    _vboMANAGER = new VBO_Manager(100);
}

GUIManager::~GUIManager()
{
    delete _texter;
    delete _vboMANAGER;
    if (_ELEMENTS.size()!=0){
        for (std::size_t i = 0; i < _ELEMENTS.size(); i++){
            delete _ELEMENTS[i];
        }
        _ELEMENTS.clear();
    }

}

void GUIManager::createClipBoard(int x, int y, clipboard_type type, int maxSize, element_shape shape){
    clipboardData tmp;
    tmp.texter = _texter;

    PinGUI::Vector2<GUIPos> position(x,y);

    _ELEMENTS.push_back(new ClipBoard(position, maxSize, type, tmp,shape));

    _needUpdate = true;
}

void GUIManager::createClipBoard(int x, int y, clipboard_type type, int* var, int maxSize, element_shape shape){
    clipboardData tmp;
    tmp.texter = _texter;
    PinGUI::Vector2<GUIPos> position(x,y);

    _ELEMENTS.push_back(new ClipBoard(position,maxSize,type,tmp,var,shape));
    _needUpdate = true;
}

void GUIManager::createComboBox(int x, int y, std::vector<std::string> items, int maxNumOfItems){

    ComboBox* tmpp;

    clipboardData tmp;
    tmp.texter = _texter;

    tmpp = new ComboBox(x,y,items,tmp,&_ELEMENTS, maxNumOfItems,&_needUpdate);

    _ELEMENTS.push_back(tmpp);

    _needUpdate = true;
}

void GUIManager::createComboBox(int x, int y, std::vector<std::string> items, int maxSize, int maxNumOfItems){

    ComboBox* tmpp;

    clipboardData tmp;
    tmp.texter = _texter;

    tmpp = new ComboBox(x,y,items,tmp,&_ELEMENTS, maxNumOfItems,&_needUpdate,maxSize);

    _ELEMENTS.push_back(tmpp);

    _needUpdate = true;
}


void GUIManager::createVolumeBoard(int x, int y, bool clickable, int* var, int maxSize){
    //Block for creating a clipboard
    {
        clipboardData tmp;
        tmp.texter = _texter;
        PinGUI::Vector2<GUIPos> position(x+VOLUMEBOARD_CLIP_OFFSET_X,y+VOLUMEBOARD_CLIP_OFFSET_Y);

        if (clickable){
            _ELEMENTS.push_back(new ClipBoard(position,maxSize,INT_ONLY,tmp,var,ROUNDED));
        } else {
            _ELEMENTS.push_back(new ClipBoard(position,maxSize,UNCLICKABLE,tmp,var,ROUNDED));
        }
    }
    PinGUI::Vector2<GUIPos> tmpPos(x,y);

    _ELEMENTS.push_back(new VolumeBoard(tmpPos,var,maxSize,_ELEMENTS.back(),&_moved));

    _needUpdate = true;
}

void GUIManager::createArrowBoard(int x, int y, int* var, int maxSize, bool clickable , int minSize, manipulationState state){

    //Block for creating a clipboard
    {
        clipboardData tmp;
        tmp.texter = _texter;
        PinGUI::Vector2<GUIPos> position(x,y);

        if (clickable){
            _ELEMENTS.push_back(new ClipBoard(position,maxSize,INT_ONLY,tmp,var));
        } else {
            _ELEMENTS.push_back(new ClipBoard(position,maxSize,UNCLICKABLE,tmp,var));
        }
    }
    PinGUI::Rect tmpRect(x,y,WINDOW_ARROW_W,WINDOW_ARROW_H);

    ArrowBoard* elem = new ArrowBoard(tmpRect,var,maxSize,_ELEMENTS.back());
    elem->addArrows(tmpRect,_ELEMENTS,state);

    _ELEMENTS.push_back(elem);

    _needUpdate = true;
}

void GUIManager::createImage(std::string filePath, int x, int y){

    _ELEMENTS.push_back(new Image(filePath,x,y));

    _needUpdate = true;
}

void GUIManager::createImage(std::string filePath, int x, int y, int width, int height){

    _ELEMENTS.push_back(new Image(filePath,x,y,width,height));

    _needUpdate = true;
}

void GUIManager::createButton(int x, int y, std::string name, PinGUI::basicPointer f){

    clipboardData tmp;
    tmp.texter = _texter;

    _ELEMENTS.push_back(new Button(x,y,name,f,tmp));

    _needUpdate = true;
}


void GUIManager::createButton(int x, int y, std::string name, PinGUI::basicPointer f, int maxSize){

    clipboardData tmp;
    tmp.texter = _texter;

    _ELEMENTS.push_back(new Button(x,y,name,f,tmp,maxSize));

    _needUpdate = true;
}

void GUIManager::createCheckBox(int x, int y, bool* var){
    _ELEMENTS.push_back(new CrossBox(x,y,var));

    _needUpdate = true;
}

void GUIManager::putElement(GUI_Element* object){
    _ELEMENTS.push_back(object);
    _needUpdate = true;
}

void GUIManager::withdrawElement(GUI_Element* object){
    std::size_t i;
    bool found = false;

    for (i = 0; i < _ELEMENTS.size(); i++) {
        if (_ELEMENTS[i]==object){
            found = true;
            break;
        }
    }

    if (found) _ELEMENTS.erase(_ELEMENTS.begin()+i);
    _needUpdate = true;
}

void GUIManager::loadVBO(){

    if (!_vboMANAGER->bufferData(0,_vboDATA))
        _needUpdate = false;
}

void GUIManager::render(){

    if (_needUpdate || _moved)
    {
       if (_moved) 
           _moved = false
           
       updateVBO();
    }

    //Rendering all the different data
    glBindVertexArray(_vboMANAGER->getVAO());

    renderElements();

    renderText();

    glBindVertexArray(0);
}

void GUIManager::renderElements(){

    if (_ELEMENTS.size()!=0){

        int tmpPos = 0;

        for (std::size_t i = 0; i < _ELEMENTS.size(); i++){

            if (!_ELEMENTS[i]->exist()){

                delete _ELEMENTS[i];
                _ELEMENTS.erase(_ELEMENTS.begin()+i);
                i--;

                continue;
            }
            _ELEMENTS[i]->draw(tmpPos);
        }
    }

}

void GUIManager::renderText(){
    _texter->renderText();
}

void GUIManager::update(){

    if (_manipulatingElement==nullptr){
        checkCollisions();
    } else {
        _manipulatingElement->manipulatingMod(&_manipulatingElement);
    }

    checkCrop();
}

void GUIManager::checkCrop(){

    if (_moved){

        doCrop();
    }
}

void GUIManager::doCrop(){

    _function.exec();
    _moved = false;

    if (!_needUpdate)
        _needUpdate = true;
}

void GUIManager::checkCollisions(){

    if (Input_Manager::getCurrentState() != MANIPULATINGMOD){

        if (!_collidingElement){

            for (std::size_t i = 0; i < _ELEMENTS.size(); i++){

                if (_ELEMENTS[i]->collide(_needUpdate,&_manipulatingElement)){

                    if (_ELEMENTS[i]->getElementType()!=WINDOW){

                        _collidingElement = _ELEMENTS[i];
                        return;
                    }
                }
            }
        } else {

            if (!_collidingElement->collide(_needUpdate,&_manipulatingElement)){

                _collidingElement->setWritingAvailability(false);
                _collidingElement = nullptr;
                _needUpdate = true;
            }
        }
    }
}

void GUIManager::updateVBO(){

    if (_vboDATA.size()!=0)
        _vboDATA.clear();

    for (std::size_t i = 0; i < _ELEMENTS.size(); i++){

        if (_ELEMENTS[i]->exist())
            _ELEMENTS[i]->loadData(&_vboDATA);
    }

    loadVBO();
}

GLuint* GUIManager::getVAOID(){
    _vboMANAGER->getVAO_P();
}

TextManager* GUIManager::getTextManager(){
    return _texter;
}

bool* GUIManager::getUpdateBool(){
    return &_needUpdate;
}

void GUIManager::moveGUI(PinGUI::Vector2<GUIPos> vect, bool croppedMovement){

    _texter->moveTextManager(vect,croppedMovement);

    for (std::size_t i = 0; i < _ELEMENTS.size(); i++){
        if (_ELEMENTS[i]->exist() && !_ELEMENTS[i]->getNetworking())
            _ELEMENTS[i]->moveElement(vect);
    }

    _needUpdate = true;
}

std::size_t GUIManager::getGUISize(){
    return _ELEMENTS.size();
}

GUI_Element* GUIManager::getGuiElement(int position){

    if (position<_ELEMENTS.size() && position >= 0)
        return _ELEMENTS[position];
    else
        return nullptr;
}

void GUIManager::setUpdate(bool state){
    _needUpdate = true;
}

GUI_Element* GUIManager::getLastGuiElement(){
    if (_ELEMENTS.size()>0)
        return _ELEMENTS.back();
    else
        return nullptr;
}

std::vector<GUI_Element*>* GUIManager::getElementVector(){
    return &_ELEMENTS;
}

GUI_Element* GUIManager::getCollidingElement(){
    return _collidingElement;
}

void GUIManager::normalizeElements(float x, float y){

    PinGUI::Vector2<GUIPos> normalizedVector(x,y);

    for (std::size_t i = 0; i < _ELEMENTS.size(); i++){

        if ( _ELEMENTS[i]->exist() && !_ELEMENTS[i]->getNetworking())
            _ELEMENTS[i]->normalizeElement(normalizedVector);
    }

    _texter->normalizeText(normalizedVector);

}

void GUIManager::moveGUITo(PinGUI::Vector2<GUIPos> vect){
    for (std::size_t i = 0; i < _ELEMENTS.size(); i++){

        if (!_ELEMENTS[i]->getNetworking())
            _ELEMENTS[i]->moveTo(vect);
    }
}

void GUIManager::cropGUI(PinGUI::Rect& rect){

    for (std::size_t i = 0; i < _ELEMENTS.size(); i++){

        if (!_ELEMENTS[i]->getNetworking() && _ELEMENTS[i]->isAllowedCrop())
            _ELEMENTS[i]->cropElement(rect);
    }

    _texter->cropText(rect);
}

bool GUIManager::getUpdate(){
    return _needUpdate;
}

void GUIManager::setFunction(PinGUI::basicPointer f){

    _function = f;
    _texter->setFunction(f);
}

clipboardData GUIManager::getClipboardData(){

    clipboardData tmp;
    tmp.texter = _texter;

    return tmp;
}
