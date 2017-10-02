#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

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

#include <unordered_map>
#include <SDL.h>
#include <ctype.h>

#include "TextManager/TextStorage.h"
#include "GUI_Sprite.h"
#include "GUI_Cursor.h"
#include "PinGUI_Vector.hpp"
#include "clFunction.hpp"

#define STATES_NUM 3
#define WINDOW_CAM_SCROLLING_SPEED 6


class Window;

namespace PinGUI{

    class wheelingInfo{
    public:
        std::shared_ptr<GUI_Sprite> _wheeledSprite;
        bool* _update;
        PinGUI::basicPointer _function;

        wheelingInfo():
            _wheeledSprite(nullptr),
            _update(nullptr)
            {

            }
    };


    class Input_Manager
    {
        private:

            static std::unordered_map<unsigned int, bool> _KEYS;

            static gameState _currentState;

            static SDL_Event _mainEvent;

            static inputState _mainInputState;

            //Pointer to an text that is being changed by writing mod
            static std::shared_ptr<TextStorage> _manipulatedText;

            static int _positionOfText;

            static writingModInfo _writingModInfo;

            static manipulatingModInfo _manipulatingModInfo;

            static std::shared_ptr<GUI_Sprite> _manipulatedSprite;

            static bool* _needUpdate;

            static bool _alreadyClicked;

            static bool _singleClickTracker;

            static bool _allowWheel;

            static bool _haveTarget;

            static bool _isOnWindow;

			static Window* _lastWindow;

            static bool _tmpState;

            static PinGUI::Rect _targetRect;

            static PinGUI::Vector2<GUIPos> _lastVector;

            static wheelingInfo _wheelingInfo;

            static bool _tmpWheelInfo;

            static PinGUI::basicPointer _clFunction;

            //These two variables do something else!!
            static PinGUI::basicPointer _clickFunction;

        public:
            static int _screenWidth;
            static int _screenHeight;

            static void process(SDL_Event* mainEvent = nullptr);

            //Normal input
            static void processInput();

            //Writing mod
            static void writingMod();

            //Manipulating mod
            static void manipulatingMod();

            static void pressKey(unsigned int keyID);

            static void setKey(unsigned int keyID, bool state);

            static void releaseKey(unsigned int keyID);

            static bool isKeyPressed(unsigned int keyID);

            static bool clicked(unsigned int keyID);

            static void setState(gameState newState);

            static void clearEnterKey();

            static gameState getState();

            static void singleClickTracker();

            static SDL_Event getEvent();

            static SDL_Event* getEvent_P();

            static void setWheeledInfo(std::shared_ptr<GUI_Sprite> sprite, bool* update, PinGUI::basicPointer f);

            static bool hasTMPWheeledInfo();

            static void setTMPWheeledInfo(std::shared_ptr<GUI_Sprite> sprite, bool* update, PinGUI::basicPointer f);

            static void cancelTMPWheeledInfo();

            static void doWheelMovement();

            static void setAllowWheel(bool state);

            static bool getAllowWheel();

            static wheelingInfo getWheelInfo();

            static void setCallbackFunction(PinGUI::basicPointer f);

            static void checkTarget();

            static bool haveTarget();

            static void setTarget(bool state,PinGUI::Rect targetRect);

            static void setTarget(bool state);

            static void setClickFunction(PinGUI::basicPointer f);

            static void setOnWindow(bool state);

			static void setLastWindow(Window* winPtr);

            static bool isOnWindow();

			static void checkLastWindow();

            static void turnOnTMPState();

            /**
                For writing mod
            **/

            //Choose a text from storage based on the index
            static std::shared_ptr<Text> chooseText();

            static char* getTextInput();

            static void setInputState(inputState state);

            static inputState getCurrentState();

            static void setManipulatedText(std::shared_ptr<TextStorage> text);

            static bool canWrite(char* ch);

            static void setWritingModInfo(writingModInfo newMod);

            /**
                Manipulation with volumeboards like type(it is used also for moving the windowses)
            **/

            static void manipulate();

            static void moveHorizontal(const int& tmpX, const int& tmpY);

            static void moveVertical(const int& tmpX, const int& tmpY);

            static void initManipulation(std::shared_ptr<GUI_Sprite> manip, bool* needUpdate);

            static void createManipulatingModInfo(GUIPos x, GUIPos y, manipulationState state);

            static void destroyManipulatingModInfo();

            static void setAlreadyClick(bool state);

            static bool hasAlreadyClicked();

            static void setScreenSize(int width, int height);

            static void convertScreenToWorld(int& x, int& y);

            static PinGUI::Vector2<GUIPos> getLastVector();

            static PinGUI::Vector2<GUIPos>* getLastVector_P();

            static std::shared_ptr<GUI_Sprite> getManipulatedSprite();
    };
}


#endif // INPUT_MANAGER_H
