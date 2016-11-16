#ifndef GRID_H
#define GRID_H
#include <vector>

using namespace std;
class Grid
{
    friend class GridWorld;

    public:
        Grid(int, int, int, vector<double>);

    private:
        int x;
        int y;
        int value;
        vector<double> gridAction;
};

#endif // GRID_H
