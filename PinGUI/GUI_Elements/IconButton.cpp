#include "IconButton.h"

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

IconButton::IconButton()
{
}


IconButton::~IconButton()
{
}

//Creating the icon with its positions, filePath to its icon picture and a pointer to a void function
IconButton::IconButton(GUIPos x, GUIPos y, std::string iconPicturePath, PinGUI::basicPointer f):
	Button(x,y,f),
	_customCollisionSprite(false),
	_collisionSprite(nullptr)
{
	addSprite(x, y, SheetManager::loadCustomSurface(iconPicturePath));
	addCollider(x, y, _SPRITES.back()->getW(), _SPRITES.back()->getH());

	//_collidable = false;
}

//With this constructor its possible to set the size of the icon collider to the selected width and height 
IconButton::IconButton(GUIPos x, GUIPos y, std::string iconPicturePath, float width, float height, PinGUI::basicPointer f) :
	Button(x, y, f),
	_customCollisionSprite(false),
	_collisionSprite(nullptr)
{
	addSprite(x, y, SheetManager::loadCustomSurface(iconPicturePath));
	addCollider(x, y, width, height);
}

//This functions sets the image of the icon to the selected image
void IconButton::setCollisionSprite(std::string iconPicturePath)
{

	if (_collisionSprite)
		_collisionSprite.reset();

	_collisionSprite =  std::make_shared<GUI_Sprite>(_position,SheetManager::loadCustomSurface(iconPicturePath));
	_customCollisionSprite = true;
}

void IconButton::setWritingAvailability(bool state) {

	if (!_customCollisionSprite)
		ClipBoard::setWritingAvailability(state);

}

void IconButton::turnOffAim() {

	if (_customCollisionSprite)
		rotateSprites();

	GUI_Element::turnOffAim();
}

void IconButton::turnOnAim() {

	if (_customCollisionSprite)
		rotateSprites();

	GUI_Element::turnOnAim();
}

void IconButton::rotateSprites() {

	std::shared_ptr<GUI_Sprite> tmpSprite = _SPRITES[0];

	_SPRITES[0] = _collisionSprite;
	_collisionSprite = tmpSprite;
}