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

#include "VBO_Manager.h"

VBO_Manager::VBO_Manager(int limit, bool vao):
    _counter(1),
    _vboID(0),
    _vaoID(0)
{
    _limit = limit;
    _staticLIMIT = limit;

    if (vao) createVAO();

    //Need to create the allocation first
    initMemory(_limit);
}

VBO_Manager::VBO_Manager():
    _counter(1),
    _vboID(0),
    _vaoID(0)
{

}

VBO_Manager::~VBO_Manager()
{
    glDeleteBuffers(1,&_vboID);
}

void VBO_Manager::initMemory(const int& limit)
{
    glBindBuffer(GL_ARRAY_BUFFER,_vboID);

    glBufferData(GL_ARRAY_BUFFER,limit*sizeof(vboData),nullptr,GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER,0);
}

bool VBO_Manager::bufferData(int startPos, const std::vector<vboData>& dataVector)
{
    bool tmp = false;

    glBindBuffer(GL_ARRAY_BUFFER,_vboID);
    startPos *= sizeof(vboData);

    //In case of having small memory we need to resize our buffer for desirable amount
    if (!canBuffer(startPos,dataVector.size())){
        addNewMemory();
        tmp = true;
    }

    glBufferSubData(GL_ARRAY_BUFFER,startPos,dataVector.size()*sizeof(vboData),dataVector.data());

    return tmp;
}

void VBO_Manager::addNewMemory(){
    //At first need to make a tmp copy of my current Buffer to be sure that im not losing any of the inserted data
    GLuint tmpVBO = 0;
    glGenBuffers(1,&tmpVBO);
    glBindBuffer(GL_COPY_READ_BUFFER,tmpVBO);

    //Now allocate a memory for the copy
    glBufferData(GL_COPY_READ_BUFFER,(_limit*_counter)*sizeof(vboData),nullptr,GL_STATIC_COPY);

    //Increment my counter
    _counter++;

    //Now resizing the right buffer and preparing it for copying
    glBindBuffer(GL_ARRAY_BUFFER,_vboID);
    glBufferData(GL_ARRAY_BUFFER,(_staticLIMIT*_counter)*sizeof(vboData),nullptr,GL_DYNAMIC_DRAW);

    //Copying
    glCopyBufferSubData(GL_COPY_READ_BUFFER,GL_ARRAY_BUFFER,0,0,(_limit*(_counter-1))*sizeof(vboData));

    glDeleteBuffers(1,&tmpVBO);
    glBindBuffer(GL_COPY_READ_BUFFER,0);
    _limit = (_staticLIMIT*_counter);
}


bool VBO_Manager::canBuffer(int startPos,int num){
    int tmp_size = 0;

    glGetBufferParameteriv(GL_ARRAY_BUFFER,GL_BUFFER_SIZE,&tmp_size);
    tmp_size /= sizeof(vboData);

    if (tmp_size>=startPos+num)
        return true;
    else
        return false;
}

void VBO_Manager::createVAO()
{
    if (_vaoID==0)glGenVertexArrays(1,&_vaoID);
    glBindVertexArray(_vaoID);

    if (_vboID==0) glGenBuffers(1,&_vboID);
    glBindBuffer(GL_ARRAY_BUFFER,_vboID);

    //This is the position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(PinGUI::Vertex),(void*)offsetof((PinGUI::Vertex,position));

    //Color attrib pointer
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,4,GL_UNSIGNED_BYTE,GL_TRUE,sizeof((PinGUI::Vertex),(void*)offsetof((PinGUI::Vertex,color));

    //UV
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,2,GL_FLOAT,GL_TRUE,sizeof((PinGUI::Vertex),(void*)offsetof((PinGUI::Vertex,uv));

    glDisableVertexAttribArray(3);

    glBindBuffer(GL_ARRAY_BUFFER,0);

    glBindVertexArray(0);
}

GLuint* VBO_Manager::getVBO_P()
{
    return &_vboID;
}

GLuint VBO_Manager::getVBO()
{
    return _vboID;
}

GLuint VBO_Manager::getVAO()
{
    return _vaoID;
}

GLuint* VBO_Manager::getVAO_P(){
    return &_vaoID;
}
