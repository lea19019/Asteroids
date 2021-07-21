#include "flyingObject.h"


// Put your FlyingObject method bodies here
void FlyingObject::advance()
{
    point.addX(velocity.getDx());
    point.addY(velocity.getDy());
    
}