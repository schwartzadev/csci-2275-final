#include "Graph.h"
#include "limits.h"
#include <stack>

using namespace std;

void Graph::unVisit()
{
    /// Unvisits all of the vertices in the graph
    for (vertex *v : vertices)
        v->visited = false;
}

void Graph::addEdge(string v1, string v2, int weight)
{
    /**
     * Adds an directional edge to the graph
     * 
     * @param v1 the starting node of the edge
     * @param v2 the ending node of the edge
     * @param weight the weight of the edge
     */
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
    /**
     * Adds a vertex to the graph if it doesn't already exist
     * 
     * @param name the name of the vertex to be added
     */
    bool inGraph = false;

    // check if already in the graph
    for (vertex *v : vertices)
    {
        if (v->name == name)
            return; // exit
    }

    // if not, add to vertices
    vertex *v = new vertex(name);
    vertices.push_back(v);
}

void Graph::displayEdges()
{
    /// Displays all of the edges in the graph
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

vertex* Graph::findVertex(string name)
{
    /**
     * Finds a vertex in the graph based on its name
     * 
     * @param name the name of the vertex to be found
     * @return a pointer to the vertex if it exists, NULL if it doesn't
     */
    for (int i = 0; i < vertices.size(); ++i)
    {
        if (vertices[i]->name == name)
            return vertices[i];
    }
    return NULL;
}

void Graph::showNonstopRoutes(string from)
{
    /**
     * Displays all of the nonstop routes from a given vertex, sorted by price low to high.
     * 
     * @param from the name of the starting vertex
     */ 
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
    /**
     * Shows the cheapest route between two vertices.
     * 
     * @param from the starting vertex in the route
     * @param from the destination vertex in the route
     */
    vertex *v = dijkstra(from, to);

    // no route was found, nodes are not connected
    if (!v->visited)
    {
        cout << "  No route found!" << endl;
        return;
    }

    // log route to the console
    cout << "Cheapest route:" << endl;
    vertex *traverse = v;
    cout << "  " << from << " -> ";
    string latestParent = from; // prevent repeats
    while (traverse->parent != nullptr && traverse->parent->name != latestParent)
    {
        cout << traverse->parent->name << " -> ";
        latestParent = traverse->parent->name;
    }
    cout << to << " ($" << v->distance << ")" << endl;

    resetAll();
}

vertex* Graph::getMinNode()
{
    /**
     * Returns the node with the smallest distance that has not yet been visited.
     * Helper function for Djikstra's algorithm.
     * 
     * @return a pointer to the vertex with the smallest distance that is also unvisited
     */
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
    /**
     * Checks if all vertices are visited
     * 
     * @return true if all vertices have been visited, else false
     */
    for (vertex *v : vertices)
    {
        if (!v->visited) // if a node has not been visited
            return false;
    }
    return true;
}

vertex* Graph::dijkstra(string start, string end)
{
    /**
     * Returns the vertex for the starting airport.
     * The cheapest routes can then be accessed with the starting airport's adjacency list.
     * 
     * @param start the starting vertex in the route
     * @param end the ending vertex in the route
     * @return a pointer to the ending vertex
     * 
    **/
    vertex *root = findVertex(start);
    vertex *destination = findVertex(end);
    root->distance = 0; // this is the starting node

    // make a PQ
    // distance as the priority variable
    priority_queue<vertex *, vector<vertex *>, vertexComparator> pQueue;

    pQueue.push(root);

    while (!destination->visited && !pQueue.empty())
    {
        // get the node that has the lowest distance value
        vertex *current = pQueue.top();

        current->visited = true;

        // once we pop the destination, we're done
        if (current->name == end)
            break;

        // pop from the queue
        pQueue.pop();

        // set the distances for the neighbors of the root node
        for (adjVertex *a : current->adj)
        {
            if (!a->v->visited)
            {
                // haven't seen v yet
                int newCumeDistance = current->distance + a->weight;
                if (a->v->distance > newCumeDistance)
                {
                    // compare the current distance to the new distance
                    // update the distance if it's shorter
                    a->v->distance = newCumeDistance;
                    a->v->parent = current;
                    pQueue.push(a->v);
                }
            }
        }
    }
    return destination;
}

void Graph::resetAll()
{
    /// Resets all vertices in the graph
    for (vertex *v : vertices)
    {
        v->visited = false; // unvisit
        v->distance = INT_MAX; // reset distance to intmax
        v->parent = nullptr; // reset parent
    }
}
