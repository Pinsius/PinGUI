# PinGUI

C++/SDL2/OpenGL created by Lubomir "Pinsius" Barantal
 
 Extensions: 
 Glew for OpenGL functions.
 http://glew.sourceforge.net/ 
 
 SDL + its extensions:
  SDL_TTF
  SDL_Image
 https://www.libsdl.org/
 
 GLM library for matrix operations
 http://glm.g-truc.net/0.9.8/index.html
 
 Boost (for bind function)
 http://www.boost.org/
 
 
I stopped to continue the development of this GUI library, as I´ve decided to dedicate my spare time to development of my own game engine. However, I was able to create my first editor prototypes using this library, it served well, but needed much more effort and time for its development. The code doesn´t have best architecture, but its working, and you may use it as you want. Thanks. 
I won´t delete the description below, so it stays as before.
 
Some of its features are :
- Text creation (using SDL_TTF extension)
- Dynamic text handling(if you write a variable, library will automatically update the text if the variable changes)
- Basic gui elements (that can be networked together so elements can consist of other elements and create pure new style)
- Advanced window creation options
- Multitabbing (window can has more tabs with different content)
- Scrolling
- Windows have its own coordinate system ( [0;0] is the left corner of the window)
- Each tab can have its own settings (for example font)

Video : https://www.youtube.com/watch?v=YxVG0uQdU_Y


This library was developed primary for learning purposes but now i consider it to be able
to handle also the GUI in my projects ( even if it still needs lot of improvements).

Things I´m still working on :
- Documentation/or at least simple manual[x]
- Update render system (so it will use benefit of matrices) to improve efficiency
- Implement own allocators (the biggest need is for text - when it changes frequently, because dynamic allocations for sprites are slowing the speed down)
- Support of multiple resolutions
- Add new elements and improve old
- Also add support to define GUI layout via XML

More info will be provided soon 
