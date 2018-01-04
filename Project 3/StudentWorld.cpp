#include "StudentWorld.h"
#include <string>
#include <sstream>  // defines the type std::ostringstream
#include <iomanip>  // defines the manipulator setw
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
StudentWorld::StudentWorld(std::string assetDir) : GameWorld(assetDir)
{
    
    gameField = new Field;
    m_compiler0 = new Compiler;
    m_compiler1 = new Compiler;
    m_compiler2 = new Compiler;
    m_compiler3 = new Compiler;
    m_ticks = 2000;
    numberOfColony0Ants = 0;
    numberOfColony1Ants = 0;
    numberOfColony2Ants = 0;
    numberOfColony3Ants = 0;
    fileNames = getFilenamesOfAntPrograms();
    
    
}
void StudentWorld::setFoodAtPosition(int x, int y, int units) {
    Actor *temp;
    
    temp = new Food(x, y, this, 2, units );
    Actor3[x][y].push_back(temp); 
    
}
void StudentWorld::updateAntCounter(int m_colony) {
    switch(m_colony) {
        case IID_ANT_TYPE0:
            numberOfColony0Ants--;
            break;
        case IID_ANT_TYPE1:
            numberOfColony1Ants--;
            break;
        case IID_ANT_TYPE2:
            numberOfColony2Ants--;
            break;
        case IID_ANT_TYPE3:
            numberOfColony3Ants--;
            break;
    }
}

