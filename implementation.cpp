#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include "classfile.h"
#include "time.h"
using namespace std;


worldobj::worldobj(){this->x = 0; this->y = 0; alreadyMoved = false; occupied = false; onfire = false;}
worldobj::~worldobj(){}
void worldobj::setX(int x){this->x  = x;}
void worldobj::setY(int y){this->y = y;}
int worldobj::getX(){return x;}
int worldobj::getY(){return y;}
bool worldobj::isMoved(){return alreadyMoved;}
bool worldobj::isOccupied(){return occupied;}
bool worldobj::isOnFire(){return onfire;}
void worldobj::setMoved(bool m){alreadyMoved = m;}
void worldobj::setOccupied(bool o){occupied = o;}
void worldobj::setOnFire(bool s){onfire = s;}
string worldobj::geticon(){return ("rsrc/worldobj.bmp");}
void worldobj::move(worldobj *A[S][S], worldobj *x, worldobj *f, worldobj *b){}
void worldobj::ageup(worldobj *A[S][S], worldobj *e, worldobj *b){}
void worldobj::setage(int x){}
string worldobj::printinfo(){return("This isn't a vehicle!");}
string worldobj::printinfoTYPE(){}
string worldobj::printinfoWCAP(){}
string worldobj::printinfoGCAP(){}
string worldobj::printinfoAGE(){}
string worldobj::printinfoREPAIR(){}
string worldobj::printinfoWATERCONSUMPT(){}
string worldobj::printinfoGASCONSUMPT(){}

fire::fire():worldobj(){setOccupied(true); setOnFire(true);}
fire::~fire(){}
string fire::geticon(){return ("rsrc/fire.bmp");}
void fire::move(worldobj *A[S][S], worldobj *x, worldobj *f, worldobj *b){
     if(isMoved() == false){
                     int r;
                     int oldX, oldY;
                     oldX = this->getX();
                     oldY = this->getY();
                     srand(time(NULL));
                     r = rand() % 4;
                     if(r == 0) this->setY((this->getY()) - 1);
                     else if(r == 1) this->setX((this->getX()) + 1);
                     else if(r == 2) this->setY((this->getY()) + 1);
                     else if(r == 3)this->setX((this->getX()) - 1);
                     while((((this->getX()) > (S-1)) || ((this->getY()) > (S-1)) || ((this->getY()) < 0)  || ((this->getX()) < 0)) || (A[this->getY()][this->getX()]->isOnFire()) ){ 
                                           this->setX(oldX); this->setY(oldY); //anati8entai oi times x,y pou p eixe prin ypologistoun ta lan8asmena x,y
                                           //srand(time(NULL));
                                           /*-------------------------------------------------------------------------*/
                                           bool cantGoUp = false;
                                           bool cantGoDown = false;
                                           bool cantGoRight = false;
                                           bool cantGoLeft = false;
                                           int x, y;
                                           x = this->getX();
                                           y = this->getY() - 1;
                                           if(y<0)cantGoUp = true;
                                           if(cantGoUp == false){
                                                       if(A[y][x]->isOnFire()) cantGoUp = true;}
                                           x = this->getX() + 1;
                                           y = this->getY();
                                           if((x>(S-1))) cantGoRight = true;
                                           if(cantGoRight == false){
                                                       if(A[y][x]->isOnFire()) cantGoRight = true;}
                                           x = this->getX();
                                           y = this->getY() + 1;
                                           if((y>(S-1))) cantGoDown = true;
                                           if(cantGoDown == false){
                                                       if(A[y][x]->isOnFire()) cantGoDown = true;}
                                           x = this->getX() - 1;
                                           y = this->getY();
                                           if(x<0) cantGoLeft = true;
                                           if(cantGoLeft == false){
                                                         if(A[y][x]->isOnFire()) cantGoLeft = true;}
                                           if(cantGoUp && cantGoDown && cantGoRight && cantGoLeft){
                                                       do{
                                                       r = rand() % S;
                                                       this->setX(r);
                                                       r = rand() % S;                                        
                                                       this->setY(r);
                                                       }while(A[this->getY()][this->getX()]->isOnFire());
                                                       A[this->getY()][this->getX()]=this; /*!!!!!!!!!!!!*/
                                                       break;} //when there is nowhere for the fire to go...
                                           r = rand() % 4;
                                           if(r == 0) this->setY((this->getY()) - 1);
                                           else if(r == 1) this->setX((this->getX()) + 1);
                                           else if(r == 2) this->setY((this->getY()) + 1);
                                           else if(r == 3)this->setX((this->getX()) - 1);}
                     vehicle *temp; temp = dynamic_cast<vehicle*>(A[this->getY()][this->getX()]);
                     if(temp != 0) delete(A[this->getY()][this->getX()]);
                     A[this->getY()][this->getX()] = this; /*!!!!!!!!!!!!!!!!!!*/
                     this->setMoved(true);
                                           }}
     

