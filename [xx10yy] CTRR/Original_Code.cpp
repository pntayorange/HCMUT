// ! Code gốc của BF_Path
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <algorithm> // Ensure this is included for reverse
using namespace std;
const int INF = numeric_limits<int>::max();
const int N = 20; // Maximum number of nodes in the graph

void reset(int BFValue[], int BFBFPrev[], int n)
{
    for (int i = 0; i < n; ++i)
    {
        BFValue[i] = INF;
        BFBFPrev[i] = -1;
    }
}

vector<int> backtrace(int BFBFPrev[], int target)
{
    vector<int> path;
    for (int at = target; at != -1; at = BFBFPrev[at])
    {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    return path;
}

string BF_Path(int G[][N], int n, char sourceChar, char targetChar)
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

    vector<int> path = backtrace(BFBFPrev, target);
    if (path.size() == 1 && path[0] == target)
    {
        return "No path exists!";
    }

    // string result = "Path: ";
    string result = "";
    for (int node : path)
    {
        result += (char)(node + 'A');
        if (node != target)
        {
            result += " ";
        }
    }
    // result += "\nCost: " + to_string(BFValue[target]);

    return result;
}

int main()
{
    ifstream fin;
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

    cout << BF_Path(G, n, 'B', 'D') << endl;
    fin.close();
}

// ! Code gốc của TSP
//*#include <iostream>
//*#include <iomanip>
//*#include <cmath>
//*#include <vector>
//*#include <limits>
//*#include <array>
//*#include <algorithm>
//*
//*using namespace std;
//*
//*class SimpleTSP
//*{
//*public:
//*    SimpleTSP(const vector<pair<int, int>> &cities);
//*    float runTSP(int startAndEndTownIndex);
//*    void printBestPath() const;
//*    vector<int> getBestPath() const;
//*    float getBestPathCosts() const;
//*
//*private:
//*    vector<pair<int, int>> mCities;
//*    vector<vector<float>> mDistanceMatrix;
//*    vector<bool> mVisitedCities;
//*    vector<int> mCurrentPath;
//*    vector<int> mBestPath;
//*    float mBestPathCosts;
//*    int mStartAndEndTownIndex;
//*
//*    void buildDistanceMatrix();
//*    float TSP(int currentCity, int cityCounter, float currentTotalCost);
//*    void printDistanceMatrix() const;
//*};
//*
//*SimpleTSP::SimpleTSP(const vector<pair<int, int>> &cities) : mCities(cities), mVisitedCities(cities.size()), mCurrentPath(cities.size()), mBestPathCosts(numeric_limits<float>::max())
//*{
//*    buildDistanceMatrix();
//*    printDistanceMatrix();
//*}
//*
//*void SimpleTSP::buildDistanceMatrix()
//*{
//*    int size = mCities.size();
//*    mDistanceMatrix.resize(size, vector<float>(size, 0.0f));
//*    for (int outerIndex = 0; outerIndex < size; ++outerIndex)
//*    {
//*        for (int innerIndex = 0; innerIndex < size; ++innerIndex)
//*        {
//*            if (outerIndex != innerIndex)
//*            {
//*                float dist = sqrt(pow(mCities[innerIndex].first - mCities[outerIndex].first, 2) +
//*                                  pow(mCities[innerIndex].second - mCities[outerIndex].second, 2));
//*                mDistanceMatrix[outerIndex][innerIndex] = dist;
//*                mDistanceMatrix[innerIndex][outerIndex] = dist;
//*            }
//*        }
//*    }
//*}
//*
//*float SimpleTSP::runTSP(int startAndEndTownIndex)
//*{
//*    mStartAndEndTownIndex = startAndEndTownIndex;
//*    fill(mVisitedCities.begin(), mVisitedCities.end(), false);
//*    mVisitedCities[startAndEndTownIndex] = true;
//*    mCurrentPath[0] = startAndEndTownIndex;
//*    mBestPathCosts = numeric_limits<float>::max();
//*    TSP(startAndEndTownIndex, 1, 0.0f);
//*    return mBestPathCosts;
//*}
//*
//*float SimpleTSP::TSP(int currentCity, int cityCounter, float currentTotalCost)
//*{
//*    if (cityCounter >= mVisitedCities.size())
//*    {
//*        float distanceToStartTown = mDistanceMatrix[currentCity][mStartAndEndTownIndex];
//*        if (distanceToStartTown > 0)
//*        {
//*            return currentTotalCost + distanceToStartTown;
//*        }
//*    }
//*
//*    float localResult = numeric_limits<float>::max();
//*    for (int i = 0; i < mVisitedCities.size(); ++i)
//*    {
//*        if (!mVisitedCities[i] && currentCity != i)
//*        {
//*            mVisitedCities[i] = true;
//*            mCurrentPath[cityCounter] = i;
//*            localResult = TSP(i, cityCounter + 1, currentTotalCost + mDistanceMatrix[currentCity][i]);
//*            mVisitedCities[i] = false;
//*            if (localResult < mBestPathCosts)
//*            {
//*                mBestPathCosts = localResult;
//*                mBestPath = mCurrentPath;
//*            }
//*        }
//*    }
//*    return localResult;
//*}
//*
//*void SimpleTSP::printBestPath() const
//*{
//*    cout << "Best path: (" << mBestPathCosts << " costs): ";
//*    for (int i : mBestPath)
//*    {
//*        cout << i << " -> ";
//*    }
//*    cout << mStartAndEndTownIndex << endl;
//*}
//*
//*vector<int> SimpleTSP::getBestPath() const
//*{
//*    return mBestPath;
//*}
//*
//*float SimpleTSP::getBestPathCosts() const
//*{
//*    return mBestPathCosts;
//*}
//*
//*void SimpleTSP::printDistanceMatrix() const
//*{
//*    for (const auto &row : mDistanceMatrix)
//*    {
//*        for (float value : row)
//*        {
//*            cout << fixed << setprecision(2) << value << "\t";
//*        }
//*        cout << endl;
//*    }
//*}
//*
//*vector<pair<int, int>> buildCities(int cityCount)
//*{
//*    vector<pair<int, int>> cities;
//*    cities.emplace_back(4, 2);
//*    cities.emplace_back(1, 5);
//*    cities.emplace_back(5, 1);
//*    cities.emplace_back(0, 0);
//*    cities.emplace_back(3, 3);
//*    cities.emplace_back(2, 4);
//*    return cities;
//*}
//*
//*int main()
//*{
//*    int cityCount = 5;
//*    vector<pair<int, int>> cities = buildCities(cityCount);
//*    SimpleTSP tsp(cities);
//*
//*    for (int i = 0; i < cities.size(); ++i)
//*    {
//*        tsp.runTSP(i);
//*        tsp.printBestPath();
//*    }
//*
//*    return 0;
//*}

