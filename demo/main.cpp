#include <iostream>

/**
This file is part of PinGUI demo
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

#include <SDL.h>
#include <GL/glew.h>

#include "PinGUI/PINGUI.h"
#include "PinGUI/GUI_Elements/WindowButton.h"
#include "FPS_Timer.h"

SDL_Window* _mainWindow = nullptr;
FPS_Timer fpsLimiter;
bool a = true;
int sliderInteger = 0;
bool isRunning = true;

/**
Create GUI in this function
**/

void createGUI() {

	//Storage for the configuration data of the window
	windowDef windowDefinition;
	windowDefinition.windowFrame = PinGUI::Rect(200, 200, 300, 300); //X pos, Y pos, Width and Height
	windowDefinition.tabs = { "Normal","Scrollable" }; // Number of tabs - if you put empty vector it will create a default tab called BLANK
	windowDefinition.type = BOTH; // Type of element type, BOTH means it has both exit button and mover area to move the window
	windowDefinition.shape = ROUNDED; // Shape of the window
	windowDefinition.windowName = "Main window"; // This is the name tag of the window - via this you can access the window later

	/*
	* To acces the window with name tag use PINGUI::bindWindow("Main window"); for window with name "Main window"
	*/

	//Create the window with a pointer to window definition
	PINGUI::createWindow(&windowDefinition);

	//Setting Dimensions of window tabs we created before
	PINGUI::window->setTabHeight(400, "Normal");
	PINGUI::window->setTabWidth(400, "Scrollable");

	//Add the title to the window
	PINGUI::window->addTitle("Demo");

	/**
	As everything is separated, you have to acces different functions via getters
	For text operations, you must use TextManager
	For GUI operations(such as creating clipboard), use GUI manager
	**/

	/*Bind the tab with the name "Normal" - it is binded from the actually binded window!
	* It actually binds a GUI and TEXT so you can access them easier 
	*/
	PINGUI::bindTab("Normal");

	//Creating slider
	PINGUI::GUI->createVolumeBoard(20,
		90,
		true,
		&sliderInteger,
		1000);

	//Textbox - text functions accessible with TEXT
	PINGUI::TEXT->writeText("Write some text here", 105, 25);
	PINGUI::GUI->createClipBoard(55,55,NORMAL,28,ROUNDED);

	PINGUI::TEXT->writeText("These two elements have same variable", 20, 140);

	//Creating arrowboard
	PINGUI::GUI->createArrowBoard(65, 175, &sliderInteger, 1000, true, 0, PinGUI::HORIZONTAL);

	//Checkbox
	PINGUI::GUI->createCheckBox(10,	50,	&a);

	/********** SECOND TAB *************/
	//Binding another tab from our window
	PINGUI::bindTab("Scrollable");

	PINGUI::GUI->createImage("dog.png",0,0,400,400);

	//Reset the GUI and TEXT so we doesn´t put it to any binded window/tab
	PINGUI::resetGUI();

	std::shared_ptr<WindowButton> ptr = std::make_shared<WindowButton>(15,350,"Start",PINGUI::GUI->getClipboardData());

	ptr->setWindowTarget(PINGUI::window);

	PINGUI::GUI->putElement(ptr);

	//Instead of calling this function for every window, call it only one time after you create the GUI
	PINGUI::normalize();
}

void initSDL_OGL();
void demoLoop();
void update();
void render();

int main(int argc, char** args) {

	initSDL_OGL();

	PINGUI::initLibrary(1024, 768);

	createGUI();

	demoLoop();

	PINGUI::destroy();

	return 0;
}

void demoLoop() {

	fpsLimiter.setFPS(200);
	fpsLimiter.initFPS();

	while (isRunning) {

		fpsLimiter.initCap();

		update();

		render();

		SDL_GL_SwapWindow(_mainWindow);

		fpsLimiter.delay();
	}
}


void update() {

	SDL_Event e;


	SDL_PollEvent(&e);

	PINGUI::processInput(&e);

	if (e.type == SDL_QUIT) {
		isRunning = false;
	}

	PINGUI::update();

}

void render() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	PINGUI::render();
}

void initSDL_OGL() {

	//Initializing SDL video
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		ErrorManager::fileError(SDL_GetError());
	}


	if (TTF_Init() == 1) {
		ErrorManager::systemError("Failed to init TTF");
	}
	IMG_Init(IMG_INIT_PNG);

	//Here i initialize SDL window with OpenGL flag - to access the OpenGL content
	_mainWindow = SDL_CreateWindow("PinGUI_Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_OPENGL);
	if (_mainWindow == nullptr) {
		ErrorManager::systemError(SDL_GetError());
	}

	//Now initializing the glContext
	SDL_GLContext glContext = SDL_GL_CreateContext(_mainWindow);
	if (glContext == nullptr) {
		ErrorManager::systemError("Error with creating the glContext");
	}

	//Setting up the glew - catching up the error message to check if it was OK or not
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK) {
		ErrorManager::systemError("Glew init fail");
	}

	//Setting the 2 buffers
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//Basic clear depth for 2d - 1.0 . And clear color
	glClearDepth(1.0);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	//Vsync init
	SDL_GL_SetSwapInterval(0);

	//Blending the transparent color
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
