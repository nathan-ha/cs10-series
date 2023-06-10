// This is a sketch of how to set up the graph with some output to help
// you see how I chose to build it.  The main here sets up the test problem
// with jug A holding 3 cups and jug B holding 5 cups.
//
// We get a graph with 15 nodes that looks like this...
// ID	(A,B)	fillA	fillB	emptyA	emptyB	pourAB	pourBA
// 0	(0,0)	1(3,0)	2(0,5)	0(0,0)	0(0,0)	0(0,0)	0(0,0)
// 1	(3,0)	1(3,0)	3(3,5)	0(0,0)	1(3,0)	15(0,3)	1(3,0)
// 2	(0,5)	3(3,5)	2(0,5)	2(0,5)	0(0,0)	2(0,5)	4(3,2)
// 3	(3,5)	3(3,5)	3(3,5)	2(0,5)	1(3,0)	3(3,5)	3(3,5)
// 4	(3,2)	4(3,2)	3(3,5)	5(0,2)	1(3,0)	2(0,5)	4(3,2)
// 5	(0,2)	4(3,2)	2(0,5)	5(0,2)	0(0,0)	5(0,2)	6(2,0)
// 6	(2,0)	1(3,0)	7(2,5)	0(0,0)	6(2,0)	5(0,2)	6(2,0)
// 7	(2,5)	3(3,5)	7(2,5)	2(0,5)	6(2,0)	7(2,5)	8(3,4)
// 8	(3,4)	8(3,4)	3(3,5)	9(0,4)	1(3,0)	7(2,5)	8(3,4)
// 9	(0,4)	8(3,4)	2(0,5)	9(0,4)	0(0,0)	9(0,4)	10(3,1)
// 10	(3,1)	10(3,1)	3(3,5)	11(0,1)	1(3,0)	9(0,4)	10(3,1)
// 11	(0,1)	10(3,1)	2(0,5)	11(0,1)	0(0,0)	11(0,1)	12(1,0)
// 12	(1,0)	1(3,0)	13(1,5)	0(0,0)	12(1,0)	11(0,1)	12(1,0)
// 13	(1,5)	3(3,5)	13(1,5)	2(0,5)	12(1,0)	13(1,5)	14(3,3)
// 14	(3,3)	14(3,3)	3(3,5)	15(0,3)	1(3,0)	13(1,5)	14(3,3)
// 15	(0,3)	14(3,3)	2(0,5)	15(0,3)	0(0,0)	15(0,3)	1(3,0)
//
// Consider vertex 7.  Here, we have 2 cups in A and 5 in B.
// If we fill A, we move to vertex 3 and will have 3 in A, 5 in B
// If we fill B, we state at vertex 7 still have 2 in A, 5 in B
// If we empty A, we move to vertex 2 and will have 0 in A, 5 in B
// If we empty B, we move to vertex 6 and will have 2 in A, 0 in B
// If we pour from A to B, nothing changes (B is already full)
// If we pour from B to A, move to vertex 8 where A is full, and B has 4
//
// For the Die Hard 3 example from zyBook, we are looking for a state
// with 0 in jug A and 4 in jug B (vertex 9).  This configuration
// exists in the graph, so it is possible to go from the initial
// state (0,0) there.  We could not get to a state like (0,6) because
// jug B can't hold that much (and that state is not in this graph)
// That's how we know if a problem is "solveable"
//
// Next, we want to find the shortest path from the empty state to
// the desired state.  This is where Dijkstra's shortest path algorithm
// comes to play (see zyBook section 10.3).  A couple ways to do that
// either put "shortest distance", "visited", and "prev" fields in the
// vertex or maintain them as outside data structures when you find
// the shortest path.
//
// For this example, you will see that state changes from the Die Hard
// example do correspond to states along the shortest path you'll find...
//
// The zybook says....
// The solution they reached was to fill the 5-gallon jug,
//    from 0:(0,0) to 2:(0,5)
// pour the 5-gallon jug into the 3-gallon jug
//    from 2:(0,5) to 4:(3,2)
// empty the 3-gallon jug
//    from 4:(3,2) to 5:(0,2)
// pour the 5-gallon jug into the 3-gallon jug
//    from 5:(0,2) to 6:(2,0)
// fill the 5-gallon jug
//    from 6:(2,0) to 7:(2,5)
// fill the 3-gallon jug from the 5-gallon jug
//    from 7:(2,5) to 8:(3,4)
// empty the 3 gallon jug
//    from 8:(3,4) to 9:(0,4)


#include <iostream>
#include <vector>

using namespace std;

class SimplifiedJug {
  // Our graph is made out of vertices.  Each with 6 outedges representing
  // which graph vertex is the result of our six possible actions
  struct vertex {
    int A;			// How much in jug A
    int B;			// How much in jug B
    int id;			// unique node id

