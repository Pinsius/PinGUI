#ifndef CLIPBOARD_H
#define CLIPBOARD_H

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


#include "../TextManager/TextStorage.h"
#include "../GUI_Element.h"
#include "../stuff.h"

#define CLIPBOARD_WIDTH_OFFSET 6
#define CLIPBOARD_HEIGHT_OFFSET 2

#define CLIPBOARD_HEIGHT 5
#define WIDTH_PER_CHAR 5
#define WIDTH_PER_DIGIT 4

#define CLIPBOARD_COLLIDER_X -1
#define CLIPBOARD_COLLIDER_Y 0
#define CLIPBOARD_COLLIDER_W 2
#define CLIPBOARD_COLLIDER_H 1

#define CLIPBOARD_RECTANGLE_COLLIDER

struct clipboardData{
    TextManager* texter;
};

class ClipBoard: public GUI_Element
{
    protected:
        //Type of clipboard
        clipboard_type _type;

        //Max int value
        int _maxValue;

        //Max size of chars (or ints if its INT only clipboard)
        int _maxSize;

        //Text storage unit
        TextStorage* _textStorage;

        //This indicates if i have rounded or rectangle shape (important for collisions)
        element_shape _shape;

        /**
            Private methods
        **/
        void setMaxSize(int& maxSize);
        void calculateMaxSize();

        PinGUI::Rect getSpriteRect(const GUIPos& tmp_width, const GUIPos& tmp_height, const PinGUI::Vector2<GUIPos> position);

        //Changing the sprite color to see if i have collision or not
        void manipulatingMod(GUI_Element** manipulatingElement);

        void setWritingAvailability(bool state);

        void writingMod();

        void initClipBoard(int& maxSize, clipboardData& data, PinGUI::Vector2<GUIPos>& position);
        void initText();
        void initText(int* var);

        void fakeInputText(int& width, int& height, const clipboardData& data);

    public:

        ClipBoard();
        ClipBoard(PinGUI::Vector2<GUIPos> position, int maxSize, clipboard_type type, clipboardData data, element_shape shape = ROUNDED);
        ClipBoard(PinGUI::Vector2<GUIPos> position, int maxSize, clipboard_type type, clipboardData data, int* var, element_shape shape = ROUNDED);
        void init(PinGUI::Vector2<GUIPos> position, int maxSize, clipboardData data, clipboard_type type = NORMAL, element_shape shape = ROUNDED);

        void onClick() override;
        void info() override;
        void setShow(bool state) override;

        ~ClipBoard();

        TextStorage* getStorage(){return _textStorage;}

        void normalizeElement(const PinGUI::Vector2<GUIPos>& vect) override;
        bool listenForClick(GUI_Element** manipulatingElement) override;
        void moveElement(const PinGUI::Vector2<GUIPos>& vect) override;
        void cropElement(PinGUI::Rect& rect) override;

        void setClipboardText(std::string text);
        void setClipboardText(std::string text, PinGUI::Rect collider);

        bool changed();

};

#endif // CLIPBOARD_H
