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

#include "Input_Manager.h"
#include <iostream>

namespace PinGUI{

    std::unordered_map<unsigned int, bool> Input_Manager::_KEYS;

    gameState Input_Manager::_currentState = GAME;

    SDL_Event Input_Manager::_mainEvent;

    inputState Input_Manager::_mainInputState = GAMEINPUT;

    int Input_Manager::_positionOfText = -1;

    std::shared_ptr<TextStorage> Input_Manager::_manipulatedText = nullptr;

    std::shared_ptr<GUI_Sprite> Input_Manager::_manipulatedSprite = nullptr;

    bool* Input_Manager::_needUpdate = nullptr;

    bool Input_Manager::_alreadyClicked = false;

    bool Input_Manager::_singleClickTracker = false;

    bool Input_Manager::_allowWheel = false;

    bool Input_Manager::_haveTarget = false;

    bool Input_Manager::_tmpWheelInfo = false;

    bool Input_Manager::_isOnWindow = false;

    manipulatingModInfo Input_Manager::_manipulatingModInfo;

    int Input_Manager::_screenWidth;

    int Input_Manager::_screenHeight;

    writingModInfo Input_Manager::_writingModInfo;

    PinGUI::Vector2<GUIPos> Input_Manager::_lastVector;

    wheelingInfo Input_Manager::_wheelingInfo;

    PinGUI::basicPointer Input_Manager::_clFunction;

    PinGUI::basicPointer Input_Manager::_clickFunction;

    PinGUI::Rect Input_Manager::_targetRect;

    bool Input_Manager::_tmpState = false;

    /**
        Storage for tmpWheel
    **/

    static wheelingInfo infoStorage;

    void Input_Manager::pressKey(unsigned int keyID){
        _KEYS[keyID] = true;

    }

    void Input_Manager::releaseKey(unsigned int keyID){
        _KEYS[keyID] = false;
    }

    void Input_Manager::setKey(unsigned int keyID, bool state){
        _KEYS[keyID] = state;
    }

    bool Input_Manager::isKeyPressed(unsigned int keyID){

        auto it = _KEYS.find(keyID);

        if (it!=_KEYS.end()) return it->second;
        else return false;
    }

    bool Input_Manager::clicked(unsigned int keyID){

        auto it = _KEYS.find(keyID);

        if (it!=_KEYS.end()){
            if (it->second){
                it->second = false;
                return true;
            }
        }
        return false;
    }

    void Input_Manager::setState(gameState newState){

        _currentState = newState;
    }

    gameState Input_Manager::getState(){
        return _currentState;
    }

    void Input_Manager::process(SDL_Event* mainEvent){

        if (mainEvent){

           _mainEvent = *mainEvent;
        } else {

            SDL_Event tmpEvent;
            SDL_PollEvent(&tmpEvent);

            _mainEvent = tmpEvent;
        }

        switch(_mainInputState){

            case GAMEINPUT: {

                processInput();
                break;
            }
            case WRITINGMOD: {

                writingMod();
                break;
            }
            case MANIPULATINGMOD:{

                manipulatingMod();
                break;
            }
        }

        if (_tmpState){

           _tmpState = false;
           _currentState = PinGUI::GAME;
        }

        GUI_Cursor::updateCursor();
    }

    void Input_Manager::processInput(){

        switch (_mainEvent.type) {
            case SDL_QUIT : {
                Input_Manager::pressKey(SDL_QUIT);
                break;
            }
            case SDL_KEYDOWN : {
                Input_Manager::pressKey(_mainEvent.key.keysym.sym);
                break;
            }
            case SDL_KEYUP : {
                Input_Manager::releaseKey(_mainEvent.key.keysym.sym);
                break;
            }
            case SDL_MOUSEBUTTONDOWN : {

                if (_mainEvent.button.button == SDL_BUTTON_LEFT){

                    if (_haveTarget) checkTarget();

                    _clickFunction.exec();
                }

                Input_Manager::pressKey(_mainEvent.button.button);
                break;
            }
            case SDL_MOUSEBUTTONUP : {

                if (_mainEvent.button.button == SDL_BUTTON_LEFT)
                    _alreadyClicked = false;

                Input_Manager::releaseKey(_mainEvent.button.button);
                break;
            }
            case SDL_MOUSEMOTION : {

                singleClickTracker();
                break;
            }
            case SDL_MOUSEWHEEL : {

                if (_allowWheel)
                    doWheelMovement();
                break;
            }
        }

    }

