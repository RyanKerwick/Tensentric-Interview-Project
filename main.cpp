#include "Puck.hpp"
#include <random>
#include <ctime>

using namespace std;

int main(){
    srand(time(0));
    MyImplementation puck_track;
    puck_track.MoveAndPerformWork();
}