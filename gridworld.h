#ifndef GRIDWORLD_H
#define GRIDWORLD_H
#include <iostream>
#include <vector>

class Grid;

class GridWorld
{
    public:
        GridWorld();
        void start(int episode);
        void getAvailableMoves(); //updates reference type(array) of availableActions
        void chooseAction();
        void printGrid();
        void printActionGrid();
        void initLookUpGrid();
        void init();

    private:
        //2D array of [row][column]
        int gridWorldMap[7][10] = {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
        };

        int columnWind[10] = { 0, 0, 0, 1, 1, 1, 2, 2, 1, 0};
        int availableActions[4];
        int agentPosition[2]; //start position

        double reward;
        int numberOfMoves;
        int action;

        double epsilon = 0.1;
        double gamma = 0.9;
        double alpha = 0.1;

        double currentActionValue, maxActionValue, newActionValue;

        std::vector<std::vector<Grid *> > lookUpGrid;

};

#endif // GRIDWORLD_H
