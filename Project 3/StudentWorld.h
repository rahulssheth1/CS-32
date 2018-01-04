#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Field.h"
#include "Actor.h"
#include "Compiler.h"
#include <string>
#include <list>
#include <vector>
#include <string>
using namespace std;
#include <iterator>
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir); 

    virtual int init(); 
	
    virtual int move();
    
    void checkIfDead(); 
    
    void setVector(Actor* some, int x, int y, Actor::Direction d, int newX, int newY);
    Field* getField() const;
    int getIIDOfFieldItem(Field::FieldItem value); 
    int getNumberOfItemsAtLocation(int x, int y, int value);
    virtual void cleanUp();
    void updateAntCounter(int m_colony);
    void setFoodAtPosition(int x, int y, int units);
    void addAdultGrasshopper(int x, int y);
    list<Actor*>  getThisVector(int h, int j) const;
    void addPheromone(int x, int y, int colony);
    void addAnt(int x, int y, Compiler* m_compiler, int colony);
    ~StudentWorld();
    

private:
    
    list <Actor*> Actor3[64][64];
    Field* gameField;
    int m_ticks;
    Compiler* m_compiler0;
    Compiler* m_compiler1;
    Compiler* m_compiler2;
    Compiler* m_compiler3;
    int numberOfColony0Ants;
    int numberOfColony1Ants;
    int numberOfColony2Ants;
    int numberOfColony3Ants;
    std::vector<std::string> fileNames; 
    
    
    
};

#endif // STUDENTWORLD_H_
