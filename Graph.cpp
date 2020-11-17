#include "Graph.h"
#include <stack>

using namespace std;

void Graph::unVisit()
{
    for (vertex v : vertices)
        v.visited = false;
}

void Graph::addEdge(string v1, string v2, int weight)
{
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i].name == v1)
        { // find the first vertex
            for (int x = 0; x < vertices.size(); x++)
            {
                if (vertices[x].name == v2 && i != x)
                { // find the second vertex

                    // check if the edge already exists
                    bool alreadyInFirst = false;
                    bool alreadyInSecond = false;
                    for (adjVertex adj : vertices[i].adj)
                    {
                        if (adj.weight == weight && adj.v->name == v2)
                        {
                            alreadyInFirst = true;
                        }
                    }
                    for (adjVertex adj : vertices[x].adj)
                    {
                        if (adj.weight == weight && adj.v->name == v1)
                        {
                            alreadyInSecond = true;
                        }
                    }
                    if (alreadyInFirst && alreadyInSecond)
                    {
                        // this exact edge already exists
                        return;
                    }

                    // add second vertex as adj to first vertex
                    adjVertex vert;
                    vert.v = &vertices[x];
                    vert.weight = weight;
                    vertices[i].adj.push_back(vert);

                    // add first vertex as adj to second vertex
                    adjVertex vertReverse;
                    vertReverse.v = &vertices[i];
                    vertReverse.weight = weight;
                    vertices[x].adj.push_back(vertReverse);
                }
            }
        }
    }
}

void Graph::addVertex(string name)
{
    bool inGraph = false;

    // check if already in the graph
    for (vertex v : vertices)
    {
        if (v.name == name)
            inGraph = true;
    }

    // if not, add to vertices
    if (!inGraph)
    {
        vertex v;
        v.name = name;
        vertices.push_back(v);
    }
}

void Graph::displayEdges()
{
    for (vertex v : vertices)
    {
        for (adjVertex adj : v.adj)
        {
            cout << "  " << adj.v->name << " (" << adj.weight << ")" << endl;
        }
    }
    return;
}

vertex *Graph::findVertex(string name)
{
    for (int i = 0; i < vertices.size(); ++i)
    {
        if (vertices[i].name == name)
            return &vertices[i];
    }
    return NULL;
}

int getWeightToParent(vertex *v)
{
    /*
    returns the weight of the edge connecting a vertex v to its parent
    */
    string parentName = v->parent->name;
    for (adjVertex adjacent : v->adj)
    {
        if (adjacent.v->name == parentName)
        {
            return adjacent.weight;
        }
    }
    return -1;
}
