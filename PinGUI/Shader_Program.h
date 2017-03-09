#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

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

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "ErrorManager.h"
#include "stuff.h"
#include "CameraManager.h"

namespace PinGUI{
    class Shader_Program
    {
        private:

            static int _attributes;

            static GLuint _programID;

            static GLuint _vertexShaderID;
            static GLuint _fragmentShaderID;

            static GLint _samplerLocation;
            static GLint _cameraMatrixLocation;


            /**
                Private methods
            **/
            static void compileShader(const std::string& filePath,GLuint id);

        public:

            static void initShaders();

            static void compileShaders(const std::string& vertexShaderFilePath,const std::string& fragmentShaderFilePath);
            static void linkShaders();

            static void addAttribute(const std::string& attributeName);

            static GLuint getUniformLocation(const std::string& uniformName);

            static void use();
            static void unuse();

    };
}


#endif // SHADER_PROGRAM_H
