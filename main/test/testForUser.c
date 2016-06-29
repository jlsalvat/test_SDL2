#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_thread.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "..\biblio\SDLS.h"
#include "..\biblio\net.h"

// put your main here

//this function is called each 100ms and send an event to the main...
Uint32 my_callbackfunc(Uint32 interval, void *param)
{
SDL_Event event;
SDL_UserEvent userevent;
/* In this example, our callback pushes an SDL_USEREVENT event
* into the queue */
userevent.type = SDL_USEREVENT;
userevent.code = 0;
userevent.data1 = NULL;
userevent.data2 = NULL;
event.type = SDL_USEREVENT;
event.user = userevent;
SDL_PushEvent(&event);
return(interval);
}
int main(int argc, char ** argv){
int quit=0,angle=0;
SDL_Event event;
// create window with a title
SDLS_init("Hello World");
// open image and copy to window
SDL_Texture * texture_vaisseau = SDLS_loadImage("images//spaceship.png"); // load image texture in RAM
Uint32 delay = 100; /* To round it down to the nearest 100 ms */
SDL_TimerID my_timer_id = SDL_AddTimer(delay, my_callbackfunc, NULL); //init timer
// handle events
while (!quit)
{
SDL_WaitEvent(&event); // c'est bloquant...
if(event.type==SDL_QUIT)
quit = true;
if(event.type== SDL_USEREVENT){
angle+=4;
if(angle>360)
angle=0;
}
SDLS_eraseWithBackgroundColor(255,255,255); // couleur du fond en blanc
SDLS_copyAndRotateTexture(texture_vaisseau,SDLS_getScreenWidth()-100,50,angle);
SDLS_displayAll(); // copy cached Video Buffer to Video buffer
}
SDLS_cleanup(); // erase memory
}

