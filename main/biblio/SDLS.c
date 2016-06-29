#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * \file SDLS.c
 * \brief using SDL2 in a simplified way in C , only one window use
 * \author JLS
 * \version 0.1
 * \date 11 June 2016
 *
 * functions for init, change color, create textures from image or creating shapes,
 * for use in developping 2D Game with SDL2 multiplatform library
 */

// default size of screen
const int SCREEN_WIDTH=680;
const int SCREEN_HEIGHT=480;

// globals variables
SDL_Renderer* gRenderer = NULL;
SDL_Window * gWindow=NULL;


/**
 * \fn int SDLS_getScreenHeight()
 * \brief getting Height -> 480 px by default
 * \return Height of SCREEN
 */
int SDLS_getScreenHeight(){
    return SCREEN_HEIGHT;
}
/**
 * \fn int SDLS_getScreenWidth()
 * \brief getting width -> 640 px by default
 * \return Width of SCREEN
 */
int SDLS_getScreenWidth(){
    return SCREEN_WIDTH;
}
/**
 * \fn SDL_Renderer* SDLS_getRenderer()
 * \brief getting the renderer of window displayed,
 *         you need this param to display shape with SDL library
 *          if you don't want use SDLS function
 * \return renderer
 */
SDL_Renderer* SDLS_getRenderer(){
    return gRenderer;
}
/**
 * \fn void SDLS_changeColor(SDL_Texture * text, int r, int g, int b)
 * \brief changing color of image texture, red, green, blue
 *       after opening an image, you can dark more of less image with this function
 * \param image texture, r : red (0,255), g : green (0,255), b blue (0,255)
 */

void SDLS_changeColor(SDL_Texture * text, int r, int g, int b){
SDL_SetTextureColorMod( text, r, g, b);
}

/**
 * \fn void SDLS_init(const char * titre)
 * \brief create window and renderer context, first function to call in main
 * \param title of window when displayed
 */

//création d'une fenêtre, et d'un render.
void SDLS_init(const char * titre)
{
    // création des structures permettant l'utilisation de la carte vidéo et du timer SDL
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);
    //creation de la fenêtre graphique
    gWindow = SDL_CreateWindow(titre,SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    // utilisation de la carte video pour l'affichage du rendu de la denêtre
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED| SDL_RENDERER_PRESENTVSYNC);
    // Si on n'y arrive pas, on quitte en enregistrant l'erreur dans stdout.txt
    if (gWindow == NULL || gRenderer == NULL)
    {
        printf("Impossible d'initialiser le mode écran à %d x %d: %s\n", SCREEN_WIDTH,
               SCREEN_HEIGHT, SDL_GetError());
        exit(1);
    }
    //On initialise SDL_TTF 2 qui gérera l'écriture de texte dans la fenêtre (utilisation de gRenderer)
    if (TTF_Init() < 0)
    {
        printf("Impossible d'initialiser SDL TTF: %s\n", TTF_GetError());
        exit(1);
    }
}
/**
 * \fn SDL_Texture *SDLS_loadImage( char *name)
 * \brief loading image in a texture (VRAM), image can be bmp, png, jpg,... format \n
 * Example :
 * \code SDL_Texture * texture_fond =SDLS_loadImage("images//elephant.png");
 *    SDLS_copyTexture(texture_fond, 0,0);// copy in video buffer in the top left
 * \endcode
 * \param path and name of file
 * \return texture
 */

// ouvrir un fichier png et le placer dans une texture
SDL_Texture *SDLS_loadImage( char *name)
{
    SDL_Surface *loadedImage = NULL;
    SDL_Texture *texture = NULL;

// Charge les images avec SDL Image dans une SDL_Surface
// pour PNG
    loadedImage = IMG_Load(name);
// pour BMP
// SDL_Surface * image = SDL_LoadBMP(name);
    //Color key image, le fond blanc est enlevé... Pas besoin de détourrer l'image
	SDL_SetColorKey( loadedImage, SDL_TRUE, SDL_MapRGB( loadedImage->format, 0xFF, 0xFF, 0xFF ) );
    if (loadedImage != NULL)
    {
// Conversion de l'image en texture
        texture = SDL_CreateTextureFromSurface(gRenderer, loadedImage);
// On se débarrasse du pointeur vers une surface
        SDL_FreeSurface(loadedImage);
        loadedImage = NULL;
    }
    else
        printf("L'image n'a pas pu être chargée! SDL_Error : %s\n", SDL_GetError());
    return texture;
}

