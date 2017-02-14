#ifndef GUIMANAGER_H
#define GUIMANAGER_H

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
#include <algorithm>
#include <typeinfo>

#include "PinGUI/TextManager/TextManager.h"

#include "PinGUI/stuff.h"
#include "PinGUI/GUI_Cursor.h"
#include "PinGUI/GUI_CollisionManager.cpp"
#include "PinGUI/GUI_ColorManager.h"
#include "PinGUI/CameraManager.h"

#include "PinGUI/VBO_Manager.h"

/*** GUI ELEMENTS ***/
#include "PinGUI/GUI_Elements/ClipBoard.h"
#include "PinGUI/GUI_Elements/ArrowBoard.h"
#include "PinGUI/GUI_Elements/VolumeBoard.h"
#include "PinGUI/GUI_Elements/CrossBox.h"
#include "PinGUI/GUI_Elements/ComboBox.h"
#include "PinGUI/GUI_Elements/Image.h"
#include "PinGUI/GUI_Elements/Button.h"

#define BUTTON_TYPES 2

//For allocation of new VBO´s(per object)
#define VBO_ALLOCATION_LIMIT 1000


class GUIManager
{
    private:
        //OpenGL stuff
        VBO_Manager* _vboMANAGER;

        //Vector of vectors for each kind of button type
        std::vector<vboData> _vboDATA;

        //Storage place for clipboards
        std::vector<GUI_Element*> _ELEMENTS;

        //TextManager that belongs to the current GUIManager(GM)
        TextManager* _texter;

        //Pointer to an element which is currently in manipulating mod
        GUI_Element* _manipulatingElement;
        GUI_Element* _collidingElement;

        //Bool for update state
        bool _needUpdate;
        bool _moved;

        //Bool for manipulating mod
        bool _manipulatingMod;

        PinGUI::basicPointer _function;

        /**
            Methods
        **/

        void createVBOStoragePlace();

        void loadVBO();
        void updateVBO();

        //Rendering methods - for each button type
        void renderElements(); //Clipboards are first because sometime i want to put the text over the clipboard
        void renderText();

        //Method for checking the collisions
        void checkCollisions();

    public:
        GUIManager();
        GUIManager(TextManager* texter);
        ~GUIManager();

        //Making methods
        void createClipBoard(int x, int y, clipboard_type type, int maxSize, element_shape shape = ROUNDED);
        void createClipBoard(int x, int y, clipboard_type type, int* var, int maxSize, element_shape shape = ROUNDED);

        void createComboBox(int x, int y, std::vector<std::string> items, int maxNumOfItems);
        void createComboBox(int x, int y, std::vector<std::string> items, int maxSize, int maxNumOfItems);

        void createArrowBoard(int x, int y, int* var, int maxSize, bool clickable = true, int minSize = 0, manipulationState state = HORIZONTAL);

        void createVolumeBoard(int x, int y, bool clickable, int* var, int maxSize);

        void createCheckBox(int x, int y, bool* var);

        void createImage(std::string filePath, int x, int y);
        void createImage(std::string filePath, int x, int y, int width, int height);

        void createButton(int x, int y, std::string name, PinGUI::basicPointer f);
        void createButton(int x, int y, std::string name, PinGUI::basicPointer f, int maxSize);

        void moveGUI(PinGUI::Vector2<GUIPos> vect, bool croppedMovement = false);
        void moveGUITo(PinGUI::Vector2<GUIPos> vect);
        void cropGUI(PinGUI::Rect& rect);

        void putElement(GUI_Element* object);
        void withdrawElement(GUI_Element* object);

        //Rendering method
        void render();

        //Update method
        void update(bool allowCollision = true);

        void checkCrop();
        void doCrop();


        /** GETTERS SETTERS **/
        clipboardData getClipboardData();

        std::vector<GUI_Element*>* getElementVector();
        GLuint* getVAOID();
        TextManager* getTextManager();
        bool* getUpdateBool();
        bool getUpdate();
        std::size_t getGUISize();

        GUI_Element* getGuiElement(int position = 0);
        GUI_Element* getLastGuiElement();
        GUI_Element* getCollidingElement();
        void setUpdate(bool state);

        void setFunction(PinGUI::basicPointer f);

        void normalizeElements(float x, float y);

};

#endif // GUIMANAGER_H
