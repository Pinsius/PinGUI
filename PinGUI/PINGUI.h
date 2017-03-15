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
#include <boost/bind.hpp>
#include <memory>

#include "GUI_Elements/Window.h"
#include "../PinGUI/Shader_Program.h"


#define WINDOW_STORAGE_SIZE 200
/**
    The main singleton for whole library
**/

class PINGUI
{
    private:

         static std::vector<std::shared_ptr<Window>> _ACTIVE_WINDOWS;

         static std::vector<std::shared_ptr<Window>> _NON_ACTIVE_WINDOWS;

         static std::shared_ptr<Window> _mainWindow;

         static std::shared_ptr<GUIManager> _mainGUIManager;

         /** Private methods **/

         static void checkActiveWindows();

         static void initStorage();

         static bool collide(std::shared_ptr<Window> win);

    public:

        static std::shared_ptr<Window> lastWindow;

        static void initLibrary(int screenWidth, int screenHeight);

        static void processInput(SDL_Event* event = nullptr);

        static void destroy();

        static void addWindow(std::shared_ptr<Window> win);

        static void createWindow(PinGUI::Rect mainFrame, std::vector<std::string> tabs, windowElementType type, element_shape shape = ROUNDED);

        static void render();

        static void update();

        static void setMainWindow(std::shared_ptr<Window> win);

        static int getSizeOfActiveWindows();

        static void checkMainWindow();

        static std::shared_ptr<GUIManager> getGUI();

        static PinGUI::basicPointer getFunctionPointer();
};

#endif // PINGUI_H