/**
 * \fn SDL_Rect  SDLS_drawFillRect(int x, int y, int w, int h)
 * \brief drawing a filled rectangle in window from position x,y first and size w*h \n
 *  Example : setting color and drawing line rectangle
 * \code  SDLS_setColor(0,0,255); //  blue color
 *  SDLS_drawFillRect(50,50,100,20); // rectangle in 50,50 size 100x20
 * \endcode
 * \param  x X top left position
 * \param  y Y top left position
 * \param  w  width
 * \param  h  height
 * \return SDL_Rect rectangle created
 */

//dessin d'un rectangle plein
SDL_Rect SDLS_drawFillRect(int x, int y, int w, int h)
{
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = w;
    r.h = h;
    SDL_RenderFillRect(gRenderer,&r);
    return r;
}

/**
 * \fn SDL_Rect  SDLS_drawLineRect(int x, int y, int w, int h)
 * \brief drawing a line rectangle in window from position x,y first and size w*h \n
 *  Example : setting color and drawing line rectangle
 * \code  SDLS_setColor(255,0,0); //  red color
 *  SDLS_drawLineRect(50,50,100,20); // rectangle in 50,50 size 100x20
 * \endcode
 * \param  x X top left position
 * \param  y Y top left position
 * \param  w  width
 * \param  h  height
 * \return SDL_Rect rectangle created
 */

//dessin d'un rectangle vide
SDL_Rect  SDLS_drawLineRect(int x, int y, int w, int h)
{
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = w;
    r.h = h;
    SDL_RenderDrawRect(gRenderer,&r);
    return r;
}

/**
 * \fn SDL_Rect SDLS_drawLine(int x1, int y1, int x2, int y2)
 * \brief drawing a line in window from x1,y1 first point to second point x2,y2 \n
 *  Example : setting color and drawing line
 * \code  SDLS_setColor(0,255,0); //  green color
 *  SDLS_drawLine(50,50,100,20); // line from 50,50 to 100,20
 * \endcode
 * \param  x1 X position of first point
 * \param  y1 Y position of first point
 * \param  x2 X position of second point
 * \param  y2 Y position of second point
 * \return SDL_Rect rectangle created
 */
//dessin d'une ligne
void SDLS_drawLine(int x1, int y1, int x2, int y2){
SDL_RenderDrawLine(gRenderer,x1,y2,x2,y2);
}
/**
 * \fn void SDLS_drawPoint(int x, int y)
 * \brief drawing a pixel in window in position x,y \n
 * \param  x X position of  point
 * \param  y Y position of  point
 */
//dessin d'un point
void SDLS_drawPoint(int x, int y)
{
    SDL_RenderDrawPoint( gRenderer, x,y );
}
/**
 * \fn void SDLS_eraseWithBackgroundColor(int r, int g, int b)
 * \brief Erase window with a background color  \n
 *  Use this function before drawing texture or shape \n
 * \code  SDLS_eraseWithBackgroundColor(255,255,255); // white background color
  * \endcode
 * \param  r RED color , 0 to  255
 * \param  g GREEN color , 0 to  255
 * \param  b BLUE color , 0 to  255
 */
//effacer le fond avec une couleur
void SDLS_eraseWithBackgroundColor(int r, int g, int b)
{
    //color du fond
    // Set render color to
    SDL_SetRenderDrawColor( gRenderer, r, g, b, 255 );
    // Clear window
    SDL_RenderClear( gRenderer );
}
/**
 * \fn void SDLS_setColor(int r, int g, int b)
 * \brief choosing a color for the next shape   \n
 *  Use this function before drawing texture or shape \n
 * \code  SDLS_setColor(0,0,0); //  black color
 *  SDLS_drawLine(50,50,100,20); // drawing a line from 50,50 to 100,20
  * \endcode
 * \param  r RED color , 0 to  255
 * \param  g GREEN color , 0 to  255
 * \param  b BLUE color , 0 to  255
 */
