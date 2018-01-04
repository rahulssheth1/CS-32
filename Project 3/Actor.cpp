#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

#include "Actor.h"
#include "StudentWorld.h"

//Actor's implementation

int MAX_FOOD_GRASSHOPPER  = 200;
int MAX_FOOD_ANTHILL = 10000;
int NOT_A_COLONY = 1000;


bool Actor::isDead() {
    return m_dead; 
}
//Checks dead



void Actor::stun() {
    m_ticks+= 2;
}
//Increments ticks by 2


int Actor::getTicks() {
    return m_ticks;
}
//Returns ticks left to sleep


void Actor::reduceTicks() {
    m_ticks--;
}
//Decrements ticks left to sleep

void Actor::setAlive() {
    m_dead = false;
}
//Set Actor to alive



void Actor::setDead() {
    m_dead = true;
}
//Set Actor to Dead



Actor::Direction Actor::randomDirection() {
    Direction d = getDirection();
    int random = randInt(1, 4);
    switch (random) {
            
        case 1:
            d = up;
            break;
        case 2:
            d = down;

            break;
        case 3:
            d = left;

            break;
        case 4:
            d = right;

            break;
            
            
    }
    return d;
}
//Return a random direction to move in



void Actor::move(Actor* some, int &x, int &y, Direction d, int &distance, StudentWorld* Sw) {
    switch(d) {
        case up:
            y--;
            if ((y >=0) && (Sw->getField()->getContentsOf(x, y) != Field::FieldItem::rock)) {
                some -> moveTo(x, y);
                distance--;
                setPoisonFalse();
                Sw->setVector(some, x, y+1, d, x, y);
                
            } else {
                y++;
                distance = 0;
                //                resetDirection(d, distance);
            }
            break;
        case right:
            x++;
            if ((x < VIEW_WIDTH) && (Sw->getField()->getContentsOf(x, y) != Field::FieldItem::rock )) {
                some ->moveTo(x ++, y);
                distance--;
                setPoisonFalse();

                Sw->setVector(some, x-1, y, d, x, y);
                
            } else {
                
                x--;
                distance = 0;
                //                resetDirection(d, distance);
                
            }
            break;
        case down:
            y++;
            if ((y < VIEW_HEIGHT) && (Sw->getField()->getContentsOf(x, y)) != Field::FieldItem::rock) {
                some ->moveTo(x, y );
                distance--;
                Sw->setVector(some, x, y-1, d, x, y);
                setPoisonFalse();

            } else {
                
                y--;
                distance = 0;
                //                resetDirection(d, distance);
                
            }
            break;
        case left:
            x--;
            if ((x < VIEW_WIDTH) && (Sw->getField()->getContentsOf(x, y) != Field::FieldItem::rock )) {
                some ->moveTo(x , y);
                distance--;
                Sw->setVector(some, x+1, y, d, x, y);
                setPoisonFalse();

                
            } else {
                
                x++;
                distance = 0;
                //                resetDirection(d, distance);
                
            }
            break;
        default:
            break;
            
    }
    
}
//Continue to move one positon in the direction you are facing.


bool Actor::getPoison() {
    return m_poison;
}
//Check if poisoned

void Actor::setPoisonTrue() {
    m_poison = true;
}
//True if just poisoned
void Actor::setPoisonFalse() {
    m_poison = false;
}
//False if moved onto new square

void Actor::checkIfStunned(int x, int y, StudentWorld* sw) {
    
    
    if (sw->getField()->getContentsOf(x, y) == Field::FieldItem::water) {
        stun();
    }
}
//check if on water

int Actor::checkFood(int x, int y, StudentWorld *sw, int max) {
   
        list<Actor*> temp = sw->getThisVector(x, y);
        list<Actor*>::iterator i = temp.begin();
        
        while (i != temp.end()) {
            
            if ((*i)->isEnergyHolder()) {
                Actor* value = (*i);
                EnergyHolder* some = dynamic_cast<EnergyHolder*>(value);
                if (some != nullptr && some->isFood()) {
                    int units = (some)->getUnits();
                    if (units > max) {
                            (some)->updateHP(-max);
                            return max;
                    }
                    (some)->setDead();
                    return units;
                }
            }
            i++;
        }
    
        
    
    return 0; 
}
//Check if on food

