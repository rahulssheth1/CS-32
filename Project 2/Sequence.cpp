//
//  Sequence.cpp
//  Project 2
//
//  Created by Rahul Sheth on 1/25/17.
//  Copyright © 2017 Rahul Sheth. All rights reserved.
//

#include "Sequence.h"
#include <iostream>

Sequence::Sequence() {
    head = nullptr;
    m_size = 0;
    
    //initializes the sequence at 0 size with nullptr head
}
Sequence::Sequence(Sequence &old) {
    Node *p = old.head;
    head = new Node;
    head -> prev = nullptr;
    head -> value = old.head -> value;
    Node *x = head;
    p = p->next;
    //Assign the first value of the new sequence to the first value of the old sequence
    while (p != nullptr) {
        Node *insert;
        insert = new Node;
        x->next  = insert;
        insert -> next = nullptr;
        insert -> prev = x;
        insert -> value = p->value;
        
        
        //Continuously copies values from the old sequence to the new one
        
        p = p->next;
        x = x-> next;
        //Increments
    }
    
    m_size = old.m_size;

}

Sequence Sequence::operator= (const Sequence &other) {
    
    if (&other == this)
        return *this;
    
    if (head == nullptr) {
        head = new Node;
        head -> next = nullptr;
        head -> prev = nullptr;
        //Initialize the new sequence if it hasn't yet
    }
   
    
    
    if (m_size > other.m_size) {
        Node *p;
        head -> value = other.head -> value;
        p = other.head;
        Node *x = head;

        Node *temp = nullptr;
        //Assign the first value of new to old head value
        while ((p != nullptr) && (x != nullptr)) {
            x->value = p->value;
            x = x->next;
            p = p->next;
            //Insert all the values from the old sequence
        }
        
        while (x -> next != nullptr) {
            temp = x->next;
        
            delete x;
        x = temp;
            //Delete all excess values from the changing sequence
            
        }
        
        m_size = other.m_size;
        //Sets the sizes equal in the end
    }
    
    else if (other.m_size > m_size) {
        Node *p;
        head -> value = other.head -> value;
        p = other.head;
        Node *x = head;
        //Sets the head values equal to each other
        
        while (x  != nullptr) {
            x->value = p->value;
            x-> next -> prev = x;
            x = x->next;
            p = p->next;
            //If there is a lack of nodes in LHS sequence, then work with the nodes you already have
            
        }
        
        while (p != nullptr) {
            Node *temp = new Node;
            x = temp;
            x-> next -> prev = x;
            x->value = p->value;
            x = x->next;
            p = p->next;
            //Insert new nodes to LHS Sequence and set them equal to RHS nodes
            
        }
        m_size = other.m_size;
    } else  {
        Node *p;
        head -> value = other.head -> value;
        p = other.head;
        Node *x = head;
        //Set head values equal
        
        while (p != nullptr) {
            x->value  = p->value;
            x= x->next;
            p = p->next;
            //Sizes are equal. simply assign
        }
        m_size = other.m_size;

    }
    
    return (*this);
}
     

Sequence::~Sequence() {
    Node *p;
    
    p = head;
    
    while (p != nullptr) {
        Node *temp = p->next;
        delete p;
        p = temp;
        //Destroys all the nodes in the sequence
        
    }
}

bool Sequence::empty() const{
    if (head == nullptr)
        return true;
    //Return if the first value is null, indicating no values
    
    return false;
}
int Sequence::size() const {
    return m_size;
}




int Sequence::remove(const ItemType &value) {
    int countRemoved = 0;
    
    if (head->value == value) {
        if (head -> next != nullptr) {
            //Checks if value is found at head and if its valid
            Node *temp = head -> next;
            delete head;
            head = temp;
            m_size--;
            countRemoved++;
            //Delete node and increment count
        } else {
            delete head;
            head = nullptr; 
            m_size--;
            countRemoved++;
            //If head is only value
        }
        
    }
     
    Node *p;
    p = head;
    Node *remove;
    while (p  != nullptr) {
        if ((p->next != nullptr) && (p ->next-> value == value)) {
            //Find node above and replace next node with node after
            remove = p -> next;
            p->next = remove->next;
            remove ->prev = p;
            delete remove;
            countRemoved++;
            continue;
            //Increment count but not the p-value since it has been replaced
            
            
        }
        p = p->next;
    }
    
    
    return countRemoved;
    
    
}


bool Sequence::erase(int pos) {
    if ((pos < 0) || (pos >= size())) {
        return false;
    }
    //Check if pos is valid
    if (pos == 0) {
        Node* temp = head ->next;
        
    delete head;
    head = temp;
        m_size--;
        return true;
        //replace the head and move the original head up one
    }
    int counter = 0;
    Node *p;
    p = head;
    while (p != nullptr) {

        if (counter == pos - 1 ) {
            m_size--; 
            //If you've hit the node above the one in question
            if (p->next != nullptr) {
            Node* temp = p->next;
            p->next = temp->next;
                temp -> prev = p;
                delete temp;
                //Replace the node in question with the one above that in question
                return true;
                
            
            } else {
                Node* temp = p->prev;
                delete p;
                temp->next = nullptr;
                return true;
                //Replacement code when it is the last node
                
            }
        }

        counter++;
        p = p->next;
        //INcrement and move thru the loop 
            
    }
    

return false;
}


