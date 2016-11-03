#include "gridworld.h"
#include <iostream>
#include <vector>
#include "grid.h"

using namespace std;

GridWorld::GridWorld()
{

}

void GridWorld::start(){
                     //row, column, default start position
    agentPosition[0] = 3;
    agentPosition[1] = 0;
                         // N, S, E, W... 1 = move available | 0 = move unavailable
    availableActions[0] = 1;
    availableActions[1] = 1;
    availableActions[2] = 1;
    availableActions[3] = 1;
    //set starting point of agent
    gridWorldMap[agentPosition[0]][agentPosition[1]] = 1;

    reward = 0;
    numberOfMoves = 0;
    //set up the lookUpGrid, Maps states to actions
    initLookUpGrid();

    bool gameOver = false;
    // check it hasn't reached the goal state
    while(!gameOver){
        chooseAction();
        Grid *g = lookUpGrid.at(agentPosition[0]).at(agentPosition[1]);
        currentActionValue = g->action[this->action];
        getAvailableMoves();

        int oldX = agentPosition[0];
        int oldY = agentPosition[1];
        //action: 0 = North | 1 = South | 2 = East | 3 = West
        if(action == 0 && availableActions[0] == 1){
            //factor in column wind effect, check to see you dont go out of bounds (bounces back to row 0)
            if(columnWind[agentPosition[1]] != 0){
                if(agentPosition[0] - (columnWind[agentPosition[1]] + 1) < 0){
                    agentPosition[0] = 0;
                }
                else{
                    agentPosition[0] = agentPosition[0] - (columnWind[agentPosition[1]] + 1);
                }
            }
            else{
                agentPosition[0]--;
            }
        }
        if(action == 1 && availableActions[1] == 1){
            if(columnWind[agentPosition[1]] != 0){
                if(agentPosition[0] - (columnWind[agentPosition[1]] - 1) < 0){
                    agentPosition[0] = 0;
                }
                else{
                    agentPosition[0] = agentPosition[0] - (columnWind[agentPosition[1]] - 1);
                }
            }
            else{
                agentPosition[0]++;
            }
        }
        if(action == 2 && availableActions[2] == 1){
            if(columnWind[agentPosition[1]] != 0){
                if(agentPosition[0] - (columnWind[agentPosition[1]]) < 0){
                    agentPosition[0] = 0;
                    agentPosition[1]++;
                }
                else{
                    agentPosition[0] = agentPosition[0] - (columnWind[agentPosition[1]]);
                    agentPosition[1]++;
                }
            }
            else{
                agentPosition[1]++;
            }
        }
        if(action == 3 && availableActions[3] == 1){
            if(columnWind[agentPosition[1]] != 0){
                if(agentPosition[0] - (columnWind[agentPosition[1]]) < 0){
                    agentPosition[0] = 0;
                    agentPosition[1]--;
                }
                else{
                    agentPosition[0] = agentPosition[0] - (columnWind[agentPosition[1]]);
                    agentPosition[1]--;
                }
            }
            else{
                agentPosition[1]--;
            }
        }
        numberOfMoves++;
        //Update player position in GridWorld
        gridWorldMap[oldX][oldY] = 0;
        gridWorldMap[agentPosition[0]][agentPosition[1]] = 1;
        //set reward
        reward -= 1;

        //find maxActionValue
        g = lookUpGrid.at(agentPosition[0]).at(agentPosition[1]);
        maxActionValue = g->action[0];
        for(int j = 1; j < 4; ++j){
            if(g->action[j] > maxActionValue)
                maxActionValue = g->action[j];
        }

        //calculate newActionValue
        newActionValue = currentActionValue + alpha *(reward + gamma * maxActionValue - currentActionValue);

        g = lookUpGrid.at(oldX).at(oldY);
        g->action[this->action] = newActionValue;
        //printGrid();

        if(agentPosition[0] == 3)
            if(agentPosition[1] == 7)
                gameOver = true;

    }//While

    reward += 1;
    cout << "Reward Total: " << reward << "\tNumber of Moves: " << numberOfMoves << "\n";

}

//updates reference type(array) of availableActions
void GridWorld::getAvailableMoves(){
    //check agents position on Grid Map
    // 7 x 10
    if(agentPosition[0] <= 0)
        availableActions[0] = 0; //North
    else
        availableActions[0] = 1;

    if(agentPosition[0] >= 6)
        availableActions[1] = 0; //South
    else
        availableActions[1] = 1;

    if(agentPosition[1] >= 9)
        availableActions[2] = 0; //East
    else
        availableActions[2] = 1;

    if(agentPosition[1] <= 0){
        availableActions[3] = 0; //West
    }
    else{
        availableActions[3] = 1;
    }
}

void GridWorld::chooseAction(){
    int count = 0;
    double aV[4] = {0};
    double maxA;
    Grid *g = lookUpGrid.at(agentPosition[0]).at(agentPosition[1]);
    for(int i = 0; i < 4; ++i){
        aV[i] = g->action[i];
    }
    double random = (rand() % 10);

    if(random < (epilson * 10)){
        action = (rand() % 4);
    }
    else{
        cout << "Else in chooseAction\n";
        //find the maximum action value
        maxA = aV[0];
        action = 0;
        for(int j = 1; j < 4; ++j){
            if(aV[j] > maxA)
                maxA = aV[j];
                action = j;
        }

        //check to see if there are multiple maximum values
        for(int i = 0; i < 4; ++i){
            if(aV[i] == maxA){
                count++;
            }
        }

        if(count > 1){
            int r = rand() % count;
            int random = 0;
            for(int i = 0; i < 4; ++i){
                if(aV[i] == maxA){
                    if(r == random){
                        action = i;
                    }
                    random++;
                }
            }
        }
    }//else
}

void GridWorld::printGrid(){
    int rows = sizeof(gridWorldMap) / sizeof(gridWorldMap[0]);
    int columns = sizeof(gridWorldMap[0]) / sizeof(int);

    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < columns; ++j){
            cout << gridWorldMap[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void GridWorld::initLookUpGrid(){
    int rows = sizeof(gridWorldMap) / sizeof(gridWorldMap[0]);
    int columns = sizeof(gridWorldMap[0]) / sizeof(int);

    double actions[4] = { 0.0, 0.0, 0.0, 0.0};
    for(int i = 0; i < rows; ++i){
        std::vector<Grid *> temp;
        for(int j = 0; j < columns; ++j){
            Grid *g = new Grid(i, j, gridWorldMap[i][j], actions);
            temp.push_back(g);
        }
        lookUpGrid.push_back(temp);
    }


}
