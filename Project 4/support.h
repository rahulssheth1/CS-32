//
//  support.h
//  Project 4 Real
//
//  Created by Rahul Sheth on 3/13/17.
//  Copyright © 2017 Rahul Sheth. All rights reserved.
//

#ifndef support_h
#define support_h
#include <string>
#include "provided.h"
#endif /* support_h */



bool operator== (GeoCoord &g1, GeoCoord &g2);
bool operator< (GeoCoord &g1, GeoCoord &g2);
bool operator> (GeoCoord &g1, GeoCoord &g2);
bool operator!= (GeoCoord& g1, GeoCoord &g2);


bool operator== (const GeoCoord& g1, GeoCoord& g2);
bool operator== (StreetSegment& s1, StreetSegment& s2); 
bool operator== (GeoSegment& s1, GeoSegment& s2);
bool operator== (const Attraction& a1, const Attraction& a2); 
struct node {
    node* parent;
    GeoCoord gc;
    double heuristic;
    
};

bool operator< (node& n1, node& n2);
bool operator== (node& n1, node& n2);
bool operator> (node& n1, node& n2);
bool operator!= (node& n1, node& n2); 
