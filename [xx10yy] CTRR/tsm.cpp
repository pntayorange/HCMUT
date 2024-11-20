#include "tsm.h"

SimpleTSP::SimpleTSP(const int G[N][N], int n) 
: Vertex(n), Min_PathCosts(numeric_limits<int>::max())
{
    for (int i = 0; i < Vertex; ++i)
    {
        for (int j = 0; j < Vertex; ++j)
        {
            if (i != j)
                Graph[i][j] = G[i][j];
            else
                Graph[i][j] = 0;
        }
    }
}

void SimpleTSP::runTSP(int original)
{
    Original = original;
    fill(begin(Visited), begin(Visited) + Vertex, false);
    Visited[original] = true;
    Current_Path[0] = original;
    Min_PathCosts = numeric_limits<int>::max();
    TSP(original, 1, 0.0f);
}

int SimpleTSP::TSP(int Current_Vertex, int Counter_Vertex, int Current_Cost)
{
    if (Counter_Vertex >= Vertex)
    {
        int distance = Graph[Current_Vertex][Original];
        if (distance > 0)
        {
            return Current_Cost + distance;
        }
    }
    
    for (int i = 0; i < Vertex; ++i)
    {
        if (!Visited[i] && Current_Vertex != i && Graph[Current_Vertex][i] != 0 && Current_Vertex != i)
        {
            Visited[i] = true;
            Current_Path[Counter_Vertex] = i;
            int result = TSP(i, Counter_Vertex + 1, Current_Cost + Graph[Current_Vertex][i]);
            Visited[i] = false;
            if (result < Min_PathCosts)
            {
                Min_PathCosts = result;
                copy(begin(Current_Path), begin(Current_Path) + Vertex, begin(Min_Path));
            }
        }
    }
    return INT_MAX;
}

string SimpleTSP::Trace()
{   
    cout << Min_PathCosts << endl;
    string ANS = "";
    for (int i = 0; i < Vertex; ++i)
    {
        ANS += (char)(Min_Path[i] + 65) + string(" ");
    }
    ANS += (char)(Original + 65) + string("\0");
    return ANS;
}

string Traveling(int G[][N], int n, char original)
{
    SimpleTSP tsp(G, n);
    tsp.runTSP((int)(original - 65));
    return tsp.Trace();
}