int Actor::checkPoison(int x, int y, StudentWorld* sw) {
    
    if (sw->getField()->getContentsOf(x, y) == Field::FieldItem::poison && !getPoison()) {
        setPoisonTrue();
        return -150;

    }
    
      
    return 0;
}
//Check if on poison
//--------------------------------------------------------------------------------------------------------------------------------------------


//Pebble's Implementation


Pebble::Pebble(int x, int y, StudentWorld* someWorld, int depth): GraphObject(IID_ROCK, x, y, right, depth) {
    Sw = someWorld;
    setAlive();
}
//Construct a pebble... a pebble just let that sink in we are making a rock


int Pebble::getColony() {
    return NOT_A_COLONY;
}
//Pebble is not an ant so it returns an int that is not in range


bool Pebble::isEnergyHolder() {
    return false;
}
//Not an energyHolder


void Pebble::doSomething() {
    return;
}
//Pebble does nothing

void Pebble::updateHP(int hp) {
    return;
}
//Pebble has no hitpoints



//--------------------------------------------------------------------------------------------------------------------------------------------

//Baby Grasshopper's implementation
babyGrasshopper::babyGrasshopper(int x, int y, StudentWorld* someWorld, int depth):  GraphObject(IID_BABY_GRASSHOPPER, x, y, d = randomDirection(), depth) {
    Sw = someWorld;
    updateHP(500);
    setDirection(d);
    distance = randInt(2, 10);
    
    setAlive();
    
}
//Construct a baby grasshopper

bool babyGrasshopper::isInsect() {
    return true;
}
//Grasshopper is an insect

void babyGrasshopper::kill() {
    //Add food into the position
    Sw->setFoodAtPosition(getX(), getY(), 100);
    setDead();
}
bool babyGrasshopper::isFood() {
    return false;
}
//It isn't food

void babyGrasshopper::resetDirection(Direction& d, int &distance) {
    d = randomDirection();
    distance = randInt(2, 10);
    
}
//Resets direction at 0.

int babyGrasshopper::getColony() {
    return NOT_A_COLONY;
}
//Baby Grasshopper has no colony


void babyGrasshopper::doSomething() {
    updateHP(-1);
    if (getUnits() == 0) {
        //call dead
        kill();
        
    }
    if (getTicks() == 0) {
        Actor::stun();
        if (getUnits() >= 1600) {
            Sw-> addAdultGrasshopper(getX(), getY());
            kill();
        }
 
   
    int x = getX();
    int y = getY();
    int units =   checkFood(x, y, Sw, MAX_FOOD_GRASSHOPPER) + checkPoison( x, y, Sw);
    updateHP(units);
        if (checkFood(x, y, Sw, MAX_FOOD_GRASSHOPPER) != 0) {
            int i = randInt(1, 2);
            if (i == 2)
                return;
        }
        if (distance == 0)
            resetDirection(d, distance);
        setDirection(d);
        Actor::move(this, x, y, d, distance, Sw);

        //Check if stunned
        checkIfStunned(x, y, Sw);

}
    else {
        reduceTicks();
    }
}
//Checks if sleeping. If not, moves,  checks if you need an adult grasshopper, poison, etc, etc






bool babyGrasshopper::isPheromone() {
    return false;
}
//Not a pheromone

//--------------------------------------------------------------------------------------------------------------------------------------------


//Pool of Water's implementation


poolOfWater::poolOfWater(int x, int y, StudentWorld* someWorld, int depth): GraphObject(IID_WATER_POOL, x, y, right, depth) {
    
    setAlive();
    sw = someWorld; 
}
//Constructed pool of water
int poolOfWater::getColony() {
    return NOT_A_COLONY;
}
//It's not an ant

void poolOfWater::doSomething() {
    return;
}
//Does nothing
bool poolOfWater::isEnergyHolder() {
    return false;
}
//Not an energy Holder
void poolOfWater::updateHP(int hP) {
    return;
}
//Has no hp

//--------------------------------------------------------------------------------------------------------------------------------------------

//Food Implementation

Food::Food(int x, int y, StudentWorld* someWorld, int depth, int units): GraphObject(IID_FOOD, x, y, right, depth) {
    updateHP(units);
    sw = someWorld;
    setAlive();
    
}
//Construct a food

int Food::getColony() {
    return NOT_A_COLONY;
}
//Not an ant

