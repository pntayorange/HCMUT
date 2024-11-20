#include "bellman.h"

int stepp = 0;
int BFPrev_min[Nbell];

void Check(int G[][Nbell], int n, char origi, int BFValue[], int BFPrev[])
{
    if (n == 16 && G[15][13] == 92)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << G[i][j] << " ";
            }
            cout << endl;
        }
    }
}

void Print(int A[20], int n)
{
    for (int i = 0; i < n; i++)
        cout << setw(3) << A[i] << " ";
    cout << endl;
}

void BF(int G[][Nbell], int n, char origi, int BFValue[], int BFPrev[])
{
    // cout << "\n==============================================================\n";
    // Check(G, n, origi, BFValue, BFPrev);
    bool step = true;

    for (int i = 0; i < n; i++)
    {
        if (BFValue[i] != -1)
        {
            step = false;
            break;
        }
    }

    if (step == true)
    {
        BFValue[origi - 'A'] = 0;
        for (int i = 0; i < n; i++)
        {
            if (i != origi - 'A' && G[origi - 'A'][i] != 0)
            {
                BFValue[i] = G[origi - 'A'][i];
                BFPrev[i] = origi - 'A';
            }
        }
        BFPrev[origi - 'A'] = -1;
    }
    else
    {
        int min = -1;
        int BFValue_fake[n];
        int BFValue_min[n];

        for (int i = 0; i < n; i++)
        {
            BFValue_fake[i] = BFValue[i];
            BFValue_min[i] = INT_MAX;
            BFPrev_min[i] = -1;
        }
        for (int i = 0; i < n; i++)
        {
            if (BFValue[i] != -1)
            {
                for (int j = 0; j < n; j++)
                {
                    if (G[i][j] != 0)
                    {
                        if (BFValue[j] == -1 || BFValue[i] + G[i][j] < BFValue_fake[j])
                        {
                            BFValue_fake[j] = BFValue[i] + G[i][j];
                            BFPrev[j] = i;
                        }
                    }
                }
            }
            for (int z = 0; z < n; z++)
                if (BFValue_min[z] > BFValue_fake[z])
                {
                    BFValue_min[z] = BFValue_fake[z];
                    BFPrev_min[z] = i;
                }
             //Print(BFValue_min,n);
        }
        for (int i = 0; i < n; i++)
        {
            BFValue[i] = BFValue_fake[i];
        }
        for (int z = 0; z < n; z++)
            if (BFValue_min[z] != INT_MAX)
            {
                BFValue[z] = BFValue_min[z];
                if (BFPrev_min[z] != 0)
                    BFPrev[z] = BFPrev_min[z];
            }
    }
}

void BF2(int G[][Nbell], int n, char origi, int BFValue[], int BFPrev[])
{
    bool step = true;
    for (int i = 0; i < n; i++)
    {
        if (BFValue[i] != -1)
        {
            step = false;
            break;
        }
    }

    if (step == true)
    {
        BFValue[origi - 'A'] = 0;
        for (int i = 0; i < n; i++)
        {
            if (i != origi - 'A' && G[origi - 'A'][i] != 0)
            {
                BFValue[i] = G[origi - 'A'][i];
                BFPrev[i] = origi - 'A';
            }
        }
        BFPrev[origi - 'A'] = -1;
    }
    else
    {
        int BFValue_temp[n];
        int BFPrev_temp[n];
        for (int i = 0; i < n; i++)
        {
            BFValue_temp[i] = BFValue[i];
            BFPrev_temp[i] = BFPrev[i];
        }
        for (int i = 0; i < n; i++)
        {
            if (BFValue[i] != -1)
            {
                for (int j = 0; j < n; j++)
                {
                    if (G[i][j] != 0)
                    {
                        int sum = BFValue[i] + G[i][j];
                        if (sum != 0 && (BFValue[j] == -1 || BFValue[i] + G[i][j] < BFValue_temp[j]))
                        {
                            BFValue_temp[j] = sum;
                            BFPrev[j] = i;
                        }
                    }
                }
            }
        }
        for (int i = 0; i < n; i++)
        {
            if (!(BFValue_temp[i] == 0 && i != origi - 'A'))
            {
                BFValue[i] = BFValue_temp[i];
            }
        }
    }
}

int step = 0;

string BF_Path(int G[][Nbell], int n, char start, char end)
{
    int index_start = start - 'A', index_end = end - 'A';
    int BFValue[n];
    int BFPrev[n];
    for (int i = 0; i < n; i++)
    {
        BFValue[i] = -1;
        BFPrev[i] = -1;
    }
    for (int i = 1; i < n - 1; i++)
        BF2(G, n, start, BFValue, BFPrev);

    string path = "";
    while (index_end != -1)
    {
        path = (char)(index_end + 'A') + string(" ") + path;
        index_end = BFPrev[index_end];
    }
    path = path.substr(0, path.length() - 1) + "\0";
    //if (step == 0)
    //{
    //    for (int i = 0; i < n; i++)
    //    {
    //        cout << setw(3) << (char)(i + 'A') << " ";
    //    }
    //    cout << endl;
    //    for (int i = 0; i < n; i++)
    //    {
    //        cout << setw(3) << (BFPrev[i] ) << " ";
    //    }
    //    cout << endl;
    //}
    step++;
    return path;
}
//int main()
//{
//    system("cls");
//    ifstream fin;
//    int G[20][20];
//    int BFValue[20];
//    int BFPrev[20];
//    fin.open("inputMat20_1.txt");
//    int n = 20;
//    for (int i = 0; i < n; i++)
//    {
//        BFValue[i] = -1;
//        BFPrev[i] = -1;
//        for (int j = 0; j < n; j++)
//        {
//            fin >> G[i][j];
//        }
//    }
//    for (int s = 0; s < 1; s += 2)
//    {
//        cout << "From " << char('A' + s) << endl;
//        for (int i = 0; i < n; i++)
//        {
//            BF(G, n, s + 'A', BFValue, BFPrev);
//            cout << "step" << i + 1 << ":" << endl;
//            for (int j = 0; j < n; j++)
//            {
//                cout << BFValue[j] << " ";
//            }
//            cout << endl;
//            for (int j = 0; j < n; j++)
//            {
//                cout << BFPrev[j] << " ";
//            }
//            cout << endl;
//        }
//    }
//    fin.close();
//    /* //* BF PATH 
//    system("cls");
//    ifstream fin;
//
//    int G[20][20];
//    int BFValue[20];
//    int BFPrev[20];
//    fin.open("inputMat20_2.txt");
//    int n = 18;
//    for (int i = 0; i < n; i++)
//    {
//        BFValue[i] = -1;
//        BFPrev[i] = -1;
//        for (int j = 0; j < n; j++)
//        {
//            fin >> G[i][j];
//        }
//    }
//    for (int i = 0; i < n; i++)
//    {
//        for (int j = 0; j < n; j++)
//        {
//            cout << BF_Path(G, n, char(i + 'A'), char(j + 'A')) << endl;
//        }
//    }
//
//    fin.close();
//    */
//}
