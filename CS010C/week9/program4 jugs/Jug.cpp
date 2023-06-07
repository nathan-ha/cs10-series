#include <stdexcept>
#include <iostream>
#include <climits>
#include <stack>
#include <vector>
#include <queue>

using std::cout;
using std::endl;
using std::vector;
using std::queue;
using std::stack;
using std::priority_queue;

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
            return;
        }

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
        currVertex.newStateAfterAction[0] = edge(id, afterFillA, costToFillA, FILL_A);
        currVertex.newStateAfterAction[1] = edge(id, afterFillB, costToFillB, FILL_B);
        currVertex.newStateAfterAction[2] = edge(id, afterEmptyA, costToEmptyA, EMPTY_A);
        currVertex.newStateAfterAction[3] = edge(id, afterEmptyB, costToEmptyB, EMPTY_B);
        currVertex.newStateAfterAction[4] = edge(id, afterPourAB, costToPourAB, POUR_AB);
        currVertex.newStateAfterAction[5] = edge(id, afterPourBA, costToPourBA, POUR_BA);
        // note: getID pushes any (currently) nonexistent vertices onto the graph
    }
    // printGraph();
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

//TODO: make more efficient, add comments

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

    int targetID = -1;
    //plan: find solution if it exists, then trace path to it
    for (const auto &currVertex : graph)
    {
        //found desired state
        if (currVertex.amountB == goal || currVertex.amountA == goal)
        {
            targetID = currVertex.id; //assuming only one solution exists at a time
        }
    }
    //no solution was found
    if (targetID == -1)
    {
        solution = "";
        return 0;
    } 

    vector<edge> nodes;
    for (unsigned i = 0; i < graph.size(); i++)
    {
        nodes.push_back(edge(-1, i, INT_MAX / 2, NONE));
    }
    //starting from empty jugs (0,0)
    nodes[0].weight = 0;

    priority_queue<edge*, vector<edge*>, compare> unvisitedQueue; // using a priority queue to visit adjacent nodes in order
    // add each vertex into the unvisited queue
    for (unsigned i = 0; i < graph.size(); i++)
    {
        for (const auto &adjNode : graph[i].newStateAfterAction)
        {
            unvisitedQueue.push(&nodes[adjNode.endID]);   
        }
    }  


    while (unvisitedQueue.size() > 0)
    {
        edge currV = *unvisitedQueue.top();
        //visit vertex with minimum distance from start
        queue<edge> newStateNodes;
        for (const auto &adjNode : graph[currV.endID].newStateAfterAction)
        {
            newStateNodes.push(edge(currV.endID, adjNode.endID, adjNode.weight, adjNode.path));
        }
        // for every node adjacent to currV...
        while (newStateNodes.size() > 0)
        {
            const auto &adjV = newStateNodes.front();
            int edgeWeight = adjV.weight;
            int altWeight = edgeWeight + nodes[currV.endID].weight;
            if (altWeight < nodes[adjV.endID].weight)
            {
                nodes[adjV.endID].weight = altWeight;
                nodes[adjV.endID].startID = currV.endID;
                nodes[adjV.endID].path = adjV.path;
            }
            newStateNodes.pop();
        }
        unvisitedQueue.pop();
    }

    int totalCost = 0;
    stack<edge*> shortestPath;
    // go backwards through graph
    for (int i = targetID; i != 0; i = nodes[i].startID)
    {
        shortestPath.push(&nodes[i]);
    }

    while (shortestPath.size() > 0)
    {
        auto currV = *shortestPath.top();
        solution += getAction(currV);
        totalCost = currV.weight;
        shortestPath.pop();
    }
    
    solution += "success " + std::to_string(totalCost);

    return 1;
}

// returns a string based on the action that made the edge
string Jug::getAction(const edge &state) const
{
    if (state.path == FILL_A)
    {
        return "fill A\n";
    }
    if (state.path == FILL_B)
    {
        return "fill B\n";
    }
    if (state.path == EMPTY_A)
    {
        return "empty A\n";
    }
    if (state.path == EMPTY_B)
    {
        return "empty B\n";
    }
    if (state.path == POUR_AB)
    {
        return "pour A B\n";
    }
    if (state.path == POUR_BA)
    {
        return "pour B A\n";
    }
    throw std::runtime_error("getAction: something went wrong");
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