// choix d'une couleur utilisée pour le dessin de formes carrées ou de lignes
void SDLS_setColor(int r, int g, int b)
{
    SDL_SetRenderDrawColor( gRenderer, r,g,b, 255 );
}
/**
 * \fn SDL_Rect SDLS_copyTexture(SDL_Texture *tex, int x, int y)
 * \brief copy texture to renderer   \n
 *  Use this function to draw an image texture in window \n
 * \code  SDL_Texture * texture_balles =SDLS_loadImage("images//balles.png"); // load image texture in RAM
 *  SDL_Rect SDLS_copyTexture(texture_balles, SDLS_getScreenWidth()/2,SDLS_getScreenHeight()/2);// copy in video buffer in the middle of windows
  * \endcode
 * \param  x position of texture in windows
 * \param  y position of texture in windows
 * \return SDL_Rect rectangle created from texture
 */
// copie de textures vers le renderer
SDL_Rect SDLS_copyTexture(SDL_Texture *tex, int x, int y)
{
    //Setup the destination rectangle to be at the position we want
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    //Query the texture to get its width and height to use
    SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(gRenderer, tex, NULL, &dst);
    return dst;
}
/**
 * \fn void SDLS_copyTextureEx(SDL_Texture *tex, SDL_Rect src, SDL_Rect dst)
 * \brief copy only a part of image source  texture (SDL_Rect src) to a to a (SDL_Rect dst) renderer   \n
 *  Use this function to draw a part of image texture in window \n
 * \code  SDL_Rect gSpriteSourceBalle[ 4 ]=
 *                                          {{0,0,25,25}, //balle rouge
 *                                          {25,0,25,25}, //balle verte
 *                                          {0,25,25,25},  //balle jaune
 *                                          {25,25,25,25}}; //balle bleu
 *  SDL_Rect gDestBalle= {62,62,25,25}; // position dans la fenêtre
 *
 *  SDL_Texture * texture_balles =SDLS_loadImage("images//balles.png"); // copy image (4 balles of size 25x25) in texture
 *  SDLS_copyTextureEx(texture_balles,gSpriteSourceBalle[0],gDestBalle); // display first balle in rectangle gDestBalle of window
 * \endcode
 * \param  tex  texture to copy to window
 * \param  src  rectangle inside texture (a part of image) you want to copy
 * \param  dst  rectangle where to copy inside window
 */

// copie de textures vers le renderer de source vers dest
void SDLS_copyTextureEx(SDL_Texture *tex, SDL_Rect src, SDL_Rect dst)
{
    SDL_RenderCopy(gRenderer, tex, &src, &dst);
}

/**
 * \fn SDL_Rect SDLS_copyAndFlipTexture(SDL_Texture *tex, int x, int y, int flip )
 * \brief copy and flip texture to renderer , same as SDL_Rect SDLS_copyTexture with adding flip option \n
 *  Use this function to draw an image texture with a flip in window \n
 * \code  SDL_Texture * texture_vaisseau = SDLS_loadImage("images//spaceship.png"); // load image texture in RAM
 *  SDLS_copyAndRotateTexture(texture_vaisseau,100,200,VERTICAL); // flip and copy to Video Buffer
 * \endcode
 * \param  tex  texture to copy to window
 * \param  x position of texture in windows
 * \param  y position of texture in windows
 * \param  vertical : use SDL_FLIP_VERTICAL or SDL_FLIP_HORIZONTAL to type of flip
 * \return SDL_Rect rectangle created from texture
 */

