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

#include "CropManager.hpp"

int CropManager::_cropVar = 0;

int CropManager::_cropSize = 0;

PinGUI::Rect CropManager::_lastCropRect(0,0,0,0);

inline bool collideFromLeft(PinGUI::Rect& cropRect, PinGUI::Rect& dstRect){

    if ((dstRect.getLeftPoint() < cropRect.x) && (dstRect.getRightPoint() > cropRect.x))
        return true;
    else
        return false;
}

inline bool collideFromRight(PinGUI::Rect& cropRect, PinGUI::Rect& dstRect){

    if ((dstRect.getLeftPoint() < cropRect.getRightPoint()) && (dstRect.getRightPoint() > cropRect.getRightPoint()))
        return true;
    else
        return false;
}

inline bool collideFromTop(PinGUI::Rect& cropRect, PinGUI::Rect& dstRect){

    if ((dstRect.getDownPoint() < cropRect.getTopPoint()) && (dstRect.getTopPoint() > cropRect.getTopPoint()))
        return true;
    else
        return false;
}

inline bool collideFromBottom(PinGUI::Rect& cropRect, PinGUI::Rect& dstRect){

    if ((dstRect.getDownPoint() < cropRect.getDownPoint()) && (dstRect.getTopPoint() > cropRect.getDownPoint()))
        return true;
    else
        return false;
}

inline bool isIn(PinGUI::Rect& cropRect, PinGUI::Rect dstRect){

    if (GUI_CollisionManager::isColliding(cropRect,dstRect))
        return true;
    else
        return false;
}


bool CropManager::doCropping(PinGUI::Rect& cropRect, GUIRect& dstRect){


    if (_lastCropRect != cropRect)
        _lastCropRect = cropRect;

    cropHorizontally(cropRect,dstRect);
    cropVertically(cropRect,dstRect);
}

//Normal checking
void CropManager::repairRect(int& var, const int& maxVar){
    if (var<1)
        var = 0;
    else if (var>maxVar)
        var = maxVar;
}

void CropManager::finishCropping(int& targetVar, int& maxVar){
    targetVar = maxVar - _cropVar ;

    repairRect(targetVar,maxVar);
}

void CropManager::cropHorizontally(PinGUI::Rect& cropRect, GUIRect& dstRect){

    bool alreadyCropped = false;

    _cropVar = 0;

    //First need to know how to crop the rect
    if (collideFromLeft(cropRect,dstRect.realRect)){

        _cropVar += cropRect.x - dstRect.realRect.getLeftPoint() + NORMALIZE_CONSTANT;

        //In this case i have to move the rect X position
        dstRect.rect.x = cropRect.x - NORMALIZE_CONSTANT;

        alreadyCropped = true;
    } else {

        if (dstRect.rect.w != dstRect.realRect.w){

            dstRect.rect.x = dstRect.realRect.x;
            dstRect.rect.w = dstRect.realRect.w;
        }
    }

    if (collideFromRight(cropRect,dstRect.realRect)){

        _cropVar +=  dstRect.realRect.getRightPoint() - cropRect.getRightPoint() - NORMALIZE_CONSTANT ;

        alreadyCropped = true;
    }

    if (alreadyCropped)
        finishCropping(dstRect.rect.w,dstRect.realRect.w);

}


void CropManager::cropVertically(PinGUI::Rect& cropRect, GUIRect& dstRect){

    bool alreadyCropped = false;

    _cropVar = 0;

    if (collideFromBottom(cropRect,dstRect.realRect)){

        _cropVar += cropRect.y - dstRect.realRect.y;

        //In this case i have to move the rect Y position
        dstRect.rect.y = cropRect.y;

        alreadyCropped = true;
    }

    if (collideFromTop(cropRect,dstRect.realRect)){

        _cropVar += dstRect.realRect.getTopPoint() - cropRect.getTopPoint();

        alreadyCropped = true;
    }

    if (!alreadyCropped && ((dstRect.rect.y!= dstRect.realRect.y)||(dstRect.rect.h!= dstRect.realRect.h))){


        dstRect.rect.y = dstRect.realRect.y;
        dstRect.rect.h = dstRect.realRect.h;
    }

    if (alreadyCropped){

        finishCropping(dstRect.rect.h,dstRect.realRect.h);

    }

}

void CropManager::cropRect(PinGUI::Rect cropRect, GUIRect& dstRect){

    if (isIn(cropRect,dstRect.realRect)){

        doCropping(cropRect,dstRect);
    }
}

void CropManager::cropSprite(GUI_Sprite* sprite, PinGUI::Rect cropRect){

    if (isIn(cropRect,sprite->getGUIRect().realRect)){

        cropSpriteVertically(sprite,cropRect) ;
        cropSpriteHorizontally(sprite,cropRect);
    } else {
        sprite->setH(0);
        sprite->setW(0);
    }
}

