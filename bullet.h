/***********************************************************************
 * Header File:
 *    Bullet : The representation of a position on the screen
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a location on the screen, including
 *    the location and the bounds.
 ************************************************************************/

#ifndef BULLET_H
#define BULLET_H

#include <iostream> // needed for insertion and extraction operator
#include <stdio.h>
#include <math.h>
#define PI 3.14159265
/*********************************************
 * BULLET
 * A single position.  
 *********************************************/
class Bullet
{
public:
   // constructors
   Bullet()            : x(0.0), y(0.0),
                        check(false), dead(false), wrap(false), angle(0.0)   {}
   Bullet(bool check)  : x(0.0), y(0.0),
                        check(check), dead(false), wrap(false), angle(0.0)   {}
   Bullet(float x, float y);
   Bullet(const Bullet & bullet) { *this = bullet; }

   // getters
   float getX()       const { return x;              }
   float getY()       const { return y;              }
   bool  getCheck()   const { return check;          }
   bool  isDead()     const { return dead;           }
   float getXMin()    const { return xMin;           }
   float getXMax()    const { return xMax;           }
   float getYMin()    const { return yMin;           }
   float getYMax()    const { return yMax;           }
   bool  getWrap()    const { return wrap;           }
   float getAngle()   const { return angle;          }
   
   // setters
   void setX(float x);
   void setY(float y);
   void setAngle(int angle);
   void addX(float dx)      { setX(getX() + dx);     }
   void addY(float dy)      { setY(getY() + dy);     }
   void setCheck(bool f)    { check = f;             }
   void setWrap(bool f)     { wrap = f;              }
   void kill()              { dead = true;           }
   void resurrect()         { dead = false;          }
    
   void advance(int speed)
   {
      addX( (float) ((sin (angle * PI / 180)) * speed));
      addY( (float) ((cos (angle * PI / 180)) * speed));
   };
   const Bullet & operator = (const Bullet & rhs);
   

private:
   float x;           // horizontal position
   float y;           // vertical position
   float angle;       // angle of shot
   
   bool  check;       // do bounds checking
   bool  dead;        // have we exceed our bounds?
   bool  wrap;        // do we wrap around the edge?
   static float xMin; // minimum extent of the x position
   static float xMax; // maximum extent of the x position
   static float yMin; // minimum extent of the y position
   static float yMax; // maximum extent of the y position
};

// stream I/O useful for debugging
std::ostream & operator << (std::ostream & out, const Bullet & pt);
std::istream & operator >> (std::istream & in,        Bullet & pt);

#endif // BULLET_H
