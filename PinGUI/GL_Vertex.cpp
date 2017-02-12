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

#include "PinGUI/GL_Vertex.h"
namespace PinGUI{
    VertexColor::VertexColor(){

    }


    VertexPosition::VertexPosition(){

    }


    VertexUV::VertexUV(){

    }

    Vertex::Vertex(){

    }

    void Vertex::setPosition(float X, float Y){
        position.x = X;
        position.y = Y;
    }

    void Vertex::setColor(GLubyte R,GLubyte G, GLubyte B, GLubyte A){
        color.r = R;
        color.g = G;
        color.b = B;
        color.a = A;
    }

    void Vertex::setUV(float U, float V){
        uv.u = U;
        uv.v = V;
    }

    void Vertex::addUV(float U, float V){
        uv.u += U;
        uv.v += V;
    }

    void Vertex::setU(float U){
        uv.u = U;
    }

    void Vertex::setV(float V){
        uv.v = V;
    }
    
}
