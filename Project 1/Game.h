//
//  Game.h
//  Project 1 CS 32
//
//  Created by Rahul Sheth on 1/10/17.
//  Copyright © 2017 Rahul Sheth. All rights reserved.
//
//
//#ifndef Game_hpp
//#define Game_hpp
//
//#include <stdio.h>
//
//#endif /* Game_hpp */
using namespace std;


class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nRats);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Arena* m_arena;
    
    // Helper functions
    string takePlayerTurn();
};


