//
//  Arena.hpp
//  Project 1 CS 32
//
//  Created by Rahul Sheth on 1/10/17.
//  Copyright © 2017 Rahul Sheth. All rights reserved.
//
//
//
//#include <stdio.h>
//
//#endif /* Arena_hpp */
#ifndef Arena_h
#define Arena_h


#include <iostream>
using namespace std;
#include "globals.h"
#include "Rats.h"
#include "Player.h"


class Arena
{
public:
    // Constructor/destructor
    Arena(int nRows, int nCols);
    ~Arena();
    
    // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     ratCount() const;
    int     getCellStatus(int r, int c) const;
    int     numberOfRatsAt(int r, int c) const;
    void    display(string msg) const;
    
    // Mutators
    void setCellStatus(int r, int c, int status);
    bool addRat(int r, int c);
    bool addPlayer(int r, int c);
    void moveRats();
    
private:
    int     m_grid[MAXROWS][MAXCOLS];
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Rat*    m_rats[MAXRATS];
    int     m_nRats;
    int     m_turns;
    
    // Helper functions
    void checkPos(int r, int c) const;
    bool isPosInBounds(int r, int c) const;
};
#endif
