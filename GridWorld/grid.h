#ifndef GRID_H
#define GRID_H


class Grid
{
    friend class GridWorld;

    public:
        Grid(int, int, int, double[]);

    private:
        int x;
        int y;
        int value;
        double * action;
};

#endif // GRID_H
