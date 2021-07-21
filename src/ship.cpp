#include "ship.h"
#define _USE_MATH_DEFINES
#include <math.h>

// Put your ship methods here

void Ship::draw()
{
	drawShip(point, rotation, thrust);
}

void Ship::leftThrust()
{
	rotation += ROTATE_AMOUNT;
	
}

void Ship::rightThrust()
{
	rotation -= ROTATE_AMOUNT;
	
}

void Ship::upperThrust()
{
	velocity.setDx(velocity.getDx() + (.5 * -sin(M_PI / 180 * rotation)));
	velocity.setDy(velocity.getDy() + (.5 * cos(M_PI / 180 * rotation)));
}

void Ship::advance()
{
	point.addX(velocity.getDx());
	point.addY(velocity.getDy());
}