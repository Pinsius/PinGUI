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

#include "ComboBox.h"


ComboBox::ComboBox(int x,
                   int y,
                   std::vector<std::string> itemList,
                   clipboardData data,
                   std::vector<GUI_Element*>* ELEMENTS,
                   int maxNumOfItems,
                   bool* update):
    _maxNumberOfItems(maxNumOfItems),
    _needUpdate(update),
    _scroller(nullptr),
    _mainItem(nullptr),
    _ELEMENTS(ELEMENTS),
    _clickable(true),
    _rollbackVect(0,0)
{
    _position.x = x;
    _position.y = y;

    _data.texter = data.texter;

    _maxSize = 0;

    findLongestWord(itemList);

    initMainSprites(x,y,data);

    for (std::size_t i = 0; i < itemList.size(); i++)
        addItem(itemList[i]);

    initScroller();
}

ComboBox::ComboBox(int x,
                   int y,
                   std::vector<std::string> itemList,
                   clipboardData data,
                   std::vector<GUI_Element*>* ELEMENTS,
                   int maxNumOfItems,
                   bool* update,
                   int maxSize):
    _maxNumberOfItems(maxNumOfItems),
    _needUpdate(update),
    _scroller(nullptr),
    _mainItem(nullptr),
    _ELEMENTS(ELEMENTS),
    _clickable(true),
    _rollbackVect(0,0)

{
    _position.x = x;
    _position.y = y;

    _data.texter = data.texter;

    _maxSize = maxSize;

    initMainSprites(x,y,data);

    for (std::size_t i = 0; i < itemList.size(); i++)
        addItem(itemList[i]);

    initScroller();
}

ComboBox::~ComboBox()
{

    if (_scroller){
        delete _scroller;
        _scroller = nullptr;
    }

    for (std::size_t i = 0; i < _ITEMS.size(); i++){

        delete _ITEMS[i];
        _ITEMS[i] = nullptr;
    }
}

void ComboBox::initMainSprites(int& x, int& y, clipboardData& data){

    SDL_Surface* tmpSurface;
    int tmp_width, tmp_height;

    fakeInputText(tmp_width,tmp_height,data);

    addCollider(x,y,tmp_width,tmp_height);
    _offsetCollider = *(getCollider());

    _textStorage = new TextStorage(data.texter);
    initText();

    //Now need to rearrange the width by adding the width of scroller
    tmp_width += PINGUI_WINDOW_DEFAULT_SCROLLER_W-BORDER_LINE;

    tmpSurface = SheetManager::createRectangle(tmp_width,tmp_height,BOARD,BORDER_LINE);

    SheetManager::putOnSurface(tmpSurface,COMBO_BOX_ARROW,tmp_width - POSITION_OF_COMBO_ARROW_X,(tmp_height/2)-(PINGUI_COMBO_BOX_ARROW_H/2));

    addSprite(x,y,tmpSurface);

    deleteCollider(0);
    addCollider(x,y,tmp_width,tmp_height);
}

void ComboBox::initScroller(){

    PinGUI::Vector2<GUIPos> tmpPos(_offsetCollider.x + _offsetCollider.w - BORDER_LINE,
                                   _offsetCollider.y - (_maxNumberOfItems * (_offsetCollider.h-BORDER_LINE) ));

    int height = _maxNumberOfItems * (_offsetCollider.h-BORDER_LINE);

    _scroller = new VerticalScroller(tmpPos,height,_needUpdate,_ELEMENTS);

    //Now init cropRect and add function that performs it
    _cropRect.rect.x = getSprite()->getX();

    _cropRect.rect.w = _offsetCollider.w;
    _cropRect.rect.h = _maxNumberOfItems * _offsetCollider.h;
    _cropRect.rect.y = _position.y - _cropRect.rect.h;

    _cropRect.realRect = _cropRect.rect;

    //Set clFunction
    PinGUI::scrollFuncPointer f;
    f._function = boost::bind(&ComboBox::updateCropArea,this,_1);

    _scroller->setCamRollFunction(f);

    _scroller->setNetworking(true);
    _scroller->hideScroller();
}

void ComboBox::updateCropArea(PinGUI::Vector2<GUIPos> vect){

    _rollbackVect += vect;

    for (std::size_t i = 0; i < _ITEMS.size(); i++){

        _ITEMS[i]->moveElement(vect);
        _ITEMS[i]->cropElement(_cropRect.rect);
    }

    *_needUpdate = true;
}

std::vector<std::string> ComboBox::getStringVector(){

    std::vector<std::string> tmp;

    for (std::size_t i = 0; i < _ITEMS.size(); i++)
        tmp.push_back(_ITEMS[i]->getStorage()->getText()->getString());

    return tmp;
}

void ComboBox::findLongestWord(std::vector<std::string>& itemList){

    for (std::size_t i = 0; i < itemList.size(); i++){

        if (itemList[i].size() > _maxSize)
            _maxSize = itemList[i].size();
    }
}

void ComboBox::addItem(std::string name){

    PinGUI::Vector2<GUIPos> tmpPos (_position.x, getPosOfNextItem());

    PinGUI::basicPointer f;
    f._function = boost::bind(&ComboBox::uploadContent,this);

    _ITEMS.push_back(new ComboBoxItem(tmpPos,name,&_mainItem,f,_maxSize,_data));

    _ELEMENTS->push_back(_ITEMS.back());
    _ITEMS.back()->setOption(_ITEMS.size());

    if (!_clickable)
        _ITEMS.back()->setCollidable(false);

    *_needUpdate = true;
}