bool Sequence::insert(int pos, const ItemType &value) {
 
    if ((pos < 0) || (pos > size())) {
        return false;
    }
    if (empty() == true) {
        Node* p;
        p = new Node;
        p->value = value;
        p->next = head;
        p->prev = nullptr;
        head = p;
        m_size++;
        return true;
        //Create head value if no other nodes
    }
    
    
    
    else if (pos == 0) {
        Node* p;
        p = new Node;
        p->value = value;
        p->next = head;
        head = p;
        head -> prev = nullptr;
        m_size++;
        //Insert as head value and move head up one
        return true;
        } else {
    
            int counter = 0; 
            Node* p;
            p = head;
            
            while (p -> next != nullptr) {
                if (counter  == pos - 1) {
                    break;
                    //If you have found node above node in question

                }
                counter++;
                p = p->next;
            }
            Node* insert;
            insert = new Node;
            insert -> next = p->next;
            p->next = insert;
            insert -> value = value;
            m_size++;
            //Insert and move all others up
            return true;
           }
}

int Sequence::insert(const ItemType &value) {
    
    Node *p;

    
    if ((empty() == true) || (value <= head->value)) {
        p = new Node;
        p->value = value;
        p->next = head;
        p-> prev = nullptr;
        head = p;
        //Insert at head node and move others up
        
        m_size++; 
        return 0;
        
    }
    else {
        int counter = 0;
        p = head;
        while (p->next != nullptr) {
            if (p->next ->value >= value ) {
                Node *insert;
                insert = new Node;
                insert -> next = p -> next;
                p->next = insert;
                insert -> prev = p;
                insert -> value = value;
                ///Insert value at node before so the rest move up
                m_size++;
                return counter;
            }
            counter++;
            p = p-> next;
        }
    }
    Node *insert;
    insert = new Node;
    p-> next = insert;
    insert -> prev = p;
    insert -> next = nullptr;
    insert -> value = value;
    m_size++;
    //INsert values in
    return m_size;
}


int Sequence::find(const ItemType &value) const {
    Node *p;
    p = head;
    int counter = 0;
    while (p != nullptr) {
        
        if (p->value == value) {
            return counter;
        }
        counter++;

        p = p->next;
        //Increment a counter to keep track of pos and find when value appears
        
    }
    return -1;
    
}




bool Sequence::get(int pos, ItemType& value) const {
    
    
    if ((pos < 0) || (pos >= size()))
        return false;
        
        
        int counter = 0;
    
    Node *p;
    p = head;
    
    while (p != nullptr) {
        if (counter == pos) {
            value = p->value;
            return true;
            //find value at pos and set it equal to value you need
        }
        counter++;
        p = p->next;
    }
    return false; 
}


bool Sequence::set(int pos, const ItemType &value) {
    if ((pos < 0) || ( pos >= size())) {
        return false;
    } else {
        int counter = 0;
        Node *p;
        p = head;
        while (p != nullptr) {
            if (counter == pos) {
                p->value = value;
                //Find value at pos and change value in pos to value you pass thru
                return true;
            }
            
            counter++;
            p = p->next;
        }
    return false;
    }
}


void Sequence::swap(Sequence &other) {
    Node *temp;
    
    temp = other.head;
    other.head = this-> head;
    this->head = temp;
    //Swap the head nodes of each so they point thru diff sequences
    
    int temp2 = other.m_size;
    other.m_size = this -> m_size;
    this -> m_size = temp2;
    //Change the sizes
    
}


int subsequence(const Sequence& seq1, const Sequence& seq2) {
    
    if ((seq2.size() > seq1.size()) || (seq2.empty() == true)) {
        return -1;
    }
    
    ItemType value1;
    ItemType value2;
    int temp;
    int y;
    int z;
    
    for (int x = 0; x < seq1.size(); x++) {
        seq1.get(x, value1);
        seq2.get(x, value2);
        //Get the values you need to check
        if ((value1 == value2) && (x + seq2.size() -1 <= seq1.size())) {
            temp = x;
            y = x;
            z = 0; 
            while (value1 == value2) {
                seq1.get(y, value1);
                seq2.get(z, value2);
                //Continuously check values thru

                if (z == seq2.size()) {
                    return temp;
                    //If you hit end of second sequence, you have a valid subsequence
                }
                y++; 
                z++;
                
            }
                
                
            }
        }
    
    
    
    return -1;
}

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result) {
    
    int size;
    bool checker;
    
    if ((&seq1 == &result) || (&seq2 == &result))
        return;
    if (seq1.size() > seq2.size()) {
        size = seq1.size();
        checker = true;
        
    }
    else {
        size = seq2.size();
        checker = false;
    }
    //Choose the greater size and keep track of what you chose with bool
    ItemType value1;
    ItemType value2;
    int y = 0;
    int size2 = result.size();
    for (int i = 0; i < size2; i++)
        result.erase(0);
    //Make result empty 
    
    for (int x = 0; x < size; x++) {
    
        if ((checker == true) && (x > seq2.size() -1)){
                seq1.get(x, value1);
                result.insert(y, value1);
                y++;
            //add only values from the larger sequence if you hit max of other sequence
            
        } else if ((checker == false) && ( x > seq1.size() - 1)) {
                seq2.get(x, value2);
                result.insert(y, value2);
                y++;
            //add only values from the larger sequence if you hit max of other sequence

        
         
        } else {
            seq1.get(x, value1);
            seq2.get(x, value2);
            
            result.insert(y, value1);
            result.insert(y+1, value2);
            y= y+2;
            //Add values from both sequence in consecutive order 
}
}
    
}







