#include "rocks.h"

// Big Rock Methods
void BigRock::advance()
{
	point.addX(velocity.getDx());
	point.addY(velocity.getDy());
	setRotation();
}
void BigRock::draw()
{
	drawLargeAsteroid(point , rotation);
}

void BigRock::setRotation()
{
	rotation += BIG_ROCK_SPIN;
}

BigRock::BigRock(const Point& point) 
{
	float dx;
	float dy;
	if (random(0, 2) == 0)
		dx = -1;
	else
		dx = 1;

	if (random(0, 2) == 0)
		dy = -1;
	else
		dy = 1;

	Velocity newVelocity;
	newVelocity.setDx(dx);
	newVelocity.setDy(dy);

	setVelocity(newVelocity);

	alive = true; 
	setPoint(point); 
}

//Medium Rock Methods
void MediumRock::advance()
{
	point.addX(velocity.getDx());
	point.addY(velocity.getDy());
	setRotation();
}
void MediumRock::draw()
{
	drawMediumAsteroid(point, rotation);
}

void MediumRock::setRotation()
{
	rotation += MEDIUM_ROCK_SPIN;
}

MediumRock::MediumRock(const Point& point, const Velocity& vel)
{
	Velocity newVelocity;
	newVelocity.setDx(vel.getDx());
	newVelocity.setDy(vel.getDy());
	setVelocity(newVelocity);
	alive = true;
	setPoint(point);
}

//Small Rock Methods
void SmallRock::advance()
{
	point.addX(velocity.getDx());
	point.addY(velocity.getDy());
	setRotation();
}
void SmallRock::draw()
{
	drawSmallAsteroid(point, rotation);
}

void SmallRock::setRotation()
{
	rotation += SMALL_ROCK_SPIN;
}

SmallRock::SmallRock(const Point& point, const Velocity& vel)
{
	Velocity newVelocity;
	newVelocity.setDx(vel.getDx());
	newVelocity.setDy(vel.getDy());
	setVelocity(newVelocity);
	alive = true;
	setPoint(point);
}

