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

#include "PINGUI.h"

windowVector PINGUI::_ACTIVE_WINDOWS;

windowVector PINGUI::_NON_ACTIVE_WINDOWS;

std::shared_ptr<Window> PINGUI::_mainWindow = nullptr;

std::shared_ptr<GUIManager> PINGUI::_mainGUIManager = nullptr;

std::shared_ptr<Window> PINGUI::window = nullptr;	

std::shared_ptr<WindowTab> PINGUI::winTab = nullptr;

std::shared_ptr<GUIManager> PINGUI::GUI = nullptr;

std::shared_ptr<TextManager> PINGUI::TEXT = nullptr;

void PINGUI::destroy(){

    _ACTIVE_WINDOWS.clear();
    _NON_ACTIVE_WINDOWS.clear();
    _mainWindow.reset();
}

void PINGUI::addWindow(std::shared_ptr<Window> win){

    win->addElementsToManager();

    _ACTIVE_WINDOWS.push_back(win);

    window = win;

    if (!_mainWindow)
        _mainWindow = win;
}

void PINGUI::createWindow(windowDef* winDef){

    auto win = std::make_shared<Window>(winDef);
    win->addElementsToManager();

    _ACTIVE_WINDOWS.push_back(win);

	window = win;

    if (!_mainWindow)
        _mainWindow = win;
}

void PINGUI::normalize() {

	for (const auto& w : _ACTIVE_WINDOWS)
		w->normalize();

	for (const auto& w : _NON_ACTIVE_WINDOWS)
		w->normalize();
}

void PINGUI::render(){

    PinGUI::Shader_Program::use();

    if (_mainGUIManager)
        _mainGUIManager->render();

    for (std::size_t i = 0; i < _ACTIVE_WINDOWS.size(); i++){

        if (_ACTIVE_WINDOWS[i]!=_mainWindow){

            _ACTIVE_WINDOWS[i]->render();
        }
    }

    if (_mainWindow && _mainWindow->getShow()){

        _mainWindow->render();
    }

    PinGUI::Shader_Program::unuse();

}

void PINGUI::update(){

    bool allowUpdate = true;

    checkActiveWindows();

    for (std::size_t i = _ACTIVE_WINDOWS.size(); i > 0; i--){

        _ACTIVE_WINDOWS[i-1]->update(allowUpdate);

        if (allowUpdate && collide(_ACTIVE_WINDOWS[i-1])){
            allowUpdate = false;
        }
    }

    if (_mainGUIManager)
        _mainGUIManager->update(allowUpdate);
}

void PINGUI::setMainWindow(std::shared_ptr<Window> win){
    _mainWindow = win;
}

void PINGUI::checkActiveWindows(){

    for (std::size_t i = 0; i < _ACTIVE_WINDOWS.size(); i++)
        if (!_ACTIVE_WINDOWS[i]->getShow()){

            _NON_ACTIVE_WINDOWS.push_back(_ACTIVE_WINDOWS[i]);
            _ACTIVE_WINDOWS.erase(_ACTIVE_WINDOWS.begin()+i);

        }

    for (std::size_t i = 0; i < _NON_ACTIVE_WINDOWS.size(); i++)
    {

        if (_NON_ACTIVE_WINDOWS[i]->getShow()){

            _ACTIVE_WINDOWS.push_back(_NON_ACTIVE_WINDOWS[i]);
            _NON_ACTIVE_WINDOWS.erase(_NON_ACTIVE_WINDOWS.begin()+i);
        }
    }
}

int PINGUI::getSizeOfActiveWindows(){
    return _ACTIVE_WINDOWS.size();
}

bool PINGUI::collide(std::shared_ptr<Window> win){

    if (GUI_CollisionManager::isColliding(GUI_Cursor::getCollider(),*(win->getCollider())))
        return true;
    else
        return false;
}

void PINGUI::checkMainWindow(){

    if (_mainWindow && !GUI_CollisionManager::isColliding(GUI_Cursor::getCollider(),*(_mainWindow->getCollider()))){

        for (std::size_t i = _ACTIVE_WINDOWS.size(); i >0; i--){

            if (GUI_CollisionManager::isColliding(GUI_Cursor::getCollider(),*(_ACTIVE_WINDOWS[i-1]->getCollider()))){

                _mainWindow = _ACTIVE_WINDOWS[i-1];

                _ACTIVE_WINDOWS[i-1] = _ACTIVE_WINDOWS.back();
                _ACTIVE_WINDOWS.back() = _mainWindow;

                return;
            }
        }
    }
}

PinGUI::basicPointer PINGUI::getFunctionPointer(){

    PinGUI::basicPointer f;
    f._function = boost::bind(&PINGUI::checkMainWindow);

    return f;
}

void PINGUI::initLibrary(int screenWidth, int screenHeight){

    _mainGUIManager = std::make_shared<GUIManager>();

    initStorage();

    SheetManager::loadAllTextures();

    GUI_Cursor::initCursor();

    PinGUI::Input_Manager::setScreenSize(screenWidth,screenHeight);

    GUI_ColorManager::initColors();

    PinGUI::CameraManager::init(screenWidth,screenHeight);

    PinGUI::Input_Manager::setClickFunction(PINGUI::getFunctionPointer());

    PinGUI::Shader_Program::initShaders();
}

void PINGUI::processInput(SDL_Event* event){

    PinGUI::Input_Manager::process(event);
}

std::shared_ptr<GUIManager> PINGUI::getGUI(){

    return _mainGUIManager;
}

void PINGUI::initStorage(){

    _ACTIVE_WINDOWS.reserve(WINDOW_STORAGE_SIZE);
    _NON_ACTIVE_WINDOWS.reserve(WINDOW_STORAGE_SIZE);
}

void PINGUI::bindTab(std::shared_ptr<WindowTab> tab) {
	winTab = tab;
	bindGUI(tab);
}

void PINGUI::bindTab(const std::string& tabName) {
	winTab = window->getTab(tabName);
	bindGUI(winTab);
}

void PINGUI::bindWindow(const std::string& windowName) {

	//Check active windows first
	std::shared_ptr<Window> resultWin = findWindow(_ACTIVE_WINDOWS,windowName);

	//If it didn´t succeed loop through the non active windows
	if (!resultWin)
		resultWin = findWindow(_NON_ACTIVE_WINDOWS, windowName);

	//Says the error log in case that u asked for window that doesn´t have entered name tag
	if (!resultWin)
		ErrorManager::errorLog("PINGUI::bindWindow", "Failed to bind window with following name: " + windowName);

	window = resultWin;
}

void PINGUI::bindGUI(std::shared_ptr<Window> win) {
	PINGUI::GUI = win->getGUI();
	PINGUI::TEXT = PINGUI::GUI->getTextManager();
}

void PINGUI::bindGUI(std::shared_ptr<WindowTab> tab) {
	PINGUI::GUI = tab->getGUI();
	PINGUI::TEXT = PINGUI::GUI->getTextManager();
}

void PINGUI::bindGUI(std::shared_ptr<GUIManager> gui) {
	PINGUI::GUI = gui;
	PINGUI::TEXT = PINGUI::GUI->getTextManager();
}

void PINGUI::resetGUI() {
	PINGUI::GUI = _mainGUIManager;
	PINGUI::TEXT = PINGUI::GUI->getTextManager();
}

std::shared_ptr<Window> PINGUI::findWindow(const windowVector& vector, const std::string& winName) {
	
	std::shared_ptr<Window> tmpWin = nullptr;

	for (const auto& w : vector) {

		if (w->getNameTag() == winName)
			tmpWin = w;

		break;
	}
	return tmpWin;
}