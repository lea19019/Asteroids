#ifndef ship_h
#define ship_h

#define SHIP_SIZE 10

#define ROTATE_AMOUNT 6
#define THRUST_AMOUNT 0.5

#include "point.h"
#include "flyingObject.h"
#include "uiDraw.h"

// Put your Ship class here

class Ship : public FlyingObject
{
public:
	Ship() { rotation = 0; thrust = false; alive = true; }
	Ship(const Point& point) { setPoint(point); }
	~Ship();
	virtual void draw();
	void rightThrust();
	void leftThrust();
	void upperThrust();
	void advance();
	void setThrust(bool thrust) { this->thrust = thrust; }
	int getRotation() const { return rotation; }

private:
	int rotation;
	bool thrust;
};


#endif /* ship_h */
