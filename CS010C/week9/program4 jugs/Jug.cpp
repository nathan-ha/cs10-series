#include <stdexcept>
#include <iostream>
#include <climits>
#include <stack>
#include <vector>
#include <queue>
#include <set>

using std::cout;
using std::endl;
using std::vector;
using std::queue;
using std::stack;
using std::priority_queue;
using std::set;

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
    bool validCosts = (costToFillA > 0) &&
                          (costToFillB > 0) &&
                          (costToEmptyA > 0) &&
                          (costToEmptyB > 0) &&
                          (costToPourAB > 0) &&
                          (costToPourBA > 0);
    bool validCapacities = (0 < capacityA && capacityA <= capacityB) &&
                            (goal <= capacityB && capacityB <= 1000);
    if (!validCosts || !validCapacities) return;

    vector<int> unfinishedVertices;
    // start vertex will be both 0 amounts
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
        currVertex.newStateAfterAction[0] = edge(id, afterFillA, costToFillA, FILL_A);
        currVertex.newStateAfterAction[1] = edge(id, afterFillB, costToFillB, FILL_B);
        currVertex.newStateAfterAction[2] = edge(id, afterEmptyA, costToEmptyA, EMPTY_A);
        currVertex.newStateAfterAction[3] = edge(id, afterEmptyB, costToEmptyB, EMPTY_B);
        currVertex.newStateAfterAction[4] = edge(id, afterPourAB, costToPourAB, POUR_AB);
        currVertex.newStateAfterAction[5] = edge(id, afterPourBA, costToPourBA, POUR_BA);
        // note: getID pushes any (currently) nonexistent vertices onto the graph
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
// uses dijkstras algorithm to find best way to fill jugs
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
    // looking for desired state
    for (const auto &currVertex : graph)
    {
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

    // starting actual solving
    vector<edge> edges;
    vector<bool> visited(graph.size(), false);
    for (unsigned i = 0; i < graph.size(); i++)
    {
        edges.push_back(edge(-1, i, INT_MAX / 2, NONE));
    }

    queue<edge*> unvisitedQueue;
    //starting from empty jugs (0,0)
    edges[0].weight = 0;
    visited[0] = true;
    // initial push to unvisited queue
    for (const auto &adjNode : graph[0].newStateAfterAction)
    {
        unvisitedQueue.push(&edges[adjNode.endID]);
    }

    while (unvisitedQueue.size() > 0)
    {
        edge *currEdge = unvisitedQueue.front();
        // add adjacent nodes to a queue
        queue<edge> newStateNodes; // "new state nodes" is synonymous to "adjacent nodes"
        for (const auto &adjNode : graph[currEdge->endID].newStateAfterAction)
        {
            newStateNodes.push(edge(currEdge->endID, adjNode.endID, adjNode.weight, adjNode.path));
        }
        // for every node adjacent to currEdge...
        while (newStateNodes.size() > 0)
        {
            const auto &adjV = newStateNodes.front();
            // add adjacent nodes to unvisited queue
            for (const auto &adjNode : graph[adjV.endID].newStateAfterAction)
            {
                if (visited[adjNode.endID] == false)
                {
                    visited[adjNode.endID] = true;
                    unvisitedQueue.push(&edges[adjNode.endID]);
                }
            }
            // update edge info if better path was changed
            int edgeWeight = adjV.weight;
            int altWeight = edgeWeight + edges[currEdge->endID].weight;
            if (altWeight < edges[adjV.endID].weight)
            {
                edges[adjV.endID].weight = altWeight;
                edges[adjV.endID].startID = currEdge->endID;
                edges[adjV.endID].path = adjV.path;
                visited[adjV.endID] = true;
            }
            newStateNodes.pop();
        }
        unvisitedQueue.pop();
    }

    // using a stack because we are starting at the end, and backtracking to the beginning
    stack<edge*> shortestPath;
    for (int i = targetID; i != 0; i = edges[i].startID)
    {
        shortestPath.push(&edges[i]);
    }
    int totalCost = 0;
    while (shortestPath.size() > 0)
    {
        auto currEdge = *shortestPath.top();
        solution += getAction(currEdge);
        totalCost = currEdge.weight;
        shortestPath.pop();
    } 
    solution += "success " + std::to_string(totalCost);
    return 1;
}

// returns a string based on the action that made the edge
string Jug::getAction(const edge &edge) const
{
    if (edge.path == FILL_A)
    {
        return "fill A\n";
    }
    if (edge.path == FILL_B)
    {
        return "fill B\n";
    }
    if (edge.path == EMPTY_A)
    {
        return "empty A\n";
    }
    if (edge.path == EMPTY_B)
    {
        return "empty B\n";
    }
    if (edge.path == POUR_AB)
    {
        return "pour A B\n";
    }
    if (edge.path == POUR_BA)
    {
        return "pour B A\n";
    }
    throw std::runtime_error("getAction: something went wrong");
}

// Helper for printGraph
void Jug::showState(int i) const
{
    cout << '\t' << i;
    if (i != -1)
    {
        cout << '(' << graph[i].amountA << ',' << graph[i].amountB << ')';
    }
}

// Display the graph in readable form
void Jug::printGraph() const
{
    cout << "ID\t(A,B)\tfillA\tfillB\temptyA\temptyB\tpourAB\tpourBA" << endl;
    for (const auto &v : graph)
    {
        cout << v.id << "\t(" << v.amountA << ',' << v.amountB << ")";
        showState(v.newStateAfterAction[0].endID);
        showState(v.newStateAfterAction[1].endID);
        showState(v.newStateAfterAction[2].endID);
        showState(v.newStateAfterAction[3].endID);
        showState(v.newStateAfterAction[4].endID);
        showState(v.newStateAfterAction[5].endID);
        cout << endl;
    }
}

Jug::~Jug()
{
    // empty destructor because I didn't use "new" at all
}