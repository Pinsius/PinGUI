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
#include "GUI_Elements/WindowButton.h"
#include "../PinGUI/Shader_Program.h"

#define WINDOW_STORAGE_SIZE 200

/**
    The main singleton for whole library
**/

typedef std::vector<std::shared_ptr<Window>> windowVector;

class PINGUI
{
    private:

         static windowVector _ACTIVE_WINDOWS;

         static windowVector _NON_ACTIVE_WINDOWS;

         static std::shared_ptr<Window> _mainWindow;

		 static std::shared_ptr<Window> _collidingWindow;

         static std::shared_ptr<GUIManager> _mainGUIManager;

         /** Private methods **/

         static void checkActiveWindows();

         static void initStorage();

         static bool collide(std::shared_ptr<Window> win);

		 static std::shared_ptr<Window> findWindow(const windowVector& vector, const std::string& winName);

    public:

        static std::shared_ptr<Window> window;

		static std::shared_ptr<WindowTab> winTab;

		static std::shared_ptr<GUIManager> GUI;

		static std::shared_ptr<TextManager> TEXT;

		//Functions

        static void initLibrary(int screenWidth, int screenHeight);

		static void normalize();

        static void processInput(SDL_Event* event = nullptr);

        static void destroy();

        static void addWindow(std::shared_ptr<Window> win);

		//Creating a window that is not manager by PINGUI but by other GUI elements(in case that its a part of a element)
		static std::shared_ptr<Window> createSubWindow(windowDef* def);

        static void createWindow(windowDef* winDef);

        static void render();

        static void update();

        static void setMainWindow(std::shared_ptr<Window> win);

        static int getSizeOfActiveWindows();

        static void checkMainWindow();

        static std::shared_ptr<GUIManager> getGUI();

        static PinGUI::basicPointer getFunctionPointer();

		//Setting the tab target
		static void bindTab(std::shared_ptr<WindowTab> tab);

		//Setting the tab target via its name
		static void bindTab(const std::string& tabName);

		//Binding the window via its name tag
		static void bindWindow(const std::string& windowName);

		//Getting just the window ptr
		static std::shared_ptr<Window> getWindow(const std::string& windowName);
		
		//Initializing the GUI and TEXT
		static void bindGUI(std::shared_ptr<Window> win);
		static void bindGUI(std::shared_ptr<WindowTab> tab);
		static void bindGUI(std::shared_ptr<GUIManager> gui);

		//Set the GUIManager and TextManager to the default
		static void resetGUI();
};

#endif // PINGUI_H
