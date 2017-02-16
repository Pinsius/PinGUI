#ifndef PINGUI_RECT_HPP
#define PINGUI_RECT_HPP

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

#include <SDL2/SDL.h>
#include <iostream>

#include "PinGUI_Vector.hpp"

//In case you use also vector objects from other libraries
namespace PinGUI{

    //This class has its own Rectangle class with floats to have better precisions
    class Rect{
    public:
        float x;
        float y;
        int w;
        int h;

        //Default constructor&destructor
        Rect(){
            this->x = 0;
            this->y = 0;
            this->w = 0;
            this->h = 0;
        }
        ~Rect(){};

        Rect(float X, float Y, int W, int H):
            x(X),
            y(Y),
            w(W),
            h(H)
        {
        };

        Rect(const PinGUI::Rect& rect){
            this->x = rect.x;
            this->y = rect.y;
            this->w = rect.w;
            this->h = rect.h;
        }

        //Overloaded operators
        /**
            Vector combination
        */

        Rect& operator=(const PinGUI::Vector2<float>& vect){
            this->x = vect.x;
            this->y = vect.y;

            return *this;
        }

        bool operator!=(const PinGUI::Rect& rect) const{
            if ((this->x != rect.x)||(this->y != rect.y)||(this->w != rect.w)||(this->h != rect.h))
                return true;
            else
                return false;
        }

        //Initializing the rect from the vector
        void initPos(const PinGUI::Vector2<float>& vect){
            this->x = vect.x;
            this->y = vect.y;
        }

        //Initializing the rect from the vector
        void initPos(const PinGUI::Vector2<int>& vect){
            this->x = vect.x;
            this->y = vect.y;
        }
        //Initializing the rect
        void initPos(PinGUI::Rect& rect){
            this->x = rect.x;
            this->y = rect.y;
        }

        //Addin a pingui vector
        void addPos(const PinGUI::Vector2<float>& vect){
            this->x += vect.x;
            this->y += vect.y;
        }

        void normalizePos(const PinGUI::Vector2<float>& vect){
            this->x += vect.x;
            this->y = vect.y - this->y;
        }

        //Addin a pingui vector
        void addPos(const PinGUI::Vector2<int>& vect){
            this->x += vect.x;
            this->y += vect.y;
        }

        void normalizePos(const PinGUI::Vector2<int>& vect){
            this->x += vect.x;
            this->y = vect.y - this->y;
        }

        //Info method (for debugging purposes..)
        void info(){
            std::cout  << "X: " << this->x << " Y: " << this->y << " W: " << this->w << " H: " << this->h << std::endl;
        }

        float getLeftPoint(){
            return this->x;
        }
        float getRightPoint(){
            return this->x + this->w;
        }

        float getTopPoint(){
            return this->y + this->h;
        }

        float getDownPoint(){
            return this->y;
        }

        float getX(){
            return this->x;
        }

        void setX(float newX){
            this->x = newX;
        }

        float getY(){
            return this->y;
        }

        void setY(float newY){
            this->y = newY;
        }

        int getW(){
            return this->w;
        }

        void setW(int newW){
            this->w = newW;
        }

        int getH(){
            return this->w;
        }

        void setH(int newH){
            this->h = newH;
        }

    };

}

class GUIRect{
    public:
        PinGUI::Rect rect;
        PinGUI::Rect realRect;

        GUIRect(){};
        ~GUIRect(){};

        GUIRect(PinGUI::Rect Rect, PinGUI::Vector2<int> vect):
            rect(Rect)
        {
            realRect.initPos(rect);
            realRect.w = vect.x;
            realRect.h = vect.y;
        }

        GUIRect(PinGUI::Rect Rect):
            rect(Rect)
            {
                realRect = rect;
            }

        GUIRect(float x, float y, int w, int h):
            rect(x,y,w,h),
            realRect(rect)
        {

        }

        int getRH(){
            return realRect.y;
        }

        void setRH(int newH){
            realRect.y = newH;
        }

        int getRW(){
            return realRect.x;
        }

        void setRW(int newW){
            realRect.x = newW;
        }

        //Addin a pingui vector
        void addPos(const PinGUI::Vector2<float>& vect){
            rect.addPos(vect);
            realRect.addPos(vect);
        }

        void normalizePos(const PinGUI::Vector2<float>& vect){
            rect.normalizePos(vect);
            realRect.normalizePos(vect);
        }

         //Addin a pingui vector
        void addPos(const PinGUI::Vector2<int>& vect){
            rect.addPos(vect);
            realRect.addPos(vect);
        }

        void normalizePos(const PinGUI::Vector2<int>& vect){
            rect.normalizePos(vect);
            realRect.normalizePos(vect);
        }

        void equalPos(){
            realRect.x = rect.x;
            realRect.y = rect.y;
        }

        bool hasEqualDimensions(PinGUI::Rect rect){

        }


};

#endif // PINGUI_RECT_HPP

