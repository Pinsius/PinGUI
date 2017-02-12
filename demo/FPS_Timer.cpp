#include "FPS_Timer.h"

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

FPS_Timer::FPS_Timer():
    fps_ticks(0),
    cap_ticks(0),
    countedFrames(0),
    FPS(60)
{
    SCREEN_TICK_PER_FRAME = 1000 / FPS;
}

FPS_Timer::~FPS_Timer()
{

}

void FPS_Timer::initFPS(void)
{
    fps_ticks = SDL_GetTicks();
}

void FPS_Timer::initCap(void)
{
    cap_ticks = SDL_GetTicks();
}

void FPS_Timer::delay(void)
{
    int frameTicks = SDL_GetTicks() - cap_ticks;

    if (frameTicks < SCREEN_TICK_PER_FRAME){
        SDL_Delay( SCREEN_TICK_PER_FRAME - frameTicks );
    }
}

void FPS_Timer::setFPS(int fps){

    FPS = fps;
    SCREEN_TICK_PER_FRAME = 1000 / FPS;
}

int FPS_Timer::tellTime(){
    return  (int)(SDL_GetTicks()/1000.0f);
}

bool FPS_Timer::updateTime(double& time){

    int old_time = time;
    time = SDL_GetTicks()/1000.0f;

    if (time!=old_time) return true;
    return false;
}
