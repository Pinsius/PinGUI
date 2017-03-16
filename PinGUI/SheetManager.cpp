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

#include "SheetManager.h"
#include <iostream>

std::vector<SDL_Surface*> SheetManager::_SURFACES;

/**
    ORDER OF LOADING IS VERY IMPORTANT!
**/

void SheetManager::loadAllTextures(){

    //First i load whole image into 1 surface
    SDL_Surface* wholeSurface = nullptr;
    wholeSurface = IMG_Load("PinGUI/TextManager/Images/TextManagerSheet.png");

    //Error checking
    if (wholeSurface==nullptr){
        ErrorManager::fileError("PinGUI/TextManager/Images/TextManagerSheet.png");
    }

    //I load all surfaces i need only once(at startup) so i have them loaded all the time prepared for use
    loadSurface(BOARD,wholeSurface);
    loadSurface(BORDER_LINE,wholeSurface);
    loadSurface(BORDER_TL,wholeSurface);
    loadSurface(BORDER_BL,wholeSurface);
    loadSurface(BORDER_TR,wholeSurface);
    loadSurface(BORDER_BR,wholeSurface);

    loadSurface(ARROW_PLUS,wholeSurface);
    loadSurface(ARROW_MINUS,wholeSurface);

    loadSurface(VOLUME_BACK,wholeSurface);
    loadSurface(VOLUME_MOVER,wholeSurface);
    loadSurface(VOLUME_FILL,wholeSurface);

    loadSurface(CHECKBOX,wholeSurface);
    loadSurface(NON_CHECKBOX,wholeSurface);

    loadComboBoxArrow(wholeSurface);

    SDL_FreeSurface(wholeSurface);

    loadWindowTextures();
}

GLuint SheetManager::loadSurface(enum surfaceType type,SDL_Surface* wholeSurface){

    //Rect to store the cropped area pos and dimensions
    SDL_Rect tmp;

    //Surface that will be loaded into my vector of Surfaces
    SDL_Surface* tmpSurface;

    //Here i set the position of the cropped area
    manageCroppedRect(&tmp,&type);

    //Setting the new surface
    tmpSurface = SDL_CreateRGBSurface(wholeSurface->flags,tmp.w, tmp.h,
                                    wholeSurface->format->BitsPerPixel,
                                    wholeSurface->format->Rmask,
                                    wholeSurface->format->Gmask,
                                    wholeSurface->format->Bmask,
                                    wholeSurface->format->Amask);

    SDL_SetSurfaceBlendMode(tmpSurface,SDL_BLENDMODE_NONE);
    //Bliting the area onto my new surface
    SDL_BlitSurface(wholeSurface,&tmp,tmpSurface,NULL);

    addToVector(tmpSurface);
}

void SheetManager::manageCroppedRect(SDL_Rect* rect,surfaceType* type){

    switch(*type){
        case BOARD : {
            rect->x = clipboardFx;
            rect->y = clipboardFy;
            rect->w = clipboardw;
            rect->h = clipboardh;
            break;
        }
        case BORDER_LINE : {
            rect->x = line_X;
            rect->y = line_Y;
            rect->w = 1;
            rect->h = 1;
            break;
        }
        case BORDER_TL : {
            rect->x = TL_X;
            rect->y = TL_Y;
            rect->w = LINE_W;
            rect->h = LINE_H;
            break;
        }
        case BORDER_TR : {
            rect->x = TR_X;
            rect->y = TR_Y;
            rect->w = LINE_W;
            rect->h = LINE_H;
            break;
        }
        case BORDER_BL : {
            rect->x = BL_X;
            rect->y = BL_Y;
            rect->w = LINE_W;
            rect->h = LINE_H;
            break;
        }
        case BORDER_BR : {
            rect->x = BR_X;
            rect->y = BR_Y;
            rect->w = LINE_W;
            rect->h = LINE_H;
            break;
        }
        case ARROW_PLUS : {
            rect->x = ARROW_PLUS_X;
            rect->y = ARROW_PLUS_Y;
            rect->w = ARROW_W;
            rect->h = ARROW_H;
            break;
        }
        case ARROW_MINUS : {
            rect->x = ARROW_MINUS_X;
            rect->y = ARROW_MINUS_Y;
            rect->w = ARROW_W;
            rect->h = ARROW_H;
            break;
        }
        case VOLUME_BACK : {
            rect->x = VOLUME_BACKGROUND_X;
            rect->y = VOLUME_BACKGROUND_Y;
            rect->w = VOLUME_BACKGROUND_W;
            rect->h = VOLUME_BACKGROUND_H;
            break;
        }
        case VOLUME_MOVER : {
            rect->x = VOLUME_MOVER_X;
            rect->y = VOLUME_MOVER_Y;
            rect->w = VOLUME_MOVER_W;
            rect->h = VOLUME_MOVER_H;
            break;
        }
        case VOLUME_FILL : {
            rect->x = VOLUME_FILL_X;
            rect->y = VOLUME_FILL_Y;
            rect->w = VOLUME_FILL_W;
            rect->h = VOLUME_FILL_H;
            break;
        }
        case CHECKBOX : {
            rect->x = CHECKBOX_X;
            rect->y = CHECKBOX_Y;
            rect->w = CHECKBOX_W;
            rect->h = CHECKBOX_H;
            break;
        }
        case NON_CHECKBOX : {
            rect->x = CHECKBOX_NON_X;
            rect->y = CHECKBOX_NON_Y;
            rect->w = CHECKBOX_W;
            rect->h = CHECKBOX_H;
            break;
        }
        case WINDOW_TAB : {
            rect->x = PINGUI_WINDOW_TAB_X;
            rect->y = PINGUI_WINDOW_TAB_Y;
            rect->w = PINGUI_WINDOW_TAB_W;
            rect->h = PINGUI_WINDOW_TAB_H;
            break;
        }
    }
}

