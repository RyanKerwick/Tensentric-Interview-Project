#ifndef PUCK_H
#define PUCK_H

#include <iostream>
#include <vector>
#include <cmath>
#include <random>

using namespace std;

struct pos{
    int x;
    int y;
};

class Puck{
    public:
        int id;
        bool hasWorked;
        pos position;  // Puck's position is stored
        Puck(int id); 
};

class PuckLibrary{
    public:
        vector<pos> parking_spots = {
            {180, 60}, {300, 60}, {420, 60},
            {420, 180}, {300, 180}, {180, 180},
            {180, 300}, {300, 300}, {420, 300}
        };
        vector<Puck> pucks;
        void Initialize(); // Create 1-9 pucks at random locations
        void Move(Puck& puck_obj, pos position); // Move puck to a position
        Puck Work(); // Work function, set hasWorked to true, place puck at start
        int dist(pos pos1, pos pos2); // Function to find distance between two positions.
};

class MyImplementation{
    public:
        void ParkPucks(PuckLibrary &puck_library); // Ensure pucks are on parking spots
        int CloseGaps(PuckLibrary &puck_library); // Move pucks to end of line and ensure no gaps exist
        void SortPucks(PuckLibrary &puck_library); // Sort pucks vector so that the index of a puck corresponds to its position on the track.
        void MoveAndPerformWork(); // Move and perform work on all pucks
        void printPuckInformation(PuckLibrary puck_library); // Print locations and status of pucks
        void printGrid(PuckLibrary puck_library, int verbose); // For each parking spot, print if there is a puck in the spot and the id of the puck.
};

#endif