bool Food::isFood() {
    return true; 
}
//It is food
bool Food::isInsect() {
    return false;
}
//Not an insect
void Food::doSomething() {
    return;
}
//Does nothing





bool Food::isPheromone() {
    return false;
}
//Not a pheromone
//--------------------------------------------------------------------------------------------------------------------------------------------


//Poison implementation

Poison::Poison(int x, int y, StudentWorld* someWorld, int depth): GraphObject(IID_POISON, x, y, right, depth) {
    sw = someWorld;
    setAlive();
}
//Construct poison object

int Poison::getColony() {
    return NOT_A_COLONY;
}
//not an ant

void Poison::doSomething() {
    return;
}
//Does nothing

bool Poison::isEnergyHolder() {
    return false;
}
//Not an energyholder

void Poison::updateHP(int hp) {
    return;
}
//Has no hp






//--------------------------------------------------------------------------------------------------------------------------------------------


//Adult Grasshopper Implementation

adultGrasshopper::adultGrasshopper(int x, int y, StudentWorld* someWorld): babyGrasshopper(x, y, someWorld, 1), GraphObject(IID_ADULT_GRASSHOPPER, x, y) {
    sw = someWorld;
    updateHP(1600);
    setAlive();
    
    
}

//Construct an adult grasshopper




void adultGrasshopper::doSomething() {
    
    ;
    if (getUnits() == 0) {
        kill();
    }
    if (getTicks() == 0) {
        Actor::stun();
        int x = getX();
        int y = getY();
        
        
        int j = randInt(1, 3);
        if (j == 3) {
            biteOthers(getX(), getY());
            return;
        }

        int units = checkFood(x, y, sw, MAX_FOOD_GRASSHOPPER);
        updateHP(units);
        if (units != 0) {
            int l = randInt(1, 2);
            if (l == 2) {
                return;
            }
        }
        if (distance == 0)
            resetDirection(d, distance);
        setDirection(d);
        int k = randInt(1, 10);
        if (k == 1 && checkIfSolidLocation(x, y)) {
            
            int l = randInt(0, coordinateVector.size() - 1);
            sw->setVector(this, coordinateVector[l].x, coordinateVector[l].y, d, x, y);
            moveTo(coordinateVector[l].x, coordinateVector[l].y);
            
        
        }
        Actor::move(this, x, y, getDirection(), distance, sw);
    } else {
        reduceTicks();
    }
}
//Similar to babyGrasshopper's do something, except for bite and finding other location to jump to.

void adultGrasshopper::biteOthers(int x, int y) {
    list<Actor*>::iterator i;
    list<Actor*>::iterator temp;
    vector<Actor*> storage;
    int counter = 0;
    list<Actor*> l = sw->getThisVector(x, y);

    if (!l.empty()) {
        i = l.begin();

            while (i != l.end()) {
                if ((*i)->isEnergyHolder()) {
                    Actor* temp3 = *i;
                EnergyHolder* temp2 = dynamic_cast<EnergyHolder*>(temp3);
                if (temp2 != nullptr && temp2->isInsect() && temp2 != this )
                    
                    storage.push_back(temp2);
                    counter++;
                
                }
                i++;
                }
            }
    if (!storage.empty()) {
    int j = randInt(0, storage.size()-1);
    storage[j]->updateHP(-50);
    Actor* temporary = storage[j];
    adultGrasshopper* value = dynamic_cast<adultGrasshopper*>(temporary);
    if (value != nullptr) {
        int i = randInt(1, 2);
        if (i == 2)
        value->biteOthers(x, y);
    }
    }
}
//Find bite possibilities.
    
    









bool adultGrasshopper::checkIfSolidLocation(int x, int y) {
    int checkX;
    int checkY;
    coord temp;
    coordinateVector.clear(); 
    
    int counter =0;
    for (int i = 0; i < 360; i = i + 12 ) {
        checkX =  10 *  roundAwayFromZero(cos(i)) + x;
        checkY = 10 * roundAwayFromZero(sin(i)) + y;
        if(checkX >= 0 && checkX < VIEW_WIDTH && checkY >= 0 && checkY < VIEW_HEIGHT) {
            counter++;
            temp.x = checkX;
            temp.y = checkY;
            coordinateVector.push_back(temp);
            
        }
    
        
        
        
    }
    
    if (counter > 0)
    return true;
    
    return false;
}


//--------------------------------------------------------------------------------------------------------------------------------------------


