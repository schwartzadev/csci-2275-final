#include <iostream>
#include "Graph.h"

using namespace std;

int main(int argc, const char *argv[])
{
    string menuStr = "======Main Menu======\n"
                     "1. Print airports\n"
                     "2. Cheapest route from A to B...\n"
                     "3. Nonstop flights from...\n"
                     "5. Quit\n";

    if (argc < 2)
    {
        cout << "Missing flights data!" << endl;
        exit(1);
    }

    int choice = 0;
    bool done = false;

    string filename(argv[1]);

    Graph g = Graph(filename);

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
