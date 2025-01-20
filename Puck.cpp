#include "Puck.hpp"
#include <format>

using namespace std;

// Puck Constructor
Puck::Puck(int id){
    this->id = id;
    hasWorked = false;
    position = {0, 0};
}

void PuckLibrary::Initialize(){

    // Create a 1-9 pucks in random positions from (0, 0) to (480, 480) on the grid.
    int randint = (rand() % 9) + 1;
    for(int i=0; i<randint; i++){
        Puck temp_puck = Puck(i);
        temp_puck.position = {rand() % 481, rand() % 481};
        pucks.push_back(temp_puck); // Add puck to the pucks vector
    }
}

void PuckLibrary::Move(Puck& puck_obj, pos position){
    cout<<"Moving Puck "<<puck_obj.id<<" to position ("<<position.x<<", "<<position.y<<")"<<endl;

    // Move the given puck to the given position
    puck_obj.position = position;
}

Puck PuckLibrary::Work(){

    // Remove last puck (which must be at the final position), update its hasWorked value, and return it for later use.
    Puck temp_puck = pucks.back();
    cout<<"Doing work on Puck "<<temp_puck.id<<endl;
    pucks.pop_back();
    temp_puck.hasWorked = true;
    return temp_puck;
}

int PuckLibrary::dist(pos pos1, pos pos2){

    // Distance formula
    return sqrt(pow((pos2.x - pos1.x), 2) + pow((pos2.y - pos1.y), 2));
}

void MyImplementation::ParkPucks(PuckLibrary &puck_library){
    int min_dist;
    bool is_occupied;
    int closest_spot_index;
    cout<<"Parking pucks"<<endl;
    
    // Move each puck to the closest unoccupied parking spot.
    for(int i=0; i<puck_library.pucks.size(); i++){
        min_dist = 1000; // Arbitrary value that is larger than any possible distance within the grid.
        Puck current_puck = puck_library.pucks.at(i);

        for(int j=0; j<puck_library.parking_spots.size(); j++){
            pos current_spot = puck_library.parking_spots.at(j);

            // First check if this parking spot is occupied.
            is_occupied = false;
            for(int k=0; k<puck_library.pucks.size(); k++){
                if(puck_library.pucks.at(k).position.x == current_spot.x && puck_library.pucks.at(k).position.y == current_spot.y){
                    is_occupied = true;
                }
            }

            // Find the 
            if(puck_library.dist(current_spot, current_puck.position) < min_dist && !is_occupied){
                min_dist = puck_library.dist(current_spot, current_puck.position);
                closest_spot_index = j;
            }
        }

        // Now that you have found the index of the closest unoccupied spot to this puck, you can move it there.
        // cout<<"Puck "<<current_puck.id<<": ("<<puck_library.parking_spots.at(closest_spot_index).x<<","<<puck_library.parking_spots.at(closest_spot_index).y<<")"<<endl;
        puck_library.Move(puck_library.pucks.at(i), puck_library.parking_spots.at(closest_spot_index));
    }
}

int MyImplementation::CloseGaps(PuckLibrary &puck_library){
    cout<<"Closing gaps"<<endl;
    int pucks_spots_diff = (puck_library.parking_spots.size() - puck_library.pucks.size());

    // Since the pucks vector is sorted, simply place each puck at its relative parking spot.
    for(int i = (puck_library.pucks.size() - 1); i>=0; i--){
        puck_library.Move(puck_library.pucks.at(i), puck_library.parking_spots.at(i+pucks_spots_diff));
    }

    return (pucks_spots_diff - 1);
}

