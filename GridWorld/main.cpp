#include <iostream>
#include "gridworld.h"
#include <time.h>

using namespace std;

int main(int argc, char *argv[]){
    srand(time(NULL));
    //Initialising values etc
    int maxEpisode = 100;
    int episode = 1;
    GridWorld* grid = new GridWorld();

    while(episode < maxEpisode){
        //start state
        grid->start();
        episode++;
    }
    return 0;
}

