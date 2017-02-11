#ifndef VBO_MANAGER_H
#define VBO_MANAGER_H

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

#include <GL/glew.h>
#include <vector>
#include <iostream>

#include "PinGUI/stuff.h"

class VBO_Manager
{
    private:
        int _counter;
        int _limit;
        int _staticLIMIT;

        GLuint _vboID;
        GLuint _vaoID;

        //Creation of VBO memory
        void initMemory(const int& limit);

        bool canBuffer(int startPos,int num);

        void addNewMemory();

    public:
        VBO_Manager(int limit, bool vao = true);
        VBO_Manager();
        ~VBO_Manager();

        //Buffering the data
        bool bufferData(int startPos, const std::vector<vboData>& dataVector);

        //Creation of VAOs
        void createVAO();
        GLuint createVAO(GLuint* vboID);

        GLuint* getVBO_P();
        GLuint getVBO();
        GLuint getVAO();
        GLuint* getVAO_P();


};

#endif // VBO_MANAGER_H
