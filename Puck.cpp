#include "Puck.hpp"
#include <format>

using namespace std;

// Defining Constructors

Puck::Puck(int id){
    id = id;
    hasWorked = false;
    position = {0, 0};
}

void PuckLibrary::Initialize(){

    // Create a 1-9 pucks in random positions on the grid.
    int randint = (rand() % 9) + 1; // Random number 1-9
    pos temp_pos;
    for(int i=0; i<randint; i++){
        Puck temp_puck = Puck(i);
        temp_puck.position = {rand() % 481, rand() % 481}; // Two random numbers 0-480
        pucks.push_back(temp_puck); // Add a puck to the pucks list
    }


}

void PuckLibrary::Move(Puck& puck_obj, pos position){
    puck_obj.position = position;
}

void PuckLibrary::Work(Puck& puck_obj){
    puck_obj.hasWorked = true;
    puck_obj.position = {0, 0};
    // Close gaps first and then park pucks
    // Reason: If there are 9 pucks, the first parking spot will not be open so the pucks must be moved forward before the puck having work done on it can occupy that spot.
}

int PuckLibrary::dist(pos pos1, pos pos2){
    return sqrt(pow((pos2.x - pos1.x), 2) + pow((pos2.y - pos1.y), 2)); // Distance formula
}

void MyImplementation::ParkPucks(PuckLibrary &puck_library){
    pos current_spot;

    // For each parking spot, move the closest puck into that location. This is done to ensure that no parking spot contains multiple pucks.
    for(int i=0; i<puck_library.parking_spots.size(); i++){
        current_spot = puck_library.parking_spots[i];
        puck_library.Move(FindClosestPuck(current_spot, puck_library), current_spot);
    }
}

void MyImplementation::CloseGaps(PuckLibrary &puck_library){
    // Find the puck that is furthest towards the end and move it forward as much as is allowed, each puck must be checked
}

void MyImplementation::MoveAndPerformWork(PuckLibrary puck_library){
    PuckLibrary puck_library;
    puck_library.Initialize();  // Initialize puck library with pucks parked and gaps closed
    ParkPucks(puck_library);
    CloseGaps(puck_library);
    // Sort pucks so that the higher the index in pucks, the further along the track the puck is.

    // Create a snapshot of the initial configuration to compare to later
    PuckLibrary initial_config = puck_library;

    // Since the internal behavior of the work cycle with 9 pucks is different than with any other number, a conditional statement is necessary.
    if(puck_library.pucks.size() == 9){

    }else{

    }

    while(true){


        // Break the loop once the current configuration is equivalent to the inital configuration and hasWorked is true for all pucks
        break;
    }


}

Puck MyImplementation::FindClosestPuck(pos parking_spot, PuckLibrary puck_library){
    int min_dist = puck_library.dist(puck_library.pucks[0].position, parking_spot); // Distance between pucks[0] and parking spot
    int temp_dist;
    Puck closest_puck = puck_library.pucks[0];
    bool on_spot;

    // Find the puck that is closest to this parking spot as long as that puck isn't already in a parking spot.
    for(int i=0; i<puck_library.pucks.size(); i++){
        on_spot = false;
        Puck temp_puck = puck_library.pucks[i];
        temp_dist = puck_library.dist(temp_puck.position, parking_spot);
        
        // Is this puck already on a parking spot?
        for(int j=0; j<puck_library.parking_spots.size(); j++){
            if(puck_library.pucks[i].position.x == puck_library.parking_spots[j].x && puck_library.pucks[i].position.y == puck_library.parking_spots[j].y){
                
            }
        }

        if(temp_dist < min_dist && !on_spot){
            min_dist = temp_dist;
            closest_puck = puck_library.pucks[i];
        }
    }

    return closest_puck;
}

// pos MyImplementation::FindClosestPos(PuckLibrary puck_library, pos position){
//     int min_dist = 679; // Maximum distance between two points in the grid
//     int temp_dist;
//     pos closest_spot = {0, 0};

//     // Go through each parking spot and return the parking spot that the puck is closest to.
//     for(int i=0; i<9; i++){
//         temp_dist = puck_library.dist(puck_library.parking_spots[i], position);
//         if(temp_dist < min_dist){
//             for(int j=0; j<puck_library.pucks.size(); j++){
//                 if(puck_library.pucks[j].position.x == puck_library.parking_spots[i].x && puck_library.pucks[j].position.y == puck_library.parking_spots[i].y){
//                     // If parking spot is taken, move on to next parking spot
//                 }
//             }
//             min_dist = temp_dist;
//             closest_spot = puck_library.parking_spots[i];
//         }
//     }
//     return closest_spot;
// }

void MyImplementation::printPuckInformation(PuckLibrary puck_library){
    for(int i=0; i<puck_library.pucks.size(); i++){
        Puck temp_puck = puck_library.pucks[i];
        cout<<format("Puck {}: x: {}, y: {}, hasWorked: {}", temp_puck.id, temp_puck.position.x, temp_puck.position.y, temp_puck.hasWorked)<<endl;
    }
}