//#ifndef MYMAP_INCLUDED
//#define MYMAP_INCLUDED
//
//#include <map>  // YOU MUST NOT USE THIS HEADER IN CODE YOU TURN IN
//
//#include <stdio.h>
//#include "support.h"
//#include <iostream>
// In accordance with the spec, YOU MUST NOT TURN IN THIS CLASS TEMPLATE,
// since you are not allowed to use any STL associative containers, and
// this implementation uses std::map.

// This code is deliberately obfuscated.

// If you can not get your own MyMap class template working, you may use
// this one during development in order to let you proceed with implementing
// the other classes for this project; you can then go back to working on
// fixing your own MyMap class template.
//
//template <typename KeyType, typename ValueType>
//class MyMap
//{
//public:
//    MyMap(const MyMap &other) = delete;
//    MyMap &operator=(const MyMap &other) = delete;
//    typedef KeyType O;using O1=int;void clear(){l01.clear();}
//    using l0=ValueType;MyMap(){}using l10=O const;O1 size()
//    const{return l01.size();}using ll0=l0 const;using Const=
//    MyMap<O,l0>;void associate(l10&Using,ll0&first){l01[
//                                                        Using]=first;}using l1=std::map<O,l0>;using l00=Const
//    const;ll0*find(l10&l11)const{auto first=l01.find(l11);
//        return(first!=l01.end()?&first->second:0);}l0*find(l10&
//                                                           l01){return(l0*)(*(l00*)(this)).find(l01);}private:l1
//    l01;
//};
//
//#endif // MYMAP_INCLUDED


//
//  MyMap.hpp
//  Project 4
//
//  Created by Rahul Sheth on 3/8/17.
//  Copyright © 2017 Rahul Sheth. All rights reserved.
//

#ifndef MyMap_h
#define MyMap_h
#include <stdio.h>
#include "support.h"
#include <iostream>
// MyMap.h

// Skeleton for the MyMap class template.  You must implement the first six
// member functions.

template<typename KeyType, typename ValueType>

class MyMap
{
public:
    MyMap() {
        root = nullptr;
        m_size = 0; 
    }
    //Initialize tree
    ~MyMap() {
        clear();
        
    }
    //Clear is same as destructing
    void clear() {
        Free(root);
        m_size = 0;
    }
    //Call recursive helper
    int size() const {
        return m_size;
    }
    void associate(const KeyType& key, const ValueType& value) {
        ValueType* some = find(key);
        if (some != nullptr) {
            ValueType* temp = some;
            *temp = value;
            return;
        }
        //some != nullptr means that value is found.
        Node* temp = new Node(key, value);
        
        insert(temp, root);
        m_size++;
        //Otherwise insert new
        
    }
    //
    
    // for a map that can't be modified, return a pointer to const ValueType
    const ValueType* find(const KeyType& key) const {
        
        Node* temp = search(key, root);
            
        const ValueType* temp2 = &temp->value;
        if (temp != nullptr) {
            return temp2;
            //This is if search was successful
        }
        
        return  nullptr;
        //Not
    }
    
    // for a modifiable map, return a pointer to modifiable ValueType
    ValueType* find(const KeyType& key)
    {
        
        
        return const_cast<ValueType*>(const_cast<const MyMap*>(this)->find(key));
    }

    
    
    // C++11 syntax for preventing copying and assignment
    MyMap(const MyMap&) = delete;
    MyMap& operator=(const MyMap&) = delete;
    
private:
   

    struct Node {
        Node* right;
        Node* left;
        ValueType value;
        KeyType key;
        Node( const KeyType& m_key, const ValueType& m_value) {
            key = m_key;
            value = m_value;
            left = right = nullptr;
        }
        
    };
    
    void Free(Node* &cur) {
        if (cur == nullptr) {
            return;
        }
        Free(cur->left);
    

        Free(cur->right);
        
        delete cur;
    }
    //Recursive deletion
    
    Node* search( KeyType key, Node* cur)  const {
        if (cur == nullptr) {
            return nullptr;
        } else {
        if (cur->key == key) {
            return cur;
        }
        else if (cur->key < key) {

            return search(key, cur->right);
        }
        else {

            return search(key, cur->left);
        
        }
        }
    }
    //Checks the tree recursively for the values
    void insert( Node* temp, Node* &cur) {
        if (cur == nullptr) {
            cur = temp;
            return;
        }
        
        if (cur->key < temp->key) {
            insert(temp, cur->right);
        }
        else {
            insert(temp, cur->left);
        }
    }
    //Insert recursively 
    Node* root;
    int m_size;
}; 









#endif /* MyMap_hpp */
