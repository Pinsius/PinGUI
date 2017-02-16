#ifndef SHEETMANAGER_H
#define SHEETMANAGER_H

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

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <vector>

#include "ErrorManager.h"
#include "Input_Manager.h"

/**
    This class is used for choosing different sprites for TextManager/PinGUI from the sheet
**/

enum surfaceType{
    BOARD,
    BORDER_LINE,
    BORDER_TL,
    BORDER_BL,
    BORDER_TR,
    BORDER_BR,
    ARROW_PLUS,
    ARROW_MINUS,
    VOLUME_BACK,
    VOLUME_MOVER,
    VOLUME_FILL,
    CHECKBOX,
    NON_CHECKBOX,
    COMBO_BOX_ARROW,
    /** Here is called loadWindowTextures() so be careful when adding new elements - they must be added in right order! **/
    WINDOW_BACKGROUND,
    WINDOW_LINE,
    WINDOW_TL,
    WINDOW_BL,
    WINDOW_TR,
    WINDOW_BR,
    WINDOW_TAB,
    WINDOW_TAB_LINE,
    WINDOW_EXITBUTTON,
    WINDOW_SCROLLER_INNER,
    WINDOW_SCROLLER_LINE,
    WINDOW_ARROW_UP,
    WINDOW_ARROW_DOWN,
    WINDOW_ARROW_RIGHT,
    WINDOW_ARROW_LEFT,
    WINDOW_SCROLLER_FILL,
    BLANK_SURFACE
};


/**
    Order for making non-rectangle shapes(for example - window, clipboard...'
    1. Add background
    2. Add lines
    3. Add vertex lines - TL,BL,TR,BR
**/

enum buttonType{
    clipboard
};

enum lineType{
    PINGUI_WINDOW,
    PINGUI_CLIPBOARD
};

/**
    CLIPBOARDS
**/

//Clipboard foreground
#define clipboardFx 0
#define clipboardFy 0

//Clipboard dimensions
#define clipboardw  53
#define clipboardh  16

//Stuff for bordering
#define line_X 53
#define line_Y 0

#define TL_X 53
#define TL_Y 1

#define TR_X 57
#define TR_Y 1

#define BL_X 53
#define BL_Y 5

#define BR_X 57
#define BR_Y 5

#define LINE_W 3
#define LINE_H 3

/*************************** END ***************************/

/** ARROW_BOXES **/

#define ARROW_PLUS_X 0
#define ARROW_PLUS_Y 16

#define ARROW_MINUS_X 13
#define ARROW_MINUS_Y 16

#define ARROW_W 13
#define ARROW_H 13

/*************************** END ***************************/

/** VOLUME_BOXES **/

#define VOLUME_BACKGROUND_X 0
#define VOLUME_BACKGROUND_Y  29
#define VOLUME_BACKGROUND_W 210
#define VOLUME_BACKGROUND_H  12

#define VOLUME_MOVER_X 210
#define VOLUME_MOVER_Y 29
#define VOLUME_MOVER_W 10
#define VOLUME_MOVER_H 12

#define VOLUME_FILL_X 220
#define VOLUME_FILL_Y 30
#define VOLUME_FILL_W 1
#define VOLUME_FILL_H 10

/*************************** END ***************************/

/** CHECK_BOXES **/

#define CHECKBOX_X 78
#define CHECKBOX_Y 0

#define CHECKBOX_NON_X 61
#define CHECKBOX_NON_Y 0

#define CHECKBOX_W 17
#define CHECKBOX_H 17

/*************************** END ***************************/

/** COMBO BOX **/

#define PINGUI_COMBO_BOX_ARROW_X 53
#define PINGUI_COMBO_BOX_ARROW_Y 8
#define PINGUI_COMBO_BOX_ARROW_W 7
#define PINGUI_COMBO_BOX_ARROW_H 4

/*************************** END ***************************/

/**
    Elements from the window sheet
**/
/*************** Window *********************/

#define PINGUI_WINDOW_X 0
#define PINGUI_WINDOW_Y 0
#define PINGUI_WINDOW_W 200
#define PINGUI_WINDOW_H 200

/**Borders**/

#define PINGUI_WINDOW_LINE_X 61
#define PINGUI_WINDOW_LINE_Y 200
#define PINGUI_WINDOW_LINE_W 1
#define PINGUI_WINDOW_LINE_H 1

#define PINGUI_WINDOW_TL_X 62
#define PINGUI_WINDOW_TL_Y 201

#define PINGUI_WINDOW_TR_X 66
#define PINGUI_WINDOW_TR_Y 201

#define PINGUI_WINDOW_BL_X 62
#define PINGUI_WINDOW_BL_Y 205

#define PINGUI_WINDOW_BR_X 66
#define PINGUI_WINDOW_BR_Y 205

#define PINGUI_WINDOW_BORDER_W 3
#define PINGUI_WINDOW_BORDER_H 3
/******************************************/

/** TABS **/

#define PINGUI_WINDOW_TAB_LINE_X 14
#define PINGUI_WINDOW_TAB_LINE_Y 200

#define PINGUI_WINDOW_TAB_X 14
#define PINGUI_WINDOW_TAB_Y 201
#define PINGUI_WINDOW_TAB_W 47
#define PINGUI_WINDOW_TAB_H 25

