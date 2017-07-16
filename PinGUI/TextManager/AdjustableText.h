#pragma once

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

#include "Text.h"

class AdjustableText:public Text
{
private:
	std::string _realText;

	std::string _fakeText;

	unsigned int _realTextSize;

	unsigned int _maxRealTextSize;

	/*
		Private methods
	*/
	inline unsigned int calculateAfterLength() {
		return unsigned int(_realText.size() - _realTextSize);
	}

	void performAdjust(bool remove);

	void adjustRealText(unsigned int afterLength);

public:
	AdjustableText(std::string Text, PinGUI::Vector2<GUIPos> pos, textInfo* info, unsigned int Size, unsigned int maxSize);
	~AdjustableText();

	void addChar(char* ch, bool change = true) override;

	void removeChar() override;

	void endInputManipulation() override;

	void startInputManipulation() override;

	void setRealTextSize(unsigned int size);

	unsigned int getMaxRealTextSize();
};

