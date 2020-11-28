#include "Graph.h"
#include "limits.h"
#include <stack>

using namespace std;

void Graph::unVisit()
{
    for (vertex *v : vertices)
        v->visited = false;
}

void Graph::addEdge(string v1, string v2, int weight)
{
    for (int i = 0; i < vertices.size(); i++)
    {
        // find the first vertex
        if (vertices[i]->name == v1)
        {
            for (int x = 0; x < vertices.size(); x++)
            {
                // find the second vertex
                if (vertices[x]->name == v2 && i != x)
                {
                    // add second vertex as adj to first vertex
                    adjVertex *vert = new adjVertex();
                    vert->v = vertices[x];
                    vert->weight = weight;
                    vertices[i]->adj.push_back(vert);
                }
            }
        }
    }
}

void Graph::addVertex(string name)
{
    bool inGraph = false;

    // check if already in the graph
    for (vertex *v : vertices)
    {
        if (v->name == name)
            inGraph = true;
    }

    // if not, add to vertices
    if (!inGraph)
    {
        vertex *v = new vertex(name);
        vertices.push_back(v);
    }
}

void Graph::displayEdges()
{
    for (vertex *v : vertices)
    {
        if (v->adj.size() > 0)
        {
            cout << v->name << " (" << v->adj.size() << " routes)" << endl;
            for (adjVertex *adj : v->adj)
                cout << "  " << adj->v->name << " (" << adj->weight << ")" << endl;
        }
    }
    return;
}

vertex *Graph::findVertex(string name)
{
    for (int i = 0; i < vertices.size(); ++i)
    {
        if (vertices[i]->name == name)
            return vertices[i];
    }
    return NULL;
}

int getWeightToParent(vertex *v)
{
    /*
    returns the weight of the edge connecting a vertex v to its parent
    */
    string parentName = v->parent->name;
    for (adjVertex *adjacent : v->adj)
    {
        if (adjacent->v->name == parentName)
        {
            return adjacent->weight;
        }
    }
    return -1;
}

void Graph::showCheapestRoutes(string from)
{
    cout << "cheapest routes from " << from << endl;
    dijkstra(from);
    // todo sort results low to high (priority queue?)
}

// START OF DIJKSTRAS

vertex *Graph::getMinNode()
{
    // return the node with the lowest distance that has not yet been visited
    int min = INT_MAX;
    vertex *minNode;

    for (vertex *v : vertices)
    {
        if (!v->visited && v->distance < min)
        {
            minNode = v;
            min = v->distance;
        }
    }
    return minNode;
}

bool Graph::allVisitedCheck()
{
    // return true if all nodes have been visited
    for (vertex *v : vertices)
    {
        if (!v->visited) // if a node has not been visited
            return false;
    }
    return true;
}

void Graph::dijkstra(string src)
{
    vertex *root = findVertex(src);
    root->distance = 0; // this is the starting node

    while (!allVisitedCheck())
    {
        vertex *minUnvisited = getMinNode();
        minUnvisited->visited = true;

        // set the distances for the neighbors of the root node
        for (adjVertex *a : minUnvisited->adj)
        {
            int newCumeDistance = minUnvisited->distance + a->weight;
            if (a->v->distance > newCumeDistance)
            {
                // compare the current distance to the new distance
                // update the distance if it's shorter
                a->v->distance = newCumeDistance;
            }
        }
    }

    // todo return a vector of vertex pointers

    for (vertex *v : vertices)
    {
        if (v->distance > 0)
        {
            // todo print full route, not just name
            cout << v->name << " (" << v->distance << ") " << endl;
        }
    }

    for (vertex *v : vertices)
    {
        // unvisit
        v->visited = false;
        // reset distance to intmax
        v->distance = INT_MAX;
    }
}
// END OF DIJKSTRAS