/*************************** END ***************************/

/** EXIT BUTTON **/

#define PINGUI_WINDOW_EXITBUTTON_X 70
#define PINGUI_WINDOW_EXITBUTTON_Y 200
#define PINGUI_WINDOW_EXITBUTTON_W 13
#define PINGUI_WINDOW_EXITBUTTON_H 13

/*************************** END ***************************/

/** SCROLLER BUTTON **/

#define PINGUI_WINDOW_SCROLLER_INNER_X 84
#define PINGUI_WINDOW_SCROLLER_INNER_Y 201

#define PINGUI_WINDOW_SCROLLER_FILL_X 96
#define PINGUI_WINDOW_SCROLLER_FILL_Y 200

#define PINGUI_WINDOW_SCROLLER_LINE_X 83
#define PINGUI_WINDOW_SCROLLER_LINE_Y 200

#define PINGUI_WINDOW_SCROLLER_W 1
#define PINGUI_WINDOW_SCROLLER_H 1

#define PINGUI_WINDOW_DEFAULT_SCROLLER_H 13
#define PINGUI_WINDOW_DEFAULT_SCROLLER_W 13

/** SCROLLER ARROWS **/

//UP - DOWN arrows
#define PINGUI_WINDOW_SCROLLER_ARROW_UPDOWN_W 9
#define PINGUI_WINDOW_SCROLLER_ARROW_UPDOWN_H 8

#define PINGUI_WINDOW_SCROLLER_ARROW_UP_X 108
#define PINGUI_WINDOW_SCROLLER_ARROW_UP_Y 204

#define PINGUI_WINDOW_SCROLLER_ARROW_DOWN_X 118
#define PINGUI_WINDOW_SCROLLER_ARROW_DOWN_Y 204

//RIGHT - LEFT arrows
#define PINGUI_WINDOW_SCROLLER_ARROW_SIDE_W 5
#define PINGUI_WINDOW_SCROLLER_ARROW_SIDE_H 9

#define PINGUI_WINDOW_SCROLLER_ARROW_LEFT_X 128
#define PINGUI_WINDOW_SCROLLER_ARROW_LEFT_Y 200

#define PINGUI_WINDOW_SCROLLER_ARROW_RIGHT_X 134
#define PINGUI_WINDOW_SCROLLER_ARROW_RIGHT_Y 200

/*************************** END ***************************/
class SheetManager
{
    private:
        static std::vector<SDL_Surface*> _SURFACES;

        static SDL_Surface* createCloneSurface(int w, int h, surfaceType source);

        static void blitSurface(int x, int y, int w, int h, surfaceType source, SDL_Surface*& dst,SDL_BlendMode mode = SDL_BLENDMODE_NONE);

        static void blitSurface(PinGUI::Rect tmpRect, surfaceType source, SDL_Surface*& dst,SDL_BlendMode mode = SDL_BLENDMODE_NONE);
    public:
        /**
            Public Methods
        **/
        static GLuint loadSurface(enum surfaceType,SDL_Surface* wholeSurface);

        static void loadAllTextures();

        static void loadWindowTextures();

        static void addToVector(SDL_Surface*);

        static void manageCroppedRect(SDL_Rect* rect,surfaceType* type);

        static void addClipboard(SDL_Surface*& target);

        static void addLineBorders(SDL_Surface*& target, lineType type);

        static void addVertexBorders(SDL_Surface*& target, lineType type);

        static void addRectangleBorders(SDL_Surface*& target, surfaceType line);

        static void addBackground(SDL_Surface*& target);

        static SDL_Surface* cloneSurface(enum surfaceType);

        /**
            Elements stuff
        **/
        static void loadComboBoxArrow(SDL_Surface*& sourceSurface);


        /**
            Window stuff
        **/
        static void loadWindow(SDL_Surface*& sourceSurface);
        static void loadWindowTab(SDL_Surface*& sourceSurface);
        static void loadWindowExitButton(SDL_Surface*& sourceSurface);
        static void loadWindowBorders(SDL_Surface*& sourceSurface);
        static void loadWindowScroller(SDL_Surface*& sourceSurface);
        static void loadWindowScrollerArrows(SDL_Surface*& sourceSurface);
        static void loadWindowScrollerFill(SDL_Surface*& sourceSurface);

        static void addTabBackGround(SDL_Surface*& target);
        static void addTabLines(SDL_Surface*& target);

        static void uploadSurface(SDL_Rect& cropRect, SDL_Surface* sourceSurface);
        static void uploadSurface(PinGUI::Rect& cropRect, SDL_Surface* sourceSurface);

        static SDL_Surface* getSurface(enum surfaceType);

        static SDL_Surface* createClipBoard(int w, int h);
        static SDL_Surface* createWindowTab(int w, int h);
        static SDL_Surface* createWindow(int w, int h);
        static SDL_Surface* createWindowScroller(int value, manipulationState state);
        static SDL_Surface* createVerticalScroller(const int& h);
        static SDL_Surface* createHorizontalScroller(const int& w);

        static SDL_Surface* createRectangle(int w, int h, surfaceType background, surfaceType line);
        static void putOnSurface(SDL_Surface* src, surfaceType target, int x, int y);
};

#endif // SHEETMANAGER_H
