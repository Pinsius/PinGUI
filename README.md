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
 
 
 
Some of its features are :
- Text creation (using SDL_TTF extension)
- Dynamic text handling(if you write a variable, library will automatically update the text if the variable changes)
- Basic gui elements (that can be networked together so elements can consist of other elements and create pure new style)
- Advanced window creation options
- Multitabbing (window can has more tabs with different content)
- Scrolling
- Windows have its own coordinate system ( [0;0] is the left corner of the window)
- Each tab can have its own settings (for example font)

Note: the library is still in development

Video : https://www.youtube.com/watch?v=YxVG0uQdU_Y


This library was developed primary for learning purposes but now i consider it to be able
to handle also the GUI in my projects ( even if it still needs lot of improvements).

Things I´m still working on :
- Documentation/or at least simple manual
- Update render system (so it will use benefit of matrices)
- Support of multiple resolutions

More info will be provided soon 
