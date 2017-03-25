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

#include "Window.h"

Window::Window(PinGUI::Rect mainFrame, std::vector<std::string> tabs, windowElementType type, element_shape shape):
    _mainFrame(mainFrame),
    _tabMovementChecker(0,0),
    _type(type),
    _windowUpdate(false),
    _tabChange(true),
    _needCrop(true),
    _mainWindowTab(nullptr),
    _verticalScroller(nullptr),
    _horizontalScroller(nullptr),
    _windowMover(nullptr),
    _windowExit(nullptr),
    _shape(shape)
{
    initPosition(mainFrame);

    //Creation of GUI manager
    _mainGUIManager = std::make_shared<GUIManager>();

    //Now setting the size of Font for Tab names
    _mainGUIManager->getTextManager()->setFontSize(WINDOW_TAB_FONT_SIZE);

    {
        PinGUI::Rect tmpPositionRect(_mainFrame);

        //Create sprite of the whole window

        if (shape==ROUNDED)
            addSprite(tmpPositionRect,SheetManager::createWindow(tmpPositionRect.w,tmpPositionRect.h));
        else if (shape==RECTANGLED)
            addSprite(tmpPositionRect,SheetManager::createRectangle(tmpPositionRect.w,tmpPositionRect.h,WINDOW_BACKGROUND,WINDOW_LINE));

        addCollider(tmpPositionRect);

        //Now need to create the tabs
        createTabs(tabs,tmpPositionRect);
    }

    _mainWindowTab = _TABS[0]->windowTab;

    //Initializing the mainTab
    if (_mainWindowTab)
        initTab();

    PinGUI::basicPointer tmpFunction;
    tmpFunction._function = boost::bind(&Window::rollbackTabCamera,this);

    for (auto&& tab : _TABS){

        tab->windowTab->setRollBackFunction(tmpFunction);
    }

    //Creating additional elements
    if (haveMover())
        createWindowMoverArea();

    if (haveExit())
        createWindowExitButton();
}

Window::~Window()
{
    _TABS.clear();
}

void Window::createTabs(std::vector<std::string>& tabs, PinGUI::Rect& positionRect){

    if (tabs.size()==0)
        createEmptyTabLine(positionRect);

    for (std::size_t i = 0; i < tabs.size(); i++){

        auto winTab = std::make_shared<WindowTab>(calculateSize(tabs.size(),positionRect,i),
                                                  &_mainWindowTab,
                                                  &_tabChange);

        auto ptr = std::make_shared<tabInfo>(tabs[i],winTab);

        _TABS.push_back(ptr);

        offsetTab(_TABS.back()->windowTab);

        //Creating a name of tab
        nameTab(_TABS[i]);

        //Setting stuff
        _TABS.back()->windowTab->setTabText(_mainGUIManager->getTextManager()->getLastText());
        _TABS.back()->windowTab->setTabDimensions(_mainFrame);

        PinGUI::basicPointer tmpF;
        tmpF._function = boost::bind(&Window::cropTabArea,this);
        _TABS.back()->windowTab->getGUI()->setFunction(tmpF);

    }

    if (_TABS.size()==1)
        _TABS[0]->windowTab->setCollidable(false);
}

void Window::createEmptyTabLine(PinGUI::Rect& positionRect){

    auto winTab = std::make_shared<WindowTab>(calculateSize(1,positionRect,0,false),
                                              &_mainWindowTab,
                                              &_tabChange);

    auto ptr = std::make_shared<tabInfo>("Blank",winTab);

    _TABS.push_back(ptr);

    _TABS.back()->windowTab->getSprite()->setH(SINGLE_WINDOWTAB_HEIGHT);
    _TABS.back()->windowTab->getSprite()->setColor(95,95,95);

    _TABS.back()->windowTab->setTabDimensions(_mainFrame);

    PinGUI::basicPointer tmpF;
    tmpF._function = boost::bind(&Window::cropTabArea,this);
    _TABS.back()->windowTab->getGUI()->setFunction(tmpF);

    offsetTab(_TABS.back()->windowTab);
}