// flipping the strucure
SDL_Rect SDLS_copyAndFlipTexture(SDL_Texture *tex, int x, int y, int flip ){
        //Setup the destination rectangle to be at the position we want
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    //Query the texture to get its width and height to use
    SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopyEx(gRenderer,tex,NULL,&dst,0,NULL,flip?SDL_FLIP_VERTICAL:SDL_FLIP_HORIZONTAL);
    return dst;
}

/**
 * \fn SDL_Rect SDLS_copyAndRotateTexture(SDL_Texture *tex, int x, int y, int angle )
 * \brief copy and rotate texture to renderer , same as SDL_Rect SDLS_copyTexture with adding rotation option \n
 *  Use this function to draw an image texture with a rotation in window \n
 * \code  SDL_Texture * texture_vaisseau = SDLS_loadImage("images//spaceship.png"); // load image texture in RAM
 *  SDLS_copyAndRotateTexture(texture_vaisseau,100,200,90); // rotate image of 90° and copy to Video Buffer
 * \endcode
 * \param  tex  texture to copy to window
 * \param  x position of texture in windows
 * \param  y position of texture in windows
 * \param  angle of rotation : use from 0 to 360° or -180° to 180°
 * \return SDL_Rect rectangle created from texture
 */
SDL_Rect SDLS_copyAndRotateTexture(SDL_Texture *tex, int x, int y, int angle ){
        //Setup the destination rectangle to be at the position we want
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    //Query the texture to get its width and height to use
    SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopyEx(gRenderer,tex,NULL,&dst,angle,NULL,SDL_FLIP_NONE);
    return dst;
}
/**
 * \fn TTF_Font *SDLS_loadFont(char * font, int taille)
 * \brief Loading Font before displaying a text \n
 *  Use this function to load a font before use of SDLS_loadText to display a text in window  \n
 * \code  TTF_Font * ttfFont2= SDLS_loadFont("fonts\\arial.ttf",15);// load font in RAM, size 15
 *  SDL_Texture *texture_text2= SDLS_loadText(ttfFont1,"text to print", 0,0,0); // copy text to print (in black color) to texture
 *  SDLS_copyTexture(texture_text2,200,100); // copy texture to window on position 200,100
 * \endcode
 * \param  font ttf format font file
 * \param  taille size of font
 * \return TTF_Font* structure of FONT
 */

//chargement de la  font
TTF_Font *SDLS_loadFont(char * font, int taille)
{

    TTF_Font* ttfFont;
    // Set size of renderer to the same as window
    SDL_RenderSetLogicalSize( gRenderer, SCREEN_WIDTH,SCREEN_HEIGHT );

    // Load our fonts, with  size
    ttfFont = TTF_OpenFont( font, taille );
    return ttfFont;
}

/**
 * \fn SDL_Texture *SDLS_loadText(TTF_Font * font, char *sz, int r, int g, int b)
 * \brief putting text into texture \n
 *  Use this function to load text to display in window, you need to load font before using this function  \n
 * \code  TTF_Font * ttfFont2= SDLS_loadFont("fonts\\arial.ttf",15);// load font in RAM, size 15
 *  SDL_Texture *texture_text2= SDLS_loadText(ttfFont1,"text to print", 0,0,0); // copy text to print (in black color) to texture
 *  SDLS_copyTexture(texture_text2,200,100); // copy texture to window on position 200,100
 * \endcode
 * \param  font ttf structure returned by SDLS_loadFont
 * \param  sz text to print
 * \param  r RED color , 0 to  255
 * \param  g GREEN color , 0 to  255
 * \param  b BLUE color , 0 to  255
 * \return SDL_Texture* texture to copy to window
 */
