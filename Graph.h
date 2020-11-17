#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <iostream>
#include <queue>

struct vertex;

struct adjVertex
{
    vertex *v;
    int weight;
};

struct vertex
{
    std::string name;
    vertex *parent;
    bool visited = false;
    int distance;
    std::vector<adjVertex> adj;
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
    std::vector<vertex> vertices; // todo make private
private:
    void unVisit();
    vertex *findVertex(std::string name);
};

#endif // GRAPH_H
