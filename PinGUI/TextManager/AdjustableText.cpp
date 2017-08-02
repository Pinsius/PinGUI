#include "AdjustableText.h"

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

AdjustableText::AdjustableText(std::string Text, PinGUI::Vector2<GUIPos> pos, textInfo* info, unsigned int Size, unsigned int maxSize):
	Text(Text,pos,info),
	_realTextSize(Size),
	_realText(Text),
	_fakeText(Text),
	_maxRealTextSize(maxSize)
{
}

AdjustableText::~AdjustableText()
{
}

void AdjustableText::addChar(char* ch, bool change) {

	//I have to perform the text checking because the input manager can resolve only the checking for the actual display text
	if (_realText.size() + 1 <= _maxRealTextSize) {

		//Perform normal text addition
		Text::addChar(ch, change);

		//Add the char to the realText
		_realText += *ch;

		//Calling the adjust function
		performAdjust(false);
	}


}

void AdjustableText::performAdjust(bool remove) {

	if (!remove) {

		//Check whether its longer than expected size or not
		if (_realText.size() > _realTextSize)
			adjustRealText(calculateAfterLength());
	}
	else {

		//Adjust the text even without checking
		adjustRealText(calculateAfterLength());
	}
}

void AdjustableText::adjustRealText(unsigned int afterLength) {


	//Substring the realText so it fits to our length
	_fakeText = _realText.substr(afterLength, _realTextSize);

	//Update the displayed part
	text = _fakeText;

	//Set the changed flag to true to alert the textmanager about change
	changed = true;
}

void AdjustableText::endInputManipulation() {
	
	if (_realText.size() > _realTextSize) {

		_fakeText = text;

		text = _realText.substr(0, _realTextSize);

		addDots();

		changed = true;
	}
}

void AdjustableText::addDots()
{
	for (std::size_t i = 0; i < 3; i++)
		text[text.size() - 1 - i] = '.';
}

void AdjustableText::startInputManipulation() {

	if (_realText.size() > _realTextSize) {

		text = _fakeText;

		changed = true;
	}
}

void AdjustableText::removeChar() {

	//Check if its necessary to adjust the text
	if (_realText.size() <= _realTextSize) {

		//If not perform normal removal
		Text::removeChar();

		//Save also new realText
		_realText = text;
	}
	else {

		//Remove last char
		_realText.pop_back();

		//Call the adjust function
		performAdjust(true);
	}
}

void AdjustableText::setRealTextSize(unsigned int size) {
	_realTextSize = size;
}

unsigned int AdjustableText::getMaxRealTextSize() {
	return _maxRealTextSize;
}