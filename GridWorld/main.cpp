#include <iostream>
#include "gridworld.h"
#include <time.h>

using namespace std;

int main(int argc, char *argv[]){
    srand(time(NULL));
    //Initialising values etc
    int maxEpisode = 100000;
    int episode = 1;
    GridWorld* grid = new GridWorld();
    grid->init();
    while(episode < maxEpisode){
        //start state
        grid->start(episode);
        episode++;
    }
    return 0;
}

