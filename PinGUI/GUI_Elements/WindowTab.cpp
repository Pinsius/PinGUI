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

WindowTab::WindowTab(PinGUI::Rect positionRect,std::shared_ptr<WindowTab>* mainTab, bool* tabChange):
    _tabChange(tabChange),
    _mainTab(mainTab)
{
    initPosition(positionRect);

    _guiManager = std::make_shared<GUIManager>();

    initSprites(positionRect);
}

WindowTab::~WindowTab()
{
}

void WindowTab::initSprites(PinGUI::Rect& positionRect){

    addSprite(positionRect,SheetManager::createWindowTab(positionRect.w,positionRect.h));
    getSprite()->setAlpha(DEFAULT_WINDOWTAB_ALPHA);

    addCollider(positionRect);
}

std::shared_ptr<GUIManager> WindowTab::getGUI(){
    return _guiManager;
}

void WindowTab::render(){
    _guiManager->render();
}

void WindowTab::update(){

    _guiManager->update();
}

void WindowTab::setWritingAvailability(bool state){

    if (*_mainTab != shared_from_this() ){

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
    (*_mainTab)->setCollidable(true);

    (*_mainTab)->getSprite()->setAlpha(0);

    //Rollback the tab camera(if needed) - and do some additional stuff.....
    WindowTab::_function.exec();

    //Now need to setup this tab as the main
    *_mainTab = std::dynamic_pointer_cast<WindowTab>(shared_from_this());

    //Allerting the window to update itself
    *_tabChange = true;

    //No longer collidable
    setCollidable(false);
}

bool WindowTab::listenForClick(manip_Element manipulatingElement){

    if (!PinGUI::Input_Manager::hasAlreadyClicked()){

        if (PinGUI::Input_Manager::clicked(SDL_BUTTON_LEFT)){

            WindowTab::onClick();
            return true;
        }
        return false;
    }
    return false;
}

void WindowTab::setTabText(std::shared_ptr<Text> text){
    _tabText = text;
}


void WindowTab::info(){
    std::cout << "WindowMover element. Address: " << this << std::endl;
}

void WindowTab::setMainTab(std::shared_ptr<WindowTab>* mainTab){
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