void SheetManager::loadComboBoxArrow(SDL_Surface*& sourceSurface){

    SDL_Rect tmpRect;
    tmpRect.x = PINGUI_COMBO_BOX_ARROW_X;
    tmpRect.y = PINGUI_COMBO_BOX_ARROW_Y;
    tmpRect.w = PINGUI_COMBO_BOX_ARROW_W;
    tmpRect.h = PINGUI_COMBO_BOX_ARROW_H;

    uploadSurface(tmpRect,sourceSurface);
}


void SheetManager::addToVector(SDL_Surface* newSurface){
    _SURFACES.push_back(newSurface);
}

SDL_Surface* SheetManager::getSurface(enum surfaceType type){
    return cloneSurface(type);
}

SDL_Surface* SheetManager::cloneSurface(enum surfaceType type){

    SDL_Surface* tmpSurface = createCloneSurface(_SURFACES[type]->w,_SURFACES[type]->h,type);

    SDL_Rect tmpRect;
    tmpRect.x = 0;
    tmpRect.y = 0;
    tmpRect.w = tmpSurface->w;
    tmpRect.h = tmpSurface->h;

    SDL_BlitScaled(_SURFACES[type],NULL,tmpSurface,&tmpRect);

    return tmpSurface;
}
void SheetManager::loadWindowTextures(){

    SDL_Surface* wholeSurface = nullptr;
    wholeSurface = IMG_Load("PinGUI/TextManager/Images/WindowSheet.png");

    //Error checking
    if (wholeSurface==nullptr){
        ErrorManager::fileError("PinGUI/TextManager/Images/WindowSheet.png");
    }

    loadWindow(wholeSurface);
    loadWindowTab(wholeSurface);
    loadWindowExitButton(wholeSurface);
    loadWindowScroller(wholeSurface);
    loadWindowScrollerArrows(wholeSurface);
    loadWindowScrollerFill(wholeSurface);
    SDL_FreeSurface(wholeSurface);
}

SDL_Surface* SheetManager::createClipBoard(int w, int h){

    SDL_Surface* final_Surface = createCloneSurface(w+2,h+2,BOARD);

    //First i link the clipboard surface
    addClipboard(final_Surface);

    //Now im going to create the borders
    //Lines
    addLineBorders(final_Surface,PINGUI_CLIPBOARD);

    //Vertex borders
    addVertexBorders(final_Surface,PINGUI_CLIPBOARD);

    //Return it
    return final_Surface;
}

void SheetManager::addClipboard(SDL_Surface*& target){

    SDL_Rect tmpRect;
    tmpRect.x = 1;
    tmpRect.y = 1;
    tmpRect.w = target->w-2;
    tmpRect.h = target->h-2;

    //"Add" clipboard(background stuff) to my surface
    SDL_BlitScaled(_SURFACES[BOARD],NULL,target,&tmpRect);
}

