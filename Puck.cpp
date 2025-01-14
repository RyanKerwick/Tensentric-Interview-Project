#include "Puck.hpp"
#include <random>

using namespace std;

// Defining Constructors

Puck::Puck(int id){
    id = id;
    hasWorked = false;
    position = {0, 0};
}

void PuckLibrary::Initialize(){
    int randint = rand() % 10;
    for(int i=0; i<randint; i++){
        Puck temp_puck = Puck(i);
        pucks.push_back(temp_puck); // Add a puck to the pucks list
        
    }
}