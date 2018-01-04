#include <string>
#include <vector>
#include "MyMap.h"
#include <iostream>
using namespace std;

class NavigatorImpl
{
public:
    NavigatorImpl();
    ~NavigatorImpl();
    bool loadMapData(string mapFile);
    NavResult navigate(string start, string end, vector<NavSegment>& directions) const;
    
private:
    AttractionMapper am;
    SegmentMapper sm;
    MapLoader ml;
    
 
   
    
    
    void insert(vector<node>& some, node a, int heuristic) const {
        vector<node>::iterator l;
        
        l = some.begin();
        while (l != some.end()) {
            if ((*l).heuristic > heuristic) {
                some.insert(l, a);
                return;
            }
            l++;
        }
        some.insert(some.end(), a);
    }

    
    bool presentInClosedVector(vector<node>& some, node& temp) const {
        for (int i = 0; i < some.size(); i++)
            if (temp == some[i])
                return true;
        
        return false;
    }
    
    bool presentInVector(vector<node>& some, node& temp) const {
        for (int i = 0; i < some.size(); i++) {
            if (temp == some[i] && temp.heuristic > some[i].heuristic)
                return true;
        }
        return false;
    }
    StreetSegment* getStreetNameForLarge(vector<StreetSegment>& v1, vector<StreetSegment>& v2) const {
        
        for (int i = 0; i < v1.size(); i++) {
            for (int j = 0 ; j < v2.size(); j++ ) {
                if (v1[i] == v2[j]) {
                    return &v1[i];
                }
                   
            }
        }
        
        return nullptr;
    }
    
    void  setDirectionsVector(vector<NavSegment> &directions, node& finishingNode, MyMap<node, node>& someMap, node& startingCoords, GeoCoord& endingCoords) const {
        node temp = finishingNode;
        node temp2;
        int i = 0;
        while (someMap.find(temp) != nullptr)  {
            temp2 = *someMap.find(temp);
            //Loop thru all nodes in nodeToParentNode
            NavSegment nav;
            GeoSegment some(temp2.gc, temp.gc);
            
            double angle = angleOfLine(some);
            
            nav.m_geoSegment = some;
            nav.m_distance = distanceEarthMiles(nav.m_geoSegment.start, nav.m_geoSegment.end);
            //Compute required values
            vector<StreetSegment> h = sm.getSegments(temp2.gc);
            if (h.size() > 1) {
                vector<StreetSegment> j = sm.getSegments(temp.gc);
                
                StreetSegment s1 = *getStreetNameForLarge(h, j);
                nav.m_streetName = s1.streetName;
            } else {
                nav.m_streetName = h[0].streetName;
            }
            //Loop thru the vectors to get the streetname
            if (i > 0) {
                if (directions[0].m_streetName != nav.m_streetName) {
                    nav.m_command = NavSegment::TURN;

                    if (angle >= 180) {
                        nav.m_direction = "Right";
                    }
                    else {
                        nav.m_direction = "Left";
                    }
                    directions.insert(directions.begin(), nav);
                    temp = temp2;
                    i++;
                    continue;
                    
                    //Change the type to Turn or Proceed
                } else
                    nav.m_command = NavSegment::PROCEED;
                nav.m_direction = getDirection(nav, angle);
            }
            else {
                    nav.m_direction = getDirection(nav, angle);
                }
            
            directions.insert(directions.begin(), nav);
            temp = temp2;
            i++;
            //Insert and leave
        }
        for (int i = 0; i < directions.size() - 2; i++ ) {
            if (directions[i+1].m_streetName != directions[i].m_streetName) {
                directions[i].m_streetName = directions[i+1].m_streetName;
                if (i-1 >= 0) {
            directions[i-1].m_geoSegment.end = directions[i].m_geoSegment.end;
            double angle = angleOfLine(directions[i-1].m_geoSegment);
            directions[i-1].m_direction  = getDirection(directions[i-1], angle);
                }
            }
            //Loop thru the directions vector and check if you need to change the street
        }
    }
    
    
    string getDirection(NavSegment& n1, double& angle) const {
        if (0 <= angle && angle <= 22.5)
            return "east";
        if (22.5 < angle && angle <= 67.5)
            return "northeast";
        if (67.5 < angle && angle <= 112.5)
            return "north";
        if (112.5 < angle && angle <= 157.5)
            return "northwest";
        if (157.5 < angle && angle <= 202.5)
            return "west";
        if (202.5 < angle && angle <= 247.5)
            return "southwest";
        if (247.5 < angle && angle <= 292.5)
            return "south";
        if (292.5 < angle && angle <= 337.5)
            return "southeast";
        if (337.5 < angle && angle <= 360)
            return "east";
        return "null";
        
        //Return the direction of the string based on coords
    }
    
    
};




NavigatorImpl::NavigatorImpl()
{
    
}





NavigatorImpl::~NavigatorImpl()
{
    
}

bool NavigatorImpl::loadMapData(string mapFile)
{
    if (ml.load(mapFile)) {
        am.init(ml);
        sm.init(ml);
        return true;
    
    }
    
    return false;  // This compiles, but may not be correct
}

