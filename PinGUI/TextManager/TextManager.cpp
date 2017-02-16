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

#include "TextManager.h"
#include <iostream>

TextManager::TextManager():
_vaoID(0),
_vboID(0),
_needUpdate(false),
_moved(false)
{
    _fontSize = 14;

    _textVBOManager = new VBO_Manager(40,true);
    _vaoID = _textVBOManager->getVAO();

    //Loading all the stuff
    loadTextInfo();
}

TextManager::TextManager(GLuint* vaoID):
_vboID(0),
_vaoID(*vaoID),
_needUpdate(false),
_moved(false)
{
    _fontSize = 14;

    _textVBOManager = new VBO_Manager(40,false);
    //Loading all the stuff
    loadTextInfo();
}

TextManager::~TextManager()
{
    glDeleteBuffers(1,&_vboID);

    if (_TEXTS.size()!=0){
        for (std::size_t i =0; i < _TEXTS.size();i++){
            delete _TEXTS[i];
        }
    }
}

//I have 2 cases, so i need to overload these functions
Text* TextManager::writeText(const std::string& text,int x, int y){

    PinGUI::Vector2<GUIPos> tmpVecc((float)x,(float)y);

    _TEXTS.push_back(new Text(text,tmpVecc,&_mainTextInfo));

    _needUpdate = true;
    return _TEXTS.back();

}

Text* TextManager::writeText(const std::string& text,int x, int y, int* var){

    PinGUI::Vector2<GUIPos> tmpVecc((float)x,(float)y);
    _TEXTS.push_back(new Text(text,tmpVecc,&_mainTextInfo,var));

    _needUpdate = true;
    return _TEXTS.back();
}

void TextManager::renderText(){

    glBindVertexArray(_vaoID);

    updateText();

    for (std::size_t i=0; i < _TEXTS.size();i++){

        if (_TEXTS[i]->getShow()){

            //Binding the texture
            glBindTexture(GL_TEXTURE_2D,_TEXTS[i]->getSprite()->getTexture());

            //Draw it
            glDrawArrays(GL_TRIANGLES,i*6,6);
        }
    }

    glBindVertexArray(0);
}

void TextManager::updateText(){

    checkForUpdate();

    if (_needUpdate){

        if (!_moved){

            _function.exec();
        } else if (_moved){
            _moved = false;
        }

        //Here is the action that is affected by stuff
        updateVBOData();
        _needUpdate = false;
        loadVBO();
    }
}

TTF_Font* TextManager::loadFont(const std::string& fontPath, int size){

    TTF_Font* tmp = nullptr;
    tmp = TTF_OpenFont(fontPath.c_str(),size);

    if (tmp==nullptr){
        ErrorManager::fileError(fontPath);
    }

    return tmp;
}

void TextManager::setColor(GLubyte R, GLubyte G, GLubyte B, GLubyte A){

    _mainTextInfo.color.r = R;
    _mainTextInfo.color.g = G;
    _mainTextInfo.color.b = B;
    _mainTextInfo.color.a = A;
}

void TextManager::loadVBO(){

    if (_textVBOManager->bufferData(0,_mainDataStorage))
        _needUpdate = true;
}

void TextManager::loadTextInfo(){

    SDL_Color tmp;

    //Default color
    tmp.r = 255;
    tmp.g = 255;
    tmp.b = 255;
    tmp.a = 255;

    _mainTextInfo.color = tmp;
    _mainTextInfo.font = loadFont("TextManager/Fonts/Oswald-Light.ttf",_fontSize);
}

void TextManager::removeData(std::size_t& position){

    _TEXTS.erase(_TEXTS.begin()+position);
    _mainDataStorage.erase(_mainDataStorage.begin()+position);

    _needUpdate = true;
}

void TextManager::checkForUpdate(){
    for (std::size_t i=0; i <_TEXTS.size();i++){

        if ( _TEXTS[i] && _TEXTS[i]->isActive()){

            _TEXTS[i]->needUpdate(&_mainTextInfo,_needUpdate);
        } else {

            removeData(i);
            i--;
        }
    }
}

std::vector<Text*>* TextManager::getMainTextStorage(){
    return &_TEXTS;
}

void TextManager::updateVBOData(){
    if (_mainDataStorage.size()!=0)
        _mainDataStorage.clear();

    for (std::size_t i = 0; i < _TEXTS.size(); i++){
        _mainDataStorage.push_back(_TEXTS[i]->getVBOData());
    }
}

void TextManager::setFontSize(int size){
    _fontSize = size;
    loadTextInfo();
}

Text* TextManager::getLastText(){
    if (_TEXTS.size()>0)
        return _TEXTS.back();
    else
        return nullptr;
}

void TextManager::moveTextManager(const PinGUI::Vector2<GUIPos>& vect, bool croppedMovement){

    for (std::size_t i = 0; i < _TEXTS.size(); i++){

        if (!_TEXTS[i]->isNetworked())
            _TEXTS[i]->moveText(vect,croppedMovement);
    }
    _moved = true;
}

textInfo* TextManager::getTextInfo(){
    return &_mainTextInfo;
}

void TextManager::setUpdate(bool state){
    _needUpdate = state;
}

void TextManager::normalizeText(const PinGUI::Vector2<GUIPos>& normalizationVector){

    for (std::size_t i = 0; i < _TEXTS.size(); i++)
        _TEXTS[i]->normalizeText(normalizationVector);
}

void TextManager::cropText(PinGUI::Rect& cropRect){

    for (std::size_t i = 0; i < _TEXTS.size(); i++){

        if (!_TEXTS[i]->isNetworked())
            CropManager::cropSprite(_TEXTS[i]->getSprite(),cropRect);
    }
}

void TextManager::setFunction(PinGUI::basicPointer f){
    _function = f;
}
