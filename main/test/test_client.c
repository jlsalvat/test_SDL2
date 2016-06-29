#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "..\biblio\SDLS.h"
#include "..\biblio\net.h"


int main(int argc, char ** argv)
{

    SDLS_init("test");
    net_init("127.0.0.1",5000,5001);
    TTF_Font * ttfFont2= SDLS_loadFont("fonts\\arial.ttf",15);
    SDL_Texture *texture_text3= SDLS_loadText(ttfFont2,"utiliser les flèches du clavier...", 0,0,0);
    int quit=false;
    SDL_Event event;
    // handle events
    while (!quit)
    {
        SDL_WaitEvent(&event); // c'est bloquant...

        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
         case SDL_KEYDOWN:       // sur l'utilisation du clavier on bouge la forme
            switch (event.key.keysym.sym)
            {
            case SDLK_LEFT:
				net_send("L");
                break;
            case SDLK_RIGHT:
				net_send("R");
                break;
            case SDLK_UP:
				net_send("U");
                break;
            case SDLK_DOWN:
				net_send("D");
                break;
            }
        }

// couleur du fond en blanc
        SDLS_eraseWithBackgroundColor(255,255,255);
        SDLS_copyTexture(texture_text3,SDLS_getScreenWidth()-200,SDLS_getScreenHeight()-30);
// test de modification des pixels, ici on assombrit toute l'image.
        // sombre();
//affichage du rendeder
        SDLS_displayAll();
    }
    // cleanup SDL
    SDL_DestroyTexture(texture_text3);
//Remove timer in case the call back was not called
    SDLS_cleanup();
    return 0;
}
