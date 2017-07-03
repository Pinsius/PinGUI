#ifndef PINGUI_VECTOR_HPP
#define PINGUI_VECTOR_HPP

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

#include <iostream>

//In case you use also vector objects from other libraries
namespace PinGUI{

    template <class dataType> class Vector2{
        public :
            //Default variables, x and y
            dataType x;
            dataType y;

            //Default constructor and destructor
            // 0.0 default positions to avoid some problems with random allocations
            Vector2(){
                this->x = 0;
                this->y = 0;
            };
            ~Vector2(){};

            //Constructor for setting the types at creation
            Vector2(dataType X, dataType Y):
            x(X),
            y(Y)
            {
            }

            //Overloaded operator =
            Vector2<dataType>& operator=(const Vector2<dataType>& sourceVect){
                this->x = sourceVect.x;
                this->y = sourceVect.y;

                return *this;
            }

            //Overloaded operator * ( for example : for timestep use)
            Vector2<dataType>& operator*(const float& num){
                this->x *= num;
                this->y *= num;
                return *this;
            }

            //Overloaded operator +=
            Vector2<dataType>& operator+=(const Vector2<dataType>& sourceVect){
                this->x += sourceVect.x;
                this->y += sourceVect.y;

                return *this;
            }

            Vector2<dataType>& operator*=(const Vector2<dataType>& sourceVect){
                this->x *= sourceVect.x;
                this->y *= sourceVect.y;

                return *this;
            }

            Vector2<dataType>& operator-=(const Vector2<dataType>& sourceVect){
                this->x -= sourceVect.x;
                this->y -= sourceVect.y;

                return *this;
            }

             //Overloaded operator >=
            bool operator>=(const Vector2<dataType>& sourceVect){

                if (this->x >= sourceVect.x && this->y>= sourceVect.y) return true;
                return false;
            }


            //Operators  == and !=
            bool operator==(const Vector2<dataType>& sourceVect){
                if (this->x==sourceVect.x && this->y==sourceVect.y) return true;
                return false;
            }

            bool operator!=(const Vector2<dataType>& sourceVect){
                if (this->x!=sourceVect.x || this->y!=sourceVect.y) return true;
                return false;
            }

            void clearVector(){
                this->x = 0;
                this->y = 0;
            }

            void info(){
                std::cout << "Vector info: X: " << this->x << " Y: " << this->y << std::endl;
            }
    };
}

#endif // PINGUI_VECTOR_HPP
