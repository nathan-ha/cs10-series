#include <stdexcept>
#include <iostream>

using std::cout;
using std::endl;


#include "Jug.h"

Jug::Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA)
    : capacityA(Ca),
      capacityB(Cb),
      goal(N),
      costToFillA(cfA),
      costToFillB(cfB),
      costToEmptyA(ceA),
      costToEmptyB(ceB),
      costToPourAB(cpAB),
      costToPourBA(cpBA)
{
    vector<int> unfinishedVertices;
    // add empty vertex to start
    unfinishedVertices.push_back(0);
    graph.push_back(vertex(0, 0, 0));

    //records the state of each jug after every action
    while (unfinishedVertices.size() > 0)
    {
        int id = unfinishedVertices.back();
        unfinishedVertices.pop_back();
        int currAmountA = graph[id].amountA;
        int currAmountB = graph[id].amountB;
        //fill the jugs
        int afterFillA = getID(capacityA, currAmountB, unfinishedVertices);
        int afterFillB = getID(currAmountA, capacityB, unfinishedVertices);
        //empty the jugs
        int afterEmptyA = getID(0, currAmountB, unfinishedVertices);
        int afterEmptyB = getID(currAmountA, 0, unfinishedVertices);

        //after pouring jugs into each other
        int roomInB = capacityB - currAmountB;
        int pourSize = std::min(currAmountA, roomInB);
        int afterPourAB = getID(currAmountA - pourSize, currAmountB + pourSize, unfinishedVertices);
        
        int roomInA = capacityA - currAmountA;
        pourSize = std::min(currAmountB, roomInA);
        int afterPourBA = getID(currAmountA + pourSize, currAmountB - pourSize, unfinishedVertices);

        //add to the adjacency list
        auto &currVertex = graph[id];
        currVertex.newStateAfterAction[0] = afterFillA;
        currVertex.newStateAfterAction[1] = afterFillB;
        currVertex.newStateAfterAction[2] = afterEmptyA;
        currVertex.newStateAfterAction[3] = afterEmptyB;
        currVertex.newStateAfterAction[4] = afterPourAB;
        currVertex.newStateAfterAction[5] = afterPourBA;
        //note: getID pushes any (currently) nonexistent vertices onto the graph
    }
}

// returns the id of the jug with the specified amounts
// if this combination does not exist, it will be added to the list of unfinished vertices
int Jug::getID(int amountA, int amountB, vector<int> &unfinishedVertices)
{
    for (unsigned i = 0; i < graph.size(); i++)
    {
        if (graph[i].amountA == amountA && graph[i].amountB == amountB) return i;
    }
    // if vertex wasn't found, add it to the list
    int id = graph.size();
    unfinishedVertices.push_back(id);
    graph.push_back(vertex(amountA, amountB, id));
    return id;
}

// solve is used to check input and find the solution if one exists
// returns -1 if invalid inputs. solution set to empty string.
// returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
// returns 1 if solution is found and stores solution steps in solution string.
int Jug::solve(string &solution) const
{
    bool validCosts = (costToFillA > 0) &&
                      (costToFillB > 0) &&
                      (costToEmptyA > 0) &&
                      (costToEmptyB > 0) &&
                      (costToPourAB > 0) &&
                      (costToPourBA > 0);
    bool validCapacities = (0 < capacityA && capacityA <= capacityB) &&
                           (goal <= capacityB && capacityB <= 1000);

    if (!validCosts || !validCapacities)
    {
        solution = "";
        return -1;
    }

    //TODO: make better solution
    for (unsigned i = 0; i < graph.size(); i++)
    {
        auto &currVertex = graph[i];
        for (unsigned j = 0; j < 5; j++)
        {
            auto currState = currVertex.newStateAfterAction[j];
            if (currState == goal)
            {
                return 1;
            }
        }
    }

    //no solution was found
    solution = "";
    return 0;
}

// Helper for printGraph
void Jug::showState(int i)
{
    cout << '\t' << i;
    if (i != -1)
    {
        cout << '(' << graph[i].amountA << ',' << graph[i].amountB << ')';
    }
}

// Display the graph in readable form
void Jug::printGraph()
{
    cout << "ID\t(A,B)\tfillA\tfillB\temptyA\temptyB\tpourAB\tpourBA" << endl;
    for (const auto &v : graph)
    {
        cout << v.id << "\t(" << v.amountA << ',' << v.amountB << ")";
        showState(v.newStateAfterAction[0]);
        showState(v.newStateAfterAction[1]);
        showState(v.newStateAfterAction[2]);
        showState(v.newStateAfterAction[3]);
        showState(v.newStateAfterAction[4]);
        showState(v.newStateAfterAction[5]);
        cout << endl;
    }
}