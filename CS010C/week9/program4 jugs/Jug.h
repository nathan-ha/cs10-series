#pragma once
#include <string>

using std::string;

/*
    A problem is given by (Ca, Cb, N, cfA, cfB, ceA, ceB, cpAB, cpBA), where
    Ca and Cb are the capacities of the jugs A and B, respectively, and
    N is the goal.
    cfA is the cost to fill A,
    cfB is the cost to fill B,
    ceA, is the cost to empty A,
    ceB is the cost to empty B,
    cpAB is the cost to pour A to B and c
    pBA is the cost to pour B to A.
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

class Jug
{
private:
    int capacityA_, capacityB_;
    int n_;
    int cfA_, cfB_;
    int ceA_, ceB_;
    int cpAB_, cpBA_;
public:
    Jug(int, int, int, int, int, int, int, int, int);
    ~Jug();

    // solve is used to check input and find the solution if one exists
    // returns -1 if invalid inputs. solution set to empty string.
    // returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
    // returns 1 if solution is found and stores solution steps in solution string.
    int solve(string &solution) const;

private:
    // anything else you need
};