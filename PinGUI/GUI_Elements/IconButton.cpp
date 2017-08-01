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

IconButton::IconButton(GUIPos x, GUIPos y, SDL_Surface* iconPictureSurface, PinGUI::basicPointer f):
	Button(x, y, f),
	_customCollisionSprite(false),
	_collisionSprite(nullptr)
{
	//Background sprite
	addSprite(x, y, SheetManager::getSurface(BOARD));

	//Now creating the sprite for icon button
	addSprite(x, y, iconPictureSurface);

	getSprite(0)->setAlpha(0);
	getSprite(0)->setColor(150, 150, 200);

	getSprite(0)->setW(getSprite(1)->getW());
	getSprite(0)->setH(getSprite(1)->getH());

	addCollider(getSprite(0)->getCollider());

	getSprite(1)->offsetToRect(*getCollider());
}

//With this constructor its possible to set the size of the icon collider to the selected width and height 
IconButton::IconButton(GUIPos x, GUIPos y, SDL_Surface* iconSurface, float width, float height, PinGUI::basicPointer f) :
	Button(x, y, f),
	_customCollisionSprite(false),
	_collisionSprite(nullptr)
{
	//Background sprite
	addSprite(x,y, SheetManager::getSurface(BOARD));

	//Now creating the sprite for icon button
	addSprite(x, y, iconSurface);

	getSprite(0)->setAlpha(0);
	getSprite(0)->setColor(150, 150, 200);

	getSprite(0)->setW(int(width));
	getSprite(0)->setH(int(height));

	addCollider(getSprite(0)->getCollider());

	getSprite(1)->offsetToRect(*getCollider());
}

//This functions sets the image of the icon to the selected image
void IconButton::setCollisionSprite(SDL_Surface* iconSurface)
{
	if (_collisionSprite)
		_collisionSprite.reset();

	_collisionSprite =  std::make_shared<GUI_Sprite>(_position,iconSurface);

	_collisionSprite->offsetToRect(*getCollider());

	_customCollisionSprite = true;
}

void IconButton::setWritingAvailability(bool state) {

	if (state) {
		getSprite()->setAlpha(255);
	}
	else {
		getSprite()->setAlpha(0);
	}
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

	std::shared_ptr<GUI_Sprite> tmpSprite = _SPRITES[1];

	_SPRITES[1] = _collisionSprite;
	_collisionSprite = tmpSprite;
}

void IconButton::offsetTo(orientation orient, GUIPos distance) {

	for (std::size_t i = 1; i < _SPRITES.size(); i++)
	{
		switch (orient)
		{
			case LEFT: {
				_SPRITES[i]->setX(_COLLIDERS[0].rect.getX() + distance);
				break;
			}
			case RIGHT: {
				_SPRITES[i]->setX(((_COLLIDERS[0].rect.getX() + _COLLIDERS[0].rect.getW()) - _SPRITES[i]->getW()) - distance);
				break;
			}
			default:break;
		}
	}

}