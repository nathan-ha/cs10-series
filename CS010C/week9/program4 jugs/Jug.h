#pragma once
#include <string>
#include <vector>
#include <climits>

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

enum action
{
    FILL_A,
    FILL_B,
    EMPTY_A,
    EMPTY_B,
    POUR_AB,
    POUR_BA,
    NONE
};

class Jug
{
private:
    struct edge
    {
        int startID;
        int endID;
        int weight;
        action path;
        edge(int startID = -1, int endID = -1, int weight = INT_MAX, action path = NONE) : startID(startID), endID(endID), weight(weight), path(path) {}
    };
    struct vertex
    {
        int amountA;
        int amountB;
        int id;
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
    // uses dijkstras algorithm
    int solve(string &solution) const;

    ~Jug();
    // no need to overload constructor/assignment since I'm not using "new" at all
private:
    // returns the id of the jug with the specified amounts
    // if this combination does not exist, it will be added to the list of unfinished vertices
    int getID(int amountA, int amountB, vector<int> &unfinishedVertices);

    // Display the graph in readable form
    void printGraph() const;

    // Helper for printGraph
    void showState(int i) const;

    // returns a string based on the action that made the edge
    string getAction(const edge &edge) const;
};

