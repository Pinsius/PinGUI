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

#include "ComboBoxItem.h"



ComboBoxItem::ComboBoxItem(PinGUI::Vector2<GUIPos> position,
                           std::string itemText,
                           ComboBoxItem** mainComboBoxItem,
                           PinGUI::basicPointer functionP,
                           int maxSize,
                           clipboardData& data):
    _function(functionP),
    _mainComboBoxItem(mainComboBoxItem),
    _option(0)
{

    init(position,maxSize,data,NORMAL,RECTANGLED);

    _maxSize = maxSize;
    _position = position;

    //ComboBox owns full control of this element (be careful)
    _networkedElement = true;

    setClipboardText(itemText);

    setShow(false);
}

ComboBoxItem::~ComboBoxItem()
{
    //dtor
}

void ComboBoxItem::onClick(){

    //Tmp disabling it
    Input_Manager::setTarget(false);


    if (*_mainComboBoxItem)
        (*_mainComboBoxItem)->setCollidable(true);

    *_mainComboBoxItem = this;

    this->setCollidable(false);

    _function.exec();

    Input_Manager::setTarget(true);

}

bool ComboBoxItem::listenForClick(GUI_Element** manipulatingElement){
    GUI_Element::listenForClick(manipulatingElement);
}

void ComboBoxItem::cropElement(PinGUI::Rect& rect){

    ClipBoard::cropElement(rect);
}

void ComboBoxItem::setOption(int opt){
    _option = opt;
}

int ComboBoxItem::getOption(void){
    return _option;
}
