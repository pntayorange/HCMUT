#ifndef TSM_H
#define TSM_H

#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
#include <algorithm>
#include <fstream>

using namespace std;

const int N = 20;

class SimpleTSP
{
private:
    int Vertex;
    int Graph[N][N];
    bool Visited[N];
    int Current_Path[N];
    int Min_Path[N];
    int Min_PathCosts;
    int Original;
    int TSP(int Current_Vertex, int Counter_Vertex, int Current_Cost);

public:
    SimpleTSP(const int G[N][N], int n);
    void runTSP(int original);
    string Trace();
};

string Traveling(int G[][N], int n, char original);

#endif // TSM_H