//affichage du texte dans la texture
SDL_Texture *SDLS_loadText(TTF_Font * font, char *sz, int r, int g, int b)
{
    SDL_Color textColor; // background white
    textColor.r=r;
    textColor.g=g;
    textColor.b=b;
    textColor.a=255;
    //SDL_SetRenderDrawColor( gRenderer, r,g,b, 255 );
    SDL_Surface* solid = TTF_RenderText_Solid( font, sz, textColor );
    SDL_Texture *solidTexture = SDL_CreateTextureFromSurface( gRenderer, solid );
    SDL_FreeSurface(solid);
    return solidTexture;
}
/**
 * \fn int SDLS_getpixels(Uint32* pixels, int w, int h)
 * \brief getting an array of pixel of window displayed \n
 *  You can use this function with SDLS_putpixels and change pixels of your window \n
 * \code // darking a zone on position 100,100 and size 20,100 of window. You need to init the window before
 *  Uint32 * pixels;
 *  pixels = (Uint32*) malloc(SDLS_getScreenHeight()*SDLS_getScreenHeight()*sizeof(Uint32)); // creation d'un tableau de pixel à la taille de la fenêtre
 *  SDLS_getpixels(pixels,SCREEN_WIDTH,SCREEN_HEIGHT); // copy de la fenêtre dans le tableau pixels
 *  for(int i=0;i<20;i++)
 *     for(int j=0;j<100;j++)
 *     {
 *          int val = pixel[100+i][100+j]; // recup pixel position 100+i et 100+j (rectangle de 20 par 100)
 *          int cr =  ((val)&0xFF0000) >> 16; // récup couleur rouge du pixel
 *          int cg =  ((val)&0xFF00) >> 8;  // recup couleur verte du pixel
 *          int cb =  ((val)&0xFF); // recup couleur bleue du pixel
 *          cr >>= 1 ;  // division par 2 de la valeur de la couleur, on assombri cette zone
 *          cg >>= 1 ;
 *          cb >>= 1 ;
 *     }
 *     SDLS_putpixels(pixels,SCREEN_WIDTH,SCREEN_HEIGHT);
 *  free(pixels);
 * \endcode
 * \param  pixels array of pixel from window
 * \param  w width of pixel to get
 * \param  h height of pixel to get
 * \return number of pixels copied
 */
//recup des pixels de la fenêtre sur w largeur et h longueur
int SDLS_getpixels(Uint32* pixels, int w, int h)
{
    int res;
    int width=w;//, height=h;
    //SDL_RenderGetLogicalSize(ren,&width,&height);
    //printf("%d %d\n",width,height);
    res = SDL_RenderReadPixels(gRenderer,NULL,SDL_PIXELFORMAT_ARGB8888,pixels,width*sizeof(Uint32));
    if (res<0)
    {
        fprintf(stderr,"Erreur getpixels : %s\n",SDL_GetError());
        return -1;
    }
    return 0;
}
/**
 * \fn int  SDLS_putpixels(Uint32* pixels, int w, int h)
 * \brief putting an array of pixel in window displayed \n
 *  see SLDS_getpixels to see an example \n
 * \param  pixels array of pixel from window
 * \param  w width of pixel to get
 * \param  h height of pixel to get
 * \return number of pixels copied
 */
// affichage des pixels sur la fenêtre
int  SDLS_putpixels(Uint32* pixels, int w, int h)
{
    SDL_Texture * tex;
    int width=w, height=h;
    //SDL_RenderGetLogicalSize(ren,&width,&height);
    tex = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_ARGB8888,
                            SDL_TEXTUREACCESS_STREAMING, width, height);
    SDL_UpdateTexture(tex, NULL, pixels, width * sizeof (Uint32));
    SDL_RenderCopy(gRenderer,tex, NULL, NULL);
    SDL_RenderPresent(gRenderer);
    SDL_DestroyTexture(tex);
    return 0;
}
/**
 * \fn Uint32 SDLS_getColor(int r, int g, int b)
 * \brief get Uint32 color code from R,G,B parameter \n
 * \param  r RED color , 0 to  255
 * \param  g GREEN color , 0 to  255
 * \param  b BLUE color , 0 to  255
 * \return color : example  SDLS_getColor(255,0,0) return 0xFF0000
 */
// transformation r, g, b en Uint32
Uint32 SDLS_getColor(int r, int g, int b)
{
    return (((r<<8)+ g)<<8 )+ b;
}

/**
 * \fn void SDLS_sombre()
 * \brief darking all the window\n
 */
