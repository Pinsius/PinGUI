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
#include "FPS_Timer.h"


SDL_Window* _mainWindow = nullptr;
FPS_Timer fpsLimiter;

int sliderInteger = 0;

/**
    Create GUI in this function
**/

void createGUI(){

    PinGUI::Rect tmp(200,200,300,300);
    std::vector<std::string> tabs;
    tabs.push_back("Normal");
    tabs.push_back("Scrollable");

    Window* tmpWindow = new Window(tmp,tabs,BOTH);

    tmpWindow->setTabWidth(400,"Scrollable");
    tmpWindow->setTabHeight(400,"Scrollable");


    tmpWindow->addTitle("Welcome to demo!");


    /**
        As everything is separated, you have to acces different functions via getters
        For text operations, you must use TextManager
        For GUI operations(such as creating clipboard), use GUI manager
    **/
    //Creating clipboard
    tmpWindow->getTab("Normal")->getGUI()->getTextManager()->writeText("Write some text here",105,25);
    tmpWindow->getTab("Normal")->getGUI()->createClipBoard(55,
                                                          55,
                                                          NORMAL,
                                                          28,
                                                          ROUNDED);
    //Creating slider
    tmpWindow->getTab("Normal")->getGUI()->createVolumeBoard(20,
                                                            110,
                                                            true,
                                                            &sliderInteger,
                                                            1000);
    //Creating arrowboard
    tmpWindow->getTab("Normal")->getGUI()->getTextManager()->writeText("These two elements have same variable",20,165);
    tmpWindow->getTab("Normal")->getGUI()->createArrowBoard(65,
                                                            200,&sliderInteger,
                                                            1000,
                                                            true,
                                                            0,
                                                            HORIZONTAL);

    /********** SECOND TAB *************/
    tmpWindow->getTab("Scrollable")->getGUI()->createImage("dog.png",0,0,400,400);

    tmpWindow->normalize();

    PINGUI::addWindow(tmpWindow);
}

void initSDL_OGL();
void demoLoop();
void update();
void render();

int main(int argc, char** args){

    initSDL_OGL();

    PINGUI::initLibrary(1024,768);

    createGUI();

    demoLoop();

    return 0;
}

void demoLoop(){

    bool isRunning = true;

    fpsLimiter.setFPS(200);
    fpsLimiter.initFPS();

    while(isRunning){

        fpsLimiter.initCap();

        update();

        render();

        SDL_GL_SwapWindow(_mainWindow);

        fpsLimiter.delay();
    }
}


void update(){

    PINGUI::processInput();
    PINGUI::update();
}

void render(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    PINGUI::render();
}

void initSDL_OGL(){

    //Initializing SDL video
    if (SDL_Init(SDL_INIT_VIDEO)!=0){
       ErrorManager::fileError(SDL_GetError());
    }


    if (TTF_Init()==1){
        ErrorManager::systemError("Failed to init TTF");
    }
    IMG_Init(IMG_INIT_PNG);

    //Here i initialize SDL window with OpenGL flag - to access the OpenGL content
    _mainWindow = SDL_CreateWindow("PinGUI_Demo",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1024,768,SDL_WINDOW_OPENGL);
    if (_mainWindow==nullptr){
        ErrorManager::systemError(SDL_GetError());
    }

    //Now initializing the glContext
    SDL_GLContext glContext = SDL_GL_CreateContext(_mainWindow);
    if (glContext==nullptr){
        ErrorManager::systemError("Error with creating the glContext");
    }

    //Setting up the glew - catching up the error message to check if it was OK or not
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK){
        ErrorManager::systemError("Glew init fail");
    }

    //Setting the 2 buffers
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);

    //Basic clear depth for 2d - 1.0 . And clear color
    glClearDepth(1.0);
    glClearColor(0.0f,0.3f,0.3f,1.0f);

    //Vsync init
    SDL_GL_SetSwapInterval(0);

    //Blending the transparent color
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
