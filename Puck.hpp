#ifndef PUCK_H
#define PUCK_H

#include <iostream>
#include <vector>

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
        PuckLibrary();
        void Initialize(); // Create 1-9 pucks at random locations
        void Move(pos position); // Move puck to a position
        void Work(Puck puck_obj); // Work function, set hasWorked to true, place puck at start
        int dist(pos pos1, pos pos2); // Function to find distance between two positions.
};

class MyImplementation{
    public:
        void ParkPucks(); // Ensure no spaces between pucks
        void CloseGaps(); // Move pucks to end of line
        void MoveAndPerformWork(); // Move and perform work on all pucks
};

#endif