PinGUI::Rect Window::calculateSize(int vecSize,const PinGUI::Rect& positionRect, std::size_t counter, bool nameIt){

    PinGUI::Rect tmp;

    tmp.w = positionRect.w/vecSize;
    tmp.x = positionRect.x +(tmp.w*(counter));
    tmp.y = (positionRect.y+positionRect.h);
    tmp.h = WINDOW_TAB_FONT_SIZE+WINDOW_TAB_SIZE;

    if (counter==vecSize-1)
        tmp.w += (positionRect.w -(vecSize*tmp.w))+1;

    return tmp;
}

void Window::nameTab(std::shared_ptr<tabInfo> tab){

    PinGUI::Rect tmpRect = *(tab->windowTab->getCollider());

    //I also need to render the text name and offset it to the correct possition
    _mainGUIManager->getTextManager()->writeText(tab->tabName,tmpRect.x,tmpRect.y);

    //Now bind it to offset rectangle
    _mainGUIManager->getTextManager()->getLastText()->setOffsetRect(tmpRect);
}

std::shared_ptr<WindowTab> Window::getTab(std::string tabName){

    for (std::size_t i = 0; i < _TABS.size(); i++){

        if (_TABS[i]->tabName==tabName)
            return _TABS[i]->windowTab;
    }

    ErrorManager::systemError("Window::getTab " + tabName + " failed to find");

    return nullptr;
}

void Window::render(){

    _mainGUIManager->render();

    //Also the opened tab need to be rendered
    if (_mainWindowTab){

        _mainWindowTab->getGUI()->render();
    }
}

void Window::update(bool allowCollision){

    if (_windowUpdate)
        moveWindow(PinGUI::Input_Manager::getLastVector());

    _mainGUIManager->update(allowCollision);

    if (_mainWindowTab){

        if (_tabChange){
            updateTab();
        }

        if (_needCrop && _mainWindowTab->getGUI()->getUpdate()){
            cropTabArea();
        }

        if (_mainWindowTab){
            _mainWindowTab->getGUI()->update(allowCollision);
        }
    }
}

void Window::addElementsToManager(){

    _mainGUIManager->putElementAtStart(shared_from_this());

    for (std::size_t i = 0; i < _TABS.size(); i++){
        _mainGUIManager->putElement(_TABS[i]->windowTab);
    }
}

void Window::offsetTab(std::shared_ptr<WindowTab> tab){

    //Offset the windowTab
    int tmpY = (getSprite()->getY()+getSprite()->getH())-WINDOW_TAB_OFFSET;
    tab->getSprite()->setY(tmpY-tab->getSprite()->getH());

    tmpY = getSprite()->getY()+getSprite()->getH()-(tab->getSprite()->getY()+tab->getSprite()->getH())-PINGUI_WINDOW_LINE_H;

    //Now the text
    PinGUI::Rect tmp;

    tmp.w = tab->getSprite()->getW();
    tmp.x = tab->getSprite()->getX();
    tmp.y = tab->getSprite()->getY();
    tmp.h = tab->getSprite()->getH();

    //Also manage the collider
    tab->setCollider(tmp);
}

void Window::createWindowMoverArea(){

    PinGUI::Rect positionRect;

    //Setting the width and height
    positionRect.h = WINDOW_MOVER_HEIGHT;
    moverWidthCalculator(positionRect.w,_mainFrame.w);

    if (!haveExit()) positionRect.w += WINDOW_EXIT_W_AREA;

    positionRect.x = _mainFrame.x + PINGUI_WINDOW_LINE_W+WINDOW_MOVER_X_OFFSET;

    int tmpY = (getSprite()->getY()+getSprite()->getH())+WINDOW_MOVER_Y_OFFSET-PINGUI_WINDOW_LINE_H;
    positionRect.y = tmpY-positionRect.h;

    _windowMover = std::make_shared<WindowMover>(positionRect,&_windowUpdate);

    _mainGUIManager->putElement(_windowMover);
}

