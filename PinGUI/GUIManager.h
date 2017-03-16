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

#include "TextManager/TextManager.h"
#include "stuff.h"
#include "GUI_Cursor.h"
#include "GUI_CollisionManager.cpp"
#include "GUI_ColorManager.h"
#include "CameraManager.h"
#include "VBO_Manager.h"
#include <memory>

/*** GUI ELEMENTS ***/
#include "GUI_Elements/ClipBoard.h"
#include "GUI_Elements/ArrowBoard.h"
#include "GUI_Elements/VolumeBoard.h"
#include "GUI_Elements/CrossBox.h"
#include "GUI_Elements/ComboBox.h"
#include "GUI_Elements/Image.h"
#include "GUI_Elements/Button.h"

#define BUTTON_TYPES 2

//For allocation of new VBO´s
#define VBO_ALLOCATION_LIMIT 1000


class GUIManager
{
    private:
        //OpenGL stuff
        std::unique_ptr<VBO_Manager> _vboMANAGER;

        //Vector of vectors for each kind of button type
        std::vector<vboData> _vboDATA;

        //Storage place for clipboards
        std::vector<std::shared_ptr<GUI_Element>> _ELEMENTS;

        //TextManager that belongs to the current GUIManager(GM)
        std::shared_ptr<TextManager> _texter;

        //Pointer to an element which is currently in manipulating mod
        GUI_Element* _manipulatingElement;

        std::shared_ptr<GUI_Element> _collidingElement;

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
        GUIManager(std::shared_ptr<TextManager> texter);
        ~GUIManager();

        //Making methods
        void createClipBoard(int x, int y, clipboard_type type, int maxSize, element_shape shape = ROUNDED);
        void createClipBoard(int x, int y, clipboard_type type, int* var, int maxSize, element_shape shape = ROUNDED);

        void createComboBox(int x, int y, std::vector<std::string> items, int maxNumOfItems);
        void createComboBox(int x, int y, std::vector<std::string> items, int maxSize, int maxNumOfItems);

        void createArrowBoard(int x, int y, int* var, int maxSize, bool clickable = true, int minSize = 0, PinGUI::manipulationState state = PinGUI::HORIZONTAL);

        void createVolumeBoard(int x, int y, bool clickable, int* var, int maxSize);

        void createCheckBox(int x, int y, bool* var);

        void createImage(std::string filePath, int x, int y);
        void createImage(std::string filePath, int x, int y, int width, int height);

        void createButton(int x, int y, std::string name, PinGUI::basicPointer f);
        void createButton(int x, int y, std::string name, PinGUI::basicPointer f, int maxSize);

        void moveGUI(PinGUI::Vector2<GUIPos> vect, bool croppedMovement = false);
        void moveGUITo(PinGUI::Vector2<GUIPos> vect);
        void cropGUI(PinGUI::Rect& rect);

        void putElement(std::shared_ptr<GUI_Element> object);
        void putElementAtStart(std::shared_ptr<GUI_Element> object);
        void withdrawElement(std::shared_ptr<GUI_Element> object);

        //Rendering method
        void render();

        //Update method
        void update(bool allowCollision = true);

        void checkCrop();
        void doCrop();

        /** GETTERS SETTERS **/
        clipboardData getClipboardData();

        std::vector<std::shared_ptr<GUI_Element>>* getElementVector();

        std::shared_ptr<TextManager> getTextManager();

        bool* getUpdateBool();

        bool getUpdate();

        std::size_t getGUISize();

        std::shared_ptr<GUI_Element> getGuiElement(int position = 0);

        std::shared_ptr<GUI_Element> getLastGuiElement();

        std::shared_ptr<GUI_Element> getCollidingElement();

        void setUpdate(bool state);

        void setFunction(PinGUI::basicPointer f);

        void normalizeElements(float x, float y);

};

#endif // GUIMANAGER_H