base::base():worldobj(){}
base::~base(){}
string base::geticon(){return "rsrc/base.bmp";}
void base::mendAll(worldobj *A[S][S], worldobj *x, worldobj *b){
     for(int i = 0; i<=(S-1); i++){
           for(int j = 0; j<=(S-1); j++){
                 vehicle *temp;
                 temp = dynamic_cast<vehicle*>(A[i][j]);
                 if(temp != 0){
                         if(temp->getrepair()){
                            temp->setwatercap(temp->getmaxWC()); /*replenish*/
                            temp->setgascap(temp->getmaxGC());
                            temp->setrepair(false); /*repair*/
                            if(((j>=11)&&(j<=17)) && ((i>=11)&&(i<=17))) A[i][j] = b;
                            else A[i][j] = x;
                            bool found = false;
                            for(int k = 11; k<=17; k++){
                                  for(int l = 11; l<=17; l++){
                                        if((A[k][l]->isOccupied()) == false) {temp->setX(l); temp->setY(k); A[k][l] = temp; found = true; break;}}
                                  if(found == true)break;}
                                  }}
                            } }
                            }

vehicle::vehicle(int wc, int mw, int gc, int mg, int wco, int gco, int a, int sp, bool r):worldobj(){
                     watercap = wc; gascap=  gc; maxWC = mw; maxGC = mg;
                     limit = wco; gascon = gco; 
                     age = a; speed = sp; 
                     needsrepair = r; setOccupied(true); waterconsumpted=0; gasconsumpted=0;}
vehicle::~vehicle(){}
int vehicle::getwatercap(){return watercap;}
void vehicle::setwatercap(int x){watercap = x;}
int vehicle::getmaxWC(){return maxWC;}
int vehicle::getmaxGC(){return maxGC;}
int vehicle::getgascap(){return gascap;}
void vehicle::setgascap(int x){gascap = x;}
void vehicle::setage(int x){age = x;}
int vehicle::getage(){return age;}
int vehicle::getwatercon(){return watercon;}
int vehicle::getlimit(){return limit;}
int vehicle::getgascon(){return gascon;}
int vehicle::getspeed(){return speed;}
int vehicle::getwaterconsumpted(){return waterconsumpted;}
void vehicle::setwaterconsumpted(int x){ waterconsumpted = x; }
int vehicle::getgasconsumpted(){return gasconsumpted;}
void vehicle::setgasconsumpted(int x){ gasconsumpted = x; }
void vehicle::setrepair(bool b){needsrepair = b;}
bool vehicle::getrepair(){return needsrepair;}
string vehicle::printinfo(){
                 stringstream ss;
                 ss << "water capacity: " << this->getwatercap() << "\n" << "gas capacity: " << this->getgascap()
                 << "\n" << "age: " << this->getage() << "\n" << "needs repair? " << ((this->getrepair())? "yes":"no") << "\n";
                 return ss.str();
                 }