/*
#include "BF_Path.h"
using namespace std;

/*
//*procedure BellmanFord(G,a)
//* Initialization Step
//*forall vertices v
//*Label[v] := ∞
//*BFPrev[v] := -1
//*Label(a) := 0 // a is the source node
//*/
// Iteration Step
//*for i from 1 to size(vertices)-1
//*forall vertices v
//*if (Label[u] + Wt(u,v)) < Label[v]
//*then
//*Label[v] := Label[u] + Wt(u,v)
//*BFPrev[v] := u
//*// Check circuit of negative value
//*forall vertices v
//*if (Label[u] + Wt(u,v)) < Label(v)
//*error "Contains circuit of negative value"

/*
string BellmanFord(struct Graph *graph, int ver_sta, int ver_end)
{
    int V = graph->V;
    int E = graph->E;
    int BFValue[V];
    int BFPrev[V];

    for (int i = 0; i < V; i++)
    {
        BFValue[i] = INT_MAX;
        BFPrev[i] = -1;
    }
    BFValue[ver_sta] = 0;

    for (int i = 1; i <= V - 1; i++)
    {
        for (int j = 0; j < E; j++)
        {
            int u = graph->edge[j].from;
            int v = graph->edge[j].to;
            int val = graph->edge[j].value;
            if (BFValue[u] != INT_MAX && BFValue[u] + val < BFValue[v])
            {
                BFValue[v] = BFValue[u] + val;
                BFPrev[v] = u;
            }
        }
    }

    //* Trace? Can i put it in this?
    string s = "";
    while (ver_end != ver_sta)
    {
        if (BFPrev[ver_end] == -1)
            break;
        s += (char)ver_end + 65;
        s += " ";
        ver_end = BFPrev[ver_end];
    }
    s += (char)ver_sta + 65;
    s += "\0";
    for (int i = 0; i < s.length() / 2; i++)
    {
        swap(s[i], s[s.length() - i - 1]);
    }
    return s;
}

int EdgeCount(int G[][20], int G_size)
{
    int edgeCount = 0;
    for (int i = 0; i < G_size; i++)
    {
        for (int j = 0; j < G_size; j++)
        {
            if (G[i][j] != 0)
                edgeCount++;
        }
    }
    return edgeCount;
}

string BF_Path(int G[][20], int ver_num, char ver_sta, char ver_end)
{

    struct Graph *graph = CreateGraph(ver_num, EdgeCount(G, ver_num));
    int edge_th = 0;
    for (int i = 0; i < ver_num; i++)
    {
        for (int j = 0; j < ver_num; j++)
        {
            if (G[i][j] != 0)
            {
                graph->edge[edge_th].from = i;
                graph->edge[edge_th].to = j;
                graph->edge[edge_th].value = G[i][j];
                edge_th++;
            }
        }
    }

    return BellmanFord(graph, (int)ver_sta - 65, (int)ver_end - 65);
}
*/
/*
string BF_Path(int G[][20], int ver_num, char ver_sta, char ver_end)
{
    int index_ver_sta = ver_sta - 65, index_ver_end = ver_end - 65;

    int BFValue[ver_num];
    int BFPrev[ver_num];
    for (int i = 0; i < ver_num; i++)
    {
        BFValue[i] = -1;
        BFPrev[i] = -1;
    }
    int n = 8;
    char origi = ver_sta;
    bool step = true;

    for (int i = 0; i < n; i++)
    { // check step 0
        if (BFValue[i] != -1)
        {
            step = false;
            break;
        }
    }

    if (step == true)
    {                             // nếu là step 0 thì
        BFValue[origi - 'A'] = 0; // gán giá trị của đỉnh bắt đầu bằng 0
        for (int i = 0; i < n; i++)
        {
            if (i != origi - 'A')
                BFValue[i] = G[origi - 'A'][i]; // gán giá trị tới các đỉnh khác
            BFPrev[i] = origi - 'A';
        }
        BFPrev[origi - 'A'] = -1; // Previous vertex tải đỉnh bắt đầu là -1
    }
    else
    {                        // các step tiếp theo
        int BFValue_temp[n]; // tạo mảng Value temp để lưu giá trị
        for (int i = 0; i < n; i++)
        {
            BFValue_temp[i] = BFValue[i]; // gán giá trị của mảng temp bằng giá trị của mảng gốc
        }
        for (int i = 0; i < n; i++)
        {
            if (BFValue[i] != -1)
            {
                for (int j = 0; j < n; j++)
                {
                    if (G[i][j] != 0)
                    {
                        if (BFValue[j] == -1)
                        { // nếu giá trị của đỉnh = -1 thì auto gán giá trị mới
                            BFValue_temp[j] = BFValue[i] + G[i][j];
                            BFPrev[j] = i;
                        }
                        else if (BFValue[i] + G[i][j] < BFValue_temp[j])
                        {                                           // so sánh trọng số bằng Value gốc + weight trên đồ thị
                            BFValue_temp[j] = BFValue[i] + G[i][j]; // gán vào temp
                            BFPrev[j] = i;
                        }
                    }
                }
            }
        }
        for (int i = 0; i < n; i++)
        {
            BFValue[i] = BFValue_temp[i]; // update giá trị mảng gốc = temp
        }
    }
    for (int i = 0; i < ver_num; i++)
    {
        cout << BFPrev[i] << " ";
    }
    //* Trace
    string s = "";
    while (index_ver_end != index_ver_sta)
    {
        if (BFPrev[index_ver_end] == -1)
            break;
        s += (char)index_ver_end + 65;
        s += " ";
        index_ver_end = BFPrev[index_ver_end];
    }
    s += (char)index_ver_sta + 65;
    s += "\0";
    for (int i = 0; i < s.length() / 2; i++)
    {
        swap(s[i], s[s.length() - i - 1]);
    }
    return s;
}

int main()
{
    ifstream fin;
    int G[20][20];
    int BFValue[20];
    int BFBFPrev[20];
    fin.open("inMat1.txt");
    int n = 8;
    for (int i = 0; i < n; i++)
    {
        BFValue[i] = -1;
        BFBFPrev[i] = -1;
        for (int j = 0; j < n; j++)
        {
            fin >> G[i][j];
        }
    }
    cout << BF_Path(G, n, 'A', 'E');
    fin.close();
}
*/
//*  Code TSP