void SheetManager::addLineBorders(SDL_Surface*& target, lineType type){

    surfaceType mainType;
    surfaceType lineType;
    switch(type){
        case PINGUI_WINDOW:{
            mainType = WINDOW_BACKGROUND;
            lineType = WINDOW_LINE;
            break;
        }
        case PINGUI_CLIPBOARD:{
            mainType = BOARD;
            lineType = BORDER_LINE;
            break;
        }
    }

    /**
        UP and DOWN lines
    **/
    //Now i need to add UP and DOWN border line
    //I need separate surface because im going to resize the original "dot"
    int line_length = target->w-4;
    SDL_Surface* upDownLine = createCloneSurface(line_length,1,mainType);

    SDL_Rect tmpRect;
    tmpRect.x = 0;
    tmpRect.y = 0;
    tmpRect.w = line_length;
    tmpRect.h = 1;

    //Now i create "the right" line surface
    SDL_BlitScaled(_SURFACES[lineType],NULL,upDownLine,&tmpRect);


    tmpRect.x = 2;

    //Now i need to add the lines to target surface
    //First the upper line
    SDL_BlitSurface(upDownLine,NULL,target,&tmpRect);


    //And now the down line
    tmpRect.y = target->h-1;
    SDL_BlitSurface(upDownLine,NULL,target,&tmpRect);

    //Clean the memory
    SDL_FreeSurface(upDownLine);

    /**
        RIGHT and LEFT lines
    **/

    int line_height = target->h-4;
    SDL_Surface* bottomLine = createCloneSurface(1,line_height,mainType);

    //Remake the rect
    tmpRect.x = 0;
    tmpRect.y = 0;
    tmpRect.w = 1;
    tmpRect.h = line_height;

    //Now i create "the right" line surface
    SDL_BlitScaled(_SURFACES[lineType],NULL,bottomLine,&tmpRect);

    //Blit them to surface
    tmpRect.y = 2;
    SDL_BlitSurface(bottomLine,NULL,target,&tmpRect);

    tmpRect.x = target->w-1;
    SDL_BlitSurface(bottomLine,NULL,target,&tmpRect);

    //Free the memory
    SDL_FreeSurface(bottomLine);
}

void SheetManager::addVertexBorders(SDL_Surface*& target, lineType type){

    SDL_Rect tmpRect;
    surfaceType mainType;

    switch(type){

        case PINGUI_WINDOW:{

            mainType = WINDOW_TL;
            tmpRect.w = PINGUI_WINDOW_BORDER_W;
            tmpRect.h = PINGUI_WINDOW_BORDER_H;

            break;
        }
        case PINGUI_CLIPBOARD:{

            mainType = BORDER_TL;
            tmpRect.w = LINE_W;
            tmpRect.h = LINE_H;
            break;
        }
    }

    //First TL
    tmpRect.x = 0;
    tmpRect.y = 0;
    tmpRect.w = LINE_W;
    tmpRect.h = LINE_H;

    SDL_SetSurfaceBlendMode(_SURFACES[mainType],SDL_BLENDMODE_BLEND);
    SDL_SetSurfaceBlendMode(_SURFACES[mainType+1],SDL_BLENDMODE_BLEND);
    SDL_SetSurfaceBlendMode(_SURFACES[mainType+2],SDL_BLENDMODE_BLEND);
    SDL_SetSurfaceBlendMode(_SURFACES[mainType+3],SDL_BLENDMODE_BLEND);

    //TL
    SDL_BlitSurface(_SURFACES[mainType],NULL,target,&tmpRect);

    //BL
    tmpRect.y = target->h-tmpRect.h;
    SDL_BlitSurface(_SURFACES[mainType+1],NULL,target,&tmpRect);

    //TR
    tmpRect.y = 0;
    tmpRect.x = target->w-tmpRect.w;
    SDL_BlitSurface(_SURFACES[mainType+2],NULL,target,&tmpRect);

    //BR
    tmpRect.x = target->w-tmpRect.w;
    tmpRect.y = target->h-tmpRect.h;
    SDL_BlitSurface(_SURFACES[mainType+3],NULL,target,&tmpRect);
}

