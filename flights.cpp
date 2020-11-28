#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Graph.h"

using namespace std;

void die(string message)
{
    cout << message << endl;
    exit(0);
}

void generate_graph(Graph *g, std::string filename)
{
    ifstream fileVertices(filename);

    // non-existant or corrupted file
    if (fileVertices.fail())
    {
        die("Check if file exists!");
    }

    float weight;
    string fromAirport, destinationAirport, line, word;
    while (std::getline(fileVertices, line))
    {
        stringstream lineStream(line);

        // parse the csv row
        std::getline(lineStream, word, ',');
        fromAirport = word;

        std::getline(lineStream, word, ',');
        destinationAirport = word;

        std::getline(lineStream, word, ',');
        weight = atof(word.c_str());

        g->addVertex(fromAirport);        // won't add if already exists
        g->addVertex(destinationAirport); // won't add if already exists
    }

    ifstream fileEdges(filename);
    while (std::getline(fileEdges, line))
    {
        stringstream lineStream(line);
        std::getline(lineStream, word, ',');
        fromAirport = word;

        std::getline(lineStream, word, ',');
        destinationAirport = word;

        std::getline(lineStream, word, ',');
        weight = atof(word.c_str());

        // add one-directional edge
        g->addEdge(fromAirport, destinationAirport, weight);
    }
}

int main(int argc, const char *argv[])
{
    string menuStr = "======Main Menu======\n"
                     "1. Print vertices\n"
                     "2. Cheapest flights from...\n"
                     "5. Quit\n";

    if (argc < 2)
    {
        die("Missing flights data!");
    }

    int choice = 0;
    bool done = false;

    string filename(argv[1]);

    Graph g = Graph();

    generate_graph(&g, filename);

    do
    {
        cout << menuStr;
        cin >> choice;

        // flush the newlines and other characters
        cin.clear();
        cin.ignore();

        switch (choice)
        {
        case 1:
        {
            g.displayEdges();
            break;
        }
        case 2:
        {
            cout << "Enter the starting airport code: ";
            string from;
            getline(cin, from);
            g.showCheapestRoutes(from);
            break;
        }
        default:
        {
            done = true;
            break;
        }
        }

    } while (!done);

    cout << "Goodbye!" << endl;
    return 0;
}
