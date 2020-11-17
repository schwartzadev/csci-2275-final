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
    ifstream file(filename);

    // non-existant or corrupted file
    if (file.fail())
    {
        die("Check if file exists!");
    }

    int weight;
    string title, word, line, cur_person;

    vector<string> people;

    std::getline(file, line);
    stringstream lineStream(line);

    // read in vertices
    while (std::getline(lineStream, word, ','))
    {
        if (word != "people")
        {
            g->addVertex(word);
            people.push_back(word);
        }
    }

    // read in edges
    while (std::getline(file, line))
    {
        stringstream lineStream(line);
        // get the name of the person
        std::getline(lineStream, word, ',');
        cur_person = word;

        // cycle through potential edges
        for (int i = 0; i < people.size(); i++)
        {
            std::getline(lineStream, word, ',');
            weight = atoi(word.c_str());

            // add edge to graph if not -1
            if (weight != -1 && weight != 0)
                g->addEdge(cur_person, people[i], weight);
        }
    }
}

int main(int argc, const char *argv[])
{
    Graph g;
    string menuStr = "======Main Menu======\n"
                   "1. Print vertices\n"
                   "5. Quit\n";

    if (argc < 2)
    {
        die("Missing flights data!");
    }

    int choice = 0;
    bool done = false;

    string filename(argv[1]);
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
