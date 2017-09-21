#ifndef ERRORMANAGER_H
#define ERRORMANAGER_H

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
#include <string>
#include <cstdlib>
#include <iostream>

///Namespace for defining error messages

namespace ErrorManager{

    /**
        Shutdowns the whole program
    **/
    //For closing program from error logs (only fatal errors)
    static void closeProgram(){
		system("pause");
        exit(1);
    }

    /**
    Fatal errors - they QUIT the game
    **/

    //System errors - they talk about system fails
    static void systemError(const std::string& errorName){

        std::cout << "System error: " << errorName.c_str();
        closeProgram();
    }

    /**
    File error  - they QUIT the game (it is better to also display the file that wasnt loaded properly)
    **/

    //Errors connected with file loading problems (Couldn´t open aaa.txt ... )
    static void fileError(const std::string& errorName){

        std::cout << "File can not be loaded! Log: " << errorName.c_str();
        closeProgram();
    }

    /**
    Causal info logs/errors
    **/

    //Just info logs - for changing resolution, telling the version of openGL etc.
    static void infoLog(const std::string& title, const std::string& info){
        std::cout << "Warning log: " << title.c_str() << info.c_str();
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,title.c_str(),info.c_str(),NULL);
    }

    static void errorLog(const std::string& title, const std::string& info){
        std::cout << "Error log: " << title.c_str() << info.c_str();
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,title.c_str(),info.c_str(),NULL);
        closeProgram();
    }
}


#endif // ERRORMANAGER_H
