#include <vector>
#include "MyMap.h"
using namespace std;
#include <iostream>

class SegmentMapperImpl
{
public:
    SegmentMapperImpl();
    ~SegmentMapperImpl();
    void init(const MapLoader& ml);
    vector<StreetSegment> getSegments(const GeoCoord& gc) const;
    
private:
    MyMap<GeoCoord, vector<StreetSegment>> coordsToStreet;
    };



SegmentMapperImpl::SegmentMapperImpl()
{
    
    
}



SegmentMapperImpl::~SegmentMapperImpl()
{
}

void SegmentMapperImpl::init(const MapLoader& ml)
{
    
    int x  = ml.getNumSegments();
    for (int i = 0; i < x; i++) {
        StreetSegment s1;
        GeoCoord temp;

        vector<StreetSegment>* temp2;
        vector<StreetSegment> streetVector;
        vector<Attraction> attractionsVector;
        ml.getSegment(i, s1);
        GeoCoord start = s1.segment.start;
        temp2 = coordsToStreet.find(start);
        if (temp2 != nullptr) {
            streetVector = *temp2;
       
            
        }
        streetVector.push_back(s1);
        coordsToStreet.associate(start, streetVector);
        //Push back into vector if available and reassociate
        streetVector.clear();

        GeoCoord end = s1.segment.end;
        temp2 = coordsToStreet.find(end);
        if (temp2 != nullptr) {
            streetVector = *temp2;
        }
        streetVector.push_back(s1);
            coordsToStreet.associate(end, streetVector);
        //Push back into vector if available and reassociate

       
        streetVector.clear();
        attractionsVector = s1.attractions;
        for (int i = 0; i < attractionsVector.size(); i++) {
            GeoCoord temp = attractionsVector[i].geocoordinates;
            temp2 = coordsToStreet.find(temp);
            
            if (temp2 != nullptr) {
                streetVector = *temp2;
            }
            streetVector.push_back(s1);
                coordsToStreet.associate(temp, streetVector);
            //Push back into vector if available and reassociate

            streetVector.clear(); 


        }
    }
    
}

vector<StreetSegment> SegmentMapperImpl::getSegments(const GeoCoord& gc) const
{
    const vector<StreetSegment> *segments;
    vector<StreetSegment> empty;
    segments = coordsToStreet.find(gc);
    
    if (segments != nullptr)
        
    
        return *segments;
    
    return empty;
    
    
    
    //Return the segment stored at coords to street
}

//******************** SegmentMapper functions ********************************

// These functions simply delegate to SegmentMapperImpl's functions.
// You probably don't want to change any of this code.

SegmentMapper::SegmentMapper()
{
    m_impl = new SegmentMapperImpl;
}

SegmentMapper::~SegmentMapper()
{
    delete m_impl;
}

void SegmentMapper::init(const MapLoader& ml)
{
    m_impl->init(ml);
}

vector<StreetSegment> SegmentMapper::getSegments(const GeoCoord& gc) const
{
    return m_impl->getSegments(gc);
}
