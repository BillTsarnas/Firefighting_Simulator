#ifndef CLASSFILE_H

#define CLASSFILE_H

#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
using namespace std;
const int S = 25;

class worldobj{
      int x; // x coordinate
      int y; // y coordinate
      bool alreadyMoved;
      bool occupied;
      bool onfire;
      public:
      worldobj();
      ~worldobj();
      void setX(int x);
      void setY(int y);
      int getX();
      int getY();
      bool isMoved();
      bool isOccupied();
      bool isOnFire();
      void setMoved(bool m);
      void setOccupied(bool o);
      void setOnFire(bool s);
      virtual string geticon();
      virtual void move(worldobj *A[S][S], worldobj *x, worldobj *f, worldobj *b);
      virtual void ageup(worldobj *A[S][S], worldobj *e, worldobj *b);
      virtual void setage(int x);
      virtual string printinfo();
      virtual string printinfoTYPE();
      virtual string printinfoWCAP();
      virtual string printinfoGCAP();
      virtual string printinfoAGE();
      virtual string printinfoREPAIR();
      virtual string printinfoWATERCONSUMPT();
      virtual string printinfoGASCONSUMPT();
      };

class fire: public worldobj{
      public:
      fire();
      ~fire();
      string geticon();
      void move(worldobj *A[S][S], worldobj *x, worldobj *f, worldobj *b);
      };
      
class base: public worldobj{
      public:
      base();
      ~base();
      string geticon();
      void mendAll(worldobj *A[S][S], worldobj *x, worldobj *b);
      };
      
class vehicle: public worldobj{
      int watercap; //water tank capacity
      int gascap;   //gas tank capacity
      int watercon; //water consumption per water throw
      int limit; //determines how many fires can be fought per move
      int gascon;   //gas consumption per move
      int age;  //a vehicle's age is increased by 1 each time unit
      int speed; //determines the distance travelled (per time unit)
      bool needsrepair; //if true, the vehicle cannot move or throw water!
      int maxWC; //determines the maximum water capacity
      int maxGC; //determines the maximum gas capacity
      int waterconsumpted; //determines the overall water consumpted
      int gasconsumpted; //determines the overall gas consumpted
      public:
      vehicle(int wc, int mw, int gc, int mg, int wco, int gco, int a, int sp, bool r);
      ~vehicle();
      int getwatercap();
      void setwatercap(int x);
      int getmaxWC();
      int getmaxGC();
      int getgascap();
      void setgascap(int x);
      void setage(int x);
      int getage();
      int getwatercon();
      int getlimit();
      int getgascon();
      int getspeed();
      int getwaterconsumpted();
      void setwaterconsumpted(int x);
      int getgasconsumpted();
      void setgasconsumpted(int x);
      void setrepair(bool b);
      bool getrepair();
      string printinfo();
      string printinfoTYPE();
      string printinfoWCAP();
      string printinfoGCAP();
      string printinfoAGE();
      string printinfoREPAIR();
      string printinfoWATERCONSUMPT();
      string printinfoGASCONSUMPT();
      void move(worldobj *A[S][S], worldobj *x, worldobj *f, worldobj *b);
      void seekFire(worldobj *A[S][S], worldobj *e, worldobj *f, worldobj *b);
      void ageup(worldobj *A[S][S], worldobj *e, worldobj *b);
      };

class groundunit:public vehicle{
      int tirestr; //TIRE STRENGTH
      public:
      groundunit(int wc, int mw, int gc, int mg, int wco, int gco, int a, int sp, bool r);
      ~groundunit();
      int gettstr();
      void settstr(int x);
      };

class pyroschrek:public groundunit{
      int idp;
      public:
      static int n; //number of pyroschreks created
      pyroschrek();
      ~pyroschrek();
      string geticon();
      string printinfo();
      string printinfoTYPE();
      };
      
class ubertank:public groundunit{
      int idu;
      public:
      static int nu; //number of ubertanks created
      ubertank();
      ~ubertank();
      string geticon();
      string printinfo();
      string printinfoTYPE();
      };

class airunit:public vehicle{  
      int aerodynamics;
      public:
      airunit(int wc, int mw, int gc, int mg, int wco, int gco, int a, int sp, bool r);
      ~airunit();
      int getaero();
      void setaero(int x);
      };
      
class helitanker:public airunit{
      int idh;
      public:
      static int nh; //number of helitankers created
      helitanker();
      ~helitanker();
      string geticon();
      string printinfo();
      string printinfoTYPE();
      };
      
class airtanker:public airunit{
      int ida;
      public:
      static int na; //number of airtankers created
      airtanker();
      ~airtanker();
      string geticon();
      string printinfo();
      string printinfoTYPE();
      };

#endif
      
