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
    _vboMANAGER = std::make_unique<VBO_Manager>(100,true);

    _texter = std::make_shared<TextManager>();
}

GUIManager::GUIManager(std::shared_ptr<TextManager> texter):
    _needUpdate(false),
    _manipulatingMod(false),
    _manipulatingElement(nullptr),
    _collidingElement(nullptr),
    _moved(false)
{
    this->_texter = texter;

    _vboMANAGER = std::make_unique<VBO_Manager>(100,true);
}

GUIManager::~GUIManager()
{
    _ELEMENTS.clear();
}

void GUIManager::createClipBoard(int x, int y, clipboard_type type, int maxSize, element_shape shape){

    clipboardData tmp;
    tmp.texter = getTextManager();

    PinGUI::Vector2<GUIPos> position(x,y);

    auto ptr = std::make_shared<ClipBoard>(position, maxSize, type, tmp,shape);
    _ELEMENTS.push_back(ptr);

    _needUpdate = true;
}

void GUIManager::createClipBoard(int x, int y, clipboard_type type, int* var, int maxSize, element_shape shape){

    clipboardData tmp;
    tmp.texter = getTextManager();
    PinGUI::Vector2<GUIPos> position(x,y);

    auto ptr = std::make_shared<ClipBoard>(position,maxSize,type,tmp,var,shape);
    _ELEMENTS.push_back(ptr);

    _needUpdate = true;

}

void GUIManager::createComboBox(int x, int y, std::vector<std::string> items, int maxNumOfItems){

    clipboardData tmp;
    tmp.texter = getTextManager();

    auto ptr = std::make_shared<ComboBox>(x,y,items,tmp,&_ELEMENTS, maxNumOfItems,&_needUpdate);

    _ELEMENTS.push_back(ptr);

    _needUpdate = true;
}

void GUIManager::createComboBox(int x, int y, std::vector<std::string> items, int maxSize, int maxNumOfItems){

    clipboardData tmp;
    tmp.texter = getTextManager();

    auto ptr = std::make_shared<ComboBox>(x,y,items,tmp,&_ELEMENTS, maxNumOfItems,&_needUpdate,maxSize);

    _ELEMENTS.push_back(ptr);

    _needUpdate = true;
}


void GUIManager::createVolumeBoard(int x, int y, bool clickable, int* var, int maxSize){

    //Block for creating a clipboard
    {
        clipboardData tmp;
        tmp.texter = getTextManager();
        PinGUI::Vector2<GUIPos> position(x+VOLUMEBOARD_CLIP_OFFSET_X,y+VOLUMEBOARD_CLIP_OFFSET_Y);

        if (clickable){

            createClipBoard(position.x,position.y,INT_ONLY,var,maxSize,ROUNDED);
        } else {
            createClipBoard(position.x,position.y,UNCLICKABLE,var,maxSize,ROUNDED);
        }
    }

    PinGUI::Vector2<GUIPos> tmpPos(x,y);

    auto ptr = std::make_shared<VolumeBoard>(tmpPos,var,maxSize,_ELEMENTS.back(),&_moved);
    _ELEMENTS.push_back(ptr);

    _needUpdate = true;
}

void GUIManager::createArrowBoard(int x, int y, int* var, int maxSize, bool clickable , int minSize, PinGUI::manipulationState state){

    //Block for creating a clipboard
    {
        clipboardData tmp;
        tmp.texter = getTextManager();
        PinGUI::Vector2<GUIPos> position(x,y);

        if (clickable){

            createClipBoard(position.x,position.y,INT_ONLY,var,maxSize,ROUNDED);
        } else {
            createClipBoard(position.x,position.y,UNCLICKABLE,var,maxSize,ROUNDED);
        }
    }
    PinGUI::Rect tmpRect(x,y,WINDOW_ARROW_W,WINDOW_ARROW_H);

    auto ptr = std::make_shared<ArrowBoard>(tmpRect,var,maxSize,_ELEMENTS.back());
    ptr->addArrows(tmpRect,_ELEMENTS,state);

    _ELEMENTS.push_back(ptr);

    _needUpdate = true;
}

