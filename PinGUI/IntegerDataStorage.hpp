#ifndef INTEGERDATASTORAGE_HPP
#define INTEGERDATASTORAGE_HPP

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

class IntegerDataStorage
{
    private:
        int* _var;
        int _last_var;

    public:
        IntegerDataStorage():
            _var(nullptr),
            _last_var(0)
        {
        }

        IntegerDataStorage(int* var):
            _var(var),
            _last_var(*var)
        {
        }

        ~IntegerDataStorage(){};

        void init(int* var){
            _var = var;
            _last_var = *var;
        }

        void equalVar(){

            _last_var = *_var;
        }

        bool changed(){

            if (_last_var != *_var){

                _last_var = *_var;
                return true;

            } return false;
        }

        int getVar(){
            return *_var;
        }

        int getLastVar(){
            return _last_var;
        }

        int* getVar_P(){
            return _var;
        }
};

#endif // INTEGERDATASTORAGE_HPP
