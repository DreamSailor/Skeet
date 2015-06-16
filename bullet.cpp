/***********************************************************************
 * Source File:
 *    Bullet : The representation of a position on the screen
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a location on the screen, including
 *    the location and the bounds.
 ************************************************************************/

#include "bullet.h"
#include <cassert>

/******************************************
 * BULLET : CONSTRUCTOR WITH X,Y
 * Initialize the bullet to the passed position
 *****************************************/
Bullet::Bullet(float x, float y) : x(0.0), y(0.0),
                                 check(false), dead(false), wrap(false), angle(0.0)
{
   setX(x);
   setY(y);
}

/*******************************************
 * BULLET : SET X
 * Set the x position if the value is within range
 *******************************************/
void Bullet::setX(float x)
{
   assert(xMin < xMax);

   // wrap as necessary
   if (wrap)
   {
      this->x = x;
      while (this->x > xMax)
         this->x -= (xMax - xMin);
      while (this->x < xMin)
         this->x += (xMax - xMin);
   }

   // trivial non-checking assignment
   else if (!check || (x >= xMin && x <= xMax))
      this->x = x;

   // of the screen
   else
      dead = true;
}

/********************************************
 * BULLET : Assignmenet
 *******************************************/
const Bullet & Bullet :: operator = (const Bullet & rhs)
{
   x        = rhs.x;
   y        = rhs.y;
   check    = rhs.check;
   dead     = rhs.dead;
   wrap     = rhs.wrap;
   angle    = rhs.angle;

   return *this;
}

/*******************************************
 * BULLET : SET Y
 * Set the y position if the value is within range
 *******************************************/
void Bullet::setY(float y)
{
   assert(yMin < yMax);

   // wrap as necessary
   if (wrap)
   {
      this->y = y;
      while (this->y > yMax)
         this->y -= (yMax - yMin);
      while (this->y < yMin)
         this->y += (yMax - yMin);
   }

   // trivial non-checking assignment
   else if (!check || (y >= yMin && y <= yMax))
      this->y = y;

   // of the screen
   else
      dead = true;
   
}

void Bullet::setAngle(int angle)
{
  this->angle = angle;
}

/******************************************
 * BULLET insertion
 *       Display coordinates on the screen
 *****************************************/
std::ostream & operator << (std::ostream & out, const Bullet & pt)
{
   out << "(" << pt.getX() << ", " << pt.getY() << ")";
   return out;
}

/*******************************************
 * BULLET extraction
 *       Prompt for coordinates
 ******************************************/
std::istream & operator >> (std::istream & in, Bullet & pt)
{
   float x;
   float y;
   in >> x >> y;

   pt.setX(x);
   pt.setY(y);

   return in;
}
   
