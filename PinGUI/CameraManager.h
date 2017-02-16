#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

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

/**
    GLM is included in here
**/
#include <glm/gtc/matrix_transform.hpp>

#include "GUI_Sprite.h"

class CameraManager
{
    private:
        static float* _staticCamera;

        static GLint _matrixLocation;

        static int _screenWidth;

        static int _screenHeight;

        /**
        For GUI elements
        static and dynamic matrices.
        **/
        static glm::mat4 _staticCameraMatrix;

        //Orthomatrix
        static glm::mat4 _orthoMatrix;

    public:

        //sets up the orthographic matrix and screen dimensions
        static void init(int screenWidth, int screenHeight);

        static float* getCamera();

        static glm::mat4 getCameraMatrix();

        static void setMatrixLocation(GLint location);
        static GLint getMatrixLocation();
};

#endif // CAMERAMANAGER_H