void Window::createWindowExitButton(){

    PinGUI::Rect positionRect;

    positionRect.x = getSprite()->getX() + getSprite()->getW() - PINGUI_WINDOW_EXITBUTTON_W - PINGUI_WINDOW_LINE_H;
    positionRect.y = getSprite()->getY() + getSprite()->getH() - PINGUI_WINDOW_EXITBUTTON_H + PINGUI_WINDOW_LINE_H;

    _windowExit = std::make_shared<WindowExit>(positionRect,this);

    _mainGUIManager->putElement(_windowExit);
}

void Window::moveWindow(PinGUI::Vector2<GUIPos> vect){

    _mainGUIManager->moveGUI(vect);

    _cameraRect.addPos(vect);

    for (std::size_t i = 0; i < _TABS.size(); i++){
        _TABS[i]->windowTab->getGUI()->moveGUI(vect);
    }

    _windowUpdate = false;
}

void Window::info(){
    std::cout << "Window element. Address: " << this;
}

bool Window::haveMover(){
    return (_type==MOVER_ONLY || _type==BOTH);
}

bool Window::haveExit(){
    return (_type==EXIT_ONLY || _type==BOTH);
}

void Window::loadScroller(){

    /** VERTICAL SCROLL **/
    //Here is IF statement for verticall scrolling, if the height is bigger than windows height, i load it , if not im not showing anything
    if (_mainWindowTab->getTabDimensions().y > _mainFrame.h){

        //Setting scroller to active state
        manageScroller(PinGUI::VERTICAL,true);
        _verticalScroller->attachScrollerToInput();

    } else{

        //Disabling it
        manageScroller(PinGUI::VERTICAL,false);
    }

    /** HORIZONTAL SCROLL **/
    if (_mainWindowTab->getTabDimensions().x > _mainFrame.w){

        manageScroller(PinGUI::HORIZONTAL,true);
    } else {

        manageScroller(PinGUI::HORIZONTAL,false);
    }
}

void Window::updateTab(){

    if (_TABS.size()==1)
        _mainWindowTab->getSprite()->setAlpha(DEFAULT_WINDOWTAB_ALPHA);
    else
        _mainWindowTab->getSprite()->setAlpha(CHOOSED_WINDOWTAP_ALPHA);

    _tabChange = false;

    _mainGUIManager->setUpdate(true);

    hideScrollers();

    loadScroller();

    setWindowCamRect();

    if (!isScrollerActive(_verticalScroller)) PinGUI::Input_Manager::setAllowWheel(false);

    cropTabArea();
}

void Window::hideScrollers(){

    if (isScrollerActive(_verticalScroller))
        _verticalScroller->hideScroller();

    if (isScrollerActive(_horizontalScroller))
        _horizontalScroller->hideScroller();
}

//First initialization
void Window::initTab(){

    _mainWindowTab->setCollidable(false);
}

void Window::addTitle(std::string windowTitle){

    PinGUI::Rect tmpRect;

    tmpRect = getSprite()->getCollider();
    tmpRect.h = WINDOW_TITLE_HEIGHT;
    tmpRect.y += getSprite()->getH() - WINDOW_TITLE_Y_OFFSET;
    tmpRect.x += WINDOW_TITLE_X_OFFSET;

    _mainGUIManager->getTextManager()->writeText(windowTitle,tmpRect.x,tmpRect.y);
    _mainGUIManager->getTextManager()->getLastText()->setOffsetRect(tmpRect);
    _mainGUIManager->getTextManager()->getLastText()->calculateTextPosition();
}

