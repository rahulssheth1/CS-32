//
//  Rats.hpp
//  Project 1 CS 32
//
//  Created by Rahul Sheth on 1/10/17.
//  Copyright © 2017 Rahul Sheth. All rights reserved.
//
using namespace std;
#ifndef Rats//.h
#define Rats.h
#include "Arena.h"
class Rat
{
public:
    // Constructor
    Rat(Arena* ap, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;
    
    // Mutators
    void move();
    
private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    int    m_health;
    int    m_idleTurnsRemaining;
};

#endif