//AntHill Implementation


AntHill::AntHill(int x, int y, StudentWorld* someWorld, int value, Compiler* someCompiler ): GraphObject(IID_ANT_HILL, x, y, right, 2 ) {
    updateHP(8999);
    m_colony = value;
    m_compiler = someCompiler;
    sw = someWorld;
    setAlive();
}
bool AntHill::isPheromone() {
    return false;
}
bool AntHill::isInsect() {
    return false;
}
int AntHill::getColony() {
    return m_colony;
}


bool AntHill::isFood() {
    return false;
}
void AntHill::doSomething() {
    updateHP(-1);
    if (getUnits() <= 0) {
        setDead();
        return;
    }
    int x = getX();
    int y = getY();
    int units = checkFood(x, y, sw, MAX_FOOD_ANTHILL);
    if (units != 0) {
        updateHP(units);
        return;
    }
    while (getUnits() >= 2000)
    addAnAnt();
        
}
void AntHill::addAnAnt() {
    
        //add an ant into this fucking game somehow
    sw->addAnt(getX(), getY(), m_compiler, m_colony);
    updateHP(-1500);
}






//--------------------------------------------------------------------------------------------------------------------------------------------


//Ant Implementation

Ant::Ant(int x, int y, StudentWorld* someWorld, Compiler* someCompiler, int value): GraphObject(value, x, y, right, 1) {
    sw = someWorld;
    m_compiler = someCompiler;
    setAlive();
    m_colony = value;
    d = randomDirection();
    setDirection(d); 
    updateHP( 1500);
     amtFood = 0;
    ic = 0;
    randomNumber = 0;
    distance = 0;
}

bool Ant::isPheromone() {
    return false;
}
int Ant::getColony() {
    return m_colony;
}
bool Ant::isInsect() {
    return true;
}
void Ant::doSomething() {

    
    
    updateHP(-1);
    
    if (getUnits() == 0) {
        sw->setFoodAtPosition(getX(), getY(), 100);
        setDead();
        sw->updateAntCounter(getColony());
        return;
    }
    
    if (getTicks() == 0) {
        list<Actor*> temp;
        list<Actor*>::iterator j;
        Actor::stun();
    Compiler::Command cmd;
    int x = getX();
    int y = getY();
        for (int i = 0; i < 10; i++) {
        if (! m_compiler ->getCommand(ic, cmd)) {
            sw->setFoodAtPosition(getX(), getY(), 100);
            setDead();
            sw->updateAntCounter(getColony());
            return ;

        }
        switch (cmd.opcode) {
            case Compiler::emitPheromone:
                temp = sw->getThisVector(getX(), getY());
                j = temp.begin();
                while (j != temp.end()) {
                    if ((*j)->isEnergyHolder()) {
                        Actor* value = *j;
                    EnergyHolder* some = dynamic_cast<EnergyHolder*>(value);
                    if (some != nullptr && some->isPheromone() && some->getColony() == getColony())
                        if (some->getUnits() != getUnits() && some->getUnits() + 256 >= 768) {
                            some->updateHP(-some->getUnits());
                            some->updateHP(768);
                            ic++;
                            break;
                        }
                    }
                    j++;
                }
                sw->addPheromone(x, y, m_colony);
                ic++;

                return;
                break;
            case Compiler::rotateCounterClockwise:

                rotateCounterClockwise();
                ic++;
                return;
                break;
            case Compiler::if_command:

                if (!checkIfCommand(stoi(cmd.operand1), ic)) {
                    ic++;
                    break;
                }
                    ic = stoi(cmd.operand2);
                

                
                break;
            case Compiler::goto_command:

                ic = stoi(cmd.operand1);
                break;
            case Compiler::faceRandomDirection:
                setDirection(randomDirection());
                ic++;

                return;
                break;
            case Compiler::generateRandomNumber:

                randomNumber = randInt(0, stoi(cmd.operand1));
                ic++;
                break;
            case Compiler::pickupFood:
                pickUpSomeFood();
                ic++;
                return;
                break;
            case Compiler::rotateClockwise:
                rotateClockwise();
                ic++;
                return;
                break;
            case Compiler::moveForward:
                x = getX();
                y = getY();
                Actor::move(this, x, y, getDirection(), distance, sw);
                if (x == getX() && y == getY()) {
                    setBlockedTrue();
                    
                } else {
                    setBlockedFalse();
                    setBittenFalse();
                }
                ic++;
                return;
                break;
            case Compiler::bite:
                if (checkEnemies()) {
                    bite();
                    return;
                }
                ic++;
                return;
                break;
            case Compiler::dropFood:
                dropSomeFood();
                ic++;
                return;
                break;
            case Compiler::eatFood:
                eatSomeFood();
                ic++;
                return;
                break;
                
        
    }
        }
    return;
    } else {
        reduceTicks();
    }
}
bool Ant::isFood() {
    return false;
}
void Ant::rotateCounterClockwise() {
    switch(d) {
    case GraphObject::up:
            d = left;
            break;
        case GraphObject::right:
            d = up;
            break;
            
        case GraphObject::down:
            d = right;
            break;
        case GraphObject::left:
            d = down;
            break;
        default:
            break;
    }
    setDirection(d);
}

