
/*
main.cpp for the main function where you set up running all the questions of the assignment.
Students decide for themselves what is the input and output in the main function to represent
their result;
• bellman.cpp and bellman.h for Bellman-Ford related functions;
• tsm.cpp and tsm.h for travelling salesman related functions along with a tsm.pdf report file
to explain your approach to finding the solution to the travelling salesman problem.
*/
//* Turn 1: g++ -o main main.cpp bellman.cpp tsm.cpp
//* Turn 2: ./main
#include <iostream>
#include <fstream>
#include <ctime>
#include "bellman.h"
#include "tsm.h"

using namespace std;

int main()
{
    int choice;
    cout << "Enter 0 for BF() or 1 for BF_Path or 2 for TSP: ";
    cin >> choice;
    if (choice == 0)
    {
        system("cls");
        ifstream fin;
        int G[20][20];
        int BFValue[20];
        int BFPrev[20];
        fin.open("inputMat20_1.txt");
        int n = 20;
        for (int i = 0; i < n; i++)
        {
            BFValue[i] = -1;
            BFPrev[i] = -1;
            for (int j = 0; j < n; j++)
            {
                fin >> G[i][j];
            }
        }
        for (int s = 0; s < 1; s += 2)
        {
            cout << "From " << char('A' + s) << endl;
            for (int i = 0; i < n; i++)
            {
                BF(G, n, s + 'A', BFValue, BFPrev);
                cout << "step" << i + 1 << ":" << endl;
                for (int j = 0; j < n; j++)
                {
                    cout << BFValue[j] << " ";
                }
                cout << endl;
                for (int j = 0; j < n; j++)
                {
                    cout << BFPrev[j] << " ";
                }
                cout << endl;
            }
        }
        fin.close();
    }
    else if (choice == 1)
    {
        system("cls");
        ifstream fin;
        int G[20][20];
        int BFValue[20];
        int BFPrev[20];
        fin.open("inputMat20_2.txt");
        int n = 18;
        for (int i = 0; i < n; i++)
        {
            BFValue[i] = -1;
            BFPrev[i] = -1;
            for (int j = 0; j < n; j++)
            {
                fin >> G[i][j];
            }
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << BF_Path(G, n, char(i + 'A'), char(j + 'A')) << endl;
            }
        }
        fin.close();
    }
    else if (choice == 2)
    {
        clock_t tStart = clock();
        system("cls");
        ifstream fin;
        int G[20][20];
        fin.open("Trave12_In.txt");
        int n = 12;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                fin >> G[i][j];
            }
        }
        string output = Traveling(G, n, 'A');
        cout << output << endl;
        fin.close();
        cout << "\nTime of execution: " << (double)(clock() - tStart) / (CLOCKS_PER_SEC) << " seconds." << endl;
    }
    else
    {
        cout << "Invalid choice." << endl;
    }

    return 0;
}
