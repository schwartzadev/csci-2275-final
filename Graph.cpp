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

void Graph::showNonstopRoutes(string from)
{
    vertex *fromVertex = findVertex(from);

    priority_queue<adjVertex *, vector<adjVertex *>, adjVertexComparator> pQueue;

    for (adjVertex *adj : fromVertex->adj)
        pQueue.push(adj);

    cout << "Nonstop routes from " << from << ":" << endl;

    // pop all items
    while (!pQueue.empty())
    {
        cout << "  " << fromVertex->name << " -> " << pQueue.top()->v->name << " ($" << pQueue.top()->weight << ")" << endl;
        pQueue.pop();
    }
}

void Graph::showCheapestRoute(string from, string to)
{
    cout << "cheapest route from " << from << " to " << to << ": ";
    vertex *v = dijkstra(from, to);
    cout << "$" << v->distance << endl;

    // reset v
    v->visited = false;
    v->distance = INT_MAX;
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

vertex *Graph::dijkstra(string start, string end)
{
    /**
     * returns the vertex for the starting airport
     * 
     * the cheapest routes can then be accessed with
     * the starting airport's adjacency list
    **/
    vertex *root = findVertex(start);
    vertex *final = findVertex(end);
    root->distance = 0; // this is the starting node

    // make a PQ
    // distance as the priority variable
    priority_queue<vertex *, vector<vertex *>, vertexComparator> pQueue;

    pQueue.push(root);

    while (!final->visited)
    {
        // get the node that has the lowest distance value
        vertex *current = pQueue.top();

        // once we pop the destination, we're done
        if (current->name == end) {
            break;
        }

        // pop from the queue
        pQueue.pop();

        current->visited = true;

        // look at adjacent nodes
        // if i have not yet visited those adjacent nodes, add them to the PQ
        for (adjVertex *adj : current->adj)
        {
            if (!adj->v->visited)
                pQueue.push(adj->v);
        }

        // set the distances for the neighbors of the root node
        for (adjVertex *a : current->adj)
        {
            int newCumeDistance = current->distance + a->weight;
            if (a->v->distance > newCumeDistance)
            {
                // compare the current distance to the new distance
                // update the distance if it's shorter
                a->v->distance = newCumeDistance;
            }
        }
    }

    for (vertex *v : vertices)
    {
        if (v->name != final->name)
        {
            // unvisit
            v->visited = false;
            // reset distance to intmax
            v->distance = INT_MAX;
        }
    }

    return final;
}
// END OF DIJKSTRAS
