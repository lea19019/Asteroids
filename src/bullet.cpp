#include "bullet.h"
#define _USE_MATH_DEFINES
#include <math.h>

// Put your bullet methods here
void Bullet::draw()
{
	if (isAlive())
	{
		drawDot(point);
	}

	if (life == 0)
	{
		kill();
	}
}

void Bullet::fire(const Point& point, float angle,const Velocity& vel)
{ 
	this->point = point;

	velocity.setDx((-sin(M_PI / 180.0 * angle) * BULLET_SPEED) + vel.getDx());
	velocity.setDy((cos(M_PI / 180.0 * angle) * BULLET_SPEED) + vel.getDy());

	alive = true;
}


void Bullet::advance()
{
	point.addX(velocity.getDx());
	point.addY(velocity.getDy());

	life--;
}