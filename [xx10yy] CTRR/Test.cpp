// BELLMAN-FORD ALGORITHM
#include <bits/stdc++.h>
using namespace std;
#define N 20
void BF(int graph[][N], int n, char start, int BFValue[], int BFPrev[])
{
    int start_vertex = start - 'A';
    bool step0 = true;

    for (int i = 0; i < n; i++)
    { // check step 0
        if (BFValue[i] != -1)
        {
            step0 = false;
            break;
        }
    }
    if (step0 == true)
    {                              // nếu là step 0 thì
        BFValue[start_vertex] = 0; // gán giá trị của đỉnh bắt đầu bằng 0
        for (int i = 0; i < n; i++)
        {
            if (i != start_vertex)
                BFValue[i] = graph[start_vertex][i]; // gán giá trị tới các đỉnh khác
            BFPrev[i] = start_vertex;
        }
        BFPrev[start_vertex] = -1; // Previous vertex tải đỉnh bắt đầu là -1
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
                    if (graph[i][j] != 0)
                    {
                        if (BFValue[j] == -1)
                        { // nếu giá trị của đỉnh = -1 thì auto gán giá trị mới
                            BFValue_temp[j] = BFValue[i] + graph[i][j];
                            BFPrev[j] = i;
                        }
                        else if (BFValue[i] + graph[i][j] < BFValue_temp[j])
                        {                                               // so sánh trọng số bằng Value gốc + weight trên đồ thị
                            BFValue_temp[j] = BFValue[i] + graph[i][j]; // gán vào temp
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
}
/*
string BF_Path(int graph[][20], int n, char start, char end)
{
    int BFValue[20];
    int BFPrev[20];
    int start_vertex = start - 'A';
    int end_vertex = end - 'A';
    string path = "";
    path += end;
    for (int i = 0; i < n; i++)
    {
        BFValue[i] = -1;
        BFPrev[i] = -1;
    }

    BFValue[start_vertex] = 0;
    for (int i = 0; i < n; i++)
    {
        if (i != start_vertex)
            BFValue[i] = graph[start_vertex][i];
        BFPrev[i] = start_vertex;
    }
    BFPrev[start_vertex] = -1;

    for (int k = 1; k < n; k++)
    {
        int BFValue_temp[n];
        for (int i = 0; i < n; i++)
        {
            BFValue_temp[i] = BFValue[i];
        }
        for (int i = 0; i < n; i++)
        {
            if (BFValue[i] != -1)
            {
                for (int j = 0; j < n; j++)
                {
                    if (graph[i][j] != 0)
                    {
                        if (BFValue[j] == -1)
                        {
                            BFValue_temp[j] = BFValue[i] + graph[i][j];
                            BFPrev[j] = i;
                        }
                        else if (BFValue[i] + graph[i][j] < BFValue_temp[j])
                        {
                            BFValue_temp[j] = BFValue[i] + graph[i][j];
                            BFPrev[j] = i;
                        }
                    }
                }
            }
        }
        for (int i = 0; i < n; i++)
        {
            BFValue[i] = BFValue_temp[i];
        }
    }

    if (start == end)
        return path;
    else
    {
        int temp = BFPrev[end_vertex];
        while (temp != start_vertex)
        {
            path = path + ' ' + (char)(temp + 'A');
            temp = BFPrev[temp];
        }

        path = path + ' ' + start;
        reverse(path.begin(), path.end());
        return path;
    }
}

string Traveling_saleman(int graph[][20], int n, char vertex)
{
    int BFValue[20];
    int BFPrev[20];
    int start_vertex = vertex - 'A';
    string path = "";
    path += vertex;
    for (int i = 0; i < n; i++)
    {
        BFValue[i] = -1;
        BFPrev[i] = -1;
    }

    BFValue[start_vertex] = 0;
    for (int i = 0; i < n; i++)
    {
        if (i != start_vertex)
            BFValue[i] = graph[start_vertex][i];
        BFPrev[i] = start_vertex;
    }
    BFPrev[start_vertex] = -1;

    for (int k = 1; k < n; k++)
    {
        int BFValue_temp[n];
        for (int i = 0; i < n; i++)
        {
            BFValue_temp[i] = BFValue[i];
        }
        for (int i = 0; i < n; i++)
        {
            if (BFValue[i] != -1)
            {
                for (int j = 0; j < n; j++)
                {
                    if (graph[i][j] != 0)
                    {
                        if (BFValue[j] == -1)
                        {
                            BFValue_temp[j] = BFValue[i] + graph[i][j];
                            BFPrev[j] = i;
                        }
                        else if (BFValue[i] + graph[i][j] < BFValue_temp[j])
                        {
                            BFValue_temp[j] = BFValue[i] + graph[i][j];
                            BFPrev[j] = i;
                        }
                    }
                }
            }
        }
        for (int i = 0; i < n; i++)
        {
            BFValue[i] = BFValue_temp[i];
        }
    }

    int min = 9999;
    int min_vertex = -1;
    for (int i = 0; i < n; i++)
    {
        if (BFValue[i] != -1 && i != start_vertex)
        {
            if (BFValue[i] < min)
            {
                min = BFValue[i];
                min_vertex = i;
            }
        }
    }
    path = path + ' ' + (char)(min_vertex + 'A');
    return path;
}
/*
    INPUT:
    0 1  2  3  4  5  6  7
    ----------------------
0.  0 72 89 77 2 58 13 69
1.  77 0 69 31 57 93 83 48
2.  52 21 0 62 8 77 32 14
3.  33 1 40 0 72 99 72 59
4.  89 24 1 61 0 12 78 63
5.  36 91 98 79 26 0 28 1
6.  18 77 49 36 98 77 0 45
7.  75 9 59 7 77 65 45 0

    BF() OUTPUT SAMPLE:
    step0:
    33 1 40 0 72 99 72 59
    3 3 3 -1 3 3 3 3
    step1:
    33 1 40 0 35 84 46 49
    3 3 3 -1 0 4 0 1
    step2:
    33 1 36 0 35 47 46 49
    3 3 4 -1 0 4 0 1
    step3:
    33 1 36 0 35 47 46 48
    3 3 4 -1 0 4 0 5
    step4:
    33 1 36 0 35 47 46 48
    3 3 4 -1 0 4 0 5
    step5:
    33 1 36 0 35 47 46 48
    3 3 4 -1 0 4 0 5
    step6:
    33 1 36 0 35 47 46 48
    3 3 4 -1 0 4 0 5
    step7:
    33 1 36 0 35 47 46 48
    3 3 4 -1 0 4 0 5
*/

/*
    BF_Path() OUTPUT SAMPLE: A E

   Graph:
    0 35 36 71 4 64 19 33
    17 0 59 83 22 31 51 37
    19 30 0 24 28 95 63 46
    30 40 75 0 74 63 33 3
    6 47 91 7 0 49 28 78
    80 13 11 63 72 0 60 86
    69 77 89 89 74 12 0 16
    68 75 62 64 82 2 37 0

    BF_Path() OUTPUT SAMPLE: A B G C H D
                             0 1 6 2 7 3

    Graph:
    0 12 99 75 84 77 37 65
    36 0 40 90 71 38 9 75
    46 72 0 38 17 46 75 8
    8 57 27 0 61 88 71 7
    54 60 76 66 0 24 50 15
    68 54 47 70 94 0 36 40
    32 11 14 44 84 18 0 61
    96 59 35 4 15 63 31 0
*/

/*
    Traveling saleman:

    0 17 40 100 32 11 29 77 73 53 52 72
    48 0 23 42 81 5 12 37 31 55 18 66
    48 97 0 74 21 43 8 37 48 13 55 88
    79 53 66 0 8 97 38 61 48 76 75 71
    18 56 42 97 0 59 40 51 77 5 65 39
    45 86 82 20 23 0 96 100 44 84 45 97
    15 53 93 53 80 7 0 29 21 78 13 43
    87 9 1 26 26 44 98 0 92 49 9 77
    30 29 66 93 28 9 76 73 0 73 91 92
    31 9 38 38 38 25 83 17 68 0 69 93
    35 61 19 45 24 10 94 33 53 90 0 62
    19 82 57 95 57 96 67 13 54 65 90 0
*/
int main()
{
    system("cls");
    char start = 'D';

    ifstream fin;
    int Graph[N][N];
    fin.open("inMat2.txt");
    int n = 8;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fin >> Graph[i][j];
        }
    }
    fin.close();

    int BFValue[20] = {-1, -1, -1, -1, -1, -1, -1, -1};
    int BFPrev[20] = {-1, -1, -1, -1, -1, -1, -1, -1};

    for (int i = 0; i < n; i++)
    {
        BF(Graph, n, start, BFValue, BFPrev);
        cout << "Step " << i +1<< ": " << endl;
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

    /*
        int graph[][20] = {
            {0, 12, 99, 75, 84, 77, 37, 65},
            {36, 0, 40, 90, 71, 38, 9, 75},
            {46, 72, 0, 38, 17, 46, 75, 8},
            {8, 57, 27, 0, 61, 88, 71, 7},
            {54, 60, 76, 66, 0, 24, 50, 15},
            {68, 54, 47, 70, 94, 0, 36, 40},
            {32, 11, 14, 44, 84, 18, 0, 61},
            {96, 59, 35, 4, 15, 63, 31, 0}
        };

        char start = 'A';
        char end = 'D';
        int n = 8;

        cout<<BF_Path(graph, n, start, end) << endl;


    */

    // int graph[][20] = {
    //     {0, 17, 40, 100, 32, 11, 29, 77, 73, 53, 52, 72},
    //     {48, 0, 23, 42, 81, 5, 12, 37, 31, 55, 18, 66},
    //     {48, 97, 0, 74, 21, 43, 8, 37, 48, 13, 55, 88},
    //     {79, 53, 66, 0, 8, 97, 38, 61, 48, 76, 75, 71},
    //     {18, 56, 42, 97, 0, 59, 40, 51, 77, 5, 65, 39},
    //     {45, 86, 82, 20, 23, 0, 96, 100, 44, 84, 45, 97},
    //     {15, 53, 93, 53, 80, 7, 0, 29, 21, 78, 13, 43},
    //     {87, 9, 1, 26, 26, 44, 98, 0, 92, 49, 9, 77},
    //     {30, 29, 66, 93, 28, 9, 76, 73, 0, 73, 91, 92},
    //     {31, 9, 38, 38, 38, 25, 83, 17, 68, 0, 69, 93},
    //     {35, 61, 19, 45, 24, 10, 94, 33, 53, 90, 0, 62},
    //     {19, 82, 57, 95, 57, 96, 67, 13, 54, 65, 90, 0}
    // };
    //
    // char vertex = 'A';
    // int n = 12;
    ////  cout << Traveling_saleman(graph, n, vertex) << endl;
    // cout << "Hello" << endl;

    return 0;
}