void SheetManager::loadWindowTab(SDL_Surface*& sourceSurface){

    //At first i load tab texture
    SDL_Rect tmpRect;
    tmpRect.x = PINGUI_WINDOW_TAB_X;
    tmpRect.y = PINGUI_WINDOW_TAB_Y;
    tmpRect.w = PINGUI_WINDOW_TAB_W;
    tmpRect.h = PINGUI_WINDOW_TAB_H;
    uploadSurface(tmpRect,sourceSurface);


    //Now the line
    tmpRect.x = PINGUI_WINDOW_TAB_LINE_X;
    tmpRect.y = PINGUI_WINDOW_TAB_LINE_Y;
    tmpRect.w = 10;
    tmpRect.h = 1;
    uploadSurface(tmpRect,sourceSurface);
}

void SheetManager::loadWindowExitButton(SDL_Surface*& sourceSurface){

    SDL_Rect tmpRect;
    tmpRect.x = PINGUI_WINDOW_EXITBUTTON_X;
    tmpRect.y = PINGUI_WINDOW_EXITBUTTON_Y;
    tmpRect.w = PINGUI_WINDOW_EXITBUTTON_W;
    tmpRect.h = PINGUI_WINDOW_EXITBUTTON_H;
    uploadSurface(tmpRect,sourceSurface);
}

void SheetManager::uploadSurface(SDL_Rect& cropRect, SDL_Surface* sourceSurface){

    SDL_Surface* targetSurface;
    targetSurface = SDL_CreateRGBSurface(sourceSurface->flags,cropRect.w, cropRect.h,
                                    sourceSurface->format->BitsPerPixel,
                                    sourceSurface->format->Rmask,
                                    sourceSurface->format->Gmask,
                                    sourceSurface->format->Bmask,
                                    sourceSurface->format->Amask);

    SDL_SetSurfaceBlendMode(targetSurface,SDL_BLENDMODE_NONE);

    //Bliting the area onto my new surface
    SDL_BlitSurface(sourceSurface,&cropRect,targetSurface,NULL);

    addToVector(targetSurface);
}

SDL_Surface* SheetManager::createWindowTab(int w, int h){

    SDL_Surface* final_Surface = createCloneSurface(w,h+2,WINDOW_BACKGROUND);

    //Modify them
    addTabBackGround(final_Surface);
    addTabLines(final_Surface);

    //Return it
    return final_Surface;
}

void SheetManager::addTabBackGround(SDL_Surface*& target){

    SDL_Rect tmpRect;
    tmpRect.x = 0;
    tmpRect.y = 1;
    tmpRect.w = target->w;
    tmpRect.h = target->h;

    //"Add" background stuff to my surface
    SDL_BlitScaled(_SURFACES[WINDOW_TAB],NULL,target,&tmpRect);
}

void SheetManager::addTabLines(SDL_Surface*& target){

    SDL_Rect tmpRect;
    tmpRect.x = 0;
    tmpRect.y = 0;
    tmpRect.w = target->w;
    tmpRect.h = 1;

    //Now blit it to target Surface
    SDL_BlitScaled(_SURFACES[WINDOW_TAB_LINE],NULL,target,&tmpRect);
    tmpRect.y = target->h-1;
    SDL_BlitScaled(_SURFACES[WINDOW_TAB_LINE],NULL,target,&tmpRect);
}

void SheetManager::loadWindow(SDL_Surface*& sourceSurface){

    SDL_Rect tmpRect;

    tmpRect.x = PINGUI_WINDOW_X;
    tmpRect.y = PINGUI_WINDOW_Y;
    tmpRect.w = PINGUI_WINDOW_W;
    tmpRect.h = PINGUI_WINDOW_H;
    uploadSurface(tmpRect,sourceSurface);

    loadWindowBorders(sourceSurface);

}

void SheetManager::loadWindowBorders(SDL_Surface*& sourceSurface){

    SDL_Rect tmpRect;
    tmpRect.x = PINGUI_WINDOW_LINE_X;
    tmpRect.y = PINGUI_WINDOW_LINE_Y;
    tmpRect.w = PINGUI_WINDOW_LINE_W;
    tmpRect.h = PINGUI_WINDOW_LINE_H;
    uploadSurface(tmpRect,sourceSurface);

    tmpRect.w = 3;
    tmpRect.h = 3;

    tmpRect.x = PINGUI_WINDOW_TL_X;
    tmpRect.y = PINGUI_WINDOW_TL_Y;
    uploadSurface(tmpRect,sourceSurface);

    tmpRect.x = PINGUI_WINDOW_BL_X;
    tmpRect.y = PINGUI_WINDOW_BL_Y;
    uploadSurface(tmpRect,sourceSurface);

    tmpRect.x = PINGUI_WINDOW_TR_X;
    tmpRect.y = PINGUI_WINDOW_TR_Y;
    uploadSurface(tmpRect,sourceSurface);

    tmpRect.x = PINGUI_WINDOW_BR_X;
    tmpRect.y = PINGUI_WINDOW_BR_Y;
    uploadSurface(tmpRect,sourceSurface);

}

