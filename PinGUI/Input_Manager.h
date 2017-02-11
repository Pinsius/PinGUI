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

#include "PinGUI/TextManager/TextStorage.h"
#include "PinGUI/GUI_Sprite.h"
#include "PinGUI/GUI_Cursor.h"
#include "PinGUI/PinGUI_Vector.hpp"
#include "PinGUI/clFunction.hpp"

#define STATES_NUM 3
#define WINDOW_CAM_SCROLLING_SPEED 6


enum gameState{
    GAME,
    GUI
};

enum inputState{
    GAMEINPUT,
    WRITINGMOD,
    MANIPULATINGMOD
};

enum manipulationState{
    HORIZONTAL,
    VERTICAL,
    WINDOW_MOVING
};

struct writingModInfo{
    bool intOnly;
    int max;
    int maxValue;
};

struct manipulatingModInfo{
    int lastX;
    int lastY;
   manipulationState manipState;
};

struct wheelingInfo{
    GUI_Sprite* _wheeledSprite;
    bool* _update;
    PinGUI::basicPointer _function;
};

class Input_Manager
{
    private:

        static std::unordered_map<unsigned int, bool> _KEYS;

        static gameState _currentState;

        static SDL_Event _mainEvent;

        static inputState _mainInputState;

        //Pointer to an text that is being changed by writing mod
        static TextStorage* _manipulatedText;

        static int _positionOfText;

        static writingModInfo _writingModInfo;

        static manipulatingModInfo _manipulatingModInfo;

        static GUI_Sprite* _manipulatedSprite;

        static bool* _needUpdate;

        static bool _alreadyClicked;

        static bool _singleClickTracker;

        static bool _allowWheel;

        static bool _haveTarget;

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

        static void process();

        //Normal input
        static void processInput();

        //Writing mod
        static void writingMod();

        static void pressKey(unsigned int keyID);

        static void setKey(unsigned int keyID, bool state);

        static void releaseKey(unsigned int keyID);

        static bool isKeyPressed(unsigned int keyID);

        static bool clicked(unsigned int keyID);

        static void setState(gameState newState);

        static gameState getState();

        static void singleClickTracker();

        static SDL_Event getEvent();

        static SDL_Event* getEvent_P();

        static void setWheeledInfo(GUI_Sprite* sprite, bool* update, PinGUI::basicPointer f);
    
        static bool hasTMPWheeledInfo();

        static void setTMPWheeledInfo(GUI_Sprite* sprite, bool* update, PinGUI::basicPointer f);

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

        /**
            For writing mod
        **/

        //Choose a text from storage based on the index
        static Text* chooseText();

        static char* getTextInput();

        static void setInputState(inputState state);

        static inputState getCurrentState();

        static void setManipulatedText(TextStorage* text);

        static bool canWrite(char* ch);

        static void setWritingModInfo(writingModInfo newMod);

        /**
            Manipulation with volumeboards like type(it is used also for moving the windowses)
        **/
        static void manipulatingMod();

        static void manipulate();

        static void moveHorizontal(const int& tmpX, const int& tmpY);

        static void moveVertical(const int& tmpX, const int& tmpY);

        static void initManipulation(GUI_Sprite* manip, bool* needUpdate);

        static void createManipulatingModInfo(int x, int y, manipulationState state);

        static void destroyManipulatingModInfo();

        static void setAlreadyClick(bool state);

        static bool hasAlreadyClicked();

        static void setScreenSize(int width, int height);

        static void convertScreenToWorld(int& x, int& y);

        static PinGUI::Vector2<GUIPos> getLastVector();

        static PinGUI::Vector2<GUIPos>* getLastVector_P();

        static GUI_Sprite* getManipulatedSprite();
};

#endif // INPUT_MANAGER_H
