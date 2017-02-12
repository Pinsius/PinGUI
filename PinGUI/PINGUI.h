#ifndef PINGUI_H
#define PINGUI_H

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

#include "PinGUI/GUI_Elements/Window.h"
#include "PinGUI/Shader_Program.h"

/**
    The main singleton for whole library
**/

class PINGUI
{
    private:
         static std::vector<Window*> _WINDOWS;

         static std::vector<Window*> _ACTIVE_WINDOWS;

         static std::vector<Window*> _NON_ACTIVE_WINDOWS;

         static Window* _mainWindow;

         static Window* _mainCollider;

         static GUIManager* _mainGUIManager;

         /** Private methods **/

         static void checkActiveWindows();

         static void findMainCollider();

    public:

        static void initLibrary(int screenWidth, int screenHeight);
    
        static void processInput();
    
        static void destroy();

        static void addWindow(Window* win);

        static void render();

        static void update();

        static void setMainWindow(Window* win);

        static int getSizeOfActiveWindows();

        static void checkMainWindow();
    
        static GUIManager* getGUI();

        static PinGUI::basicPointer getFunctionPointer();
};

#endif // PINGUI_H
