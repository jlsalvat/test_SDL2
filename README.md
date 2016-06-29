###Development Libraries used :
* SDL2-2.0.4 : https://www.libsdl.org/download-2.0.php	
*	SDL2_ttf-2.0.14 : https://www.libsdl.org/projects/SDL_ttf/
*	SDL2_net-2.0.1 : https://www.libsdl.org/projects/SDL_net/
*	SDL2_gfx : https://sourceforge.net/projects/sdl2gfx/
*	SDL_image 2.0 : https://www.libsdl.org/projects/SDL_image/

###How to use ?
	download code::block : version used 12.11
	open testForUser.cbp (project name ) inside main folder
	compile and run and enjoy

###Documentation :
	open main/docs/html/index.html

###How to create a new project ?
	copy an existing project
	open it in an editor (notepad++ or sublime)
	change the name in <Option title> and in <Option output=>(for name of exe)
	launch code::block

###Architecture :
> SDL2 : folder contain include and library SDL2 used by main folder

> main : folder contain projects and library 
  * -------biblio : user libraries folder  SDLS.c and net.c 
  * -------bin : used by code::block to generate exe file
  * -------[doc\html\index.html](https://htmlpreview.github.io/?https://github.com/jlsalvat/test_SDL2/blob/master/main/docs/html/index.html)  : html help documents on SDLS.c 
  * -------fonts : fonts folder, you can download new font inside this folder
  * -------images : images folder, you can download images (jpeg, png,...)
  * -------obj : used by code::block when compile
  * -------test : main test program using biblio folder


