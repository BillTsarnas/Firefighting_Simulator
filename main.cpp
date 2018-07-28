#include "SDL/SDL.h" 
#include <cstdlib>
#include <iostream>
#include "classfile.h"
#include "windows.h"
#include "conio.h"
#include <vector>
#include <string>
#include <sstream>
#include "utilityfuncs.h"

using namespace std;


int main(int argc, char *argv[])
{   /*intialization of the SDL and setting up the envrinonment*/
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) { return 1; }
    if( TTF_Init() == -1 ) { return 1; } 
    SDL_WM_SetIcon(IMG_Load("rsrc/fire_meaney.png"), NULL);
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    if( screen == NULL ) { return 1; }
    SDL_WM_SetCaption( "rsrc/ProjectFire Visual", NULL );
    font = TTF_OpenFont( "rsrc/SEVESBRG.TTF", 50 );
    font1 = TTF_OpenFont( "rsrc/MIASWFTE.TTF", 20 );
    if( font == NULL ) { cout << "load font error\n"; }
    message = TTF_RenderText_Solid( font, "PROJECT FIRE", textColor );
    SDL_Surface *start = load_image("rsrc/start.png");
    SDL_Surface *black = load_image("rsrc/black.png");
    SDL_Surface *information = load_image("rsrc/information.png");
    apply_surface(0, 0, start, screen);
    SDL_Flip(screen);
    bool starting = false;
    while(!starting){
                 while( SDL_PollEvent( &event ) ) {
                        if( event.type == SDL_KEYDOWN){
                            if(event.key.keysym.sym == SDLK_SPACE) starting = true;
                            else if(event.key.keysym.sym == SDLK_i){
                                 apply_surface(0, 0, information, screen);
                                 SDL_Flip(screen);
                                 }
                                 }
                                 }
                                 }
                            
                            
                          
    SDL_FreeSurface(start); SDL_FreeSurface(information);
    apply_surface(680, 0, black, screen);
    SDL_FreeSurface(black);
    worldobj *A[S][S];
    worldobj *x1;
    x1 = new worldobj;
    fire *f;
    f = new fire;
    base *b;
    b = new base;
    fpool.push_back(f); //insert the new fire into the vector. The vector helps us clear the memory at the end of the program
    for(int i = 0; i<=(S-1); i++){
            for(int j = 0; j<=(S-1); j++){
                    A[i][j] = x1;}
                    }
    /*-----------------spawn----------------*/
    for(int i = 11; i<=17; i++){
            for(int j = 11; j<=17; j++) A[i][j] = b;} //base set up
    srand(time(NULL));
    int randX = rand() % S;
    int randY = rand() % S;
    A[randY][randX] = f;
    f->setX(randX); f->setY(randY); 
    b->setX(11); b->setY(11); //here a fire is randomly deployed
    deploy_randomALL(A); //a random number of vehicles (of all types) is deployed
    /*------------------------------------------------------------------------------------------*/
    int count = 0;
    int countEND = 0;
    int countVEH = 0;
    
    
    update(A, 0, count, countVEH);
    /*------------------------------------*/
    
    bool quit = false;
    while(quit == false){
                 
            for(int i = 0; i<=(S-1); i++){ /*all the vehicles and fires in the map move here*/
                    for(int j = 0; j<=(S-1); j++){
                                           bool cantGoUp = false;
                                           bool cantGoDown = false;
                                           bool cantGoRight = false;
                                           bool cantGoLeft = false;
                                           int x, y;
                                           x = j;
                                           y = i - 1;
                                           if(y<0)cantGoUp = true;
                                           if(cantGoUp == false){
                                                       if(A[y][x]->isOnFire()) cantGoUp = true;}
                                           x = j + 1;
                                           y = i;
                                           if((x>(S-1))) cantGoRight = true;
                                           if(cantGoRight == false){
                                                       if(A[y][x]->isOnFire()) cantGoRight = true;}
                                           x = j;
                                           y = i + 1;
                                           if((y>(S-1))) cantGoDown = true;
                                           if(cantGoDown == false){
                                                       if(A[y][x]->isOnFire()) cantGoDown = true;}
                                           x = j - 1;
                                           y = i;
                                           if(x<0) cantGoLeft = true;
                                           if(cantGoLeft == false){
                                                         if(A[y][x]->isOnFire()) cantGoLeft = true;}
                            if(cantGoUp && cantGoDown && cantGoRight && cantGoLeft){A[i][j]->setage(999);} /*minor bug fix*/
                            else A[i][j] -> move(A, x1, f, b);}
                            }
    for(int m = 0; m<=(S-1); m++){
            for(int n = 0; n<=(S-1); n++){
                    A[m][n] -> setMoved(false);
                    A[m][n] -> ageup(A, x1, b);} //the vehicles in the map get older
                    }
                    
    
    update(A, 0, count, countVEH);
    
    if(count<=18) b->mendAll(A, x1, b); //the base searches for vehicles that need help and repairs them
    
     /*event handling*-----------------------------------------------------------------------------------------------------------------------*/
    while( SDL_PollEvent( &event ) ) {
                 //If the user has Xed out the window 
                 if( event.type == SDL_QUIT ) { 
                     //Quit the program 
                     quit = true; }
                 if( event.type == SDL_KEYDOWN){
                     if(event.key.keysym.sym == SDLK_ESCAPE){
                                             update(A, 1, count, countVEH);
                                             SDL_WM_SetCaption( "ProjectFire Visual (PAUSE)", NULL );
                                             bool pause = true;
                                             bool motionEnable = true;
                                             bool clickEnable = true;
                                             bool mapEnable = false;
                                             bool vhOptionsEnable = false;
                                             bool selectingDest = false;
                                             bool canMove = true;
                                             bool deploying = false;
                                             bool arson = false;
                                             int x = 0, y = 0;
                                             int selectedX = 0, selectedY = 0;
                                             int destX = 0, destY = 0;
                                             int vehicleSelection = 0;
                                             SDL_Surface *panelVSinfo, *black, *panelNVinfo, *panelARinfo, *VSpanel, *ARpanel, *NVpanel;
                                             panelVSinfo = load_image("rsrc/panelVSinfo.png");
                                             VSpanel = load_image("rsrc/VSpanel.png");
                                             ARpanel = load_image("rsrc/ARpanel.jpg");
                                             NVpanel = load_image("rsrc/NVpanel.png");
                                             panelNVinfo = load_image("rsrc/panelNVinfo.png");
                                             panelARinfo = load_image("rsrc/panelARinfo.png");
                                             black = load_image("rsrc/black.png");
                                             while(pause){
                                                          while(SDL_PollEvent( &event )){
                                                                               if(event.type==SDL_QUIT){pause = false; quit = true;}
                                                                               if(event.type==SDL_KEYDOWN){ 
                                                                                                            if(event.key.keysym.sym == SDLK_ESCAPE) pause = false;
                                                                                                            else if(event.key.keysym.sym == SDLK_BACKSPACE){
                                                                                                                 pause = true;
                                                                                                                 motionEnable = true;
                                                                                                                 clickEnable = true;
                                                                                                                 mapEnable = false;
                                                                                                                 vhOptionsEnable = false;
                                                                                                                 selectingDest = false;
                                                                                                                 canMove = true;
                                                                                                                 deploying = false;
                                                                                                                 destX = 0; destY = 0;
                                                                                                                 update(A, 1, count, countVEH);
                                                                                                                 }
                                                                                                                 }
                                                                               if( event.type == SDL_MOUSEMOTION ){
                                                                                    x = event.motion.x; y = event.motion.y;
                                                                                    if( (( x > (50+680) ) && ( x < (135+680) ) && ( y > (250+165) ) && ( y < (335+165) )) &&motionEnable ) {apply_surface(680, 600, panelVSinfo, screen); SDL_Flip(screen);}
                                                                                    else if( (( x > (235+680) ) && ( x < (320+680) ) && ( y > (250+165) ) && ( y < (335+165) )) &&motionEnable) {apply_surface(680, 600, panelARinfo, screen); SDL_Flip(screen);}
                                                                                    else if( (( x > (420+680) ) && ( x < (500+680) ) && ( y > (250+165) ) && ( y < (335+165) ) ) &&motionEnable) {apply_surface(680, 600, panelNVinfo, screen); SDL_Flip(screen);}
                                                                                    else {if(motionEnable){apply_surface(680, 600, black, screen); SDL_Flip(screen);}}
                                                                                    }
                                                                               if( event.type == SDL_MOUSEBUTTONDOWN ){
                                                                                   if( event.button.button == SDL_BUTTON_LEFT ){
                                                                                       x = event.button.x; y = event.button.y;
                                                                                       if( (( x > (50+680) ) && ( x < (135+680) ) && ( y > (250+165) ) && ( y < (335+165) )) &&clickEnable ) {
                                                                                           clickEnable = false; mapEnable = true; motionEnable = false;
                                                                                           apply_surface(680, 165, VSpanel, screen); 
                                                                                           SDL_Flip(screen);
                                                                                           }
                                                                                       else if( (( x > (235+680) ) && ( x < (320+680) ) && ( y > (250+165) ) && ( y < (335+165) )) &&clickEnable ) {
                                                                                            clickEnable = false; mapEnable = true; motionEnable = false; deploying = false; selectingDest = true;
                                                                                            arson = true;
                                                                                            apply_surface(680, 165, ARpanel, screen); 
                                                                                            SDL_Flip(screen);
                                                                                            }
                                                                                       else if( (( x > (420+680) ) && ( x < (500+680) ) && ( y > (250+165) ) && ( y < (335+165) )) &&clickEnable ) {
                                                                                            clickEnable = false; mapEnable = false; motionEnable = false;  deploying = true;
                                                                                            apply_surface(680, 165, NVpanel, screen); 
                                                                                            SDL_Flip(screen);
                                                                                            }
                                                                                       else if(((x>26)&&(x<702)&&(y>26)&&(y<702)) && mapEnable && (selectingDest==false)){
                                                                                            vhOptionsEnable = true;
                                                                                            SDL_Surface *info, *repair, *move, *destroy;
                                                                                            info = load_image("rsrc/VSpanel.png");
                                                                                            repair = load_image("rsrc/repair.png");
                                                                                            move = load_image("rsrc/move.png");
                                                                                            destroy = load_image("rsrc/destroy.png");
                                                                                            apply_surface(680, 165, info, screen);
                                                                                            apply_surface(1100, 165, move, screen);
                                                                                            apply_surface(1100, 250, repair, screen);
                                                                                            apply_surface(1100, 335, destroy, screen);
                                                                                            SDL_FreeSurface(info);
                                                                                            int i, j;
                                                                                            i = (y-26)/26;
                                                                                            j = (x-26)/26;
                                                                                            vehicle *temp;
                                                                                            temp = dynamic_cast<vehicle *>(A[i][j]);
                                                                                            if(temp != 0){
                                                                                            selectedY = i;
                                                                                            selectedX = j;
                                                                                            info = TTF_RenderText_Solid( font1, (A[i][j]->printinfoTYPE()).c_str(), textColor );
                                                                                            apply_surface(680, 165, info, screen);
                                                                                            SDL_FreeSurface(info);
                                                                                            info = TTF_RenderText_Solid( font1, (A[i][j]->printinfoWCAP()).c_str(), textColor );
                                                                                            apply_surface(680, 185, info, screen);
                                                                                            SDL_FreeSurface(info);
                                                                                            info = TTF_RenderText_Solid( font1, (A[i][j]->printinfoGCAP()).c_str(), textColor );
                                                                                            apply_surface(680, 205, info, screen);
                                                                                            SDL_FreeSurface(info);
                                                                                            info = TTF_RenderText_Solid( font1, (A[i][j]->printinfoAGE()).c_str(), textColor );
                                                                                            apply_surface(680, 225, info, screen);
                                                                                            SDL_FreeSurface(info);
                                                                                            info = TTF_RenderText_Solid( font1, (A[i][j]->printinfoREPAIR()).c_str(), textColor );
                                                                                            apply_surface(680, 245, info, screen);
                                                                                            SDL_FreeSurface(info);
                                                                                            info = TTF_RenderText_Solid( font1, (A[i][j]->printinfoWATERCONSUMPT()).c_str(), textColor );
                                                                                            apply_surface(680, 265, info, screen);
                                                                                            SDL_FreeSurface(info);
                                                                                            info = TTF_RenderText_Solid( font1, (A[i][j]->printinfoGASCONSUMPT()).c_str(), textColor );
                                                                                            apply_surface(680, 285, info, screen);
                                                                                            SDL_Flip(screen);
                                                                                            SDL_FreeSurface(info); SDL_FreeSurface(move); SDL_FreeSurface(repair); SDL_FreeSurface(destroy);}
                                                                                            else{
                                                                                                 info = TTF_RenderText_Solid( font1, (A[i][j]->worldobj::printinfo()).c_str(), textColor );
                                                                                                 apply_surface(680, 165, info, screen); SDL_Flip(screen);
                                                                                                 SDL_FreeSurface(info);}
                                                                                            }
                                                                                 else if( (( x > 1100 ) && ( x < 1180 ) && ( y > 165 ) && ( y < (80+165) )) && vhOptionsEnable ){
                                                                                      selectingDest = true;
                                                                                      SDL_Surface *dest;
                                                                                      vhOptionsEnable = false; 
                                                                                      dest = load_image("rsrc/dest.png");
                                                                                      apply_surface(680, 165, dest, screen); SDL_Flip(screen);
                                                                                      SDL_FreeSurface(dest);
                                                                                      }
                                                                                 else if(((x>26)&&(x<702)&&(y>26)&&(y<702)) && mapEnable && selectingDest){ 
                                                                                      destX = (x-26)/26; destY = (y-26)/26;
                                                                                       }
                                                                                 else if((x>680)&&(x<(680+550))&&(y>383)&&(y<165+500) && selectingDest && (deploying==false)){
                                                                                      vehicle *temp1; temp1 = dynamic_cast<vehicle*>(A[selectedY][selectedX]);
                                                                                      if(temp1 == 0) canMove = false;
                                                                                      if(canMove) transfer(A, x1, b, selectedX, selectedY, destX, destY);
                                                                                      pause = true;
                                                                                      motionEnable = true;
                                                                                      clickEnable = true;
                                                                                      mapEnable = false;
                                                                                      vhOptionsEnable = false;
                                                                                      selectingDest = false;
                                                                                      canMove = true;
                                                                                      deploying = false;
                                                                                      destX = 0; destY = 0;
                                                                                      update(A, 1, count, countVEH);}
                                                                                 else if( (( x > 1100 ) && ( x < 1180 ) && ( y > 250 ) && ( y < (80+250) )) && vhOptionsEnable ){
                                                                                      SDL_Surface *info, *repair, *move, *destroy;
                                                                                      vehicle *temp;
                                                                                      info = load_image("rsrc/VSpanel.png");
                                                                                      repair = load_image("rsrc/repair.png");
                                                                                      move = load_image("rsrc/move.png");
                                                                                      destroy = load_image("rsrc/destroy.png");
                                                                                      temp = dynamic_cast<vehicle*>(A[selectedY][selectedX]);
                                                                                      if(temp != 0) {
                                                                                              temp->setrepair(false);
                                                                                              temp->setgascap(temp->getmaxGC());
                                                                                              temp->setwatercap(temp->getmaxWC());
                                                                                      }
                                                                                      apply_surface(680, 165, info, screen);
                                                                                      apply_surface(1100, 165, move, screen);
                                                                                      apply_surface(1100, 250, repair, screen);
                                                                                      apply_surface(1100, 335, destroy, screen);
                                                                                      SDL_FreeSurface(info);
                                                                                      info = TTF_RenderText_Solid( font1, (A[selectedY][selectedX]->printinfoTYPE()).c_str(), textColor );
                                                                                      apply_surface(680, 165, info, screen);
                                                                                      SDL_FreeSurface(info);
                                                                                      info = TTF_RenderText_Solid( font1, (A[selectedY][selectedX]->printinfoWCAP()).c_str(), textColor );
                                                                                      apply_surface(680, 185, info, screen);
                                                                                      SDL_FreeSurface(info);
                                                                                      info = TTF_RenderText_Solid( font1, (A[selectedY][selectedX]->printinfoGCAP()).c_str(), textColor );
                                                                                      apply_surface(680, 205, info, screen);
                                                                                      SDL_FreeSurface(info);
                                                                                      info = TTF_RenderText_Solid( font1, (A[selectedY][selectedX]->printinfoAGE()).c_str(), textColor );
                                                                                      apply_surface(680, 225, info, screen);
                                                                                      SDL_FreeSurface(info);
                                                                                      info = TTF_RenderText_Solid( font1, (A[selectedY][selectedX]->printinfoREPAIR()).c_str(), textColor );
                                                                                      apply_surface(680, 245, info, screen);
                                                                                      SDL_FreeSurface(info);
                                                                                      info = TTF_RenderText_Solid( font1, (A[selectedY][selectedX]->printinfoWATERCONSUMPT()).c_str(), textColor );
                                                                                      apply_surface(680, 265, info, screen);
                                                                                      SDL_FreeSurface(info);
                                                                                      info = TTF_RenderText_Solid( font1, (A[selectedY][selectedX]->printinfoGASCONSUMPT()).c_str(), textColor );
                                                                                      apply_surface(680, 285, info, screen);
                                                                                      SDL_Flip(screen);
                                                                                      SDL_FreeSurface(info); SDL_FreeSurface(move); SDL_FreeSurface(repair); SDL_FreeSurface(destroy);}
                                                                                 else if( (( x > 1100 ) && ( x < 1180 ) && ( y > 335 ) && ( y < (80+335) )) && vhOptionsEnable ){
                                                                                      SDL_Surface *info, *repair, *move, *destroy;
                                                                                      vehicle *temp;
                                                                                      info = load_image("rsrc/VSpanel.png");
                                                                                      repair = load_image("rsrc/repair.png");
                                                                                      move = load_image("rsrc/move.png");
                                                                                      destroy = load_image("rsrc/destroy.png");
                                                                                      temp = dynamic_cast<vehicle*>(A[selectedY][selectedX]);
                                                                                      if(temp != 0) {
                                                                                              temp->setrepair(true);
                                                                                      }
                                                                                      apply_surface(680, 165, info, screen);
                                                                                      apply_surface(1100, 165, move, screen);
                                                                                      apply_surface(1100, 250, repair, screen);
                                                                                      apply_surface(1100, 335, destroy, screen);
                                                                                      SDL_FreeSurface(info);
                                                                                      info = TTF_RenderText_Solid( font1, (A[selectedY][selectedX]->printinfoTYPE()).c_str(), textColor );
                                                                                      apply_surface(680, 165, info, screen);
                                                                                      SDL_FreeSurface(info);
                                                                                      info = TTF_RenderText_Solid( font1, (A[selectedY][selectedX]->printinfoWCAP()).c_str(), textColor );
                                                                                      apply_surface(680, 185, info, screen);
                                                                                      SDL_FreeSurface(info);
                                                                                      info = TTF_RenderText_Solid( font1, (A[selectedY][selectedX]->printinfoGCAP()).c_str(), textColor );
                                                                                      apply_surface(680, 205, info, screen);
                                                                                      SDL_FreeSurface(info);
                                                                                      info = TTF_RenderText_Solid( font1, (A[selectedY][selectedX]->printinfoAGE()).c_str(), textColor );
                                                                                      apply_surface(680, 225, info, screen);
                                                                                      SDL_FreeSurface(info);
                                                                                      info = TTF_RenderText_Solid( font1, (A[selectedY][selectedX]->printinfoREPAIR()).c_str(), textColor );
                                                                                      apply_surface(680, 245, info, screen);
                                                                                      SDL_FreeSurface(info);
                                                                                      info = TTF_RenderText_Solid( font1, (A[selectedY][selectedX]->printinfoWATERCONSUMPT()).c_str(), textColor );
                                                                                      apply_surface(680, 265, info, screen);
                                                                                      SDL_FreeSurface(info);
                                                                                      info = TTF_RenderText_Solid( font1, (A[selectedY][selectedX]->printinfoGASCONSUMPT()).c_str(), textColor );
                                                                                      apply_surface(680, 285, info, screen); 
                                                                                      SDL_Flip(screen);
                                                                                      SDL_FreeSurface(info); SDL_FreeSurface(move); SDL_FreeSurface(repair); SDL_FreeSurface(destroy);
                                                                                      }
                                                                                 else if((x>680)&&(x<(680+80))&&(y>(165+78))&&(y<(165+157))&& deploying) {vehicleSelection = 0; SDL_Surface *info; info = load_image("rsrc/uberinfo.png"); apply_surface(680, 165, NVpanel, screen); apply_surface(680+110, 165+105, info, screen); SDL_Flip(screen); SDL_FreeSurface(info);}
                                                                                 else if((x>680)&&(x<(680+80))&&(y>(165+179))&&(y<(165+259))&& deploying) {vehicleSelection = 1; SDL_Surface *info; info = load_image("rsrc/pyroinfo.png"); apply_surface(680, 165, NVpanel, screen); apply_surface(680+110, 165+210, info, screen); SDL_Flip(screen); SDL_FreeSurface(info);}
                                                                                 else if((x>680)&&(x<(680+80))&&(y>(165+285))&&(y<(165+365))&& deploying) {vehicleSelection = 2; SDL_Surface *info; info = load_image("rsrc/heliinfo.png"); apply_surface(680, 165, NVpanel, screen); apply_surface(680+110, 165+311, info, screen); SDL_Flip(screen); SDL_FreeSurface(info);}
                                                                                 else if((x>680)&&(x<(680+80))&&(y>(165+386))&&(y<(165+467))&& deploying) {vehicleSelection = 3; SDL_Surface *info; info = load_image("rsrc/airinfo.png"); apply_surface(680, 165, NVpanel, screen); apply_surface(680+110, 165+420, info, screen); SDL_Flip(screen); SDL_FreeSurface(info);}
                                                                                 else if((x>(680+210))&&(x<(680+340))&&(y>(165+473))&&(y<(165+500))&& deploying){
                                                                                      mapEnable = true;
                                                                                      selectingDest = true;
                                                                                      SDL_Surface *dest;
                                                                                      dest = load_image("rsrc/dest.png");
                                                                                      apply_surface(680, 165, dest, screen); SDL_Flip(screen);
                                                                                      SDL_FreeSurface(dest);
                                                                                      }
                                                                                 else if((x>680)&&(x<(680+550))&&(y>383)&&(y<165+500) && selectingDest && deploying){
                                                                                      vehicle *temp; temp = dynamic_cast<vehicle*>(A[destY][destX]);
                                                                                      if(temp != 0) delete(A[destY][destX]); //if there was previusly another vehicle in the destination spot, it is deleted
                                                                                      if(vehicleSelection == 0) A[destY][destX] = new ubertank;
                                                                                      else if(vehicleSelection == 1) A[destY][destX] = new pyroschrek;
                                                                                      else if(vehicleSelection == 2) A[destY][destX] = new helitanker;
                                                                                      else if(vehicleSelection == 3) A[destY][destX] = new airtanker;
                                                                                      A[destY][destX] -> setX(destX); A[destY][destX] -> setY(destY);
                                                                                      pause = true;
                                                                                      motionEnable = true;
                                                                                      clickEnable = true;
                                                                                      mapEnable = false;
                                                                                      vhOptionsEnable = false;
                                                                                      selectingDest = false;
                                                                                      canMove = true;
                                                                                      deploying = false;
                                                                                      destX = 0; destY = 0;
                                                                                      update(A, 1, count, countVEH);}
                                                                                 else if((x>(680+420))&&(x<(680+500))&&(y>165)&&(y<165+335) && selectingDest && arson){
                                                                                      arsoning(A, destX, destY);
                                                                                      pause = true;
                                                                                      motionEnable = true;
                                                                                      clickEnable = true;
                                                                                      mapEnable = false;
                                                                                      vhOptionsEnable = false;
                                                                                      selectingDest = false;
                                                                                      canMove = true;
                                                                                      deploying = false;
                                                                                      arson = false;
                                                                                      destX = 0; destY = 0;
                                                                                      update(A, 1, count, countVEH);
                                                                                      }
                                                                                       }
                                                                                   }
                                                                               }} SDL_FreeSurface(panelVSinfo); SDL_FreeSurface(panelNVinfo); SDL_FreeSurface(panelARinfo); SDL_FreeSurface(black); SDL_FreeSurface(VSpanel);SDL_FreeSurface(ARpanel);/*SDL_FreeSurface(info);*/}
                                 }
                                 SDL_WM_SetCaption( "ProjectFire Visual", NULL );
                                   }
    countEND = 0;
    for(int m = 0; m<=(S-1); m++){
            for(int n = 0; n<=(S-1); n++){
                    if(A[m][n] -> isOnFire()) countEND++; 
                    }}
    
    if(countEND == S * S){cout << "Oh no!!! All the world is on fire... THE END."; break;} //if all blocks are on fire, the simulation stops
    }
    
    for(int m = 0; m<=(S-1); m++){     //clear the memory--- CLEANUP CODE
            for(int n = 0; n<=(S-1); n++) {
                    vehicle *temp;
                    temp = dynamic_cast<vehicle*>(A[m][n]);
                    if(temp != 0){delete(A[m][n]); A[m][n] = x1;}
                    }}
    for(int m = 0; m < fpool.size(); m++) delete (fpool[m]);
    delete (x1);
    delete (b);
    SDL_FreeSurface( screen );
    SDL_FreeSurface( message );
    SDL_FreeSurface( baseinfo );
    SDL_Surface( noveh );
    TTF_Quit();
    SDL_Quit(); 
    return EXIT_SUCCESS;
}