void GUIManager::createImage(std::string filePath, int x, int y){

    auto ptr = std::make_shared<Image>(filePath,x,y);
    _ELEMENTS.push_back(ptr);

    _needUpdate = true;
}

void GUIManager::createImage(std::string filePath, int x, int y, int width, int height){

    auto ptr = std::make_shared<Image>(filePath,x,y,width,height);
    _ELEMENTS.push_back(ptr);

    _needUpdate = true;
}

void GUIManager::createButton(int x, int y, std::string name, PinGUI::basicPointer f){

    clipboardData tmp;
    tmp.texter = getTextManager();

    auto ptr = std::make_shared<Button>(x,y,name,f,tmp);
    _ELEMENTS.push_back(ptr);

    _needUpdate = true;
}


void GUIManager::createButton(int x, int y, std::string name, PinGUI::basicPointer f, int maxSize){

    clipboardData tmp;
    tmp.texter = getTextManager();

    auto ptr = std::make_shared<Button>(x,y,name,f,tmp,maxSize);
    _ELEMENTS.push_back(ptr);

    _needUpdate = true;
}

void GUIManager::createCheckBox(int x, int y, bool* var){

    auto ptr = std::make_shared<CrossBox>(x,y,var);
    _ELEMENTS.push_back(ptr);

    _needUpdate = true;
}

void GUIManager::putElement(std::shared_ptr<GUI_Element> object){

    _ELEMENTS.push_back(object);

    _needUpdate = true;
}

void GUIManager::withdrawElement(std::shared_ptr<GUI_Element> object){

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
           _moved = false;

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

void GUIManager::update(bool allowCollision){

    if (!_manipulatingElement){

        if (allowCollision){

            checkCollisions();
        } else {

            for (std::size_t i = 0; i < _ELEMENTS.size(); i++){

                if (_ELEMENTS[i]->isAiming()){

                    _ELEMENTS[i]->turnOffAim();
                    _needUpdate = true;
                }
            }
         }
    } else {

        _manipulatingElement->manipulatingMod(_manipulatingElement);
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

    if (PinGUI::Input_Manager::getCurrentState() != PinGUI::MANIPULATINGMOD){

        if (!_collidingElement){

            for (std::size_t i = 0; i < _ELEMENTS.size(); i++){

                if (_ELEMENTS[i]->collide(_needUpdate,_manipulatingElement)){

                    if (_ELEMENTS[i]->getElementType() != WINDOW){

                        _collidingElement = _ELEMENTS[i];

                        return;
                    }
                }
            }
        } else {

            if (!_collidingElement->collide(_needUpdate,_manipulatingElement)){

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

std::shared_ptr<TextManager> GUIManager::getTextManager(){

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

std::shared_ptr<GUI_Element> GUIManager::getGuiElement(int position){

    if (position<_ELEMENTS.size() && position >= 0)
        return _ELEMENTS[position];
    else
        ErrorManager::errorLog("GUIManager::getGuiElement()", "Tried to get a element with nullptr");
}

void GUIManager::setUpdate(bool state){
    _needUpdate = true;
}

std::shared_ptr<GUI_Element> GUIManager::getLastGuiElement(){

    if (_ELEMENTS.size()>0)
        return _ELEMENTS.back();
    else
        ErrorManager::errorLog("GUIManager::getLastGuiElement()", "Tried to get a element with nullptr");
}

std::vector<std::shared_ptr<GUI_Element>>* GUIManager::getElementVector(){
    return &_ELEMENTS;
}

std::shared_ptr<GUI_Element> GUIManager::getCollidingElement(){
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
    tmp.texter = getTextManager();

    return tmp;
}

void GUIManager::putElementAtStart(std::shared_ptr<GUI_Element> object){
    _ELEMENTS.insert(_ELEMENTS.begin(),object);
}
