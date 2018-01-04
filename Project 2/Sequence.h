//
//  Sequence.hpp
//  Project 2
//
//  Created by Rahul Sheth on 1/25/17.
//  Copyright © 2017 Rahul Sheth. All rights reserved.
//

#ifndef Sequence_h
#define Sequence_h
#include <string>

typedef std::string ItemType;

class Sequence
{
public:
    Sequence();
    Sequence(Sequence &old);
    Sequence operator= (const Sequence &other);
    bool empty() const; //
    int size() const; //
    ~Sequence(); 
    bool insert(int pos, const ItemType& value); //
    int insert(const ItemType& value);
    bool erase(int pos);
    int remove(const ItemType& value); //
    bool get(int pos, ItemType& value) const; //
    bool set(int pos, const ItemType& value); //
    int find(const ItemType& value) const; //
    void swap(Sequence& other); //
    
private:
    struct Node {
        ItemType value;
        Node* next;
        Node* prev; 
    };
    Node* head;
    int m_size;
};


int subsequence(const Sequence& seq1, const Sequence& seq2);


void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);

#endif /* Sequence_hpp */
