/*********************************************************************
 * File: game.cpp
 * Description: Contains the implementaiton of the game class
 *  methods.
 *
 *********************************************************************/

#include "game.h"

// These are needed for the getClosestDistance function...
#include <limits>
#include <algorithm>
using namespace std;

#include <typeinfo>

/***************************************
 * GAME CONSTRUCTOR
 ***************************************/
Game::Game(Point tl, Point br): topLeft(tl), bottomRight(br)
{
    score = 0;
    createRocks();
    millenniumFalcon = NULL;
    millenniumFalcon = createShip();
}

void Game::handleInput(const Interface & ui)
{
    if (ui.isLeft())
    {
        millenniumFalcon->leftThrust();
    }

    if (ui.isRight())
    {
        millenniumFalcon->rightThrust();
    }

    if (ui.isSpace())
    {
        if (millenniumFalcon->isAlive())
        {
            Bullet newBullet;
            newBullet.fire(millenniumFalcon->getPoint(), millenniumFalcon->getRotation(), millenniumFalcon->getVelocity());

            bullets.push_back(newBullet);
        }
    }

    if (ui.isUp())
    {
        millenniumFalcon->setThrust(true);
        millenniumFalcon->upperThrust();
    }

    if (!ui.isUp())
    {
        millenniumFalcon->setThrust(false);
    }

    if (!millenniumFalcon->isAlive())
    {
        char text[256] = "You lost";
        char text2[256] = "Press S key to play again";
        drawText(Point(-35.0, 25), text);
        drawText(Point(-90.0, -5), text2);
        
        if (ui.isSKey())
        {
            rocks.clear();
            createRocks();
            millenniumFalcon = NULL;
            millenniumFalcon = createShip();
        }
    }
    
}

void Game::draw(const Interface & ui)
{
    for (int i = 0; i < rocks.size(); i++)
    {
        if (rocks[i]->isAlive())
        {
            rocks[i]->draw();
        }
        
        
    }
    if (millenniumFalcon->isAlive())
    {
        millenniumFalcon->draw();
    }
    

    for (int i = 0; i < bullets.size(); i++)
    {
       
        bullets[i].draw();
        
    }
}

void Game::advance()
{
    this->advanceRocks();
    advanceShip();
    advanceBullets();
    cleanUpZombies();
    handleCollisions();
}


void Game::createRocks()
{
    for (int i = 0; i < 5; i++)
    {
        Point newPoint;
        newPoint.setX(random(bottomRight.getY(), topLeft.getY()));
        newPoint.setY(random(bottomRight.getY(), topLeft.getY()));
        
        BigRock* rocky = new BigRock(newPoint);
        rocks.push_back(rocky);
    }
}

void Game::advanceRocks()
{
    for (int i = 0; i < rocks.size(); i++)
    {
        rocks[i]->advance();
        

        if (!(rocks[i]->getPoint().getX() >= (topLeft.getX() - 5) && 
            rocks[i]->getPoint().getX() <= (bottomRight.getX() + 5)) )
        {
            rocks[i]->setPoint(Point(rocks[i]->getPoint().getX() * -1, rocks[i]->getPoint().getY()));
        }

        if (!(rocks[i]->getPoint().getY() <= (topLeft.getY() + 5) &&
            rocks[i]->getPoint().getY() >= (bottomRight.getY() - 5)))
        {
            rocks[i]->setPoint(Point(rocks[i]->getPoint().getX(), rocks[i]->getPoint().getY() * -1));
        }

    }

}

Ship* Game::createShip()
{
    Ship* newShip = NULL;

    newShip = new Ship;

    return newShip;
}

void Game::advanceBullets()
{
    for (int i = 0; i < bullets.size(); i++)
    {
        bullets[i].advance();

        if (!(bullets[i].getPoint().getX() >= (topLeft.getX() - 5) &&
            bullets[i].getPoint().getX() <= (bottomRight.getX() + 5)))
        {
            bullets[i].setPoint(Point(bullets[i].getPoint().getX() * -1, bullets[i].getPoint().getY()));
        }

        if (!(bullets[i].getPoint().getY() <= (topLeft.getY() + 5) &&
            bullets[i].getPoint().getY() >= (bottomRight.getY() - 5)))
        {
            bullets[i].setPoint(Point(bullets[i].getPoint().getX(), bullets[i].getPoint().getY() * -1));
        }
    }
    
}

void Game::advanceShip()
{
    millenniumFalcon->advance();

    if (!(millenniumFalcon->getPoint().getX() >= (topLeft.getX() - 5) &&
        millenniumFalcon->getPoint().getX() <= (bottomRight.getX() + 5)))
    {
        millenniumFalcon->setPoint(Point(millenniumFalcon->getPoint().getX() * -1, millenniumFalcon->getPoint().getY()));
    }

    if (!(millenniumFalcon->getPoint().getY() <= (topLeft.getY() + 5) &&
        millenniumFalcon->getPoint().getY() >= (bottomRight.getY() - 5)))
    {
        millenniumFalcon->setPoint(Point(millenniumFalcon->getPoint().getX(), millenniumFalcon->getPoint().getY() * -1));
    }
}

