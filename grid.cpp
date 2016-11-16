#include "grid.h"

Grid::Grid(int x, int y, int value, vector<double> action)
{
    //x position on map
    this->x = x;
    //y position on map
    this->y = y;
    //value at the position... 0 = nothing there | 1 = player or finish
    this->value = value;
    //action values for whether a move was good or not. Array of size 4
    // index 0 = North move values | 1 = South move values | 2 = East move values | 3 = West move values
    this->gridAction = action;
}
