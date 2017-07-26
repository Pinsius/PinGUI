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

#include "WindowButton.h"

WindowButton::WindowButton(GUIPos x, GUIPos y, std::string name, clipboardData data):
    Button(x,y,name,data)
{

}

WindowButton::WindowButton(GUIPos x, GUIPos y, std::string name, clipboardData data, std::shared_ptr<Window> target):
    Button(x,y,name,data),
	_target(target)
{
    //ctor
}

WindowButton::WindowButton(GUIPos x, GUIPos y, std::string name, clipboardData data, std::shared_ptr<Window> target, int maxSize):
    Button(x,y,name,data,maxSize),
	_target(target)
{

}

WindowButton::~WindowButton()
{
}

void WindowButton::onClick(){

	if (!_target->getShow())
	{
        _target->setShow(true);
	}
    else
        _target->setShow(false);
}

void WindowButton::setWindowTarget(std::shared_ptr<Window> target){

    _target = target;
}
