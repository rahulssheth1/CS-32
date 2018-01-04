#include <string>
#include "MyMap.h"
#include <vector>
using namespace std;
#include <iostream> 

class AttractionMapperImpl
{
public:
    AttractionMapperImpl();
    ~AttractionMapperImpl();
    void init(const MapLoader& ml);
    bool getGeoCoord(string attraction, GeoCoord& gc) const;
    
private:
    MyMap<string, GeoCoord> attractionsToCoords;
    
    
};


AttractionMapperImpl::AttractionMapperImpl()
{
   
}

AttractionMapperImpl::~AttractionMapperImpl()
{
    
}

void AttractionMapperImpl::init(const MapLoader& ml)
{
    
    
    
    
    int x = ml.getNumSegments();
    vector<Attraction> temp;
    StreetSegment s1;
    for (int i = 0; i < x; i++) {
        //Loop thru all segments
        ml.getSegment(i, s1);
        
        if (!s1.attractions.empty()) {
            temp = s1.attractions;
            for (int i = 0; i < temp.size(); i++) {
                string name = temp[i].name;
                //Get name of attraction
                for (int i = 0; i < name.size(); i++) {
                    name[i] = tolower(name[i]);
                }
                attractionsToCoords.associate(name, temp[i].geocoordinates);
                //Associate name by coords
            }
        }
    }
}

bool AttractionMapperImpl::getGeoCoord(string attraction, GeoCoord& gc) const
{
   
    const GeoCoord* temp = attractionsToCoords.find(attraction);
    for (int i = 0; i < attraction.size(); i++) {
        attraction[i] = tolower(attraction[i]); 
    }
    //Check for lowercase attraction as that's how its stored
    if (temp != nullptr) {
        gc = *temp;
        return true;
        //return true if attractions to coords worked 

    }
    delete temp; 
    return false;
    
}

//******************** AttractionMapper functions *****************************

// These functions simply delegate to AttractionMapperImpl's functions.
// You probably don't want to change any of this code.

AttractionMapper::AttractionMapper()
{
    m_impl = new AttractionMapperImpl;
}

AttractionMapper::~AttractionMapper()
{
    delete m_impl;
}

void AttractionMapper::init(const MapLoader& ml)
{
    m_impl->init(ml);
}

bool AttractionMapper::getGeoCoord(string attraction, GeoCoord& gc) const
{
    return m_impl->getGeoCoord(attraction, gc);
}