void SheetManager::addBackground(SDL_Surface*& target){

    SDL_Rect tmpRect;
    tmpRect.x = 1;
    tmpRect.y = 1;
    tmpRect.w = target->w-2;
    tmpRect.h = target->h-2;

    //"Add" clipboard(background stuff) to my surface
    SDL_SetSurfaceAlphaMod(_SURFACES[WINDOW_BACKGROUND],240);

    SDL_BlitScaled(_SURFACES[WINDOW_BACKGROUND],NULL,target,&tmpRect);
}

SDL_Surface* SheetManager::createWindow(int w, int h){

    SDL_Surface* final_Surface = createCloneSurface(w+2,h,WINDOW_BACKGROUND);

    addBackground(final_Surface);
    addLineBorders(final_Surface,PINGUI_WINDOW);
    addVertexBorders(final_Surface,PINGUI_WINDOW);

    //Return it
    return final_Surface;
}

void SheetManager::loadWindowScroller(SDL_Surface*& sourceSurface){

    SDL_Rect tmpRect;

    tmpRect.w = PINGUI_WINDOW_SCROLLER_W;
    tmpRect.h = PINGUI_WINDOW_SCROLLER_H;

    //Inner part of scroller
    tmpRect.x = PINGUI_WINDOW_SCROLLER_INNER_X;
    tmpRect.y = PINGUI_WINDOW_SCROLLER_INNER_Y;
    uploadSurface(tmpRect,sourceSurface);

    //Line
    tmpRect.x = PINGUI_WINDOW_SCROLLER_LINE_X;
    tmpRect.y = PINGUI_WINDOW_SCROLLER_LINE_Y;
    uploadSurface(tmpRect,sourceSurface);

}

SDL_Surface* SheetManager::createWindowScroller(int value, PinGUI::manipulationState state){

    switch(state){
        case PinGUI::VERTICAL : {

            return createVerticalScroller(value);
        }
        case PinGUI::HORIZONTAL : {

            return createHorizontalScroller(value);
        }
        default :
        //In case of error variables
        ErrorManager::systemError("Sheetmanager::createWindowScroller received a bad manip state");
    }

}

SDL_Surface* SheetManager::createVerticalScroller(const int& h){

    SDL_Surface* final_Surface = createCloneSurface(PINGUI_WINDOW_DEFAULT_SCROLLER_W,h,WINDOW_SCROLLER_INNER);

    //Top
    blitSurface(1,1,PINGUI_WINDOW_DEFAULT_SCROLLER_W,h,WINDOW_SCROLLER_INNER,final_Surface);

    addRectangleBorders(final_Surface,WINDOW_SCROLLER_LINE);

    return final_Surface;
}

SDL_Surface* SheetManager::createHorizontalScroller(const int& w){

    SDL_Surface* final_Surface = createCloneSurface(w,PINGUI_WINDOW_DEFAULT_SCROLLER_H,WINDOW_SCROLLER_INNER);

    //Top
    blitSurface(1,1,w,PINGUI_WINDOW_DEFAULT_SCROLLER_H,WINDOW_SCROLLER_INNER,final_Surface);

    addRectangleBorders(final_Surface,WINDOW_SCROLLER_LINE);

    return final_Surface;
}

SDL_Surface* SheetManager::createCloneSurface(int w, int h, surfaceType source){

    SDL_Surface* final_Surface = SDL_CreateRGBSurface(0,w, h,
                                    _SURFACES[source]->format->BitsPerPixel,
                                    _SURFACES[source]->format->Rmask,
                                    _SURFACES[source]->format->Gmask,
                                    _SURFACES[source]->format->Bmask,
                                    _SURFACES[source]->format->Amask);
    return final_Surface;
}

