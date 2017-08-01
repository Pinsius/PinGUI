#ifndef GUI_ELEMENT_H
#define GUI_ELEMENT_H

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

#include <SDL.h>
#include <vector>
#include <functional>
#include <memory>

#include "GUI_Sprite.h"
#include "GUI_Cursor.h"
#include "GUI_CollisionManager.cpp"
#include "GUI_ColorManager.h"
#include "Input_Manager.h"
#include "stuff.h"
#include "SheetManager.h"
#include "PinGUI_Rect.hpp"
#include "clFunction.hpp"
#include "CropManager.hpp"

class GUIManager;

enum elementType{
    UNDEFINED,
    CLIPBOARD,
    ARROWBOX,
    VOLUMEBOARD,
    CROSSBOX,
    WINDOW,
    WINDOWMOVER,
    WINDOWTAB,
    WINDOWSCROLLER,
    WINDOWARROW,
    WINDOWEXIT,
    HORIZONTAL_SCROLLER,
    VERTICAL_SCROLLER,
    COMBOBOX,
    COMBOBOX_ITEM
};

enum CHANGER{
    MINUS,
    PLUS
};

class GUI_Element : public std::enable_shared_from_this<GUI_Element>
{
	protected:
		PinGUI::Vector2<GUIPos> _position;

		std::vector<std::shared_ptr<GUI_Sprite>> _SPRITES;

		std::vector<GUIRect> _COLLIDERS;

		bool _aimON;

		bool _collidable;

		bool _show;

		bool _exist;

		//It means element is a subElement to another element
		bool _networkedElement;

		bool _allowCropp;

		/**
			Private methods
		**/
		void initPosition(const PinGUI::Rect& rect);

		void initPosition(GUIPos x, GUIPos y);

    public:

        typedef GUI_Element*& manip_Element;

        GUI_Element();
        virtual ~GUI_Element();

        void addSprite(PinGUI::Rect rect,SDL_Surface* source,SDL_Color color);
        void addSprite(PinGUI::Rect rect,SDL_Surface* source);
        void addSprite(GUIPos x, GUIPos y, SDL_Surface* source);

		void changeSprite(GUIPos x, GUIPos y, SDL_Surface* source, std::size_t pos);

        void addCollider(GUIPos x, GUIPos y, int w, int h);
        void addCollider(PinGUI::Rect tmpRect);

        void deleteSprite(int pos);
        void deleteCollider(int pos);

        std::size_t getCollidersCount();

		virtual bool cursorOn();

        //Virtual methods - every element can modify its own behavior via these functions
        virtual void turnOnAim();

        virtual void turnOffAim();

        virtual bool collide(bool& needUpdate, manip_Element manipulatingElement);

        virtual void manipulatingMod(manip_Element manipulatingElement){};

        virtual void endManipulatingMod(manip_Element manipulatingElement);

        virtual bool listenForClick(manip_Element manipulatingElement);

        virtual void onClick() {};

        virtual void onAim();

        virtual void onEndAim(){};

        virtual void draw(int& pos);

        virtual void update(){};

		virtual bool changed() { return false;}

        virtual void info();

        virtual elementType getElementType();

        virtual void normalizeElement(const PinGUI::Vector2<GUIPos>& vect);

        virtual void setShow(bool state);

        virtual void moveElement(const PinGUI::Vector2<GUIPos>& vect);

        virtual void moveTo(PinGUI::Vector2<GUIPos> vect);

        virtual void cropElement(PinGUI::Rect& rect);

        virtual void doAdditionalFunc(){};

        virtual void setWritingAvailability(bool state){};

        virtual void setAllowCrop(bool state);

        virtual void putElementToManager(std::shared_ptr<GUIManager> m);

		virtual void setAlpha(Uint8 a);

        bool isAllowedCrop();

        //Normal methods
        GLuint getTexture(int pos = 0);

        vboData* getVBOData(int pos = 0);

        PinGUI::Rect* getCollider(int pos = 0);

        GUIRect* getGUICollider(int pos = 0);

        void setCollider(PinGUI::Rect rect,int pos = 0);

        void setCollidable(bool col){_collidable = col;}

        bool getCollidable();

        /// By default it returns first sprite, if you put -1 here, it will return the back of the container
        std::shared_ptr<GUI_Sprite> getSprite(unsigned int pos = 0);

        void loadData(std::vector<vboData>* vboData);

        void moveCollider(GUIRect& rect,const PinGUI::Vector2<GUIPos>& vect);

        void moveCollider(PinGUI::Rect& rect,const PinGUI::Vector2<GUIPos>& vect);


        bool getShow();

        float getX();

        float getY();

        void setX(float x);

        void setY(float y);

        void setNetworking(bool state);

        bool getNetworking();

        void setExist(bool state);

        bool exist();

        float getTopPoint(int pos = 0);

        PinGUI::Vector2<GUIPos> getPositionVector();

        PinGUI::Vector2<GUIPos>* getPositionVector_P();

        bool isAiming();

        void setAim(bool state);
};

#endif // GUI_ELEMENT_H
