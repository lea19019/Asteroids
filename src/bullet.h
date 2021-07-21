#ifndef bullet_h
#define bullet_h

#define BULLET_SPEED 5
#define BULLET_LIFE 40

#include "flyingObject.h"
#include "uiDraw.h"

// Put your Bullet class here

class Bullet : public FlyingObject
{
public:
	Bullet() { alive = true;  life = BULLET_LIFE; }
	~Bullet() {}
	virtual void draw();
	void fire(const Point& point, float angle, const Velocity & vel);
	virtual void advance();
protected:
	float life;
};


#endif /* bullet_h */
