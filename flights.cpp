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
    /**
     * Generates nodes and edges for a graph, based on an input file.
     * 
     * @param g a pointer to the graph to be generated
     * @param filename a string equal to the filename of the input file
     */
    ifstream fileAirports(filename);

    // non-existant or corrupted file
    if (fileAirports.fail())
    {
        die("Check if file exists!");
    }

    float weight; // the edge weight
    string fromAirport, destinationAirport, line, word;

    // first pass through the file, add airports
    while (std::getline(fileAirports, line))
    {
        stringstream lineStream(line); // get the line

        // parse the csv row
        std::getline(lineStream, word, ',');
        fromAirport = word;

        std::getline(lineStream, word, ',');
        destinationAirport = word;

        std::getline(lineStream, word, ',');
        weight = atof(word.c_str());

        // add vertices to graph
        g->addAirport(fromAirport);        // won't add if already exists
        g->addAirport(destinationAirport); // won't add if already exists
    }

    ifstream fileEdges(filename);
    // second pass through the file, add edges
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
                     "1. Print airports\n"
                     "2. Cheapest route from A to B...\n"
                     "3. Nonstop flights from...\n"
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
            cout << "Enter the departing airport code: ";
            string from, to;
            getline(cin, from);
            cout << "Enter the arriving airport code: ";
            getline(cin, to);
            g.showCheapestRoute(from, to);
            break;
        }
        case 3:
        {
            cout << "Enter the departing airport code: ";
            string from;
            getline(cin, from);
            g.showNonstopRoutes(from);
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
