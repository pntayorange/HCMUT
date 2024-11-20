
#include <iostream>
#include <vector>
#include <unordered_map>
#include <limits>
#include <fstream>
#include <bits/stdc++.h>
#include <cstdio>
#include <cstdint>

using namespace std;
void BF(int Graph[20][20], int n, char start, int BFValue[], int BFPrev[])
{
    int first = start - 'A';
    int sum;
    int count = 0;
    BFValue[first] = 0;
    int *ValuePast = new int[n];
    for (int i = 0; i < n; i++)
    {
        ValuePast[i] = BFValue[i];
    }
    for (int i = 0; i < n; i++)
    {

        for (int j = 0; j < n; j++)
        {
            if (Graph[i][j] != 0 && BFValue[i] != -1)
            {
                sum = ValuePast[i] + Graph[i][j];

                if (BFValue[i] != -1 && (BFValue[j] == -1))
                {
                    ValuePast[j] = BFValue[j];
                    BFValue[j] = sum;
                    BFPrev[j] = i;
                    count++;
                }

                if (BFValue[i] != -1 && (sum < BFValue[j]))
                {
                    ValuePast[j] = BFValue[j];
                    BFValue[j] = sum;
                    BFPrev[j] = i;
                }
            }
        }
        if (count == n - 1)
            break;
    }
}
int main()
{
    system("cls");
    ifstream fin;
    int G[20][20];
    int G2[20][20];
    int BFValue[20];
    int BFPrev[20];
    fin.open("inputMat12_1.txt");
    int n = 8;
    for (int i = 0; i < n; i++)
    {
        BFValue[i] = -1;
        BFPrev[i] = -1;
        for (int j = 0; j < n; j++)
        {
            fin >> G[i][j];
        }
    }
    fin.close();
    fin.open("inputMat12_1.txt");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fin >> G2[i][j];
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (i % 2)
            BF(G, n, 'H', BFValue, BFPrev);
        else
            BF(G2, n, 'H', BFValue, BFPrev);
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
    fin.close();
}
/*#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <algorithm> // Ensure this is included for std::reverse
using namespace std;
const int INF = std::numeric_limits<int>::max();
const int N = 20; // Maximum number of nodes in the graph

void reset(int BFValue[], int BFBFPrev[], int n)
{
    for (int i = 0; i < n; ++i)
    {
        BFValue[i] = INF;
        BFBFPrev[i] = -1;
    }
}

std::vector<int> backtrace(int BFBFPrev[], int target)
{
    std::vector<int> path;
    for (int at = target; at != -1; at = BFBFPrev[at])
    {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());
    return path;
}

std::string BF_Path(int G[][N], int n, char sourceChar, char targetChar)
{

    int source = sourceChar - 'A';
    int target = targetChar - 'A';
    if (sourceChar == targetChar)
    {
        string result = "";
        result += (char)(source + 'A');
        return result;
    }
    int BFValue[N], BFBFPrev[N];
    reset(BFValue, BFBFPrev, n);
    BFValue[source] = 0;

    for (int i = 0; i < n - 1; ++i)
    {
        for (int u = 0; u < n; ++u)
        {
            for (int v = 0; v < n; ++v)
            {
                if (G[u][v] != 0 && BFValue[u] != INF && BFValue[u] + G[u][v] < BFValue[v])
                {
                    BFValue[v] = BFValue[u] + G[u][v];
                    BFBFPrev[v] = u;
                }
            }
        }
    }

    for (int u = 0; u < n; ++u)
    {
        for (int v = 0; v < n; ++v)
        {
            if (G[u][v] != 0 && BFValue[u] != INF && BFValue[u] + G[u][v] < BFValue[v])
            {
                return "Negative cycle found!";
            }
        }
    }

    std::vector<int> path = backtrace(BFBFPrev, target);
    if (path.size() == 1 && path[0] == target)
    {
        return "No path exists!";
    }

    // std::string result = "Path: ";
    std::string result = "";
    for (int node : path)
    {
        result += (char)(node + 'A');
        if (node != target)
        {
            result += " ";
        }
    }
    // result += "\nCost: " + std::to_string(BFValue[target]);

    return result;
}

int main()
{
    std::ifstream fin;
    int G[N][N];
    fin.open("inputMat12_1.txt");
    int n = 8; // Assuming the number of nodes is 8, can be read from file as well
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            fin >> G[i][j];
        }
    }

    std::cout << BF_Path(G, n, 'B', 'D') << std::endl;
    fin.close();
}
*/

/*  //****************************************************************

#include <iostream>
#include <vector>
#include <unordered_map>
#include <limits>
#include <fstream>
#include <bits/stdc++.h>
#include <cstdio>
#include <cstdint>

using namespace std;
void BF(int Graph[20][20], int n, char start, int BFValue[], int BFPrev[])
{
    int first = start - 'A';
    int sum;
    int count = 0;
    BFValue[first] = 0;
    int *ValuePast = new int[n];
    for (int i = 0; i < n; i++)
    {
        ValuePast[i] = BFValue[i];
    }
    for (int i = 0; i < n; i++)
    {

        for (int j = 0; j < n; j++)
        {
            if (Graph[i][j] != 0 && BFValue[i] != -1)
            {
                sum = ValuePast[i] + Graph[i][j];

                if (BFValue[i] != -1 && (BFValue[j] == -1))
                {
                    ValuePast[j] = BFValue[j];
                    BFValue[j] = sum;
                    BFPrev[j] = i;
                    count++;
                }

                if (BFValue[i] != -1 && (sum < BFValue[j]))
                {
                    ValuePast[j] = BFValue[j];
                    BFValue[j] = sum;
                    BFPrev[j] = i;
                }
            }
        }
        if (count == n - 1)
            break;
    }
}
*/