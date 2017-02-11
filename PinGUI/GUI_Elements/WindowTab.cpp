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

#include "WindowTab.h"



WindowTab::WindowTab(PinGUI::Rect positionRect,WindowTab** mainTab, bool* tabChange):
    _mainTab(mainTab),
    _tabChange(tabChange)
{
    initPosition(positionRect);

    _guiManager = new GUIManager();

    initSprites(positionRect);
}

WindowTab::WindowTab(TextManager* texter)
{
    _guiManager = new GUIManager(texter);
}

WindowTab::~WindowTab()
{
    delete _guiManager;
}

void WindowTab::initSprites(PinGUI::Rect& positionRect){

    addSprite(positionRect,SheetManager::createWindowTab(positionRect.w,positionRect.h));
    getSprite()->setAlpha(DEFAULT_WINDOWTAB_ALPHA);

    addCollider(positionRect);
}

GUIManager* WindowTab::getGUI(){
    return _guiManager;
}

void WindowTab::render(){
    _guiManager->render();
}

void WindowTab::update(){

    _guiManager->update();
}

void WindowTab::setWritingAvailability(bool state){

    if (*_mainTab != this){

        if (state){

            getSprite()->setColor(235,235,235);
            getSprite()->setAlpha(ON_COLLIDE_WINDOWTAB_ALPHA);
        } else {

            getSprite()->changeColor(GUI_ColorManager::getColor(CLIPBOARD_NCOLOR));
            getSprite()->setAlpha(DEFAULT_WINDOWTAB_ALPHA);
        }
    } else {

        getSprite()->setColor(0,235,0);
        getSprite()->setAlpha(CHOOSED_WINDOWTAP_ALPHA);
    }

}

void WindowTab::onClick(){

    //Setting the old mainTab to collidable state
    (*(_mainTab))->setCollidable(true);
    (*(_mainTab))->getSprite()->setAlpha(DEFAULT_WINDOWTAB_ALPHA);

    //Rollback the tab camera(if needed) - and do some additional stuff.....
    WindowTab::_function.exec();

    //Now need to setup this tab as the main
    *_mainTab = this;

    //Allerting the window to update itself
    *_tabChange = true;

    //No longer collidable
    setCollidable(false);
}

bool WindowTab::listenForClick(GUI_Element** manipulatingElement){

    if (!Input_Manager::hasAlreadyClicked()){

        if (Input_Manager::clicked(SDL_BUTTON_LEFT)){

                onClick();
                return true;
        }
        return false;
    }
    return false;
}

void WindowTab::setTabText(Text* text){
    _tabText = &text;
}


void WindowTab::info(){
    std::cout << "WindowMover element. Address: " << this << std::endl;
}

void WindowTab::setMainTab(WindowTab** mainTab){
    _mainTab = mainTab;
}

void WindowTab::setTabDimensions(PinGUI::Rect& rect){
    _tabDimensions.x = rect.w;
    _tabDimensions.y = rect.h;
}

void WindowTab::setTabDimensions(PinGUI::Vector2<int> dims){
    _tabDimensions.x = dims.x;
    _tabDimensions.y = dims.y;
}

void WindowTab::setTabHeight(int height){
    _tabDimensions.y = height;
}

void WindowTab::setTabWidth(int width){
    _tabDimensions.x = width;
}

PinGUI::Vector2<int> WindowTab::getTabDimensions(){
    return _tabDimensions;
}

void WindowTab::setRollBackFunction(PinGUI::basicPointer Function){
    _function = Function;
}
