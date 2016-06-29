#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_thread.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "..\biblio\SDLS.h"
#include "..\biblio\net.h"

// afficher 2 vaisseaux et les déplacer avec la souris ou les flèches du clavier
// afficher des rectangles et/ou lignes

//Scene sprites
SDL_Rect gSpriteSourceBalle[ 4 ]= {{0,0,25,25}, //balle rouge
    {25,0,25,25}, //balle verte
    {0,25,25,25},  //balle jaune
    {25,25,25,25}
}; //balle bleu
SDL_Rect gSpriteSourceBonhomme[ 6 ]=
{
    {0,0,96,225},
    {96,0,96,225},
    {192,0,96,225},
    {288,0,96,225},
    {384,0,96,225},
    {480,200,96,225}
};
SDL_Rect gDestBalle= {62,62,25,25};
SDL_Rect gDestBonhomme= {500,200,96,225};
int gFlagBalle=0;
int gFlagBonhomme=0;
int gQuit=false;
SDL_Point gVaisseau_position[2]={ {40,420}, {40, 20}};
int gAngle=0;


int threadReceiver( void* data )
{
    char msg[30];
    printf( "Running thread with value = %d\n", (int)data );
    while( gQuit == false )
    {
        //on renvoie la donnée lue

        if(net_CheckForData(msg)>0)
        {
            puts(msg);
            SDL_Event event;
            SDL_UserEvent userevent;

            /* In this example, our callback pushes an SDL_USEREVENT event
            into the queue, and causes our callback to be called again at the
            same interval: */

            userevent.type = SDL_USEREVENT;
            userevent.code = 1;
            userevent.data1 = msg;
            userevent.data2 = NULL;

            event.type = SDL_USEREVENT;
            event.user = userevent;

            SDL_PushEvent(&event);

        }
        SDL_Delay(50);
    }

}


Uint32 my_callbackfunc(Uint32 interval, void *param)
{
    SDL_Event event;
    SDL_UserEvent userevent;

    /* In this example, our callback pushes an SDL_USEREVENT event
    into the queue, and causes our callback to be called again at the
    same interval: */

    userevent.type = SDL_USEREVENT;
    userevent.code = 0;
    userevent.data1 = NULL;
    userevent.data2 = NULL;

    event.type = SDL_USEREVENT;
    event.user = userevent;

    SDL_PushEvent(&event);
    return(interval);
}

void   gestion_evt(SDL_Rect rectA,SDL_Rect rectB)
{
        SDL_Event event;



    SDL_WaitEvent(&event); // c'est bloquant...

    switch (event.type)
    {
    case SDL_USEREVENT:
        if(event.user.code ==0)
        {
            gAngle+=4;
            if(gAngle>360)
                gAngle=0;
        }
        if(event.user.code ==1)
        {
            char * sz=(char*)event.user.data1;
            switch(sz[0])
            {
            case 'U':
                gVaisseau_position[1].y--;
                break;
            case 'D':
                gVaisseau_position[1].y++;
                break;
            case 'L':
                gVaisseau_position[1].x--;
                break;
            case 'R':
                gVaisseau_position[1].x++;
            }
        }

        break;
    case SDL_QUIT:
        gQuit = true;
        break;
    case SDL_MOUSEBUTTONDOWN : // sur le clic de la souris on bouge la forme
        if( event.button.button == SDL_BUTTON_LEFT )
        {
            //Get the mouse offsets
            rectB.x = event.button.x;
            rectB.y = event.button.y;
            if(!SDL_HasIntersection(&rectA, &rectB))
            {
                gVaisseau_position[0].x=event.button.x;
                gVaisseau_position[0].y=event.button.y;
            }
            else
                printf("problème avec la souris, intersection avec rectangle");

            gFlagBalle=1;
        }
        break;
    case SDL_KEYDOWN:       // sur l'utilisation du clavier on bouge la forme
        gFlagBonhomme=1;
        switch (event.key.keysym.sym)
        {
        case SDLK_LEFT:
            rectB.x=--gVaisseau_position[0].x;
            if(SDL_HasIntersection(&rectA, &rectB))
                gVaisseau_position[0].x++;
            break;
        case SDLK_RIGHT:
            rectB.x=++gVaisseau_position[0].x;
            if(SDL_HasIntersection(&rectA, &rectB))
                gVaisseau_position[0].x--;
            break;
        case SDLK_UP:
            rectB.y=--gVaisseau_position[0].y;
            if(SDL_HasIntersection(&rectA, &rectB))
                gVaisseau_position[0].y++;
            break;
        case SDLK_DOWN:
            rectB.y=++gVaisseau_position[0].y;
            if(SDL_HasIntersection(&rectA, &rectB))
                gVaisseau_position[0].y--;
            break;
        }
    }
}

