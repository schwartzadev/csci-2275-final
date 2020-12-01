#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <iostream>
#include <queue>
#include <limits.h>

struct vertex;

struct adjVertex
{
    vertex *v;
    int weight;
};

class adjVertexComparator
{
public:
    int operator()(const adjVertex * adj1, const adjVertex * adj2)
    {
        return adj1->weight > adj2->weight;
    }
};

struct vertex
{
    std::string name;
    vertex *parent = nullptr;
    bool visited = false;
    int distance = INT_MAX;
    std::vector<adjVertex*> adj;
    vertex() {};
    vertex(std::string inName)
    {
        name = inName;
    };
};

class vertexComparator
{
public:
    int operator()(const vertex *v1, const vertex *v2)
    {
        return v1->distance > v2->distance;
    }
};

class Graph
{
public:
    Graph(){};
    ~Graph(){};
    void addEdge(std::string v1, std::string v2, int weight);
    void addVertex(std::string name);
    int isAdjacent(std::string v1, std::string v2);
    void displayEdges();
    void showCheapestRoute(std::string from, std::string to);
    void showNonstopRoutes(std::string from);
    void resetAll();
    std::vector<vertex *> vertices; // todo make private
private:
    vertex * dijkstra(std::string from, std::string to);
    void pathBack();
    vertex * getMinNode();
    bool allVisitedCheck();
    void unVisit();
    vertex * findVertex(std::string name);
};

#endif // GRAPH_H
