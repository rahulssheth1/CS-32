//
//  support.cpp
//  Project 4 Real
//
//  Created by Rahul Sheth on 3/13/17.
//  Copyright © 2017 Rahul Sheth. All rights reserved.
//

#include <stdio.h>
#include "support.h"
//Operators for regular coords
bool operator== (GeoCoord &g1, GeoCoord &g2)  {
    
    if (g1.latitude == g2.latitude && g1.longitude == g2.longitude)
        return true;
    
    
    return false;
}


bool operator< (GeoCoord &g1, GeoCoord &g2) {
    
    return (g1.latitude < g2.latitude);
    
    
}

bool operator> (GeoCoord &g1, GeoCoord &g2) {
    return (g1.latitude > g2.latitude);
}

bool operator!= (GeoCoord &g1, GeoCoord &g2) {
    return (g1.longitude != g2.longitude || g1.latitude != g2.latitude);
    
}


//Operators for const coords
bool operator== (const GeoCoord& g1, const GeoCoord& g2) {
    return (g1.latitude == g2.latitude && g1.longitude == g2.longitude); 
}

bool operator== (const Attraction& a1, const Attraction& a2) {
    return a1.name == a2.name;
}

bool operator== (GeoSegment& s1, GeoSegment& s2) {
    return (s1.end == s2.end && s1.start == s2.start);
}
bool operator== (StreetSegment& s1, StreetSegment& s2) {
    return (s1.attractions == s2.attractions && s1.segment == s2.segment && s1.streetName == s2.streetName); 
}




//Operators for nodes 
bool operator< (node& n1, node& n2) {
    return n1.heuristic < n2.heuristic;
}
bool operator== (node& n1, node& n2) {
    return n1.heuristic == n2.heuristic && n1.parent == n2.parent && n1.gc == n2.gc;
}
bool operator> (node& n1, node& n2) {
    return n1.heuristic > n2.heuristic; 
}


bool operator!= (node& n1, node& n2) {
    return n1.heuristic != n2.heuristic || n1.parent != n2.parent || n1.gc != n2.gc;

}