void Ant::rotateClockwise() {
    switch(d) {
        case GraphObject::down:
            d = left;
            break;
        case GraphObject::left:
            d = up;
            break;
        case GraphObject::up:
            d = right;
            break;
        case GraphObject::right:
            d = down;
            break;
    }
    setDirection(d);
}
void Ant::dropSomeFood() {
    bool setDown = false;
    list<Actor*> i = sw->getThisVector(getX(), getY());
    list<Actor*>::iterator temp = i.begin();
    while (temp != i.end()) {
        if ((*temp)->isEnergyHolder()) {
            Actor* value = *temp;
            EnergyHolder* some = dynamic_cast<EnergyHolder*>(value);
            if (some ->isFood()) {
                some->updateHP(amtFood);
                amtFood = 0;
                setDown = true;
            }
            
        }
        temp++;
    }
    if (!setDown) {
        sw->setFoodAtPosition(getX(), getY(), amtFood);
        amtFood = 0;
        setDown  = true;
    }
   }

void Ant::pickUpSomeFood() {
    
    
    list<Actor*> j = sw->getThisVector(getX(), getY());
    list<Actor*>::iterator temp = j.begin();
    while (temp != j.end()) {
        Actor* value = *temp;
        EnergyHolder* some = dynamic_cast<EnergyHolder*>(value);
        if (some->isFood()) {
            int units = some->getUnits();
            if (units > 400)
                units = 400;
            if (units + amtFood>= 1800) {
                amtFood = 1800;
                some->updateHP(-(1800-amtFood));
                break;
            }
            
            amtFood += units;
            some->setDead();
        }
        temp++;

        
    }
    
}
void Ant::eatSomeFood() {
    if (amtFood > 100) {
        updateHP(100);
        amtFood -= 100;
    }
    updateHP(amtFood);
    amtFood = 0;
}
bool Ant::checkEnemies() {
    BitePossibilities.clear();
    list<Actor*>::iterator i;
    list<Actor*> temp = sw->getThisVector(getX(), getY());
    i = temp.begin();
    while (i != temp.end()) {
        if ((*i)->isEnergyHolder()) {
            Actor* value = *i;
            EnergyHolder* some = dynamic_cast<EnergyHolder*>(value);
            if (some != nullptr && some->isInsect()) {
       
        
        switch (m_colony) {
            case IID_ANT_TYPE0:
                if (some ->getColony() != IID_ANT_TYPE0 )
                    BitePossibilities.push_back(*i);
                break;
            case IID_ANT_TYPE1:
                if (some ->getColony() != IID_ANT_TYPE1 )
                    BitePossibilities.push_back(*i);
                
                break;
            case IID_ANT_TYPE2:
                if (some ->getColony() != IID_ANT_TYPE2)
                    BitePossibilities.push_back(*i);
                break;
            case IID_ANT_TYPE3:
                if (some -> getColony() != IID_ANT_TYPE3)
                    BitePossibilities.push_back(*i);
                break;
            default:
                break;
        }
            
        }
    }
    }
    if (BitePossibilities.size() != 0)
        return true;
    return false;
}

void Ant::bite() {
    
    int i = randInt(0, BitePossibilities.size() - 1);
    
    BitePossibilities[i]->updateHP(-15);
}