// modification de tous les pixels de la fenêtre
void SDLS_sombre()
{
    Uint32 * pixels;
    int x,y;
    int val;
    int cr,cg,cb;

    /* Récupération des pixels */
    pixels = (Uint32*) malloc(SCREEN_WIDTH*SCREEN_HEIGHT*sizeof(Uint32));
    if (!pixels)
    {
        fprintf(stderr,"Erreur allocation\n");
        return;
    }
    SDLS_getpixels(pixels,SCREEN_WIDTH,SCREEN_HEIGHT);

    /* Traitement */
    for (x=0; x<SCREEN_WIDTH; x++)
    {
        for(y=0; y<SCREEN_HEIGHT; y++)
        {
            val = *(pixels+x+y*SCREEN_WIDTH); //lecture pixel
            cr =  ((val)&0xFF0000) >> 16; // récup couleur rouge du pixel
            cg =  ((val)&0xFF00) >> 8;  // recup couleur verte du pixel
            cb =  ((val)&0xFF); // recup couleur bleue du pixel
            cr >>= 1 ;  // division par 2 de la valeur de la couleur
            cg >>= 1 ;
            cb >>= 1 ;
            *(pixels + x+y*SCREEN_WIDTH) = SDLS_getColor(cr,cg,cb); // mise à jour du pixel
        }
    }
    /* Affichage des pixels */
    SDLS_putpixels(pixels,SCREEN_WIDTH,SCREEN_HEIGHT);
    free(pixels);
}
/**
 * \fn void SDLS_displayAll()
 * \brief use this function after creating shape and texture to display in window\n
 * use of double buffering : all operation before this function  are put in video RAM but not displayed
 *\code SDLS_init("Hello World");
 *  SDLS_setColor(255,0,0); //  red color
 *  SDLS_drawLineRect(50,50,100,20); // rectangle in 50,50 size 100x20
 *  SDLS_displayAll(); // copy cached Video Buffer to Video buffer
 *  SDL_Delay(3000); // wait 3s to see the window
 *  SDLS_cleanup();  // erase memory
 * \endcode
 */
 // copier le buffer video vers la RAM VIDEO aff (technique du double buffer)
void SDLS_displayAll(){
    SDL_RenderPresent(gRenderer);
}
/**
 * \fn void SDLS_cleanup()
 * \brief erase memory used by SDL to access video memory
 */
// tout effacer
void SDLS_cleanup()
{
    //On fait le ménage et on remet les pointeurs à NULL
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    //On quitte SDL_TTF 2
    TTF_Quit();

    //On quitte la SDL
    SDL_Quit();
}
/**
 * \fn void createShapes()
 * \brief example of use of  primitive gfx shapes, thick Lines, circles, roundedrectangle, triangle, bezier courbe \n
 * documentation  http://www.ferzkopp.net/Software/SDL2_gfx/Docs/html/_s_d_l2__gfx_primitives_8h.html \n
 * see source code of void createShapes() to see how to use in your code
 */
//http://www.ferzkopp.net/Software/SDL2_gfx/Docs/html/_s_d_l2__gfx_primitives_8h.html
//utilisation de la primitive gfx
// ici on ajoute des cercles pein ou vide
// on peut aussi ajouter des courbes de bézier, des polygones,des lignes épaisses...
void createShapes(){
        Sint16 circleR = 100;
        Sint16 circleX = 300;
        Sint16 circleY = 300;
        SDL_Renderer* renderer=SDLS_getRenderer();
        filledCircleColor(renderer, circleX, circleY, circleR, 0xFF0000FF);
        circleRGBA(renderer,200,200,100,0,255,0,255);
        roundedRectangleRGBA(renderer,10,10,100,100,30,120,120,0,255);
        thickLineRGBA(renderer,450,150,150,450,50,255,0,255,255);
        trigonRGBA(renderer,100,100,200,200,100,300,0,255,120,255);
        Sint16 vx[10]={10,50,150,200, 220,240,410,500,200,250};
         Sint16 vy[10]={10,80,10,0,10,30,50,80,30,150};
        bezierRGBA(renderer,vx,vy,10,3,50,0,255,255);
}