string vehicle::printinfoTYPE(){}
string vehicle::printinfoWCAP(){stringstream ss; ss << "water capacity: " << this->getwatercap(); return ss.str(); }
string vehicle::printinfoGCAP(){stringstream ss; ss << "gas capacity: " << this->getgascap(); return ss.str();}
string vehicle::printinfoAGE(){stringstream ss; ss << "age: " << this->getage(); return ss.str();}
string vehicle::printinfoREPAIR(){stringstream ss; ss <<  "needs repair? " << ((this->getrepair())? "yes":"no"); return ss.str();}
string vehicle::printinfoWATERCONSUMPT(){stringstream ss; ss << "water consumpted so far: " << this->getwaterconsumpted(); return ss.str();}
string vehicle::printinfoGASCONSUMPT(){stringstream ss; ss << "gas consumpted so far: " << this->getgasconsumpted(); return ss.str();}
void vehicle::move(worldobj *A[S][S], worldobj *x, worldobj *f, worldobj *b){
     if((isMoved() == false) && (getrepair() == false)){
                     worldobj *temp;
                     int r;
                     int oldX, oldY;
                     oldX = this->getX();
                     oldY = this->getY();
                     temp = A[this->getY()][this->getX()];
                     if(((oldX>=11)&&(oldX<=17)) && ((oldY>=11)&&(oldY<=17))) A[oldY][oldX] = b;
                     else A[this->getY()][this->getX()] = x;
                     //srand(time(NULL));
                     r = rand() % 4;
                     if(r == 0) this->setY((this->getY()) - (this->getspeed()));
                     else if(r == 1) this->setX((this->getX()) + (this->getspeed()));
                     else if(r == 2) this->setY((this->getY()) + (this->getspeed()));
                     else if(r == 3)this->setX((this->getX()) - (this->getspeed()));
                     while((((this->getX()) > (S-1)) || ((this->getY()) > (S-1)) || ((this->getY()) < 0)  || ((this->getX()) < 0)) || (A[this->getY()][this->getX()]->isOccupied()) ){ 
                                           this->setX(oldX); this->setY(oldY); //anati8entai oi times x,y pou p eixe prin ypologistoun ta lan8asmena x,y
                                           //srand(time(NULL));
                                           r = rand() % 4;
                                           if(r == 0) this->setY((this->getY()) - (this->getspeed()));
                                           else if(r == 1) this->setX((this->getX()) + (this->getspeed()));
                                           else if(r == 2) this->setY((this->getY()) + (this->getspeed()));
                                           else if(r == 3)this->setX((this->getX()) - (this->getspeed()));}
                     A[this->getY()][this->getX()] = temp;
                     this->setgascap((this->getgascap()) - (this->getgascon())); //katanalwnontai kaysima
                     this->setgasconsumpted((this->getgasconsumpted()) + (this->getgascon()));
                     this->setMoved(true);
                     this->seekFire(A, x, f, b);
                     }
     }
     
     
void vehicle::seekFire(worldobj *A[S][S], worldobj *e, worldobj *f, worldobj *b){
     int x, y;
     int encountered = 0;
     x = (this->getX()) + 1; //seek right
     y = this->getY();
     if(( (x<=(S-1))&&(y<=(S-1))&&(x>0)&&(y>0) ) && (A[y][x]->isOnFire()) && (encountered < (this->getlimit())) && (this->getwatercap()>0) ) {
          setwatercap(getwatercap() - 5); 
          this->setwaterconsumpted((this->getwaterconsumpted()) + 5);  
          if(((x>=11)&&(x<=17)) && ((y>=11)&&(y<=17)))A[y][x] = b;
          else A[y][x] = e; 
          encountered++;}
     x = (this->getX()) - 1; //seek left
     y = this->getY();
     if(( (x<=(S-1))&&(y<=(S-1))&&(x>0)&&(y>0) ) && (A[y][x]->isOnFire()) && (encountered < (this->getlimit())) && (this->getwatercap()>0) ) {
          setwatercap(getwatercap() - 5);   
          this->setwaterconsumpted((this->getwaterconsumpted()) + 5); 
          if(((x>=11)&&(x<=17)) && ((y>=11)&&(y<=17)))A[y][x] = b;
          else A[y][x] = e; 
          encountered++;}
     x = (this->getX()); //seek down
     y = this->getY() + 1;
     if(( (x<=(S-1))&&(y<=(S-1))&&(x>0)&&(y>0) ) && (A[y][x]->isOnFire()) && (encountered < (this->getlimit())) && (this->getwatercap()>0) ) {
          setwatercap(getwatercap() - 5); 
          this->setwaterconsumpted((this->getwaterconsumpted()) + 5);   
          if(((x>=11)&&(x<=17)) && ((y>=11)&&(y<=17)))A[y][x] = b;
          else A[y][x] = e; 
          encountered++;}
     x = (this->getX()); //seek up
     y = this->getY() - 1;
     if(( (x<=(S-1))&&(y<=(S-1))&&(x>0)&&(y>0) ) && (A[y][x]->isOnFire()) && (encountered < (this->getlimit())) && (this->getwatercap()>0) ) {
          setwatercap(getwatercap() - 5);   
          this->setwaterconsumpted((this->getwaterconsumpted()) + 5); 
          if(((x>=11)&&(x<=17)) && ((y>=11)&&(y<=17)))A[y][x] = b;
          else A[y][x] = e; 
          encountered++;}
     if((getwatercap() <= 0) || (getgascap() <=0)) setrepair(true);
     }
     