void StudentWorld::checkIfDead() {
    list<Actor*>::iterator i;
    for (int h = 0; h < 64; h++) {
        for (int j = 0; j < 64;
             j++) {
            i = Actor3[h][j].begin();
            while (i != Actor3[h][j].end()) {
                if ((*i)->isDead()) {
                    (*i)->setVisible(false);
                    i = Actor3[h][j].erase(i);
                    
                    continue;
                }
                i++;
            }
        }
    }
}
int StudentWorld::init()
{
    
    Actor* temp;
    list<Actor*>::iterator i;
    list<Actor*>::iterator temp2;
    vector<string> fileName = getFilenamesOfAntPrograms();
    string error;
    gameField -> loadField(getFieldFilename());
    if (!m_compiler0->compile(fileName[0], error)) {
        setError(fileNames[0] + " " + error);
        return false;
    }
    if (!m_compiler1->compile(fileName[1], error)) {
        setError(fileNames[1] + " " + error);
        return false;
    }
    if (!m_compiler2->compile(fileName[2], error)) {
        setError(fileNames[2] + " " + error);
        return  false;
    }
    
    if (!m_compiler3->compile(fileName[3], error)) {
        setError(fileNames[3] + " " + error);
        return false;
    }
    

    for (int h = 0; h < 64; h++) {
        
        for (int j = 0; j < 64; j++) {
            
            Field::FieldItem item = gameField->getContentsOf(h, j);
            
            switch(item) {
                case Field::FieldItem::anthill0:
                    temp = new AntHill(h, j, this, 0, m_compiler0);
                    Actor3[h][j].push_back(temp);
                    break;
                case Field::FieldItem::anthill1:
                    temp = new AntHill(h, j, this, 1, m_compiler1);
                    Actor3[h][j].push_back(temp);
                    break;
                case Field::FieldItem::anthill2:
                    temp = new AntHill(h, j, this, 2, m_compiler2);
                    Actor3[h][j].push_back(temp);
                    break;
                case Field::FieldItem::anthill3:
                    temp = new AntHill(h, j, this, 3, m_compiler3);
                    Actor3[h][j].push_back(temp);
                    break;
                
                case Field::FieldItem::food:
                    temp = new Food(h, j, this, 2, 6000);
                    Actor3[h][j].push_back(temp);
                    break;
                    
                case Field::FieldItem::rock:
                    temp = new Pebble(h, j, this, 1);
                    Actor3[h][j].push_back(temp);
                    break;
                    
                case Field::FieldItem::grasshopper:
                    temp = new babyGrasshopper(h, j, this, 1);
                    Actor3[h][j].push_back(temp);
                    break;
                    
                case Field::FieldItem::water:
                    temp = new poolOfWater(h, j, this, 2);
                    Actor3[h][j].push_back(temp);
                    break; 
                case Field::FieldItem::poison:
                    temp = new Poison(h, j, this, 2);
                    Actor3[h][j].push_back(temp);
                    break; 
                default:
                    break;
            }
        }
    }
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::  move()
{
    
    m_ticks--;
    checkIfDead();
    ostringstream some;
    some << setw(fileNames[0].size() + 4) << fileNames[0] << numberOfColony0Ants;
    some.fill(' ');
    some << setw(fileNames[1].size() + 4) << fileNames[1] << numberOfColony1Ants;
    some.fill(' ');
    some << setw(fileNames[2].size() + 4) << fileNames[2] << numberOfColony2Ants;
    some.fill(' ');
    some << setw(fileNames[3].size() + 4) << fileNames[3] << numberOfColony3Ants;
    some.fill(' ');
    
    
    
    setGameStatText(some.str());
    
    for (int h = 0; h < 64; h++) {
        for (int j = 0; j < 64; j++) {
            if (!Actor3[h][j].empty()) {
                list<Actor*>::iterator i;
                i = Actor3[h][j].begin();
                list<Actor*>::iterator temp;

                while ( i != Actor3[h][j].end()) {
                    temp = ++i;
                    --i;
                    (*i)-> doSomething();
                    i = temp;
                }
                
            }
            
        }
    }

    
    if (m_ticks <= 0) {
        setWinner("USCAnt.bug");
        return GWSTATUS_PLAYER_WON;

    }
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::setVector(Actor* some, int x, int y, Actor::Direction d, int newX, int newY) {
    list<Actor*>::iterator i;
    
    i = Actor3[x][y].begin();
    
    while (i != Actor3[x][y].end()) {
        if (*i == some) {
            i = Actor3[x][y].erase(i);
            Actor3[newX][newY].push_back(some);
            continue;
        }
        i++;
        
    }
    
}

void StudentWorld::cleanUp()
{
    for (int h = 0; h < 64; h++) {
        for (int j = 0; j < 64; j++) {
            std::list<Actor*>::iterator i;
            i = Actor3[h][j].begin();
            while ( i != Actor3[h][j].end()) {
                
                delete *i;
                
                i++;
            }
        }
    }
    cout << numberOfColony0Ants << "0 Ants" << endl << numberOfColony1Ants << endl << "1 Ants" << endl << numberOfColony2Ants << endl << "2 Ants" << endl << numberOfColony3Ants << "3 ants" << endl;
    delete gameField;
    delete m_compiler0;
    delete m_compiler1;
    delete m_compiler2;
    delete m_compiler3;
}

StudentWorld::~StudentWorld() {
    cleanUp(); 
}


Field* StudentWorld::getField() const {
    return gameField;
}


int StudentWorld::getNumberOfItemsAtLocation(int x, int y, int value) {
    list<Actor*>::iterator i = Actor3[x][y].begin();
    int counter = 0;
    int temp  = value; 
    
    while (i != Actor3[x][y].end()) {
        if ((*i)->getID() == temp) {
            counter++;
        }
        i++;
    }
    
    
    
    return counter;
}

int StudentWorld::getIIDOfFieldItem(Field::FieldItem value) {
    switch (value) {
        case Field::FieldItem::poison:
             return IID_POISON;
            break;
        case Field::FieldItem::anthill0:
        case Field::FieldItem::anthill1:
        case Field::FieldItem::anthill2:
        case Field::FieldItem::anthill3:
            return IID_ANT_HILL;
            break;
        case Field::FieldItem::food:
            return IID_FOOD;
            break;
        case Field::FieldItem::water:
            return IID_WATER_POOL;
            break;
        case Field::FieldItem::grasshopper:
            return IID_BABY_GRASSHOPPER;
            break;
        case Field::FieldItem::rock:
            return  IID_ROCK;
            break;
            
        default:
            return 0;
            break;
    }

    
}

void StudentWorld::addAdultGrasshopper(int x, int y) {
    cout << "Added AdultGrasshopper" << endl; 
    Actor *temp = new adultGrasshopper(x, y, this );
    Actor3[x][y].push_back(temp);
    
}

void StudentWorld::addAnt(int x, int y, Compiler* m_compiler, int colony) {
    Actor* temp;
    
    switch(colony) {
        case IID_ANT_TYPE0:
            temp = new Ant(x, y, this, m_compiler, IID_ANT_TYPE0);
            Actor3[x][y].push_back(temp);
            numberOfColony0Ants++;
            break;
        case IID_ANT_TYPE1:
            temp = new Ant(x, y, this, m_compiler, IID_ANT_TYPE1);
            Actor3[x][y].push_back(temp);
            numberOfColony1Ants++;
            break;
        case IID_ANT_TYPE2:
            temp = new Ant(x, y, this, m_compiler, IID_ANT_TYPE2);
            Actor3[x][y].push_back(temp);
            numberOfColony2Ants++;
            break;
        case IID_ANT_TYPE3:
            temp = new Ant(x , y, this, m_compiler, IID_ANT_TYPE3);
            Actor3[x][y].push_back(temp);
            numberOfColony3Ants++; 
            break;
        default:
            break; 
    }
}
void StudentWorld::addPheromone(int x, int y, int colony) {
    Actor *temp;
    
    switch(colony) {
        case IID_ANT_TYPE0:
            temp = new Pheromone(x, y, this, IID_PHEROMONE_TYPE0, IID_ANT_TYPE0);
            Actor3[x][y].push_back(temp);
            break;
        case IID_ANT_TYPE1:
            temp = new Pheromone(x, y, this, IID_PHEROMONE_TYPE1, IID_ANT_TYPE1);
            Actor3[x][y].push_back(temp);
            break;
        case IID_ANT_TYPE2:
            temp = new Pheromone(x, y, this, IID_PHEROMONE_TYPE2, IID_ANT_TYPE2);
            Actor3[x][y].push_back(temp);
            break;
        case IID_ANT_TYPE3:
            temp = new Pheromone(x, y, this, IID_PHEROMONE_TYPE3, IID_ANT_TYPE3);
            Actor3[x][y].push_back(temp);
            break;
        default:
            break;
            
    }
}

list<Actor*> StudentWorld::getThisVector(int h, int j) const {
    return Actor3[h][j]; 
}
