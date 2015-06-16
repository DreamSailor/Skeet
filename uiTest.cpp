/****************************************
 * UI TEST
 * Just a simple program to test the user
 * interface consisting of uiDraw and uiInteract
 ***************************************/


#include "point.h"
#include "uiInteract.h"
#include "uiDraw.h"
using namespace std;

/************************************
 * Test structure to capture the ball
 * that I will move around the screen
 ***********************************/
class Ball
{
public:
   Ball() : sides(3), rotation(20), pt(), score(1) { }

   // this is just for test purposes.  Don't make member variables public!
   Point pt;          // location of the polygon on the screen
   int sides;         // number of sides in the polygon.  Initially three
   int rotation;      // the angle or orientation of the polygon
   int score;
};

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface *pUI, void * p)
{
   Ball * pBall = (Ball *)p;  // cast the void pointer into a known type
   Point point;
   point.setX(point.getXMax()-45);
   point.setY(point.getYMin()+20);
  
   

   // move the polygon
   if (pUI->isRight())
      pBall->pt.addX(1);
   if (pUI->isLeft())
      pBall->pt.addX(-1);
   if (pUI->isUp())
   {
      pBall->pt.addY(1);
     // drawNumber(point, pBall->score++);
      
   }
   if (pUI->isDown())
      pBall->pt.addY(-1);
   
   // use the space bar to change the number of sides.
   if (pUI->isSpace())
      pBall->sides++;
   if (pBall->sides == 20)
      pBall->sides = 3;

   // rotate constantly
      pBall->rotation++;
      if(pBall->score == 32,000)
         pBall-score = 0;
      
      
      drawNumber(point, pBall->score++);
   //pBall->pt.addX(1);
   
   // draw
   drawPolygon(pBall->pt, /*position*/
              20, /* radius */
              pBall->sides /*segments*/,
              pBall->rotation /*rotation*/);
}

// set the bounds of the drawing rectangle
float Point::xMin = -200.0;
float Point::xMax =  200.0;
float Point::yMin = -200.0;
float Point::yMax =  200.0;

/*********************************
 * Main is pretty sparse.  Just initialize
 * my ball type and call the display engine.
 * That is all!
 *********************************/
int main(int argc, char ** argv)
{
   Interface ui(argc, argv, "Triangle");    // initialize OpenGL
   Ball ball;                           // initialize the game state
   ui.run(callBack, &ball);             // set everything into action

   return 0;
}