void ComboBox::deleteItem(std::string name){

    for (std::size_t i = 0; i < _ITEMS.size(); i++){

        if (_ITEMS[i]->getStorage()->getText()->getString()==name){

            _ITEMS[i]->setExist(false);
            _ITEMS.erase(_ITEMS.begin() + i);
        }
    }
    reMoveTabs();
}


void ComboBox::clearComboBox(){

    for (std::size_t i = 0; i < _ITEMS.size(); i++){

        _ITEMS[i]->setExist(false);
    }
    _ITEMS.clear();
}

void ComboBox::reMoveTabs(){

    PinGUI::Vector2<GUIPos> tmp(0,_offsetCollider.h-BORDER_LINE);

    for (std::size_t i = 0; i < _ITEMS.size(); i++){

        _ITEMS[i]->moveElement(tmp);
    }

    *_needUpdate = true;
}


GUIPos ComboBox::getPosOfNextItem(){

    return (_position.y - (getSprite()->getH() * (_ITEMS.size()+1)) + (_ITEMS.size()+1));
}

void ComboBox::moveElement(const PinGUI::Vector2<GUIPos>& vect){

    ClipBoard::moveElement(vect);
    _scroller->moveElement(vect);

    for (std::size_t i = 0; i < _ITEMS.size(); i++)
        _ITEMS[i]->moveElement(vect);

    moveCollider(_offsetCollider,vect);

    moveCollider(_cropRect.realRect,vect);
    moveCollider(_cropRect.rect,vect);
}

void ComboBox::onClick(){

    if (_cropRect.rect != _cropRect.realRect){

        ErrorManager::infoLog("PinGUI::log","Combobox list cannot be loaded due to cropped area. Move it to normal area");
        return;
    }

    for (std::size_t i = 0; i < _ITEMS.size(); i++)
        _ITEMS[i]->setShow(true);

    PinGUI::basicPointer tmpF;
    tmpF._function = boost::bind(&ComboBox::hideContent,this);
    PinGUI::Input_Manager::setCallbackFunction(tmpF);

    _cropRect.rect.x = _offsetCollider.x;
    _cropRect.rect.w = _offsetCollider.w;
    _cropRect.rect.h = _maxNumberOfItems * (_offsetCollider.h-BORDER_LINE);

    if (_ITEMS.size()>_maxNumberOfItems){

        _cropRect.rect.w += PINGUI_WINDOW_DEFAULT_SCROLLER_W-BORDER_LINE;
        _cropRect.rect.h = _maxNumberOfItems * (_offsetCollider.h-BORDER_LINE);
    } else {
        _cropRect.rect.h = _ITEMS.size() * (_offsetCollider.h-BORDER_LINE);
    }

    _cropRect.rect.y = _offsetCollider.y - _cropRect.rect.h;

    _cropRect.realRect = _cropRect.rect;

    PinGUI::Input_Manager::setTarget(true,_cropRect.rect);

    if (_maxNumberOfItems< _ITEMS.size()){

        loadScroller();
        _scroller->setShow(true);

        PinGUI::basicPointer f;
        f._function = boost::bind(&Scroller::checkForWheelMove,_scroller);

        PinGUI::Input_Manager::setTMPWheeledInfo(_scroller->getSprite(1),_needUpdate,f);
    }

    updateCropArea(_rollbackVect);
}

void ComboBox::loadScroller(){

    _scroller->loadScrollMover(_cropRect.rect.h,(_ITEMS.size() * (_offsetCollider.h-1)));
}

bool ComboBox::listenForClick(GUI_Element** manipulatingElement){

    GUI_Element::listenForClick(manipulatingElement);
}

void ComboBox::hideContent(){

    _rollbackVect.y *= -1;

    updateCropArea(_rollbackVect);

    _rollbackVect.clearVector();

    for (std::size_t i = 0; i < _ITEMS.size(); i++)
        _ITEMS[i]->setShow(false);

    if (_maxNumberOfItems< _ITEMS.size()){

        _scroller->hideScroller();

        PinGUI::Input_Manager::cancelTMPWheeledInfo();
        PinGUI::Input_Manager::setAllowWheel(false);
    }
}

void ComboBox::uploadContent(){

    setClipboardText(_mainItem->getStorage()->getText()->getString(),_offsetCollider);

    _func.exec(_mainItem->getOption());

    hideContent();
}

void ComboBox::setShow(bool state){

    for (std::size_t i = 0; i < _ITEMS.size(); i++)
        _ITEMS[i]->setShow(state);

    if (_maxNumberOfItems< _ITEMS.size()){
        loadScroller();
    }

}

elementType ComboBox::getElementType(){
    return COMBOBOX;
}

void ComboBox::cropElement(PinGUI::Rect& rect){

    ClipBoard::cropElement(rect);

    CropManager::cropRect(rect,_cropRect);
}

void ComboBox::setFunc(PinGUI::comboBoxFuncPointer func){
    _func = func;
}

void ComboBox::setUnclickable(){

    for (std::size_t i = 0; i < _ITEMS.size(); i++)
        _ITEMS[i]->setCollidable(false);

    _clickable = false;
}