void Game::cleanUpZombies()
{
    vector<Bullet>::iterator bulletIt = bullets.begin();
    while (bulletIt != bullets.end())
    {
        Bullet bullet = *bulletIt;

        if (!bullet.isAlive())
        {
            // remove from list and advance
            bulletIt = bullets.erase(bulletIt);
        }
        else
        {
            bulletIt++; // advance
        }
    }

    vector<Rocks*>::iterator golem = rocks.begin();
    while (golem != rocks.end())
    {
        Rocks *rock = *golem;
        if (!rock->isAlive())
        {
            golem = rocks.erase(golem);
        }
        else
        {
            golem++;
        }
    }

}
// You may find this function helpful...

/**********************************************************
 * Function: getClosestDistance
 * Description: Determine how close these two objects will
 *   get in between the frames.
 **********************************************************/

float Game :: getClosestDistance(const FlyingObject &obj1, const FlyingObject &obj2) const
{
   // find the maximum distance traveled
   float dMax = max(abs(obj1.getVelocity().getDx()), abs(obj1.getVelocity().getDy()));
   dMax = max(dMax, abs(obj2.getVelocity().getDx()));
   dMax = max(dMax, abs(obj2.getVelocity().getDy()));
   dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.
   
   float distMin = std::numeric_limits<float>::max();
   for (float i = 0.0; i <= dMax; i++)
   {
      Point point1(obj1.getPoint().getX() + (obj1.getVelocity().getDx() * i / dMax),
                     obj1.getPoint().getY() + (obj1.getVelocity().getDy() * i / dMax));
      Point point2(obj2.getPoint().getX() + (obj2.getVelocity().getDx() * i / dMax),
                     obj2.getPoint().getY() + (obj2.getVelocity().getDy() * i / dMax));
      
      float xDiff = point1.getX() - point2.getX();
      float yDiff = point1.getY() - point2.getY();
      
      float distSquared = (xDiff * xDiff) +(yDiff * yDiff);
      
      distMin = min(distMin, distSquared);
   }
   
   return sqrt(distMin);
}

void Game::handleCollisions()
{
    for (int i = 0; i < rocks.size(); i++)
    {
        if (rocks[i]->isAlive() && millenniumFalcon->isAlive())
        {
            if (rocks[i]->getSize() > getClosestDistance(*millenniumFalcon, *rocks[i]) - 1)
            {
                if (typeid(*rocks[i]) == typeid(BigRock))
                {
                    bigRockCollision(*rocks[i]);
                }
                else if (typeid(*rocks[i]) == typeid(MediumRock))
                {
                    mediumRockCollision(*rocks[i]);
                }
                rocks[i]->kill();
                millenniumFalcon->kill();
            }
        }
    }
    for (int i = 0; i < bullets.size(); i++)
    {
        for (int j = 0; j < rocks.size(); j++)
        {
            if (bullets[i].isAlive() && rocks[j]->isAlive())
            {
                if (rocks[j]->getSize() > getClosestDistance(bullets[i], *rocks[j]))
                {
                    if (typeid(*rocks[j]) == typeid(BigRock))
                    {
                        bigRockCollision(*rocks[j]);
                    }
                    else if (typeid(*rocks[j]) == typeid(MediumRock))
                    {
                        mediumRockCollision(*rocks[j]);
                    }
                    rocks[j]->kill();
                    bullets[i].kill();
                }
            }
        }
    }
    
}

void Game::bigRockCollision(const Rocks& rocky)
{
    Point newPoint;
    newPoint.setX(rocky.getPoint().getX());
    newPoint.setY(rocky.getPoint().getY());

    Velocity vel1;
    vel1.setDx(rocky.getVelocity().getDx());
    vel1.setDy(rocky.getVelocity().getDy() + 1);

    Velocity vel2;
    vel2.setDx(rocky.getVelocity().getDx());
    vel2.setDy(rocky.getVelocity().getDy() - 1);

    Velocity vel3;
    vel3.setDx(rocky.getVelocity().getDx() + 2);
    vel3.setDy(rocky.getVelocity().getDy());

    MediumRock* rock1 = new MediumRock(newPoint, vel1);
    MediumRock* rock2 = new MediumRock(newPoint, vel2);
    SmallRock* rock3 = new SmallRock(newPoint, vel3);

    rocks.push_back(rock1);
    rocks.push_back(rock2);
    rocks.push_back(rock3);
}

void Game::mediumRockCollision(const Rocks& rocky)
{
    Point newPoint;
    newPoint.setX(rocky.getPoint().getX());
    newPoint.setY(rocky.getPoint().getY());

    Velocity vel1;
    vel1.setDx(rocky.getVelocity().getDx() + 3);
    vel1.setDy(rocky.getVelocity().getDy());

    Velocity vel2;
    vel2.setDx(rocky.getVelocity().getDx() - 3);
    vel2.setDy(rocky.getVelocity().getDy());

    SmallRock* rock1 = new SmallRock(newPoint, vel1);
    SmallRock* rock2 = new SmallRock(newPoint, vel2);

    rocks.push_back(rock1);
    rocks.push_back(rock2);
}
