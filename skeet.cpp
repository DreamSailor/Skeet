/***********************************************************************
* Program:
*    Project 2, Skeet            
*    Brother McCracken, CS165
* Author:
*    Jeffry Simpson, Samuel Koontz
* Summary: 
*    The driver program for the game of skeet
*
*    Estimated:  0.0 hrs   
*    Actual:     0.0 hrs
*      Please describe briefly what was the most difficult part.
************************************************************************/

#include "point.h"
#include "uiInteract.h"
#include "uiDraw.h"
#include <stdio.h>
#include <math.h>

#define PI 3.14157
#define SKEETRADIUS 10
#define MISSLERADIUS 2 
#define MAXSHOTS 5

using namespace std; 

// set the bounds of the game

float Point::xMin = -200.0;
float Point::xMax =  200.0;
float Point::yMin = -200.0;
float Point::yMax =  200.0;

const int bulletSpeed = 10;      //Speed of the projectile
static int delayCnt = 30;  //Delay counter
static int boomCnt = 0;           //Length of time for explosion
const int boomSpeed = 2;

/************************************
 * Skeet class
 ***********************************/
class Skeet
{
   public:
      Skeet();          
      void update(int left, int right, bool spacebar);
      bool checkHit (Point * rhs);
      void draw();
      
   private:      
      Point pt[5];         //bullets     
      Point missiles[5];   //Missile icons
      Point skeet;         // skeet 
      Point gun;           // Gun
      Point boomStart;    //skeet explosion starting point
      Point boom[15];     //explosive fragments
      int shots;          //shots taken
      int hit;            //Birds hit
      int total;          //Total Birds
      float dx;     // horizontal velocity of the skeet
      float dy;     // vertical velocity of the skeet
      bool  yUpper;   //flag used to indicate upper or lower half of the screen
      
      bool  debug;    //for debug options
      int refresh;      // screen refresh for debug
      
};

/***************************************************
 * Skeet :: CONSTRUCTOR
 * Give the skeet a random vertical velocity and set
 * the positions of everything else.
 ***************************************************/
Skeet::Skeet() : pt(), 
                 hit(0),
                 total(0), 
                 refresh(0), 
                 debug(false)
{ 
   // set the skeet start position
   if (debug)
      cout << "Calling Constructor\n";
   
   //Set X starting position and speed
   skeet.setX(skeet.getXMin() + 1.0);  
   dx = (float)random(3,6);             
                                       
   //Set Y starting position and Speed
   skeet.setY((float)random(skeet.getYMin(), skeet.getYMax())); 
   if (skeet.getY() > 0)  // 0 == middle of the screen
   {
      yUpper = true;
      dy = (float)random(-4,0);//send downward if starting in upper half
   }
   else
   {
      yUpper = false;
      dy = (float)random(0,4);//send upward if we start low.
   }

   //Set up the Gun
   gun.setX(gun.getXMax());
   gun.setY(gun.getYMin());
   gun.angle = 45;
   gun.length = 120;
   shots = 0;
}

/********************************************
 * Skeet :: update
 * Move the elements on the screen 
 *******************************************/
void Skeet::update(int left, int right, bool spacebar)
{

   //------------Skeet movement section -----------
   
   if (debug)      //update debug counter on the lower left side of screen
      refresh++;  //tracks we are doing something
     
   if (skeet.isDead()) //Check if the skeet  dead
   {

      delayCnt--; // Don't do anything while we delay
      if (delayCnt <= 0)
      {
         for (int i = 0; i < shots; i++)
         {
            pt[i].kill();
            shots = 0;
         }
         
         delayCnt = random(1,30);   //Reset the Delay for next time

         if (debug)
            cout << "Entering the Dead Zone next delay count = " 
                 << delayCnt 
                 << endl;


         skeet.resurrect();         //Reset the flag

           //Set X starting position and speed
         skeet.setX(skeet.getXMin() + 1.0);  //Reset X to left side of screen
         dx = (float)random(3,6);  // set the  Skeet velocity.  
          
           //starting vertical location
         skeet.setY((float)random(skeet.getYMin(), skeet.getYMax())); 

         if (skeet.getY() > 0)   //Check if upper or lower
         {
            yUpper = true;
            dy = (float)random(-4,0);//send downward if start in upper half
         }
         else
         {
            yUpper = false;
            dy = (float)random(0,4);//send upward if we start low.
         }

         if (debug)
         {
            cout << "Starting Y/X = " 
                 << skeet.getY() 
                 << "/" << skeet.getX() 
                 << endl;
            cout << "Speed Y/X = "  
                 << dy 
                 << ":"
                 << dx
                 << endl;
         }
      }
      
   }
   
   //Check if we are and the right edge of the window or off the top or bottom
   if (skeet.getX() + dx >= skeet.getXMax() 
       || skeet.getY() + dy >= skeet.getYMax() 
       || skeet.getY() + dy <= skeet.getYMin()
      )
   {

     //If we are out of bounds and haven't already killed the bird kill it now.
      if (!skeet.isDead())   
      {
         if (debug)
            cout << "Setting Skeet to dead\n";
         skeet.kill();                     //Set flag to not draw
         total++;                         //advance count of total skeets
      }
         
   }

   else  //Move the skeet forward 
   {
      
      skeet.addX(dx);      
      skeet.addY(dy);   

   }
   //------------Gun movement section -----------
   
   if (right && gun.angle > 1)
      gun.angle -= 5;
   if (left && gun.angle < 89)
      gun.angle += 5;
   if (spacebar && shots <= 4)
   {
      shots++;
      pt[shots - 1].resurrect();
      pt[shots - 1].
                    setX(-(60 * (sin(gun.getAngle() * PI / 180)))
                    + gun.getX());
      pt[shots - 1].
                    setY((60 * (cos(gun.getAngle() * PI / 180)))
                    + gun.getY());
      pt[shots - 1].setAngle(gun.getAngle());
      if (debug)
      {
         cout << "Add Shot " 
              << shots - 1 
              << " X,Y = " 
              << pt[shots - 1].getX() 
              << "," << pt[shots - 1].getY() 
              << endl;
        
      }
              
   }   

   //------------Shot movement section -----------
   for (int i = 0; i < shots; i++)
   {
      
      pt[i].addX((-bulletSpeed) * sin(pt[i].getAngle() * PI / 180));
      pt[i].addY((bulletSpeed) * cos(pt[i].getAngle() * PI / 180));

      if (checkHit(&pt[i])) //hit skeet
      {
         if (debug)
            cout << "Hit the bird";
         boomCnt = 60;
         for (int j = 0; j < 15; j++)
         {
            boom[j].resurrect();
            boom[j].setX(pt[i].getX());
            boom[j].setY(pt[i].getY());
            boom[j].setAngle(random(0, 360));
         }
         skeet.kill();
         hit++;
         total++;
         for (int i = 0; i < shots; i++)
         {
            pt[i].kill();
            shots = 0;
         }
      }
   } 
//boom   
   if (boomCnt > 0)
   {   
      for (int i = 0; i < 15; i++)
      {
         boom[i].addX((boomSpeed) * sin(boom[i].getAngle() * PI / 180));
         boom[i].addY((boomSpeed) * cos(boom[i].getAngle() * PI / 180));
         if (boomCnt == 1)
            boom[i].kill();
      }
   
      boomCnt--;
   }
}

