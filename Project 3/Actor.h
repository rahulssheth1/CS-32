#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "Field.h"

#include "Compiler.h"
#include <vector>
using namespace std;
#include <iostream>
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp




class StudentWorld; 
class Actor:  virtual public GraphObject {
public:
    virtual void doSomething() = 0;
    
    bool isDead();
    void setDead();
    void setAlive();
    void stun();
    int getTicks();
    void reduceTicks();
    virtual void updateHP(int hp) = 0;
    virtual int getColony() = 0;
    virtual bool isEnergyHolder() = 0;
    void checkIfStunned(int x, int y, StudentWorld* sw);
    int checkFood(int x, int y, StudentWorld *sw, int max);
    int checkPoison(int x, int y, StudentWorld* sw);
    bool getPoison();
    void setPoisonTrue();
    void setPoisonFalse();
    Direction randomDirection();
    void move(Actor* some, int &x, int &y, Direction d, int &distance, StudentWorld *Sw);
    
private:
    bool m_dead = false;
    int m_ticks = 0;
    bool m_poison = false; 

};

class EnergyHolder: public Actor {
public:
    virtual bool isFood() = 0;
    bool isEnergyHolder();
    int getUnits();
    void updateHP(int hp);
    virtual bool isInsect() = 0;
    virtual bool isPheromone() = 0;
    virtual int getColony() = 0;
    void stun();
    void setBitten();
    void setBittenFalse();
    bool isBitten();
    
private:
    bool m_bitten = false;
    int m_units = 0;
};

class Poison: public Actor {
public:
    Poison(int x, int y, StudentWorld* someWorld, int depth);
    void doSomething();
    bool isEnergyHolder();
    void updateHP(int hp);
    int getColony();
private:
    StudentWorld* sw;

};

class Food: public EnergyHolder {
    
public:
    
    Food(int x, int y, StudentWorld* someWorld, int depth, int units);
    void doSomething();
    bool isPheromone();
    int getColony();
    bool isFood(); 
    bool isBitten();
    bool isInsect();
private:
    StudentWorld* sw;
};

class poolOfWater: public Actor {
public:
    
    poolOfWater(int x, int y, StudentWorld* someWorld, int depth);
    void doSomething();
    bool isEnergyHolder();
    bool isBitten();
    void updateHP(int hp);
    int getColony();
private:
    StudentWorld* sw; 
    
    
};

class Pebble:  public Actor  {
public:
    
    Pebble(int x, int y, StudentWorld* someWorld, int depth);
    bool isEnergyHolder();
    void doSomething();
    int getColony();
    bool isBitten();
    void updateHP(int hp);


private:
    StudentWorld* Sw;
};

class babyGrasshopper: public EnergyHolder {
public:
    
    babyGrasshopper(int x, int y, StudentWorld* someWorld, int depth);
    void kill();
    bool isFood();
    int getColony();
    bool isPheromone();
    void resetDirection(Direction &d, int &distance); 
    void doSomething();
    bool isInsect();

    
private:
    Direction d;
    StudentWorld* Sw;
    int distance;
};

class AntHill: public EnergyHolder {
public:
    AntHill(int x, int y, StudentWorld* someWorld, int value, Compiler* someCompiler );
    bool isFood();
    void doSomething();
    bool isPheromone();
    bool isInsect();
    int getColony();
    void addAnAnt();
private:
    int m_colony;
    Compiler* m_compiler;
    StudentWorld* sw; 
    
};
class adultGrasshopper: public babyGrasshopper {
    
public:
    
    adultGrasshopper(int x, int y, StudentWorld *someWorld);
    void doSomething();
    void biteOthers(int x, int y);
    bool checkIfSolidLocation(int x, int y);

private:
    StudentWorld* sw;
    int distance;
    Direction d;
    struct coord {
        int x;
        int y;
    };
    bool m_bitten;
    vector<coord> coordinateVector;
    
};

class Ant: public EnergyHolder {
    
public:
    
    Ant(int x, int y, StudentWorld* someWorld, Compiler* someCompiler, int value);
    void doSomething();
    bool isFood();
    void setBlockedTrue();
    bool isPheromone();
    bool getBlocked();
    bool checkIfCommand(int operand1, int& ic);
    bool isInsect();
    void rotateCounterClockwise();
    void rotateClockwise(); 
    void dropSomeFood();
    void pickUpSomeFood();
    int  getColony();
    void eatSomeFood();
    bool checkEnemies();
    void setBlockedFalse();
    void bite();
private:
    StudentWorld* sw;
    Compiler* m_compiler;
    vector<Actor*> BitePossibilities; 
    int m_colony;
    Direction d;
    int amtFood;
    int randomNumber;
    int distance;
    int ic; 
    bool m_blocked = false; 
};

class Pheromone: public EnergyHolder {
    
public:
    Pheromone(int x, int y, StudentWorld* someWorld, int type, int colonyType);
     void doSomething();
    bool isPheromone();
    bool isInsect();
    bool isFood();
    int getColony();
    
private:
    int m_type;
    int strengthUnits;
    StudentWorld* sw;
    int colony;
};


#endif // ACTOR_H_

