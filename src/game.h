/*********************************************************************
 * File: game.h
 * Description: Defines the game class for Asteroids
 *
 *********************************************************************/

#ifndef GAME_H
#define GAME_H

#include "uiInteract.h"
#include "uiDraw.h"
#include "point.h"
#include "velocity.h"
#include <vector>
#include "rocks.h"
#include "ship.h"
#include "bullet.h"

class Game
{
public:
    Game(Point tl, Point br);
    ~Game() {}
    void handleInput(const Interface& ui);
    void advance();
    void draw(const Interface& ui);

private:
    int score;
    Point topLeft;
    Point bottomRight;
    std::vector<Rocks*> rocks;
    Ship* millenniumFalcon;
    void createRocks();
    void advanceRocks();
    Ship* createShip();
    std::vector<Bullet> bullets;
    void advanceBullets();
    void advanceShip();
    void cleanUpZombies();
    float getClosestDistance(const FlyingObject& obj1, const FlyingObject& obj2) const;
    void handleCollisions();
    void bigRockCollision(const Rocks& rocky);
    void mediumRockCollision(const Rocks& rocky);
    void smallRockCollision(const Rocks& rocky);
};


#endif /* GAME_H */
