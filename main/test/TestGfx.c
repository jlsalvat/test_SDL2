#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "..\biblio\SDLS.h"
#include "..\biblio\net.h"

// afficher 2 vaisseaux et les déplacer avec la souris ou les flèches du clavier
// afficher des rectangles et/ou lignes

//Scene sprites

int gQuit=false;


int main(int argc, char ** argv)
{
  int x,y;
    // init SDL
    SDLS_init("test");

    //chargement des textures et des fonts et du timer


    // handle events
    while (!gQuit)
    {
        SDL_Event event;
        SDL_WaitEvent(&event); // c'est bloquant...

        switch (event.type)
        {
               case SDL_QUIT:
            gQuit = true;
            break;
        case SDL_MOUSEBUTTONDOWN : // sur le clic de la souris on bouge la forme
            if( event.button.button == SDL_BUTTON_LEFT )
            {
                x=event.button.x;
                y=event.button.y;
            }
            break;
        case SDL_KEYDOWN:       // sur l'utilisation du clavier on bouge la forme
            switch (event.key.keysym.sym)
            {
            case SDLK_LEFT:
                x-=10;
                break;
            case SDLK_RIGHT:
x+=10;
                break;
            case SDLK_UP:
y-=10;
                break;
            case SDLK_DOWN:
y+=10;
                break;
            }
        }

// couleur du fond en blanc
        SDLS_eraseWithBackgroundColor(255,255,255);
 /*       SDL_Renderer* renderer=SDLS_getRenderer();

        Sint16 circleR = 100;
        Sint16 circleX = 300;
        Sint16 circleY = 300;

        filledCircleColor(renderer, circleX, circleY, circleR, 0xFF0000FF);
        circleRGBA(renderer,200,200,100,0,255,0,255);
        roundedRectangleRGBA(renderer,10,10,100,100,30,120,120,0,255);
        thickLineRGBA(renderer,450,150,150,450,50,255,0,255,255);
        trigonRGBA(renderer,100,100,200,200,100,300,0,255,120,255);
        Sint16 vx[10]={x,50,150,170,290,410,150,200,250,400};
         Sint16 vy[10]={y,80,10,110,10,130,10,210,30,350};
        bezierRGBA(renderer,vx,vy,10,3,50,0,255,255);*/
        SDLS_displayAll();
    }
// cleanup SDL

    SDLS_cleanup();
    return 0;
}
