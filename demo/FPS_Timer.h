#ifndef FPS_TIMER_H
#define FPS_TIMER_H

/**
    This file is part of PinGUI demo

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

class FPS_Timer
{
    private:

        Uint32 fps_ticks;
        Uint32 cap_ticks;
        int countedFrames;
        int FPS;
        int SCREEN_TICK_PER_FRAME;

    public:
        FPS_Timer();
        ~FPS_Timer();

        void initFPS();
        void initCap();

        void delay();
        int tellTime();
        bool updateTime(double& time);
        void setFPS(int fps);
};

#endif // FPS_TIMER_H
