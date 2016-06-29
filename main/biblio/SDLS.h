#ifndef SDLS_h
#define SDLS_h

#define false 0
#define true !false

#define VERTICAL 1
#define HORIZONTAL 0


int SDLS_getScreenHeight();
int SDLS_getScreenWidth();
SDL_Renderer* SDLS_getRenderer();
void SDLS_changeColor(SDL_Texture * text, int r, int g, int b);
// ouvrir un fichier png et le placer dans une texture
SDL_Texture *SDLS_loadImage( char *name);
//création d'une fenêtre, et d'un render.
void SDLS_init(const char * titre);
//dessin d'un rectangle plein
SDL_Rect SDLS_drawFillRect(int x, int y, int w, int h);
//dessin d'un rectangle vide
SDL_Rect SDLS_drawLineRect(int x, int y, int w, int h);
//dessin d'une ligne
void SDLS_drawLine(int x1, int y1, int x2, int y2);
//dessin d'un point
void SDLS_drawPoint(int x, int y);
//effacer le fond avec une couleur
void SDLS_eraseWithBackgroundColor(int r, int g, int b);
// choix d'une couleur utilisée pour le dessin de formes carrées ou de lignes
void SDLS_setColor(int r, int g, int b);
// copie de textures vers le renderer
SDL_Rect SDLS_copyTexture(SDL_Texture *tex, int x, int y);
//copie de textures de src vers destination, plus complexe
// a utiliser quand il y a plusieurs images dans l'image source...
void SDLS_copyTextureEx(SDL_Texture *tex, SDL_Rect src, SDL_Rect dst);
SDL_Rect SDLS_copyAndFlipTexture(SDL_Texture *tex, int x, int y ,int vertical);
SDL_Rect SDLS_copyAndRotateTexture(SDL_Texture *tex, int x, int y, int angle );
// affichage du renderer
void SDLS_displayAll();
//chargement de la  font
TTF_Font *SDLS_loadFont(char * font, int taille);
//affichage du texte dans la texture
SDL_Texture *SDLS_loadText(TTF_Font * font, char *sz, int r, int g, int b);
//recup des pixels de la fenêtre sur w largeur et h longueur
int SDLS_getpixels(Uint32* pixels, int w, int h);
// affichage des pixels sur la fenêtre
int  SDLS_putpixels(Uint32* pixels, int w, int h);
// transformation r, g, b en Uint32
Uint32 SDLS_getColor(int r, int g, int b);
// modification de tous les pixels de la fenêtre
void SDLS_sombre();

void createShapes();

void SDLS_cleanup();




#endif