void vehicle::ageup(worldobj *A[S][S], worldobj *e, worldobj *b){
     setage(getage()+1);
     if((getage() == 25) || (getage() == 35) || (getage() == 40) || (getage() == 45))setrepair(true);
     else if(age == 50){ /*at the age of 50 the vehicle is deleted!*/
          if(((getX()>=11)&&(getX()<=17)) && ((getY()>=11)&&(getY()<=17))) A[getY()][getX()] = b;
          else A[getY()][getX()] = e;
          delete(this);}
     }
          

groundunit::groundunit(int wc, int mw, int gc, int mg, int wco, int gco, int a, int sp, bool r):vehicle(wc, mw, gc, mg, wco, gco, a, sp, r){}
groundunit::~groundunit(){}
int groundunit::gettstr(){ return tirestr; }
void groundunit::settstr(int x){ tirestr = x; }

int pyroschrek::n = 0;
pyroschrek::pyroschrek():groundunit(50, 50, 100, 100, 1, 5, 0, 2, false){idp = ++n; settstr(50);}
pyroschrek::~pyroschrek(){}
string pyroschrek::geticon(){return "rsrc/pyro.bmp";}
string pyroschrek::printinfo(){
       stringstream ss;
       ss << "\nVehicle Type: Pyroshrek "<< idp <<"\n"<< this->vehicle::printinfo();
       return ss.str();}
string pyroschrek::printinfoTYPE(){stringstream ss; ss << "Vehicle Type: PYROSCHREK " << idp; return ss.str();}

int ubertank::nu = 0;
ubertank::ubertank():groundunit(100, 100, 100, 100, 2, 5, 0, 1, false){idu = ++nu; settstr(100);}
ubertank::~ubertank(){}
string ubertank::geticon(){return "rsrc/uber.bmp";}
string ubertank::printinfo(){
       stringstream ss;
       ss << "\nVehicle Type: Ubertank " << idu << "\n" << this->vehicle::printinfo();
       return ss.str();}
string ubertank::printinfoTYPE(){stringstream ss; ss << "Vehicle Type: UBERTANK " << idu; return ss.str();}

airunit::airunit(int wc, int mw, int gc, int mg, int wco, int gco, int a, int sp, bool r):vehicle(wc, mw, gc, mg, wco, gco, a, sp, r){}
airunit::~airunit(){}
int airunit::getaero(){ return aerodynamics; }
void airunit::setaero(int x){ aerodynamics = x; }

int helitanker::nh = 0;
helitanker::helitanker():airunit(5, 5, 100, 100, 1, 5, 0, 1, false){idh = ++nh; setaero(50);}
helitanker::~helitanker(){}
string helitanker::geticon(){return "rsrc/heli.bmp";}
string helitanker::printinfo(){
     stringstream ss;
     ss << "\nVehicle Type: Helitanker " << idh << "\n" << this->vehicle::printinfo();
     return ss.str();}
string helitanker::printinfoTYPE(){stringstream ss; ss << "Vehicle Type: HELITANKER " << idh; return ss.str();}

int airtanker::na = 0;
airtanker::airtanker():airunit(10, 10, 100, 100, 1, 5 , 0, 2, false){ida = ++na; setaero(100);}
airtanker::~airtanker(){}
string airtanker::geticon(){return "rsrc/air.bmp";}
string airtanker::printinfo(){
       stringstream ss;
       ss << "\nVehicle Type: Airtanker " << ida << "\n" << this->vehicle::printinfo();
       return ss.str();}
string airtanker::printinfoTYPE(){stringstream ss; ss << "Vehicle Type: AIRTANKER " << ida; return ss.str();}