void Window::createVerticalScroller(int height){

    //First need to create a scroller
    height += PINGUI_WINDOW_LINE_H;

    PinGUI::Vector2<GUIPos> position;

    position.x = _TABS.back()->windowTab->getSprite()->getX() + _TABS.back()->windowTab->getSprite()->getW() - PINGUI_WINDOW_DEFAULT_SCROLLER_W + PINGUI_WINDOW_LINE_W;

    if (_shape==RECTANGLED)
        position.x -= RECTANGLE_VERTICAL_SCROLLER_OFFSET;


    position.y = _TABS.back()->windowTab->getSprite()->getY() - height + PINGUI_WINDOW_LINE_H;

    _verticalScroller = std::make_shared<VerticalScroller>(position,
                                                           height,
                                                           _mainGUIManager->getUpdateBool(),
                                                           _mainGUIManager->getElementVector());

    _mainGUIManager->putElement(_verticalScroller);
    _verticalScroller->createArrows(_mainGUIManager->getElementVector());

    _verticalScroller->setCamRollFunction(getCamRollFunction());
}

void Window::createHorizontalScroller(int width){

    //First need to create a scroller
    //Multiplying it by 2 because i count the line from left and right side
    width += PINGUI_WINDOW_LINE_W*2;

    PinGUI::Vector2<GUIPos> position;

    position.x = _TABS[0]->windowTab->getSprite()->getX();
    position.y = getSprite()->getY();

    _horizontalScroller = std::make_shared<HorizontalScroller>(position,
                                                               width,
                                                               _mainGUIManager->getUpdateBool(),
                                                               _mainGUIManager->getElementVector());

    _mainGUIManager->putElement(_horizontalScroller);
    _horizontalScroller->createArrows(_mainGUIManager->getElementVector());

    _horizontalScroller->setCamRollFunction(getCamRollFunction());
}

PinGUI::scrollFuncPointer Window::getCamRollFunction(){

    PinGUI::scrollFuncPointer tmpF;
    tmpF._function = boost::bind(&Window::updateTabCamera,this,_1);
    return tmpF;
}

void Window::setTabDimensions(PinGUI::Vector2<int> dims, std::string tabName){

    getTab(tabName)->setTabDimensions(dims);
    checkDimensions(PinGUI::VERTICAL,dims.y);
    checkDimensions(PinGUI::HORIZONTAL,dims.x);
}

void Window::setTabHeight(int height, std::string tabName){

    getTab(tabName)->setTabHeight(height);
    checkDimensions(PinGUI::VERTICAL,height);
}

void Window::setTabWidth(int width, std::string tabName){

    getTab(tabName)->setTabWidth(width);
    checkDimensions(PinGUI::HORIZONTAL,width);
}

void Window::checkDimensions(PinGUI::manipulationState state, const int& value){

    switch(state){
        case PinGUI::VERTICAL : {

            //Only checking if i have to create a Scroller
            if (value>_mainFrame.h && !_verticalScroller){

                createVerticalScroller(calculateScrollerSize(state));
            }

            return;
        }
        case PinGUI::HORIZONTAL : {

            if (value>_mainFrame.w && !_horizontalScroller){

                createHorizontalScroller(calculateScrollerSize(state));
            }
            return;
        }
    }
}

void Window::manageScroller(PinGUI::manipulationState state, bool show){

    switch(state){

        case PinGUI::VERTICAL : {

            if (_verticalScroller){

                _verticalScroller->setShow(show);

                if (show)
                    _verticalScroller->loadScrollMover(_mainFrame.h,_mainWindowTab->getTabDimensions().y);
            }
            break;
        }
        case PinGUI::HORIZONTAL : {

            if (_horizontalScroller){

                _horizontalScroller->setShow(show);
               if (show){

                    adjustHorizontalScrollerWidth();
                    _horizontalScroller->loadScrollMover(_mainFrame.w,_mainWindowTab->getTabDimensions().x);
               }
            }
            break;
        }
    }
}

int Window::calculateScrollerSize(PinGUI::manipulationState state){

    switch(state){

        case PinGUI::VERTICAL : {

            return _mainWindowTab->getSprite()->getY() - getSprite()->getY();
        }
        case PinGUI::HORIZONTAL : {

            return _mainFrame.w;
        }
        default : return 0;
    }
}

elementType Window::getElementType(){

    return WINDOW;
}

void Window::onAim(){

    if(isScrollerActive(_verticalScroller)) _verticalScroller->attachScrollerToInput();

    PinGUI::Input_Manager::setOnWindow(true);
}