    void Input_Manager::writingMod(){

        switch (_mainEvent.type){
            case SDL_QUIT : {
                Input_Manager::pressKey(SDL_QUIT);
                return;
            }
            case SDL_KEYDOWN : {

                switch(_mainEvent.key.keysym.sym){
                    case SDLK_BACKSPACE: {

                        _clFunction.exec();

                        _manipulatedText->removeChar(0);
                        return;
                    }
                    case SDLK_RETURN :
                    case SDLK_KP_ENTER :
                    case SDLK_ESCAPE : {

                        Input_Manager::pressKey(_mainEvent.key.keysym.sym);
                        return;
                    }
                }
                return;
            }
            case SDL_TEXTINPUT : {

                if (canWrite(_mainEvent.text.text) && (_mainEvent.key.repeat == 0)){

                    //Also call callback
                    _clFunction.exec();

                    //I add the char to a manipulated text
                    _manipulatedText->addChar(_mainEvent.text.text,0,_writingModInfo);

                    return;
                }
                return;
            }
        }
    }

    void Input_Manager::manipulatingMod(){

        switch(_mainEvent.type){

            case SDL_KEYDOWN:{

                Input_Manager::pressKey(_mainEvent.key.keysym.sym);
                return;
            }

            case SDL_MOUSEBUTTONUP:{

                if (_mainEvent.button.button==SDL_BUTTON_LEFT){
                    Input_Manager::setKey(_mainEvent.button.button,false);
                }
                return;
            }

            case SDL_MOUSEMOTION:{

                manipulate();
                *_needUpdate = true;
                return;
            }
        }
    }

    void Input_Manager::singleClickTracker(){

        //Single click tracker function
        if (isKeyPressed(SDL_BUTTON_LEFT))
            _alreadyClicked = true;
    }


    void Input_Manager::manipulate(){

        int tmpX;
        int tmpY;

        SDL_GetMouseState(&tmpX,&tmpY);
        convertScreenToWorld(tmpX,tmpY);

        //Moving the sprite in horizontal line
        if ((_manipulatingModInfo.manipState == HORIZONTAL) || (_manipulatingModInfo.manipState == WINDOW_MOVING)){

            moveHorizontal(tmpX,tmpY);
        }

        //Moving the sprite in vertical line
        if ((_manipulatingModInfo.manipState == VERTICAL) || (_manipulatingModInfo.manipState == WINDOW_MOVING)){

            moveVertical(tmpX,tmpY);
        }

        *_needUpdate = true;
    }

    void Input_Manager::moveHorizontal(const int& tmpX, const int& tmpY){

        int diff = tmpX - GUI_Cursor::getX();

        _lastVector.x = diff;

        if (_manipulatingModInfo.manipState != WINDOW_MOVING)
            _manipulatedSprite->setX(_manipulatedSprite->getX()+diff);
    }

    void Input_Manager::moveVertical(const int& tmpX, const int& tmpY){

        int diff = tmpY - GUI_Cursor::getY();

        _lastVector.y = diff;


        if (_manipulatingModInfo.manipState!=WINDOW_MOVING)
            _manipulatedSprite->setY(_manipulatedSprite->getY()+diff);
    }

    std::shared_ptr<Text> Input_Manager::chooseText(){

        // If its the position of text -1 i know i didnt change it so i want to use a default position (0)
        if (_positionOfText==-1)
            return _manipulatedText->getText(0);
        else
            return _manipulatedText->getText(_positionOfText);
    }


    SDL_Event Input_Manager::getEvent(){
        return _mainEvent;
    }

    void Input_Manager::setInputState(inputState state){
        _mainInputState = state;
    }

    inputState Input_Manager::getCurrentState(){
        return _mainInputState;
    }

    void Input_Manager::setManipulatedText(std::shared_ptr<TextStorage> text){
        _manipulatedText = text;
    }

    bool Input_Manager::canWrite(char* ch){

        if ((chooseText()->getTextSize()+1) <= _writingModInfo.max){
            return true;
        } else return false;
    }

    void Input_Manager::setWritingModInfo(writingModInfo newMod){
        _writingModInfo = newMod;
    }

    void Input_Manager::initManipulation(std::shared_ptr<GUI_Sprite> manip, bool* needUpdate){

        SDL_SetRelativeMouseMode(SDL_TRUE);
        _manipulatedSprite = manip;
        _needUpdate = needUpdate;
    }

