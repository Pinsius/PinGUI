#ifndef WINDOW_H
#define WINDOW_H

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

#include <vector>
#include <string>
#include <functional>
#include <boost/bind.hpp>

#include "../GUI_Elements/WindowTab.h"
#include "../stuff.h"
#include "../PinGUI_Vector.hpp"
#include "../PinGUI_Rect.hpp"
#include "../GUI_Elements/WindowMover.h"
#include "../GUI_Elements/WindowExit.h"
#include "../GUI_Elements/Window_Arrow.h"
#include "../GUI_Elements/HorizontalScroller.h"
#include "../GUI_Elements/VerticalScroller.h"
#include "../CropManager.hpp"

/** MANIPULATION WITH WINDOW TABS **/
#define WINDOW_TAB_FONT_SIZE 14
#define WINDOW_TAB_SIZE 10
#define WINDOW_TAB_OFFSET 40

/** WINDOW MOVER **/
#define WINDOW_MOVER_MAX_HEIGHT 15
#define WINDOW_MOVER_WIDTH_MINUS 15
#define WINDOW_MOVER_HEIGHT 25
#define WINDOW_MOVER_X_OFFSET 1
#define WINDOW_MOVER_Y_OFFSET -1

/** SINGLE WINDOWTAB HEIGHT **/
#define SINGLE_WINDOWTAB_HEIGHT 0

/** WINDOW TITLE **/
#define WINDOW_TITLE_X_OFFSET 0
#define WINDOW_TITLE_Y_OFFSET 18
#define WINDOW_TITLE_HEIGHT 15

//This is just temporary solution for flow movement with timestep
#define MOVEMENT_MULTIPLIER 1.45
#define RECTANGLE_VERTICAL_SCROLLER_OFFSET 1

inline void moverWidthCalculator(int& width, int& frameWidth){
    width = frameWidth - PINGUI_WINDOW_EXITBUTTON_W - PINGUI_WINDOW_LINE_W - WINDOW_MOVER_WIDTH_MINUS;
}

//Better encapsulation of data
class windowDef {
	public:
		PinGUI::Rect windowFrame;
		std::vector<std::string> tabs;
		windowElementType type;
		element_shape shape;
		std::string windowName;
		unsigned int tabOffset;

		windowDef(PinGUI::Rect WindowFrame, std::vector<std::string> Tabs, windowElementType Type, element_shape Shape = ROUNDED) :
			windowFrame(WindowFrame),
			tabs(Tabs),
			type(Type),
			shape(Shape),
			windowName(BLANK),
			tabOffset(WINDOW_TAB_OFFSET)
		{
		}

		//Default constr
		windowDef() :
			type(BOTH),
			shape(ROUNDED),
			tabOffset(WINDOW_TAB_OFFSET)
		{
		}
};

/**
    tabName for easily controling the tab choose with just typping the name of the window tab
**/
class tabInfo{
public:
    std::string tabName;
    std::shared_ptr<WindowTab> windowTab;

    tabInfo(std::string name, std::shared_ptr<WindowTab> tab):
        tabName(name),
        windowTab(tab)
        {

        }
    ~tabInfo()
        {

        }
};

class Window: public GUI_Element
{
    protected:
        //Informations about position, window frame etc.
        PinGUI::Rect _mainFrame;

        //Window camera rect - for cropping
        PinGUI::Rect _cameraRect;

        //It keeps information about mover and exit button
        windowElementType _type;

        //Shape (it can behave differently on different shapes)
        element_shape _shape;

		//"Name tag" for window so it will be able to bind it at the later stage
		std::string _windowName;

		//Title
		std::string _windowTitle;

		//This represents the offset of the tabs
		unsigned int _tabOffset;

		std::shared_ptr<Text> _windowTitleText;

        //Elements important for every window - they need to be unique and saved via those pointers
        std::shared_ptr<WindowMover> _windowMover;

        std::shared_ptr<WindowExit> _windowExit;

        std::shared_ptr<VerticalScroller> _verticalScroller;

        std::shared_ptr<HorizontalScroller> _horizontalScroller;

		std::shared_ptr<Window>* _mainWindowPtr;

		std::vector<std::shared_ptr<Window>> _attachedWindows;

        //Here is my renderer for GUI
        std::shared_ptr<GUIManager> _mainGUIManager;

        //The main windowTab that will be rendered
        std::shared_ptr<WindowTab> _mainWindowTab;

        //Vector of tab info;
        std::vector<std::shared_ptr<tabInfo>> _TABS;

        //Camera vector
        PinGUI::Vector2<GUIPos> _tabMovementChecker;

        bool _needCrop;

        //Bool to keep the track in case of moving the whole window
        bool _windowUpdate;

        // Bool to keep if the tabs was changed (so i can refresh the scrollbar)
        bool _tabChange;

        bool _enabledScrollerManagement;

		bool _alreadyMovedTo;

