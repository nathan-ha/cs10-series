#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;

/*
    A problem is given by (Ca, Cb, N, cfA, cfB, ceA, ceB, cpAB, cpBA), where
    Ca and Cb are the capacities of the jugs A and B, respectively, and
    N is the goal.
    cfA is the cost to fill A,
    cfB is the cost to fill B,
    ceA, is the cost to empty A,
    ceB is the cost to empty B,
    cpAB is the cost to pour A to B and
    cpBA is the cost to pour B to A.
    A solution is a sequence of steps that leaves jug A empty, and exactly N gallons in jug B

    The possible steps are:
        fill A
        fill B
        empty A
        empty B
        pour A B
        pour B A
        success X
*/
enum action {FILL_A, FILL_B, EMPTY_A, EMPTY_B, POUR_AB, POUR_BA};

class Jug
{
private:
    struct vertex
    {
        int amountA;
        int amountB;
        int id;

        struct edge 
        {
            int id; //id of the destination
            action path;
            int cost;
            edge(int id = -1, int cost = 0) : id(id), cost(cost) {}
        };
        vector<edge> newStateAfterAction; // adjacency list
        vertex(int amountA, int amountB, int id) : amountA(amountA), amountB(amountB), id(id), newStateAfterAction(6, -1) {}
    };
    int capacityA, capacityB;
    int goal;
    int costToFillA, costToFillB;
    int costToEmptyA, costToEmptyB;
    int costToPourAB, costToPourBA;
    vector<vertex> graph;

public:
    Jug(int, int, int, int, int, int, int, int, int);

    // solve is used to check input and find the solution if one exists
    // returns -1 if invalid inputs. solution set to empty string.
    // returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
    // returns 1 if solution is found and stores solution steps in solution string.
    int solve(string &solution) const;

private:
    // returns the id of the jug with the specified amounts
    // if this combination does not exist, it will be added to the list of unfinished vertices
    int getID(int amountA, int amountB, vector<int> &unfinishedVertices);

    // returns the action which yields the lowest cost
    int findMinCost(int vertexID) const;

    // Display the graph in readable form
    void printGraph();
    
    // Helper for printGraph
    void showState(int i);

    // returns the action which led to the state
    string getAction(const vertex::edge &state) const;

    // returns cost to get to an adjacent vertex
    int costFrom(int startID, int endID) const;

};