/********************************************
 * Skeet :: checkHit
 * Determines if the point is close enough to the skeet 
 * to be a hit 
 *******************************************/
bool Skeet::checkHit (Point * rhs)
{
   if ((std::abs(skeet.getX() - rhs->getX()) <= SKEETRADIUS       &&
        std::abs(skeet.getY() - rhs->getY()) <= SKEETRADIUS)      ||
       (std::abs(skeet.getX() - rhs->getX()) <= MISSLERADIUS      &&
        std::abs(skeet.getY() - rhs->getY()) <= MISSLERADIUS ))
      return true;
   else
      return false;
}


/*************************************************
 * Skeet : DRAW
 * Draw the stuff
 ************************************************/
void Skeet::draw()
{
   // draw the ball
   if (!skeet.isDead())
   {  
      drawCircle(skeet, SKEETRADIUS);
   }

   //draw the missiles
   if (shots)
   {
      for (int i = 0; i < shots; i++) 
      {

         if (!pt[i].isDead())
         {
            drawRect(pt[i], 5, 15, pt[i].angle);
            drawDot(pt[i]); 
         }
      
      }
   }

   //draw explosion
   if (boomCnt)
   {   
      for (int i = 0; i < 15; i++)
      {
         if (!boom[i].isDead())
         {
            drawPolygon(boom[i], 8, 3, (random(0,360)));
         }
      }
   }      

   //draw the gun
   drawRect(gun, 10, gun.length, gun.angle);
   
   // draw the score
   Point drawScore(skeet.getXMin() + 15, skeet.getYMax() - 15);
   drawNumber(drawScore, hit);

   // draw the label for the score
   Point drawScoreLabel(skeet.getXMin() + 12, skeet.getYMax() - 45);
   drawText(drawScoreLabel, "HITS");
   
   //Draw count of MISSED skeets
   Point drawTotalSkeets(skeet.getXMax() - 45, skeet.getYMax() - 15);
   drawNumber(drawTotalSkeets, total);

   // draw the label for the MISSED skeets
   Point drawTotalLabel(skeet.getXMax() - 85, skeet.getYMax() - 45);
   drawText(drawTotalLabel, "TOTAL BIRDS");

   //draw shots remaining
   for (int i = 0; i < (5 - shots); i++)
   {
      missiles[i].setX(skeet.getXMax() - 68 - (i * 18));
      missiles[i].setY(skeet.getYMin() + 15);
      drawRect(missiles[i], 5, 15, 90);
      drawDot(missiles[i]); 
   }
   
   //draw explosion

   //draw refresh
   if (debug)
   {
      Point pointDebug(skeet.getXMin() + 5, skeet.getYMin() + 15);
      drawNumber(pointDebug, refresh); 
   }
}

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface *pUI, void * p)
{
   
 
   
   Skeet * pSkeet = (Skeet *)p;  // cast the void pointer into a known type
     
   // advance the ball
   pSkeet->update(pUI->isLeft(), pUI->isRight(), pUI->isSpace());
 
   // draw it
   pSkeet->draw();
}
   
/********************************************
 * Main
 * Main driver function
 *******************************************/
int main(int argc, char** argv)
{

   Interface ui(argc, argv, "Skeet Shooter");    // initialize OpenGL
   Skeet skeet;                           // initialize the game state
   ui.run(callBack, &skeet);             // set everything into action

   return 0;
}

