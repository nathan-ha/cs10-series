#include <stdexcept>
#include <iostream>
#include <limits>


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

    // records the state of each jug after every action
    while (unfinishedVertices.size() > 0)
    {
        int id = unfinishedVertices.back();
        unfinishedVertices.pop_back();
        int currAmountA = graph[id].amountA;
        int currAmountB = graph[id].amountB;
        // fill the jugs
        int afterFillA = getID(capacityA, currAmountB, unfinishedVertices);
        int afterFillB = getID(currAmountA, capacityB, unfinishedVertices);
        // empty the jugs
        int afterEmptyA = getID(0, currAmountB, unfinishedVertices);
        int afterEmptyB = getID(currAmountA, 0, unfinishedVertices);

        // after pouring jugs into each other
        int roomInB = capacityB - currAmountB;
        int pourSize = std::min(currAmountA, roomInB);
        int afterPourAB = getID(currAmountA - pourSize, currAmountB + pourSize, unfinishedVertices);
        
        int roomInA = capacityA - currAmountA;
        pourSize = std::min(currAmountB, roomInA);
        int afterPourBA = getID(currAmountA + pourSize, currAmountB - pourSize, unfinishedVertices);

        // add to the adjacency list
        auto &currVertex = graph[id];
        currVertex.newStateAfterAction[0].id = afterFillA;
        currVertex.newStateAfterAction[1].id = afterFillB;
        currVertex.newStateAfterAction[2].id = afterEmptyA;
        currVertex.newStateAfterAction[3].id = afterEmptyB;
        currVertex.newStateAfterAction[4].id = afterPourAB;
        currVertex.newStateAfterAction[5].id = afterPourBA;
        // note: getID pushes any (currently) nonexistent vertices onto the graph

        // assuming each action costs the same, no matter how much water you pour
        //TODO: is this assumption valid?
        currVertex.newStateAfterAction[0].cost = costToFillA;
        currVertex.newStateAfterAction[1].cost = costToFillB;
        currVertex.newStateAfterAction[2].cost = costToEmptyA;
        currVertex.newStateAfterAction[3].cost = costToEmptyB;
        currVertex.newStateAfterAction[4].cost = costToPourAB;
        currVertex.newStateAfterAction[5].cost = costToPourBA;

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
    int targetID = -1;
    //plan: find solution if it exists, then trace path to it
    for (const auto &currVertex : graph)
    {
        //found desired state
        if (currVertex.amountB == goal)
        {
            targetID = currVertex.id;
        }
    }
    //no solution was found
    if (targetID == -1)
    {
        solution = "";
        return 0;
    }
    //searching for shortest path   
    vector<int> unvisitedVertexIDs;
    vector<int> costs(graph.size(), INT_MAX - 1000); //stores the cost to get to each vertex, subtracting 1000 to prevent weird overflow behavior
    vector<int> predecessorIDs(graph.size(), -1);
    for (unsigned i = 0; i < graph.size(); i++)
    {
        unvisitedVertexIDs.push_back(static_cast<int>(i)); // all the ids are just the index of the vector
    }
    costs[0] = 0; // start vertex will be the first element

    while (unvisitedVertexIDs.size() != 0)
    {
        //visit vertex with minimum distance from start
        int currVertexID = findMinCost(0);
        const vertex &currV = graph[currVertexID];
        for (unsigned i = 0; i < currV.newStateAfterAction.size(); i++)
        {
            const auto &adjacentV = currV.newStateAfterAction[i];
            int edgeWeight = adjacentV.cost;
            int altCost = costs[currVertexID] + edgeWeight;
            // If shorter path from startV to adjV is found,
            // update adjV's distance and predecessor
            if (altCost < costs[i])
            {
                solution += "action"; //TODO: add actions to each edge
                costs[i] = altCost;
            }
        }
    }

}

// returns the action which yields the lowest cost
int Jug::findMinCost(int vertexID) const
{
    const auto &currV = graph[vertexID];
    int minCost = currV.newStateAfterAction[0].cost;
    int minCostID = currV.newStateAfterAction[0].id;
    for (const auto &currEdge : currV.newStateAfterAction)
    {
        if (currEdge.cost < minCost)
        {
            minCost = currEdge.cost;
            minCostID = currEdge.id;
        }
    }
    return minCostID;
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

// // Display the graph in readable form
// void Jug::printGraph()
// {
//     cout << "ID\t(A,B)\tfillA\tfillB\temptyA\temptyB\tpourAB\tpourBA" << endl;
//     for (const auto &v : graph)
//     {
//         cout << v.id << "\t(" << v.amountA << ',' << v.amountB << ")";
//         showState(v.newStateAfterAction[0]);
//         showState(v.newStateAfterAction[1]);
//         showState(v.newStateAfterAction[2]);
//         showState(v.newStateAfterAction[3]);
//         showState(v.newStateAfterAction[4]);
//         showState(v.newStateAfterAction[5]);
//         cout << endl;
//     }
// }