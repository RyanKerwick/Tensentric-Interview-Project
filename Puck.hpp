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
        void Work(Puck& puck_obj); // Work function, set hasWorked to true, place puck at start
        int dist(pos pos1, pos pos2); // Function to find distance between two positions.
};

class MyImplementation{
    public:
        void ParkPucks(PuckLibrary &puck_library); // Ensure pucks are on parking spots
        void CloseGaps(PuckLibrary &puck_library); // Move pucks to end of line and ensure no gaps exist
        void MoveAndPerformWork(PuckLibrary puck_library); // Move and perform work on all pucks
        Puck FindClosestPuck(pos parking_spot, PuckLibrary puck_library); // Find the closest puck so a given parking spot
        pos FindClosestPos(PuckLibrary puck_library, pos position); // Find the closest parking spot to a puck's position
        void printPuckInformation(PuckLibrary puck_library); // Print locations and status of pucks
};

#endif