int main(int argc, char ** argv)
{
    // variables

    SDL_Rect rectB, rectA;

    // init SDL
    SDLS_init("test");
    net_init("127.0.0.1",5001,5000);
    //Run the thread
    int data = 101;
    SDL_Thread* threadID = SDL_CreateThread( threadReceiver, "Receiver", (void*)data );
    //chargement des textures et des fonts et du timer

    SDL_Texture * texture_fond =SDLS_loadImage("images//elephant.png");
    SDL_Texture * texture_balles =SDLS_loadImage("images//balles.png");
    SDL_Texture * texture_bonhomme= SDLS_loadImage("images//marche.png");
    SDL_Texture * texture_vaisseau = SDLS_loadImage("images//spaceship.png");
    TTF_Font * ttfFont1= SDLS_loadFont("fonts\\sketchy.ttf",20);
    TTF_Font * ttfFont2= SDLS_loadFont("fonts\\arial.ttf",15);
    SDL_Texture *texture_text1= SDLS_loadText(ttfFont1,"animation", 255,0,255);
    SDL_Texture *texture_text2= SDLS_loadText(ttfFont1,"ELEPHANT", 0,0,180);
    SDL_Texture *texture_text3= SDLS_loadText(ttfFont2,"Utiliser la souris ou le clavier...", 0,0,0);

    Uint32 delay = 100;  /* To round it down to the nearest 100 ms */
    SDL_TimerID my_timer_id = SDL_AddTimer(delay, my_callbackfunc, NULL);

    // handle events
    while (!gQuit)
    {
        gestion_evt(rectA,rectB);
// couleur du fond en blanc
        SDLS_eraseWithBackgroundColor(255,255,255);
        SDLS_copyTexture(texture_fond,0,0);
        SDLS_changeColor(texture_fond, 255, 130,0);
//dessin de formes rectangles, lignes
        SDLS_setColor(0,230,0);
        rectA=SDLS_drawFillRect(50,50,50,50); // premier rectangle plein
        SDLS_setColor(230,0,0);
        SDLS_drawLine(0, SDLS_getScreenHeight() / 2, SDLS_getScreenWidth(), SDLS_getScreenHeight() / 2); //une ligne
        SDLS_setColor(100,120,50);
        SDLS_drawLineRect(SDLS_getScreenWidth()-100,50,65,65); //une rectangle vide
//une ligne verticale en pointillé utilisant des points
        SDLS_setColor(0xFF, 0, 0x00 );
        for( int i = 0; i < SDLS_getScreenHeight(); i += 4 )
        {
            SDLS_drawPoint( SDLS_getScreenWidth() / 2, i );
            SDLS_drawPoint( SDLS_getScreenWidth() / 2, i+1 );
        }

// dessin d'une balle différente à chaque clic
        static int cpt1=0,cpt2=0;
        if(gFlagBalle)
        {
            gFlagBalle=0;
            cpt1++;
            if (cpt1==4)
                cpt1=0;
            printf("cpt1=%d\n",cpt1);
        }
//animation d'un bohomme à chaque appui sur touche
        if(gFlagBonhomme)
        {
            gFlagBonhomme=0;
            cpt2++;
            if (cpt2==5)
                cpt2=0;
            printf("cpt2=%d, angle=%d\n",cpt2,gAngle);
        }

        SDLS_copyTextureEx(texture_balles,gSpriteSourceBalle[cpt1],gDestBalle);
        SDLS_copyTextureEx(texture_bonhomme,gSpriteSourceBonhomme[cpt2],gDestBonhomme);
        rectB=SDLS_copyTexture(texture_vaisseau,gVaisseau_position[0].x,gVaisseau_position[0].y);
        SDLS_copyAndFlipTexture(texture_vaisseau,gVaisseau_position[1].x,gVaisseau_position[1].y,VERTICAL);
        SDLS_copyAndRotateTexture(texture_vaisseau,SDLS_getScreenWidth()-100,50,gAngle);
        SDLS_copyTexture(texture_text1,SDLS_getScreenWidth()-120,20);
        SDLS_copyTexture(texture_text2,200,100);
        SDLS_copyTexture(texture_text3,SDLS_getScreenWidth()-200,SDLS_getScreenHeight()-30);
// test de modification des pixels, ici on assombrit toute l'image.
        // sombre();
//affichage du rendeder
        SDLS_displayAll();
    }
    // cleanup SDL
    SDL_DestroyTexture(texture_vaisseau);
    SDL_DestroyTexture(texture_text1);
    SDL_DestroyTexture(texture_text2);
    SDL_DestroyTexture(texture_text3);
//Remove timer in case the call back was not called
    SDL_RemoveTimer( my_timer_id );
    SDL_WaitThread( threadID, NULL );
    SDLS_cleanup();
    return 0;
}
