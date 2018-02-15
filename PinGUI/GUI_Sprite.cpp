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

#include "GUI_Sprite.h"
#include <iostream>

GUI_Sprite::GUI_Sprite(PinGUI::Rect rect, SDL_Surface* source,SDL_Color color):
    _textureID(0)
{
    _rect.rect.initPos(rect);

    //Setting the color data
    _color.r = color.r;
    _color.g = color.g;
    _color.b = color.b;
    _color.a = color.a; 

    //Create texture from the source texture
    createTexture(source);
}

GUI_Sprite::GUI_Sprite(PinGUI::Rect rect,SDL_Surface* source):
    _textureID(0)
{
    _rect.rect.initPos(rect);

    initColor();

    //Create texture from the source texture
    createTexture(source);
}

GUI_Sprite::GUI_Sprite(PinGUI::Vector2<GUIPos> pos, SDL_Surface* source):
    _textureID(0)
{
    _rect.rect.initPos(pos);

    initColor();

    //Create texture from the source texture
    createTexture(source);
}

GUI_Sprite::GUI_Sprite(const std::string& text, PinGUI::Vector2<GUIPos> pos,textInfo* info):
    _textureID(0)
{
    _rect.rect.initPos(pos);

    initColor();

    loadTextSprite(text,info);
}

GUI_Sprite::GUI_Sprite(const std::string& text,textInfo* info):
    _textureID(0)
{
    _rect.rect.x = 0;
    _rect.rect.y = 0;

    initColor();

    loadTextSprite(text,info);
}

void GUI_Sprite::loadTextSprite(const std::string& text, textInfo*& info){

    SDL_Surface* tmpSurface = nullptr;

    tmpSurface = TTF_RenderText_Blended(info->font,text.c_str(), info->color);

    if (tmpSurface==nullptr){
		std::cout << SDL_GetError() << std::endl;
        ErrorManager::systemError("Cannot make a text texture");
    }

    createTexture(tmpSurface);
}

GUI_Sprite::~GUI_Sprite()
{
    glDeleteTextures(1,&_textureID);
}


void GUI_Sprite::initColor(){

     //Setting the color data
    _color.r = 255;
    _color.g = 255;
    _color.b = 255;
    _color.a = 255;
}

void GUI_Sprite::createTexture(SDL_Surface* surface){

    glGenTextures(1,&_textureID);

    if (_textureID==0)
        ErrorManager::systemError("Cannot generate GUI texture!");

    glBindTexture(GL_TEXTURE_2D,_textureID);

    int Mode = GL_RGB;

    if (surface->format->BytesPerPixel==4){

        Mode = GL_RGBA;
    }

    glTexImage2D(GL_TEXTURE_2D,0,Mode,surface->w,surface->h,0,Mode,GL_UNSIGNED_BYTE,surface->pixels);

    //Wrapping
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

    //Filtering
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D,0);
    _rect.rect.w = surface->w;
    _rect.rect.h = surface->h;

    createVBO();

    SDL_FreeSurface(surface);
    _rect.realRect = _rect.rect;
}

void GUI_Sprite::changeTexture(SDL_Surface* surface){

    if (_textureID!=0)
        glDeleteTextures(1,&_textureID);

    createTexture(surface);
}

void GUI_Sprite::createVBO(VBO_UV_UPDATE_MODE mode){

    updatePositions();
    updateColors();

    switch(mode){
        case U : {
            updateHorizontalUVs();
            break;
        }
        case V : {
            updateVerticalUVs();
            break;
        }
        case UV : {
            updateUVs();
            break;
        }

    }

}

void GUI_Sprite::updateColors(){

    for (int i = 0; i < 6; i++){

        _dataPointer.vertices[i].setColor(_color.r,_color.g,_color.b,_color.a);
    }
}

void GUI_Sprite::updatePositions(){

    _dataPointer.vertices[0].setPosition(getX() + getW(), getY() + getH());
    _dataPointer.vertices[1].setPosition(getX(), getY() + getH());
    _dataPointer.vertices[2].setPosition(getX(),getY());
    _dataPointer.vertices[3].setPosition(getX(),getY());
    _dataPointer.vertices[4].setPosition(getX() + getW(), getY());
    _dataPointer.vertices[5].setPosition(getX() + getW(), getY() + getH());

}