        //Moving vector
        PinGUI::Vector2<GUIPos> _movingVect;

        /**
            Private methods *****************************************************************************
        **/
       void initTab();

       void createTabs(std::vector<std::string>& tabs, PinGUI::Rect& positionRect, unsigned int tabOffset);

       void nameTab(std::shared_ptr<tabInfo> tab);

       void createEmptyTabLine(PinGUI::Rect& positionRect, unsigned int tabOffset);

       void createWindowMoverArea();

       void createWindowExitButton();

       PinGUI::Rect calculateSize(int vecSize,const PinGUI::Rect& positionRect, std::size_t counter, bool nameIt = true);

       void offsetTab(std::shared_ptr<WindowTab> tab, const unsigned int& tabOffset);

       bool haveMover();

       bool haveExit();

       void checkDimensions(PinGUI::manipulationState state, const int& value);

       //This function is called everytime when you switch the tab
       void updateTab();

       //Function to update the tabs camera
       void updateTabCamera(PinGUI::Vector2<GUIPos> vect);

       void setWindowCamRect();

       void cropTabArea();

       PinGUI::scrollFuncPointer getCamRollFunction();

       bool isScrollerActive(std::shared_ptr<HorizontalScroller>& scroller);

       bool isScrollerActive(std::shared_ptr<VerticalScroller>& scroller);

	   bool isScrollerDeployed(std::shared_ptr<Scroller> scroller);

	   void normalizeAttachedWindows(const GUIPos& x, const GUIPos& y);

	   PinGUI::Rect getOffsetRectForTitle();

	   bool checkWindowRect();

    public:
        Window(){};
        Window(windowDef* winDef);
        ~Window();

		void deleteWindow();

        void addElementsToManager();

		void addElementsToManager(std::shared_ptr<GUIManager> gui);

        int calculateScrollerSize(PinGUI::manipulationState state);

        void createVerticalScroller(int height);

        void adjustHorizontalScrollerWidth();

        void createHorizontalScroller(int width);

        //It return nullptr if the tab doesn´t exist
        std::shared_ptr<WindowTab> getTab(std::string tabName);

        void normalizeTab(std::shared_ptr<WindowTab> tab, const float& x, const float& y);

        void addTitle(std::string windowTitle);

        void render();

        void update(bool allowCollision = true);

        void moveWindow(PinGUI::Vector2<GUIPos> vect);

		void moveBaseWindow(PinGUI::Vector2<GUIPos> vect);

		void normalizeElement(const PinGUI::Vector2<GUIPos>& vect) override;

        void info() override;

        void onAim() override;

        void onEndAim() override;

		void setExist(bool state) override;

        bool listenForClick(manip_Element manipulatingElement) override;

		void setAlpha(Uint8 a) override;

		void moveTo(PinGUI::Vector2<GUIPos> vect) override;

		void setShow(bool state) override;

		bool isCursorIn();

		//Gets the current X and Y position of the click inside the window tab
		PinGUI::Vector2<GUIPos> getInsideCursorPosition(PinGUI::Vector2<GUIPos> screenMousePosition);

        /** Re-dimensioning the tabs **/
        void setTabDimensions(PinGUI::Vector2<int> dims, std::string tabName);

        void setTabHeight(int height, std::string tabName);

        void setTabWidth(int width, std::string tabName);

		void enableVerticalScroller();

        //Scroller functions
        void loadScroller();

        void reloadScroller(GUIPos diff, PinGUI::manipulationState state);

        void hideScrollers();

        void manageScroller(PinGUI::manipulationState state, bool show);

        void rollbackTabCamera();


        /**
            [0,0] is for this function the left corner of window, so [10,5] means windowPosX+10,windowPosY+5
            Manage it via macros WINDOW_TITLE_X_OFFSET + WINDOW_TITLE_Y_OFFSET
        **/

        void normalize();

        void setScrollerManagement(bool state);

        elementType getElementType() override;

        std::shared_ptr<GUIManager> getGUI();

        std::shared_ptr<Scroller> getScroller(PinGUI::manipulationState state);

        PinGUI::Rect getCropRect();

        PinGUI::Rect* getCropRect_P();

        PinGUI::Vector2<GUIPos> getRollbackVector();

		const std::string& getNameTag() const;

		std::string getWindowTitle() const;

		void setNameTag(const std::string& nameTag);

		/******** Two functions for changing the window title ***/

		//This function changes the title immediately
		void setWindowTitle(const std::string& newTitle);

		//This waits for the next update cycle
		void changeWindowTitle(const std::string& newTitle);

		/***************************************************/

		void setMainWindow(std::shared_ptr<Window>* ptr);

		void setAsMainWindow();

		void attachWindow(std::shared_ptr<Window> winPtr);

		float getPotentionalCropHeight();

		float getPotentionalCropWidth();

		unsigned int getTabOffset();
};

#endif // WINDOW_H
