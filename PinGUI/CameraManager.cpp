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

#include "CameraManager.h"

float* CameraManager::_staticCamera = nullptr;

GLint CameraManager::_matrixLocation;

glm::mat4 CameraManager::_staticCameraMatrix;

int CameraManager::_screenWidth;

int CameraManager::_screenHeight;

glm::mat4 CameraManager::_orthoMatrix;

void CameraManager::init(int screenWidth, int screenHeight){

    _screenWidth = screenWidth;
    _screenHeight = screenHeight;

    PinGUI::Vector2<GUIPos> _position(screenWidth/2,screenHeight/2);

    _orthoMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight);

    glm::vec3 translate(-_position.x + _screenWidth / 2, -_position.y + _screenHeight / 2, 0.0f);

    _staticCameraMatrix = glm::translate(_orthoMatrix,translate);
    
    _staticCamera = &(_staticCameraMatrix[0][0]);
}

glm::mat4 CameraManager::getCameraMatrix(){
    return _staticCameraMatrix;
}
float* CameraManager::getCamera(){
    return _staticCamera;
}

void CameraManager::setMatrixLocation(GLint location){
    _matrixLocation = location;
}

GLint CameraManager::getMatrixLocation(){
    return _matrixLocation;
}
