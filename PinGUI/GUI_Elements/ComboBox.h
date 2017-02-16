#ifndef COMBOBOX_H
#define COMBOBOX_H

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

#include <boost/bind.hpp>

#include "../GUI_Elements/ClipBoard.h"
#include "../GUI_Elements/VerticalScroller.h"
#include "../GUI_Elements/ComboBoxItem.h"

#define DEFAULT_NUM_OF_COMBO_ITEMS 4
#define DEFAULT_LENGTH_OF_KEYCOMBO_WORD 10

#define POSITION_OF_COMBO_ARROW_X 13

class ComboBox: public ClipBoard
{
    private:

        std::vector<GUI_Element*>* _ELEMENTS;

        //Also scroller
        VerticalScroller* _scroller;

        //Crop area
        GUIRect _cropRect;

        //ITEMS
        std::vector<ComboBoxItem*> _ITEMS;

        //Maximum number of Items(that are allowed without scrolling)
        int _maxNumberOfItems;

        //The main collider for offseting the chosen text
        PinGUI::Rect _offsetCollider;

        //ClipboardData
        clipboardData _data;

        //The main option
        ComboBoxItem* _mainItem;

        bool* _needUpdate;

        PinGUI::comboBoxFuncPointer _func;

        PinGUI::Vector2<GUIPos> _rollbackVect;

        bool _clickable;

        /**
            Private methods
        **/
        void initMainSprites(int& x, int& y, clipboardData& data);

        void loadCropArea(PinGUI::Vector2<GUIPos> vect);

        void updateCropArea(PinGUI::Vector2<GUIPos> vect);

        void findLongestWord(std::vector<std::string>& itemList);

        GUIPos getPosOfNextItem();

        void hideContent();

        void uploadContent();

        void loadScroller();

        void reMoveTabs();

    public:
        ComboBox(int x,
                 int y,
                 std::vector<std::string> itemList,
                 clipboardData data, std::vector<GUI_Element*>* ELEMENTS,
                 int maxNumOfItems,
                 bool* update);

        ComboBox(int x,
                 int y,
                 std::vector<std::string> itemList,
                 clipboardData data, std::vector<GUI_Element*>* ELEMENTS,
                 int maxNumOfItems,
                 bool* update,
                 int maxSize);

        ~ComboBox();

        void initScroller();

        void setFunc(PinGUI::comboBoxFuncPointer func);

        std::vector<std::string> getStringVector();

        void addItem(std::string name);

        void deleteItem(std::string name);

        void clearComboBox();

        void setUnclickable();

        void moveElement(const PinGUI::Vector2<GUIPos>& vect) override;

        void onClick() override;

        bool listenForClick(GUI_Element** manipulatingElement) override;

        void setShow(bool state) override;

        void cropElement(PinGUI::Rect& rect) override;

        elementType getElementType() override;
};

#endif // COMBOBOX_H