void Window::onEndAim(){

    if (isScrollerActive(_verticalScroller)){

        if (PinGUI::Input_Manager::getWheelInfo()._wheeledSprite){

            if (PinGUI::Input_Manager::getWheelInfo()._wheeledSprite == _verticalScroller->getSprite(1))
                PinGUI::Input_Manager::setAllowWheel(false);
        }

    }

    PinGUI::Input_Manager::setOnWindow(false);
    turnOffAim();
}

bool Window::listenForClick(manip_Element manipulatingElement){

    if (PinGUI::Input_Manager::getState() != PinGUI::GUI)
        PinGUI::Input_Manager::setState(PinGUI::GUI);

    if (isScrollerActive(_verticalScroller)  && !PinGUI::Input_Manager::hasTMPWheeledInfo()){

        if (!PinGUI::Input_Manager::getAllowWheel()) PinGUI::Input_Manager::setAllowWheel(true);
    }
    return false;
}

void Window::adjustHorizontalScrollerWidth(){

    //Checking if I have vertical scroller
    if (_mainWindowTab->getTabDimensions().y > _mainFrame.h){

        _horizontalScroller->getSprite()->setW(getSprite()->getW() - _verticalScroller->getSprite()->getW());
    } else {

        _horizontalScroller->getSprite()->setW(_mainFrame.w + (PINGUI_WINDOW_LINE_W*2));
    }

    _horizontalScroller->modifyArrowPos();

}

void Window::normalize(){

    float x = _TABS[0]->windowTab->getSprite()->getX();
    float y = _TABS[0]->windowTab->getSprite()->getY();

    for (std::size_t i = 0; i < _TABS.size(); i++){

      normalizeTab(_TABS[i]->windowTab,x,y);
      _TABS[i]->windowTab->getGUI()->getTextManager()->setUpdate(true);
    }

    setWindowCamRect();
}

void Window::normalizeTab(std::shared_ptr<WindowTab> tab, const float& x, const float& y){

    tab->getGUI()->normalizeElements(x,y);
}

void Window::updateTabCamera(PinGUI::Vector2<GUIPos> vect){

    _needCrop = true;

    _tabMovementChecker += vect;

    _mainWindowTab->getGUI()->moveGUI(vect,true);
}

void Window::rollbackTabCamera(){

    _tabMovementChecker.x *= -1;
    _tabMovementChecker.y *= -1;

    _mainWindowTab->getGUI()->moveGUI(_tabMovementChecker);

    //Need to crop the things back
    cropTabArea();
    _tabMovementChecker.clearVector();
}

void Window::cropTabArea(){

    if (isScrollerActive(_verticalScroller) || isScrollerActive(_horizontalScroller)){

        _mainWindowTab->getGUI()->cropGUI(_cameraRect);
        _needCrop = false;
    }
}

void Window::setWindowCamRect(){

    //X is still the same
    _cameraRect.x = _COLLIDERS[0].rect.x;

    //Y is changing - because of horizontal scroller
    if (isScrollerActive(_horizontalScroller)){

        _cameraRect.y = _COLLIDERS[0].rect.y + _horizontalScroller->getSprite()->getH();
    } else {

        _cameraRect.y = _COLLIDERS[0].rect.y+1;
    }

    _cameraRect.h = _TABS[0]->windowTab->getSprite()->getY() - _cameraRect.y;

    //Same with width - because of vertical scroller
    if (isScrollerActive(_verticalScroller)){

        _cameraRect.w = _COLLIDERS[0].rect.w - _verticalScroller->getSprite()->getW();
    } else {

        _cameraRect.w = _COLLIDERS[0].rect.w-1;
    }

    _cameraRect.x++;

    if (_shape==RECTANGLED)
        _cameraRect.w -= RECTANGLE_VERTICAL_SCROLLER_OFFSET;

    _cameraRect.w++;
}

std::shared_ptr<GUIManager> Window::getGUI(){
    return _mainGUIManager;
}
