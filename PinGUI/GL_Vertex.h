#ifndef GL_VERTEX_H
#define GL_VERTEX_H

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

namespace PinGUI{
    
    class VertexColor{
        public:
            GLubyte r;
            GLubyte g;
            GLubyte b;
            GLubyte a;

            VertexColor();
            VertexColor(GLubyte R,GLubyte G, GLubyte B, GLubyte A):
                r(R),
                g(G),
                b(B),
                a(A){
                };
            void setColor(GLubyte R,GLubyte G, GLubyte B, GLubyte A)
            {
                r = R;
                g = G;
                b = B;
                a = A;
            };
    };



    class VertexPosition{
        public:
            float x;
            float y;
            VertexPosition();
            VertexPosition(int X, int Y):
                x(X),
                y(Y){
                };

    };

    class VertexUV{
        public:
            float u;
            float v;
            VertexUV();
            VertexUV(float U, float V):
                u(U),
                v(V){
                };
    };


    class Vertex{
        public:
            VertexPosition position;
            VertexColor color;
            VertexUV uv;

            Vertex();
            Vertex(VertexColor Color, VertexPosition Position, VertexUV UV):
                color(Color),
                position(Position),
                uv(UV)
                {};
            void setPosition(float X, float Y);
            void setColor(GLubyte R,GLubyte G, GLubyte B, GLubyte A);
            void setUV(float U, float V);
            void addUV(float U, float V);
            void setU(float U);
            void setV(float V);
    };

}


#endif // GL_VERTEX_H

