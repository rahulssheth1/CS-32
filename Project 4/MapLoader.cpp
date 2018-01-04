#include "provided.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class MapLoaderImpl
{
public:
    MapLoaderImpl();
    ~MapLoaderImpl();
    bool load(string mapFile);
    size_t getNumSegments() const;
    bool getSegment(size_t segNum, StreetSegment& seg) const;
private:
    int getLineNumber(istream& some);
    vector<StreetSegment> segVector;
};

MapLoaderImpl::MapLoaderImpl()
{
}

MapLoaderImpl::~MapLoaderImpl()
{
}

int MapLoaderImpl::getLineNumber(istream& some) {
    
    int lineCount = 0;
    string line;
    
    while (getline(some, line))
        lineCount++;
    return lineCount;
}

bool MapLoaderImpl::load(string mapFile)
{
  
   
    GeoSegment value;
    ifstream infile(mapFile);
    
    if (infile.is_open()) {
        //Checks if load is successful
            while (infile.peek() != -1) {
                StreetSegment temp;
                string latitude;
                string longitude;
                string endLatitude;
                string endLongitude;
                
                getline(infile, temp.streetName);
                
                //Get streetname
                
                getline(infile, latitude, ',');
                if (infile.peek() == ' ')
                    infile.ignore(69420, ' ');
                getline(infile, longitude, ' ');
                GeoCoord startCoord(latitude, longitude);
                getline(infile, endLatitude, ',');
                if (infile.peek() == ' ')
                    infile.ignore(69420, ' ');
                getline(infile, endLongitude);
                GeoCoord endCoord(endLatitude, endLongitude);
                //Get the start and end coords
                
                
                
                value.start = startCoord;
                value.end = endCoord;
                temp.segment = value;
                //Initialize the segment to the temp segment based on coords
                int attraction;
                infile >> attraction;
                infile.ignore(69420, '\n');
                if (attraction > 0) {
                    for (int j = 0; j < attraction; j++) {
                        Attraction some;
                        string latitude;
                        string longitude;
                        
                        //Checks thru the attraction
                        
                        
                        
                        getline(infile, some.name, '|');
                        getline(infile, latitude, ',');
                        if (infile.peek() == ' ')
                            infile.ignore(69420, ' ');
                        getline(infile, longitude);
                        
                        some.geocoordinates = GeoCoord(latitude, longitude); 
                        temp.attractions.push_back(some);
                        //Push the attractions back into temp streetsegment
                    }
                }
                segVector.push_back(temp);
                //Push into the vector
                
                
            }

        
        return true;

        
    } else {
        cout << "error" << endl;
        return false;
        //Return false if infile did not open
    }
}

size_t MapLoaderImpl::getNumSegments() const
{
    return segVector.size(); // This compiles, but may not be correct
}

bool MapLoaderImpl::getSegment(size_t segNum, StreetSegment &seg) const
{
    if (segNum >= getNumSegments())
    return false;
    //if segNum is too large return false
    else {
        seg = segVector[segNum];
        return true;
        //change the seg value 
    }
    // This compiles, but may not be correct
}

//******************** MapLoader functions ************************************

// These functions simply delegate to MapLoaderImpl's functions.
// You probably don't want to change any of this code.

MapLoader::MapLoader()
{
    m_impl = new MapLoaderImpl;
}

MapLoader::~MapLoader()
{
    delete m_impl;
}

bool MapLoader::load(string mapFile)
{
    return m_impl->load(mapFile);
}

size_t MapLoader::getNumSegments() const
{
    return m_impl->getNumSegments();
}

bool MapLoader::getSegment(size_t segNum, StreetSegment& seg) const
{
    return m_impl->getSegment(segNum, seg);
}