bool Ant::checkIfCommand(int operand1, int& ic) {
    list<Actor*> temp = sw->getThisVector(getX(), getY());
    list<Actor*> directionTemp;
    list<Actor*>::iterator i;
    switch(getDirection()) {
case up:
    directionTemp = sw->getThisVector(getX(), getY()-1);
    break;
case down:
    directionTemp = sw->getThisVector(getX(), getY()+1);
    break;
case left:
    directionTemp = sw->getThisVector(getX()-1, getY());
    break;
case right:
    directionTemp = sw->getThisVector(getX()+1, getY());
    break;
    }
    switch(operand1) {
        case 1:
            if (randomNumber  == 0) {
                return true;
            }
            
            
            
            break;
            
            
        case 2:

            if ( amtFood != 0) {
                return true;
            }
            
            
            break;
        case 3:

            if (amtFood <= 25) {
                return true;
            }
            
                       break;
        case 4:
            //Get Enemy

            i = temp.begin();
            while (i != temp.end()) {
                if ((*i)->isEnergyHolder()){
                    Actor* value = *i;
                    EnergyHolder* some = dynamic_cast<EnergyHolder*>(value);
                    if (some != nullptr && some->isInsect() && some->getColony() != getColony()) {

                        return true;
                    }
                }
                i++;
            }

            break;
        case 5:

            i = temp.begin();
            while (i != temp.end()) {
                if ((*i)->isEnergyHolder()) {
                    Actor* value = *i;
                    EnergyHolder* some = dynamic_cast<EnergyHolder*>(value);
                    if (some != nullptr && some->isFood()) {

                        return true;
                    }
                }
                i++;
            }
            
            break;
        case 6:
            //anthill

            i = temp.begin();
            while (i != temp.end()) {
                if ((*i)->isEnergyHolder()) {
                    Actor* value = *i;
                    EnergyHolder* some = dynamic_cast<EnergyHolder*>(value);
                    if (some != nullptr && !some->isInsect() && some->getColony() == getColony()) {

                        return true;
                    }
                }
                i++;
            }

            break;
        case 7:
            //Pheromone

            i = directionTemp.begin();
            while (i != directionTemp.end()) {
                if ((*i)->isEnergyHolder()) {
                    Actor* value = *i;
                    EnergyHolder* some = dynamic_cast<EnergyHolder*>(value);
                    if (some != nullptr) {
                        if (some ->isPheromone()) {
                            return true;
                        }
                    }
                }
                i++;
            }
                        break;
        case 8:

            i = directionTemp.begin();
            while (i != directionTemp.end()) {
                if ((*i)->isEnergyHolder()) {
                    Actor* value = *i;
                    EnergyHolder* some = dynamic_cast<EnergyHolder*>(value);
                    if (some != nullptr) {
                        if (some->isInsect() && some != this && some->getColony() != getColony()) {
                            return true;
                            
                        }
                    }
                }
                i++;
            }
                        break;
        case 9:
            if (isBitten()) {
                
                return true;
            }
            break;
        case 10:
            
            if (getBlocked())
                return true;
            break;
        default:
            break;
    }
        
        

        return false;
}


void Ant::setBlockedTrue() {
    m_blocked = true; 
}
void Ant::setBlockedFalse() {
    m_blocked = false; 
}

bool Ant::getBlocked() {
    return m_blocked;
}








//--------------------------------------------------------------------------------------------------------------------------------------------

//Pheromone Implementation


Pheromone::Pheromone(int x, int y, StudentWorld* someWorld, int type, int colonyType): GraphObject(type, x, y, right, 2) {
    
    sw = someWorld;
    m_type = type;
    setAlive();
    updateHP(256);
    colony = colonyType;
}
bool Pheromone::isPheromone() {
    return true; 
}
int Pheromone::getColony() {
    return colony;
}
bool Pheromone::isFood() {
    return false;
}
bool Pheromone::isInsect() {
    return false;
    
}

void Pheromone::doSomething() {
    updateHP(-1);
    
    if (getUnits() == 0)
        setDead();
}







//--------------------------------------------------------------------------------------------------------------------------------------------


//EnergyHolder Implementation


bool EnergyHolder::isEnergyHolder() {
    return true;
    
}

bool EnergyHolder::isBitten() {
    return m_bitten;
}

void EnergyHolder::setBitten() {
    m_bitten = true; 
}

void EnergyHolder::setBittenFalse() {
    m_bitten = false; 
}

int EnergyHolder::getUnits() {
    return m_units;
}

void EnergyHolder::updateHP(int hp) {
    m_units += hp;
}