void MyImplementation::SortPucks(PuckLibrary &puck_library){
    int num_sorted = 0;
    cout<<"Sorting pucks vector"<<endl;
    // Sort pucks by their position on the track. The last index of the pucks vector will correspond to the last parking spot on the track.
    // Note: We can't assume the gaps have been closed as CloseGaps is dependent on this function.

    // First, starting from the end of the track, locate the closest pucks.
    for(int i = (puck_library.parking_spots.size() - 1); i>= 0; i--){
        pos current_spot = puck_library.parking_spots.at(i);

        for(int j=0; j<puck_library.pucks.size(); j++){
            Puck current_puck = puck_library.pucks.at(j);

            if(current_puck.position.x == current_spot.x && current_puck.position.x == current_spot.x){

                // As we backtrack the parking spots, we'll place the pucks we find at the end, offset by the number of pucks we've sorted prior.
                // This will result in the pucks position in the vector corresponding to their parking spot.
                for(int k=j; k<puck_library.pucks.size() - 1 - num_sorted; k++){
                    Puck temp_puck = puck_library.pucks.at(k);
                    puck_library.pucks.at(k) = puck_library.pucks.at(k+1);
                    puck_library.pucks.at(k+1) = temp_puck;
                }
            }
        }
    }
}

void MyImplementation::MoveAndPerformWork(){

    // This will be the standalone function ran in main.cpp, so it will initialize, run, and complete the entire operation.
    PuckLibrary puck_library;
    puck_library.Initialize(); // Initialize the puck library, park all pucks, sort the pucks vector by position on the track, and close the gaps.
    ParkPucks(puck_library);
    SortPucks(puck_library);
    CloseGaps(puck_library);

    // Create a snapshot of the initial configuration to compare to later.
    PuckLibrary initial_configuration = puck_library;

    /* 
        Run this loop until the current configuration is identical to the initial configuration and hasWorked is true for all pucks.
        This loop will follow these steps:
            0. Print puck info
            1. Do work on the final puck, popping it out of the vector and storing it for later.
            2. Close the gaps of all remaining pucks, where the CloseGaps function will return the last empty parking spot.
            3. Place the popped puck in that last empty parking spot and place it at the beginning of the vector. This will keep the vector sorted so subsequent calls of SortPucks are not needed.
            4. If the break case is not met, repeat.
    */
    int last_empty_spot;
    bool run = true;
    
    cout<<"Initial Configuration: "<<endl;
    while(run){

        printGrid(puck_library, 0);
        // Step 1
        Puck working_puck = puck_library.Work();
        // Step 2
        last_empty_spot = CloseGaps(puck_library);
        // Step 3
        puck_library.Move(working_puck, puck_library.parking_spots.at(last_empty_spot));
        puck_library.pucks.push_back(working_puck);
        for(int i=puck_library.pucks.size()-1; i>0; i--){
            Puck temp_puck = puck_library.pucks.at(i);
            puck_library.pucks.at(i) = puck_library.pucks.at(i-1);
            puck_library.pucks.at(i-1) = temp_puck;
        }
        // Step 4

        run = false;
        for(int i=0; i<puck_library.pucks.size(); i++){
            Puck current_puck = puck_library.pucks.at(i);
            Puck initial_puck = initial_configuration.pucks.at(i);
            if(current_puck.position.x != initial_puck.position.x || current_puck.position.y != initial_puck.position.y ||
            current_puck.id != initial_puck.id || !current_puck.hasWorked){
                run = true;
            }
        }
        
    }

    cout<<"Final Configuration: "<<endl;
    printGrid(puck_library, 0);
    return;
}


void MyImplementation::printPuckInformation(PuckLibrary puck_library){

    // Print position and work status of each puck.
    for(int i=0; i<puck_library.pucks.size(); i++){
        Puck temp_puck = puck_library.pucks.at(i);
        cout<<"Puck "<<temp_puck.id<<": x: "<<temp_puck.position.x<<", y: "<<temp_puck.position.y<<", hasWorked: "<<temp_puck.hasWorked<<endl;
    }
    cout<<"====================================="<<endl;
}

void MyImplementation::printGrid(PuckLibrary puck_library, int verbose){
    int offset = puck_library.parking_spots.size() - puck_library.pucks.size();
    cout<<"START  -> ";
    for(int i=0; i<puck_library.parking_spots.size(); i++){
        if(i < offset){
            cout<<"EMPTY -> ";
        }else{
            cout<<"FILLED (Puck: "<<puck_library.pucks.at(i-offset).id<<") -> ";
        }
    }
    cout<<"END"<<endl;
    if(verbose){
        printPuckInformation(puck_library);
    }
}