void GUI_Sprite::updateUVs(){

    //1st triangle
    //Top right
    _dataPointer.vertices[0].setUV(1.0f,1.0f);

    //Top left
    _dataPointer.vertices[1].setUV(0.0f,1.0f);

    //Bottom left
    _dataPointer.vertices[2].setUV(0.0f,0.0f);

    //2nd triangle

    //Bottom left
    _dataPointer.vertices[3].setUV(0.0f,0.0f);

    //Bottom right
    _dataPointer.vertices[4].setUV(1.0f,0.0f);

    //Top right
    _dataPointer.vertices[5].setUV(1.0f,1.0f);
}


void GUI_Sprite::updateVerticalUVs(){

    _dataPointer.vertices[0].setV(1.0f);
    _dataPointer.vertices[1].setV(1.0f);
    _dataPointer.vertices[2].setV(0.0f);
    _dataPointer.vertices[3].setV(0.0f);
    _dataPointer.vertices[4].setV(0.0f);
    _dataPointer.vertices[5].setV(1.0f);
}

void GUI_Sprite::updateHorizontalUVs(){

    _dataPointer.vertices[0].setU(1.0f);
    _dataPointer.vertices[1].setU(0.0f);
    _dataPointer.vertices[2].setU(0.0f);
    _dataPointer.vertices[3].setU(0.0f);
    _dataPointer.vertices[4].setU(1.0f);
    _dataPointer.vertices[5].setU(1.0f);
}

void GUI_Sprite::setX(float x){

    if(_rect.rect.x != x){

        _rect.realRect.x = x;
        _rect.rect.x = x;
        updatePositions();
    }
}

void GUI_Sprite::changeColor(SDL_Color tmp){

    _color = tmp;
    updateColors();
}

void GUI_Sprite::setAlpha(int value){

    _color.a = value;
    updateColors();
}

float GUI_Sprite::getX(){

    return _rect.rect.x;
}

void GUI_Sprite::setY(float y){

    if(_rect.rect.y != y){

        _rect.rect.y = y;
        _rect.realRect.y = y;
        updatePositions();
    }
}

float GUI_Sprite::getY(){

    return _rect.rect.y;
}

void GUI_Sprite::setW(int newW){

    if(_rect.rect.w != newW){

        _rect.rect.w = newW;
        updatePositions();
    }

}

void GUI_Sprite::moveSprite(const PinGUI::Vector2<GUIPos>& vect){

    PinGUI::Vector2<GUIPos> tmp(vect.x,vect.y);

    _rect.rect.addPos(tmp);
    _rect.realRect.addPos(tmp);

    updatePositions();
}


vboData* GUI_Sprite::getVBOData(){

    return &_dataPointer;
}

void GUI_Sprite::setH(int newH){

    if(_rect.rect.h != newH){

        _rect.rect.h = newH;
        updatePositions();
    }
}

void GUI_Sprite::setRH(int rh){

    _rect.realRect.h = rh;
    _rect.rect.h = rh;

    updatePositions();
}

void GUI_Sprite::setRW(int rw){

    _rect.realRect.w = rw;
    _rect.rect.w = rw;

    updatePositions();
}

void GUI_Sprite::offsetToRect(PinGUI::Rect offsetRect){

    float tmpX = offsetRect.x + (offsetRect.w/2);
    float tmpY = offsetRect.y + (offsetRect.h/2);

    PinGUI::Vector2<float> pos(tmpX - ((getW())/2),tmpY - ((getH())/2));

    _rect.rect.x = pos.x;
    _rect.rect.y = pos.y;
    _rect.equalPos();

    updatePositions();
}

void GUI_Sprite::setPos(PinGUI::Vector2<GUIPos> pos){

    _rect.rect.initPos(pos);
    _rect.realRect.initPos(pos);

    updatePositions();
}

void GUI_Sprite::setColor(Uint8 R, Uint8 G, Uint8 B){

    _color.r = R;
    _color.g = G;
    _color.b = B;
    updateColors();
}

void GUI_Sprite::addDimensions(int w, int h){

    _rect.rect.w += w;
    _rect.rect.h += h;
    updatePositions();
}

GUIRect GUI_Sprite::getGUIRect(){

    return _rect;
}

GUIRect* GUI_Sprite::getGUIRect_P(){

    return &_rect;
}

void GUI_Sprite::decW(int num){

    _rect.rect.w = _rect.realRect.w + num;
    updatePositions();
}

void GUI_Sprite::decH(int num){

    _rect.rect.h = _rect.realRect.h + num;
    updatePositions();
}

void GUI_Sprite::setRect(PinGUI::Rect rect){

    if (_rect.rect != rect){

        _rect.rect = rect;
        createVBO();
    }
}

void GUI_Sprite::incW(int num){

    _rect.rect.w += num;
    updatePositions();
}