    void Input_Manager::createManipulatingModInfo(int x, int y, manipulationState state){

        _manipulatingModInfo.lastX = x;
        _manipulatingModInfo.lastY = y;
        _manipulatingModInfo.manipState = state;
    }

    void Input_Manager::destroyManipulatingModInfo(){

        _manipulatedSprite = nullptr;
        _needUpdate = nullptr;
    }

    void Input_Manager::setAlreadyClick(bool state){
        _alreadyClicked = state;
    }

    bool Input_Manager::hasAlreadyClicked(){
        return _alreadyClicked;
    }

    void Input_Manager::convertScreenToWorld(int& x, int& y){

        y = _screenHeight - y;
    }

    void Input_Manager::setScreenSize(int width, int height){

        _screenWidth = width;
        _screenHeight = height;
    }

    PinGUI::Vector2<GUIPos> Input_Manager::getLastVector(){
        return _lastVector;
    }

    std::shared_ptr<GUI_Sprite> Input_Manager::getManipulatedSprite(){
        return _manipulatedSprite;
    }

    SDL_Event* Input_Manager::getEvent_P(){
        return &_mainEvent;
    }

    void Input_Manager::setWheeledInfo(std::shared_ptr<GUI_Sprite> sprite, bool* update, PinGUI::basicPointer f){

        _wheelingInfo._wheeledSprite = sprite;
        _wheelingInfo._update = update;
        _wheelingInfo._function = f;
    }

    void Input_Manager::setTMPWheeledInfo(std::shared_ptr<GUI_Sprite> sprite, bool* update, PinGUI::basicPointer f){

        infoStorage = _wheelingInfo;

        _wheelingInfo._update = update;
        _wheelingInfo._wheeledSprite = sprite;
        _wheelingInfo._function = f;

        if (!_allowWheel)
            _allowWheel = true;

        _tmpWheelInfo = true;
    }

    void Input_Manager::cancelTMPWheeledInfo(){

        _wheelingInfo = infoStorage;
        _tmpWheelInfo = false;
    }

    void Input_Manager::doWheelMovement(){

        if (_wheelingInfo._wheeledSprite && _wheelingInfo._update){
            if (_mainEvent.wheel.y > 0){

                _wheelingInfo._wheeledSprite->setY(_wheelingInfo._wheeledSprite->getY()+WINDOW_CAM_SCROLLING_SPEED);
            } else if (_mainEvent.wheel.y < 0){

                _wheelingInfo._wheeledSprite->setY(_wheelingInfo._wheeledSprite->getY()-WINDOW_CAM_SCROLLING_SPEED);
            }

            *_wheelingInfo._update = true;
            _wheelingInfo._function.exec();
        }
    }

    void Input_Manager::setAllowWheel(bool state){

        _allowWheel = state;
    }


    bool Input_Manager::getAllowWheel(){
        return _allowWheel;
    }

    wheelingInfo Input_Manager::getWheelInfo(){
        return _wheelingInfo;
    }


    PinGUI::Vector2<GUIPos>* Input_Manager::getLastVector_P(){
        return &_lastVector;
    }

    void Input_Manager::setCallbackFunction(PinGUI::basicPointer f){
        _clFunction = f;
    }

    bool Input_Manager::haveTarget(){
        return _haveTarget;
    }

    void Input_Manager::setTarget(bool state,PinGUI::Rect targetRect){
        _haveTarget = state;
        _targetRect = targetRect;
    }

    void Input_Manager::setTarget(bool state){
        _haveTarget = state;
    }

    void Input_Manager::checkTarget(){

        if (!GUI_CollisionManager::isColliding(GUI_Cursor::getCollider(),_targetRect)){

            _haveTarget = false;
            _clFunction.exec();
        }
    }

    void Input_Manager::setClickFunction(PinGUI::basicPointer f){

        _clickFunction = f;
    }

    bool Input_Manager::hasTMPWheeledInfo(){
        return _tmpWheelInfo;
    }

    void Input_Manager::setOnWindow(bool state){
        _isOnWindow = state;
    }

    bool Input_Manager::isOnWindow(){
        return _isOnWindow;
    }

    void Input_Manager::turnOnTMPState(){
        _tmpState = true;
    }

    void Input_Manager::clearEnterKey(){
        setKey(SDLK_RETURN,false);
        setKey(SDLK_KP_ENTER,false);
    }
}

