#ifndef UTILITYFUNCS_H
#define UTILITYFUNCS_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <cstdlib>
#include <iostream>
#include "classfile.h"
#include "windows.h"
#include "conio.h"
#include <vector>
#include <string>

using namespace std;

vector<fire*> fpool;

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 680;
const int SCREEN_BPP = 32;
SDL_Surface *screen = NULL;
SDL_Event event;
SDL_Surface *message = NULL;
SDL_Surface *baseinfo = NULL;
SDL_Surface *noveh = NULL;
SDL_Surface *warning = NULL;
TTF_Font *font = NULL; 
TTF_Font *font1 = NULL; 
SDL_Color textColor = { 255, 255, 255 };
  


SDL_Surface *load_image(string filename ) { 
            //Temporary storage for the image that's loaded 
            SDL_Surface* loadedImage = NULL; 
            //The optimized image that will be used 
            SDL_Surface* optimizedImage = NULL;
            //Load the image 
            loadedImage = IMG_Load( filename.c_str() );
            if( loadedImage != NULL ) { 
                  //Create an optimized image 
                  optimizedImage = SDL_DisplayFormat( loadedImage ); 
                  //Free the old image 
                  SDL_FreeSurface( loadedImage ); }
            //Return the optimized image 
            return optimizedImage; }
            

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination , SDL_Rect* clip = NULL) { 
     //Make a temporary rectangle to hold the offsets 
     SDL_Rect offset; 
     //Give the offsets to the rectangle 
     offset.x = x; offset.y = y;
     //Blit the surface 
     SDL_BlitSurface( source, NULL, destination, &offset ); }
            


void transfer(worldobj *A[S][S], worldobj *x, worldobj *b, int sx, int sy, int dx, int dy){//moves a vehicle to a new position
          worldobj *temp;
          temp = A[sy][sx];
          if(((sx>=11)&&(sx<=17)) && ((sy>=11)&&(sy<=17))) A[sy][sx] = b;
          else A[sy][sx] = x;
          A[dy][dx] = temp;
          A[dy][dx]-> setX(dx); A[dy][dx]-> setY(dy);
          A[dy][dx]->setMoved(false);
}

      
void deploy_randomALL(worldobj *A[S][S]){
     int x, y, n;
     srand(time(NULL));
     n = rand() % 2;
     for(int i = 0; i<=n; i++){
             worldobj *t;
             t = new pyroschrek;
             x = rand() % S;
             y = rand() % S;
             while(A[y][x]->isOccupied()){ x = rand() % S; y = rand() % S;}
             A[y][x] = t;
             t->setX(x); t->setY(y);}
     n = rand() % 2;
     for(int i = 0; i<=n; i++){
             worldobj *t;
             t = new ubertank;
             x = rand() % S;
             y = rand() % S;
             while(A[y][x]->isOccupied()){ x = rand() % S; y = rand() % S;}
             A[y][x] = t;
             t->setX(x); t->setY(y);}
     n = rand() % 2;
     for(int i = 0; i<=n; i++){
             worldobj *t;
             t = new helitanker;
             x = rand() % S;
             y = rand() % S;
             while(A[y][x]->isOccupied()){ x = rand() % S; y = rand() % S;}
             A[y][x] = t;
             t->setX(x); t->setY(y);}
     n = rand() % 2;
     for(int i = 0; i<=n; i++){
             worldobj *t;
             t = new airtanker;
             x = rand() % S;
             y = rand() % S;
             while(A[y][x]->isOccupied()){ x = rand() % S; y = rand() % S;}
             A[y][x] = t;
             t->setX(x); t->setY(y);}
             }

void arsoning(worldobj *A[S][S], int dx, int dy){//creates a new fire
     A[dy][dx] = new fire;
     A[dy][dx]->setY(dy);  A[dy][dx]->setX(dx);
     fire *temp = dynamic_cast<fire*>(A[dy][dx]);
     fpool.push_back(temp);
     }

void update(worldobj *A[S][S], int state, int &count, int &countVEH){//updates the screen
    count = 0;
    countVEH = 0;
    stringstream ss;
    for(int m = 11; m<=17; m++){
            for(int n = 11; n<=17; n++){
                    if(A[m][n] -> isOnFire()) count++; 
                    }}
    for(int m = 0; m<=(S-1); m++){
            for(int n = 0; n<=(S-1); n++){
                    if((!(A[m][n] -> isOnFire())) && (A[m][n] -> isOccupied())) countVEH++; 
                    }}
    
    string str;
    ss << "Base status: " << count << " blocks on fire";
    str = ss.str();
    baseinfo = TTF_RenderText_Solid( font1, str.c_str(), textColor );
    ss.str("");
    str.clear();
    ss << "Num of vehicles on map: " << countVEH;
    str = ss.str();
    noveh = TTF_RenderText_Solid( font1, str.c_str(), textColor );
    ss.str("");
    str.clear();
    warning = TTF_RenderText_Solid( font1, "warning: must not exceed 23", textColor );
    //if(count<=18) b->mendAll(A, x1, b);
    
    
     if (state==0){
     int h = 26;
     SDL_Surface *feta, *panel, *panelRUN;
     feta = load_image("rsrc/back.bmp");
     panel = load_image("rsrc/panel0.png");
     panelRUN = load_image("rsrc/panelRUN.png");
     apply_surface(0, 0, feta, screen);
     apply_surface(680,60 , panel, screen);
     apply_surface(680, 165, panelRUN, screen);
     for(int i = 0; i<=(S-1); i++){
             int w = 26;
             for(int j = 0; j<=(S-1); j++){
                     SDL_Surface *temp;
                     temp = load_image(A[i][j]->geticon());
                     if(temp == NULL) cout << "Load img error\n";
                     else{
                     apply_surface(w, h, temp, screen);
                     w += 26;
                     SDL_FreeSurface( temp );}
                     }
                     h += 26;}
     apply_surface(680, 0, message, screen);
     apply_surface(680, 60, baseinfo, screen);
     apply_surface(680, 80, warning, screen);
     apply_surface(680, 100, noveh, screen);
     SDL_FreeSurface( feta );
     SDL_FreeSurface( panel );
     SDL_FreeSurface( panelRUN);
     SDL_Flip( screen );
     SDL_Delay(800);}
     
     if(state == 1){
     int h = 26;
     SDL_Surface *feta, *panel, *panel1;
     feta = load_image("rsrc/back.bmp");
     panel = load_image("rsrc/panel0.png");
     panel1 = load_image("rsrc/panel1.png");
     apply_surface(0, 0, feta, screen);
     apply_surface(680,60 , panel, screen);
     apply_surface(680, 165, panel1, screen);
     for(int i = 0; i<=(S-1); i++){
             int w = 26;
             for(int j = 0; j<=(S-1); j++){
                     SDL_Surface *temp;
                     temp = load_image(A[i][j]->geticon());
                     if(temp == NULL) cout << "Load img error\n";
                     else{
                     apply_surface(w, h, temp, screen);
                     w += 26;
                     SDL_FreeSurface( temp );}
                     }
                     h += 26;}
     apply_surface(680, 0, message, screen);
     apply_surface(680, 60, baseinfo, screen);
     apply_surface(680, 80, warning, screen);
     apply_surface(680, 100, noveh, screen);
     SDL_FreeSurface( feta );
     SDL_FreeSurface( panel );
     SDL_FreeSurface( panel1 );
     SDL_Flip( screen );
     /*SDL_Delay(800);*/}
    
             }
   
#endif
