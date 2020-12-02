#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <iostream>
#include <queue>
#include <limits.h>

struct airport;

struct adjVertex
{
    airport *v;
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

// todo refactor to airport
struct airport
{
    std::string name;
    airport *parent = nullptr;
    bool visited = false;
    int distance = INT_MAX;
    std::vector<adjVertex*> adj;
    airport() {};
    airport(std::string inName)
    {
        name = inName;
    };
};

class airportComparator
{
public:
    int operator()(const airport *v1, const airport *v2)
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
    void addAirport(std::string name);
    void showCheapestRoute(std::string from, std::string to);
    void showNonstopRoutes(std::string from);
    void displayEdges();
private:
    void resetAll();
    std::vector<airport *> airports;
    airport * dijkstra(std::string from, std::string to);
    airport * getMinNode();
    bool allVisitedCheck();
    void unVisit();
    airport * findAirport(std::string name);
};

#endif // GRAPH_H