void SheetManager::blitSurface(int x, int y, int w, int h, surfaceType source, SDL_Surface*& dst,SDL_BlendMode mode){

    SDL_Rect tmpRect;
    tmpRect.x = x;
    tmpRect.y = y;
    tmpRect.w = w;
    tmpRect.h = h;

    if (mode!=SDL_BLENDMODE_NONE) SDL_SetSurfaceBlendMode(_SURFACES[source],mode);

    SDL_BlitScaled(_SURFACES[source],NULL,dst,&tmpRect);
}

void SheetManager::blitSurface(PinGUI::Rect tmpRect, surfaceType source, SDL_Surface*& dst,SDL_BlendMode mode){

    SDL_Rect TmpRect;
    TmpRect.x = tmpRect.x;
    TmpRect.y = tmpRect.y;
    TmpRect.w = tmpRect.w;
    TmpRect.h = tmpRect.h;

    if (mode!=SDL_BLENDMODE_NONE) SDL_SetSurfaceBlendMode(_SURFACES[source],mode);

    SDL_BlitScaled(_SURFACES[source],NULL,dst,&TmpRect);
}

void SheetManager::loadWindowScrollerArrows(SDL_Surface*& sourceSurface){

    SDL_Rect tmpRect;
    tmpRect.w = PINGUI_WINDOW_SCROLLER_ARROW_UPDOWN_W;
    tmpRect.h = PINGUI_WINDOW_SCROLLER_ARROW_UPDOWN_H;

    tmpRect.x = PINGUI_WINDOW_SCROLLER_ARROW_UP_X;
    tmpRect.y = PINGUI_WINDOW_SCROLLER_ARROW_UP_Y;
    uploadSurface(tmpRect,sourceSurface);

    tmpRect.x = PINGUI_WINDOW_SCROLLER_ARROW_DOWN_X;
    tmpRect.y = PINGUI_WINDOW_SCROLLER_ARROW_DOWN_Y;
    uploadSurface(tmpRect,sourceSurface);

    tmpRect.w = PINGUI_WINDOW_SCROLLER_ARROW_SIDE_W;
    tmpRect.h = PINGUI_WINDOW_SCROLLER_ARROW_SIDE_H;

    tmpRect.x = PINGUI_WINDOW_SCROLLER_ARROW_LEFT_X;
    tmpRect.y = PINGUI_WINDOW_SCROLLER_ARROW_LEFT_Y;
    uploadSurface(tmpRect,sourceSurface);

    tmpRect.x = PINGUI_WINDOW_SCROLLER_ARROW_RIGHT_X;
    tmpRect.y = PINGUI_WINDOW_SCROLLER_ARROW_RIGHT_Y;
    uploadSurface(tmpRect,sourceSurface);
}

void SheetManager::loadWindowScrollerFill(SDL_Surface*& sourceSurface){

    SDL_Rect tmpRect;

    tmpRect.x = PINGUI_WINDOW_SCROLLER_FILL_X;
    tmpRect.y = PINGUI_WINDOW_SCROLLER_FILL_Y;
    tmpRect.w = 1;
    tmpRect.h = 1;

    uploadSurface(tmpRect,sourceSurface);
}

void SheetManager::addRectangleBorders(SDL_Surface*& target, surfaceType line){

    /**UP DOWN lines**/

    //Upper line
    blitSurface(0,0,target->w,1,WINDOW_SCROLLER_LINE,target);

    //Bottom line
    blitSurface(0,target->h-1,target->w,1,WINDOW_SCROLLER_LINE,target);


    /** RIGHT&LEFT LINES **/

    //Left
    blitSurface(0,1,1,target->h-2,WINDOW_SCROLLER_LINE,target);

    //Right
    blitSurface(target->w-1,1,1,target->h-2,WINDOW_SCROLLER_LINE,target);
}

SDL_Surface* SheetManager::createRectangle(int w, int h, surfaceType background, surfaceType line){

    SDL_Surface* final_Surface = createCloneSurface(w,h,background);


    //Background
    if (background != BLANK_SURFACE)
        blitSurface(1,1,w-1,h-1,background,final_Surface);

    //Lines around
    if (line != BLANK_SURFACE)
        addRectangleBorders(final_Surface,line);

    return final_Surface;
}

void SheetManager::putOnSurface(SDL_Surface* src, surfaceType target, int x, int y){

    blitSurface(x,y,_SURFACES[target]->w,_SURFACES[target]->h,target,src,SDL_BLENDMODE_BLEND);
}
