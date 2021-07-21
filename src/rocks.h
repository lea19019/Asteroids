#ifndef rocks_h
#define rocks_h

#define BIG_ROCK_SIZE 16
#define MEDIUM_ROCK_SIZE 8
#define SMALL_ROCK_SIZE 4

#define BIG_ROCK_SPIN 2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN 10

#include "flyingObject.h"
#include "uiDraw.h"
#include "velocity.h"

// Define the following classes here:
//   Rock

class Rocks : public FlyingObject
{
public:
	Rocks() {}
	Rocks(const Point& point) { alive = true; setPoint(point); }
	~Rocks() {}
	virtual void draw() = 0;
	virtual void advance() {}
	virtual int getSize() = 0;
private:

};

//   BigRock

class BigRock : public Rocks
{
public:
	BigRock() {}
	BigRock(const Point& point);
	virtual void draw();
	virtual void advance();
	void setRotation();
	virtual int getSize() { return BIG_ROCK_SIZE; }
private:
	int rotation;
};

//   MediumRock

class MediumRock : public BigRock
{
public:
	MediumRock() {}
	MediumRock(const Point& point, const Velocity& vel);
	virtual void advance();
	virtual void draw();
	void setRotation();
	virtual int getSize() { return MEDIUM_ROCK_SIZE; }
private:
	int rotation;
};

//   SmallRock

class SmallRock : public MediumRock
{
public:
	SmallRock() {}
	SmallRock(const Point& point, const Velocity& vel);
	virtual void advance();
	virtual void draw();
	void setRotation();
	virtual int getSize() { return SMALL_ROCK_SIZE; }
private:
	int rotation;
};

#endif /* rocks_h */
