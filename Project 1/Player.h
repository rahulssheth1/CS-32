//
//  Player.hpp
//  Project 1 CS 32
//
//  Created by Rahul Sheth on 1/10/17.
//  Copyright © 2017 Rahul Sheth. All rights reserved.
//

//#ifndef Player_hpp
//#define Player_hpp
//
//#include <stdio.h>
//
//#endif /* Player_hpp */

#ifndef Player.h
#define Player.h
using namespace std;
#include "Arena.h"

class Player
{
public:
    // Constructor
    Player(Arena* ap, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;
    
    // Mutators
    string dropPoisonPellet();
    string move(int dir);
    void   setDead();
    
private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    bool   m_dead;
};

#endif

