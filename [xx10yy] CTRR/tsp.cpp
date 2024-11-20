//* Với inputMat20_1.txt thì n=12 là 2s còn n = 13 là 24s(gấp 12) => n=14(là hơn 144s)
//* Với Trave12_In.txt thì n=12 là 4.073s
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
    cout <<Min_PathCosts<<endl;
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

int main()
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
    string output = Traveling(G, n, 'J');
    cout << output << endl;
    // int cost = pathlength(G, n, output);
    // double partile = 0;
    // if ((354 - 354 * partile) <= cost && cost <= (354 + 354 * partile))
    //{
    //     cout << "your output is correct";
    // }
    fin.close();
    cout << "\nTime of execution: " << (double)(clock() - tStart) / (CLOCKS_PER_SEC) << " seconds." << endl;
    return 0;
}
/* A E D G B H C F A */
/*n=14
184
A M H D L G I N E K J B C F A

Time of execution: 581.047 seconds.
n=13
198
A M E B D C H F J I L G K A

Time of execution: 19.018 seconds.
n=12
215
A B J F G C I L D K E H A
*/