#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <climits>
#include <cstring>
#include <string>

using namespace std;

class TravelingSP
{
private:
    int Matrix[20][20];
    bool Visited[20];
    int Path[20];
    int TPS_Path[20];
    int MinPathCost;
    int Original;
    int Ver_num;

    int TSP(int Cur_Ver, int Visited_Ver_Num, int Cur_TotalCost)
    {
        if (Visited_Ver_Num >= Ver_num)
        {
            int distance = Matrix[Cur_Ver][Original];
            if (distance > 0)
            {
                return Cur_TotalCost + distance;
            }
        }

        int PathCost = INT_MAX;
        for (int i = 0; i < Ver_num; ++i)
        {
            if (!Visited[i] && Cur_Ver != i && Matrix[Cur_Ver][i] != 0)
            {
                Visited[i] = true;
                Path[Visited_Ver_Num] = i;
                int newCost = TSP(i, Visited_Ver_Num + 1, Cur_TotalCost + Matrix[Cur_Ver][i]);
                Visited[i] = false;
                if (newCost < MinPathCost)
                {
                    MinPathCost = newCost;
                    memcpy(TPS_Path, Path, sizeof(Path));
                }
            }
        }
        return PathCost;
    }

public:
    TravelingSP(int G[20][20], int n) : MinPathCost(INT_MAX), Ver_num(n)
    {
        memcpy(Matrix, G, sizeof(Matrix));
        memset(Visited, false, sizeof(Visited));
        memset(Path, 0, sizeof(Path));
        memset(TPS_Path, 0, sizeof(TPS_Path));
    }