    // This is our adjacency list... each vertex can go one of six
    // places for our six possible actions.  Sometimes this is right
    // back to this vertex (e.g. if we are empty (0,0) and we do an
    // emptyA action, we are still empty.  -1 means unset here
    vector<int> newStateAfterAction;

    vertex(int A, int B, int id)
      : A(A), B(B), id(id), newStateAfterAction(6,-1)
    {}
  };


  int cA;			// capacity of A jug
  int cB;			// capacity of B jug
  
  // This is the graph we are trying to build.  Each vertex has six
  // outedges that represent the new state AFTER you do a...
  // * fillA
  // * fillB
  // * emptyA
  // * emptyB
  // * pourAToB
  // * pourBToA
  vector<vertex> graph;

  // This looks up an A:B combination in the graph and returns its
  // id (same as its index)
  int findInGraph(int A, int B, vector<int>& unfinishedVertices) {
    // We may already have this combination of A and B.  If so, return it
    for(int i=0; i < graph.size(); ++i) {
        if (graph[i].A == A && graph[i].B == B) return i;
    }

    // We did not have it, so create a new vertex with this combination
    // Also add the index to the list of unfinished nodes so we remember
    // to set its six outedges
    int id = graph.size();
    unfinishedVertices.push_back(id);
    cout << "Add: " << A << "," << B << " at index " << id << endl;
    graph.push_back( vertex(A, B, id) );
    return id;
  }

public:
  SimplifiedJug(int cA, int cB)
    : cA(cA), cB(cB)
  {
    // As we build the graph, we want to add in new vertices and we
    // have to remember to set all the outedges.  This just keeps
    // track of which ones are not part of the graph
    vector<int> unfinishedNodes;

    // We start by adding the empty jug.  This creates a new vertex
    // and appends it to the graph.  Since we haven't set its six
    // out edges yet, we will make a note of it in the unfinishedNodes
    // stack
    int index = findInGraph(0, 0, unfinishedNodes);

    // So here, we have one vertex in the graph.  It has an id of 0,
    // and the outedges are all -1 (unset), but it is in the list
    // of unfinishedNodes, so we'll fix that below
    cout << "What graph looks like after we've added just the empty node (unfixed)" << endl;
    printGraph();
    cout << endl;

    // Now, for each unfinished vertex, we have to add connections that correspond
    // to the new state after doing one of the six actions (so six outedges).
    // Doing this may create new unfinished vertices
    while(unfinishedNodes.size() > 0) {
      // Get an unfinished node
      int id = unfinishedNodes.back();
      unfinishedNodes.pop_back();

      
      // This state has a current A and B value
      int A = graph[id].A;
      int B = graph[id].B;
      cout << "Fix vertex " << id << " (" << A << ',' << B << ")" << endl;
      // State after we fill up the A jug
      int fillA = findInGraph(cA, B, unfinishedNodes);

      // After filling the B jug
      int fillB = findInGraph(A, cB, unfinishedNodes);

      // After emptying the A jug
      int emptyA = findInGraph(0, B, unfinishedNodes);

      // After emptying the B jug
      int emptyB = findInGraph(A, 0, unfinishedNodes);

      // After pouring A into B
      int roomInB = cB - B;
      int poursize = min(A, roomInB);
      int pourAToB = findInGraph(A-poursize, B+poursize, unfinishedNodes);

      // After pouring B into A
      int roomInA = cA - A;
      poursize = min(B, roomInA);
      int pourBToA = findInGraph(A+poursize, B-poursize, unfinishedNodes);

      // Now we can set the six outedges for this vertex
      graph[id].newStateAfterAction[0] = fillA;
      graph[id].newStateAfterAction[1] = fillB;
      graph[id].newStateAfterAction[2] = emptyA;
      graph[id].newStateAfterAction[3] = emptyB;
      graph[id].newStateAfterAction[4] = pourAToB;
      graph[id].newStateAfterAction[5] = pourBToA;

      // The graph may now has some new unfinished vertices in it.
      printGraph();
      cout << endl;
    }
  }

  // Helper for printGraph
  void showState(int i) {
    cout << '\t' << i;
    if (i != -1) {
      cout << '(' << graph[i].A << ',' << graph[i].B << ')';
    }
  }

  // Display the graph in readable form
  void printGraph() {
    cout << "ID\t(A,B)\tfillA\tfillB\temptyA\temptyB\tpourAB\tpourBA" << endl;
    for(const auto& v: graph) {
      cout << v.id << "\t(" << v.A << ',' << v.B << ")";
      showState(v.newStateAfterAction[0]);
      showState(v.newStateAfterAction[1]);
      showState(v.newStateAfterAction[2]);
      showState(v.newStateAfterAction[3]);
      showState(v.newStateAfterAction[4]);
      showState(v.newStateAfterAction[5]);
      cout << endl;
    }
  }
};

int main() {
  SimplifiedJug G(3,5);
}
 