NavResult NavigatorImpl::navigate(string start, string end, vector<NavSegment> &directions) const
{
    for (int i = 0; i < start.size(); i++ ) {
        start[i] = tolower(start[i]);
    }
    for (int j = 0; j < end.size(); j++){
        end[j] = tolower(end[j]); 
    }
    MyMap<node, node> nodeToParentNode;
    GeoCoord realEnd;
    GeoCoord endingCoords;
    GeoCoord endingCoords2;
    GeoCoord startingCoords;
    GeoCoord startingCoords2;
    if (!am.getGeoCoord(end, realEnd))
        return NAV_BAD_DESTINATION;
    //Return bad destination if invalid
    vector<StreetSegment> endingCoordVector = sm.getSegments(realEnd);
    endingCoords = endingCoordVector[0].segment.start;
    endingCoords2 = endingCoordVector[0].segment.end;
    GeoCoord temp2;
    vector<node> nodeVector;
    vector<node> closedVector;
    if (!am.getGeoCoord(start, temp2))
        return NAV_BAD_SOURCE; 
    node beginning;
    beginning.gc = temp2;
    beginning.parent = nullptr;
    vector<StreetSegment> segVector;
    segVector = sm.getSegments(temp2);
    for (int i = 0; i < segVector.size(); i++) {
        node cur;
        cur.gc = segVector[i].segment.end;
        cur.heuristic = distanceEarthMiles(beginning.gc, cur.gc);
        insert(nodeVector, cur, cur.heuristic);
        nodeToParentNode.associate(cur, beginning);
        node otherCur;
        otherCur.parent = nullptr;
        otherCur.gc = segVector[i].segment.start;
        otherCur.heuristic = distanceEarthMiles(beginning.gc, otherCur.gc);
        insert(nodeVector, otherCur, otherCur.heuristic);
        nodeToParentNode.associate(otherCur, beginning);
        //Loop thru all beginning nodes and insert into the node vector
    }
    
    while (!nodeVector.empty()) {
        vector<StreetSegment> segVector;
        node temp = nodeVector.front();
        nodeVector.erase(nodeVector.begin());
        if (presentInClosedVector(closedVector, temp))
            continue;
        
        
        segVector = sm.getSegments(temp.gc);
        //Get the segments
        
        for (int i = 0; i < segVector.size(); i++) {
            node cur;
            node cur2;
            //LOop thru segments
            bool shouldIInsert1 = true;
            bool shouldIInsert2 = true;
            cur.gc = segVector[i].segment.end;
            cur.heuristic =  distanceEarthMiles(beginning.gc, cur.gc) + distanceEarthMiles(cur.gc, realEnd);
            
            cur2.gc = segVector[i].segment.start;
            cur2.heuristic =  distanceEarthMiles(beginning.gc, cur.gc) + distanceEarthMiles(cur2.gc, realEnd);
            
            
            if (cur.gc == temp.gc)
                shouldIInsert1 = false;
            if (cur2.gc == temp.gc)
                shouldIInsert2 = false;
            
            
            if ((cur.gc == endingCoords || cur.gc == endingCoords2)) {
                //Check if the starting coords are ath the end
                nodeToParentNode.associate(cur, temp);
                node a;
                a.gc = realEnd;
               
                nodeToParentNode.associate(a, cur);
                node temp = a;
                setDirectionsVector(directions, a, nodeToParentNode, beginning, startingCoords);
                return NAV_SUCCESS;
            }
            if ((cur2.gc == endingCoords || cur2.gc == endingCoords2)) {
                
                
                //Check if the ending coords are ath the end

                nodeToParentNode.associate(cur2, temp);
                
               
                    
                node a;
                a.gc = realEnd;
                
                nodeToParentNode.associate(a, cur2);
                
                setDirectionsVector(directions, a, nodeToParentNode, beginning, startingCoords);
                return NAV_SUCCESS;
            }
            if (presentInClosedVector(closedVector, cur))
                shouldIInsert1 = false;
            if (presentInClosedVector(closedVector, cur2))
                shouldIInsert2 = false;
            if (presentInVector(nodeVector, cur2))
                shouldIInsert2 = false;
            if (presentInVector(closedVector, cur2))
                shouldIInsert2 = false;
           
            if (presentInVector(nodeVector, cur))
                shouldIInsert1 = false;
            if (presentInVector(closedVector, cur))
                shouldIInsert1 = false;
            
            //Checks to make sure that they are valid coords to insert in
            if (shouldIInsert1 == true) {

                insert(nodeVector, cur, cur.heuristic);
                
                nodeToParentNode.associate(cur, temp);
                
            }
            if (shouldIInsert2 == true) {

                insert(nodeVector, cur2, cur2.heuristic);
                
                    nodeToParentNode.associate(cur2, temp);
            }
            //Insert in

        }

        closedVector.push_back(temp);
//Push temp onto the closed vector

        
    }
    
    
    return NAV_NO_ROUTE;  // This compiles, but may not be correct
}

//******************** Navigator functions ************************************

// These functions simply delegate to NavigatorImpl's functions.
// You probably don't want to change any of this code.

Navigator::Navigator()
{
    m_impl = new NavigatorImpl;
}

Navigator::~Navigator()
{
    delete m_impl;
}

bool Navigator::loadMapData(string mapFile)
{
    return m_impl->loadMapData(mapFile);
}

NavResult Navigator::navigate(string start, string end, vector<NavSegment>& directions) const
{
    return m_impl->navigate(start, end, directions);
}