    int runTSP(int original)
    {
        Original = original;
        memset(Visited, false, sizeof(Visited));
        Visited[original] = true;
        Path[0] = original;
        MinPathCost = INT_MAX;
        TSP(original, 1, 0);
        return MinPathCost;
    }

    string Trace() const
    {
        string s = "";
        for (int i = 0; i < Ver_num; ++i)
        {
            cout <<TPS_Path[i]<< " ";
            s += (char)TPS_Path[i] + 65;
            s += " ";
        }
        s += (char)Original + 65 + '\0';
        cout <<endl;
        return s;
    }
};

string Traveling(int G[20][20], int ver_num, char start)
{
    TravelingSP tsp(G, ver_num);
    tsp.runTSP((int)start - 65);
    return tsp.Trace();
}
int main(void)
{
    clock_t tStart = clock();
    system("cls");
    ifstream fin;
    int G[20][20];
    fin.open("TC_TSP4-5.txt");
    int n = 12;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fin >> G[i][j];
        }
    }
    for (int i=0;i<12;i++)
    {
        cout <<"================================================================"<<endl;
        cout << Traveling(G, n, (char) (65+ i))<<endl;
    }
    

    fin.close();
    cout << "\n Time of execution: " << (double)(clock() - tStart) / (CLOCKS_PER_SEC) << " seconds." << endl;
}
// ! Code Gốc 2.0 (Phù hợp cho test không phải bài nộp)
// !        #include <iostream>
// !        #include <iomanip>
// !        #include <cmath>
// !        #include <limits>
// !        #include <algorithm>
// !        #include <fstream>
// !        
// !        using namespace std;
// !        
// !        const int MAX_CITY_COUNT = 20;
// !        
// !        class SimpleTSP
// !        {
// !        public:
// !            SimpleTSP(const float distanceMatrix[MAX_CITY_COUNT][MAX_CITY_COUNT], int cityCount);
// !            float runTSP(int startAndEndTownIndex);
// !            void printBestPath() const;
// !            const int* getBestPath() const;
// !            float getBestPathCosts() const;
// !        
// !        private:
// !            int mCityCount;
// !            float mDistanceMatrix[MAX_CITY_COUNT][MAX_CITY_COUNT];
// !            bool mVisitedCities[MAX_CITY_COUNT];
// !            int mCurrentPath[MAX_CITY_COUNT];
// !            int mBestPath[MAX_CITY_COUNT];
// !            float mBestPathCosts;
// !            int mStartAndEndTownIndex;
// !        
// !            float TSP(int currentCity, int cityCounter, float currentTotalCost);
// !            void printDistanceMatrix() const;
// !        };
// !        
// !        SimpleTSP::SimpleTSP(const float distanceMatrix[MAX_CITY_COUNT][MAX_CITY_COUNT], int cityCount)
// !            : mCityCount(cityCount), mBestPathCosts(numeric_limits<float>::max())
// !        {
// !            for (int i = 0; i < mCityCount; ++i)
// !            {
// !                for (int j = 0; j < mCityCount; ++j)
// !                {
// !                    mDistanceMatrix[i][j] = distanceMatrix[i][j];
// !                }
// !            }
// !            printDistanceMatrix();
// !        }
// !        
// !        float SimpleTSP::runTSP(int startAndEndTownIndex)
// !        {
// !            mStartAndEndTownIndex = startAndEndTownIndex;
// !            fill(begin(mVisitedCities), begin(mVisitedCities) + mCityCount, false);
// !            mVisitedCities[startAndEndTownIndex] = true;
// !            mCurrentPath[0] = startAndEndTownIndex;
// !            mBestPathCosts = numeric_limits<float>::max();
// !            TSP(startAndEndTownIndex, 1, 0.0f);
// !            return mBestPathCosts;
// !        }
// !        
// !        float SimpleTSP::TSP(int currentCity, int cityCounter, float currentTotalCost)
// !        {
// !            if (cityCounter >= mCityCount)
// !            {
// !                float distanceToStartTown = mDistanceMatrix[currentCity][mStartAndEndTownIndex];
// !                if (distanceToStartTown > 0)
// !                {
// !                    return currentTotalCost + distanceToStartTown;
// !                }
// !            }
// !        
// !            float localResult = numeric_limits<float>::max();
// !            for (int i = 0; i < mCityCount; ++i)
// !            {
// !                if (!mVisitedCities[i] && currentCity != i && mDistanceMatrix[currentCity][i] != 0)
// !                {
// !                    mVisitedCities[i] = true;
// !                    mCurrentPath[cityCounter] = i;
// !                    float result = TSP(i, cityCounter + 1, currentTotalCost + mDistanceMatrix[currentCity][i]);
// !                    mVisitedCities[i] = false;
// !                    if (result < mBestPathCosts)
// !                    {
// !                        mBestPathCosts = result;
// !                        copy(begin(mCurrentPath), begin(mCurrentPath) + mCityCount, begin(mBestPath));
// !                    }
// !                }
// !            }
// !            return localResult;
// !        }
// !        
// !        void SimpleTSP::printBestPath() const
// !        {
// !            cout << "Best path: (" << mBestPathCosts << " costs): ";
// !            for (int i = 0; i < mCityCount; ++i)
// !            {
// !                cout << mBestPath[i] << " -> ";
// !            }
// !            cout << mStartAndEndTownIndex << endl;
// !        }
// !        
// !        const int* SimpleTSP::getBestPath() const
// !        {
// !            return mBestPath;
// !        }
// !        
// !        float SimpleTSP::getBestPathCosts() const
// !        {
// !            return mBestPathCosts;
// !        }
// !        
// !        void SimpleTSP::printDistanceMatrix() const
// !        {
// !            for (int i = 0; i < mCityCount; ++i)
// !            {
// !                for (int j = 0; j < mCityCount; ++j)
// !                {
// !                    cout << fixed << setprecision(2) << mDistanceMatrix[i][j] << "\t";
// !                }
// !                cout << endl;
// !            }
// !        }
// !        
// !        string Traveling(float distanceMatrix[][MAX_CITY_COUNT], int cityCount, char Original )
// !        {
// !        
// !            SimpleTSP tsp(distanceMatrix, cityCount);
// !        
// !            for (int i = 0; i < cityCount; ++i)
// !            {
// !                tsp.runTSP(i);
// !                tsp.printBestPath();
// !            }
// !            return 0;
// !        }
// !        
// !        int main()
// !        {
// !          clock_t tStart = clock();
// !            system("cls");
// !            ifstream fin;
// !            float G[20][20];
// !            fin.open("TC_TSP4-5.txt");
// !            int n = 12;
// !            for (int i = 0; i < n; i++)
// !            {
// !                for (int j = 0; j < n; j++)
// !                {
// !                    fin >> G[i][j];
// !                }
// !            }
// !            for (int i=0;i<12;i++)
// !            {
// !                cout <<"================================================================"<<endl;
// !                cout << Traveling(G, n, (char) (65+ i))<<endl;
// !            }
// !            
// !        
// !            fin.close();
// !            cout << "\n Time of execution: " << (double)(clock() - tStart) / (CLOCKS_PER_SEC) << " seconds." << endl;
// !            return 0;
// !        }