void CropManager::cropSpriteVertically(GUI_Sprite*& sprite, PinGUI::Rect& cropRect){

    PinGUI::Vector2<float> percentage(0.0f,0.0f);
    GUIRect rect = sprite->getGUIRect();
    int cropSize = 0;
    bool alreadyCropped = false;

    if (collideFromTop(cropRect,rect.realRect) ){

        _cropVar = (rect.realRect.getTopPoint() - cropRect.getTopPoint()) ;

        percentage.x = 1.0f - (static_cast<float>(_cropVar) / static_cast<float>(rect.realRect.h));

        changeUV(UP, sprite->getVBOData(), percentage);

        cropSize -= _cropVar;

    } else if (sprite->getGUIRect().rect.h != rect.realRect.h){

        sprite->getGUIRect_P()->rect.h = sprite->getGUIRect_P()->realRect.h;
        sprite->getGUIRect_P()->rect.y = sprite->getGUIRect_P()->realRect.y;
        sprite->createVBO(V);
    }

    if (collideFromBottom(cropRect,rect.realRect) ){

        _cropVar =  rect.realRect.getTopPoint() - cropRect.y;

        cropSize -= cropRect.y - rect.realRect.getDownPoint();

        percentage.x = 1.0f - (static_cast<float>(_cropVar) / static_cast<float>(rect.realRect.h));

        changeUV(DOWN, sprite->getVBOData(), percentage);

        sprite->getGUIRect_P()->rect.y = cropRect.y;

    } else if (sprite->getGUIRect().rect.h != rect.realRect.h){

        sprite->setH(rect.realRect.h);
        percentage.x = 1.0f;
        changeUV(UP, sprite->getVBOData(), percentage);
        sprite->updatePositions();
    }


    if (cropSize!=0){

        sprite->decH(cropSize);
    }
}

void CropManager::cropSpriteHorizontally(GUI_Sprite*& sprite, PinGUI::Rect& cropRect){

    PinGUI::Vector2<float> percentage(0.0f,0.0f);
    GUIRect rect = sprite->getGUIRect();
    int cropSize = 0;
    bool cropLeft = false;
    bool cropRight = false;
    float normalizeDistance = 0.0f;

    if (collideFromLeft(cropRect,rect.realRect)){

        _cropVar = (cropRect.getLeftPoint() - rect.realRect.getLeftPoint()) + NORMALIZE_CONSTANT;

        percentage.x = static_cast<float>(_cropVar) / static_cast<float>(rect.realRect.w);

        changeUV(LEFT, sprite->getVBOData(), percentage);

        sprite->getGUIRect_P()->rect.x = cropRect.x ;

        cropSize -= _cropVar;

        cropLeft = true;

    } else {

        if (sprite->getGUIRect_P()->rect.w != rect.realRect.w){

            sprite->getGUIRect_P()->rect.w = sprite->getGUIRect_P()->realRect.w;
            sprite->getGUIRect_P()->rect.x = sprite->getGUIRect_P()->realRect.x;
            sprite->createVBO(U);
        }

    }

    if (collideFromRight(cropRect,rect.realRect)){


        _cropVar = static_cast<int>(rect.realRect.getRightPoint() - cropRect.getRightPoint());

        percentage.x = 1.0f - (static_cast<float>(_cropVar) / static_cast<float>(rect.realRect.w));

        changeUV(RIGHT, sprite->getVBOData(), percentage);

        cropSize -= _cropVar;

        cropRight = true;

    } else if (cropSize==0){

        sprite->setW(rect.realRect.w);
        percentage.x = 1.0f;
        changeUV(RIGHT, sprite->getVBOData(), percentage);
        sprite->updatePositions();
    }

    if (cropSize!=0){

        sprite->decW(cropSize);

        if (cropLeft && cropRight){

            sprite->incW(1);
        }
    }

}

void CropManager::changeUV(orientation orient, vboData* dataPointer, PinGUI::Vector2<float> percentage){

    /**
        1 - Top left
        2,3 - Bottom Left
        4 - Bottom right
        0,5 - Top right

    **/

    switch(orient){

        case LEFT : {

            dataPointer->vertices[1].setU(percentage.x);
            dataPointer->vertices[2].setU(percentage.x);
            dataPointer->vertices[3].setU(percentage.x);

            break;
        }

        case RIGHT : {

            dataPointer->vertices[0].setU(percentage.x);
            dataPointer->vertices[4].setU(percentage.x);
            dataPointer->vertices[5].setU(percentage.x);

            break;
        }

        case UP : {

            dataPointer->vertices[0].setV(percentage.x);
            dataPointer->vertices[1].setV(percentage.x);
            dataPointer->vertices[5].setV(percentage.x);

            break;
        }

        case DOWN : {

            dataPointer->vertices[2].setV(percentage.x);
            dataPointer->vertices[3].setV(percentage.x);
            dataPointer->vertices[4].setV(percentage.x);

            break;
        }
    }
}
