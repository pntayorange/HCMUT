#include <iostream>
#include <vector>
#include <unordered_map>
#include <limits>
#include <fstream>
#include <bits/stdc++.h>
#include <cstdio>
#include <cstdint>
#include <iomanip>
#define N 20
using namespace std;

void BF2(int G[][N], int n, char origi, int BFValue[], int BFPrev[])
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
                        if (sum != 0)
                            if (BFValue[j] == -1 || BFValue[i] + G[i][j] < BFValue_temp[j])
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
            if (BFValue_temp == 0 && i != origi - 'A')
                ;
            else
                BFValue[i] = BFValue_temp[i];
        }
    }
}
int step = 0;
string BF_Path(int G[][N], int n, char start, char end)
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
    if (step == 0)
    {
        for (int i = 0; i < n; i++)
        {
            cout << setw(3) << (char)(i + 'A') << " ";
        }
        cout << endl;
        for (int i = 0; i < n; i++)
        {
            cout << setw(3) << (char)(BFPrev[i] + 'A') << " ";
        }
        cout << endl;
    }
    step++;
    return path;
}
int main()
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
//* True: B A E D ### False: B F E D
//* Prev: 1 -1 7 4 0 7 0 1
//* True: C K G ### False: C K A G
/*
A
A F B
A C
A G O D
A G E
A F
A G
A R H
A L I
A G E N J
A C K
A L
A Q M
A G E N
A G O
A L P
A Q
A R
B L K A
B
B R C
B L I O D
B L I O E
B L K A F
B L K G
B R H
B L I
B J
B L K
B L
B Q M
B N
B L I O
B L P
B Q
B R
C K A
C B
C
C D
C O E
C K A F
C K G
C O H
C K I
C O N J
C K
C L
C L P M
C O N
C O
C L P
C L P Q
C K A R
D L K A
D B
D L I C
D
D L I O E
D F
D L K G
D L I O H
D L I
D L J
D L K
D L
D M
D L I O N
D L I O
D L P
D L P Q
D L R
E N J A
E N J B
E N J C
E D
E
E D F
E G
E N H
E D L I
E N J
E D L K
E D L
E D M
E N
E G O
E D L P
E D L P Q
E N J B R
F B L K A
F B
F O C
F O D
F O E
F
F O E G
F O H
F B L I
F O N J
F B L K
F B L
F B Q M
F O N
F O
F B L P
F B Q
F B R
G A
G E N J B
G O C
G O D
G E
G A F
G
G O H
G O D L I
G E N J
G O C K
G O D L
G O D M
G E N
G O
G O D L P
G O D L P Q
G A R
H G A
H F B
H M I C
H G O D
H G E
H F
H G
H
H M I
H G E N J
H M I C K
H G O D L
H M
H G E N
H G O
H G O D L P
H F B Q
H F B R
I C K A
I O N J B
I C
I O D
I O E
I C K A F
I C K G
I O H
I
I O N J
I C K
I C L
I O D M
I O N
I O
I C L P
I C L P Q
I C K A R
J A
J B
J C
J C D
J A G E
J A F
J A G
J B R H
J C K I
J
J C K
J B L
J B Q M
J C O N
J C O
J B L P
J B Q
J B R
K A
K A F B
K I C
K I O D
K G E
K A F
K G
K A R H
K I
K I O N J
K
K I C L
K A Q M
K I O N
K I O
K I C L P
K A Q
K A R
L K A
L J B
L I C
L I O D
L I O E
L K A F
L K G
L I O H
L I
L J
L K
L
L P M
L I O N
L I O
L P
L P Q
L R
M I C K A
M D B
M I C
M D
M I O E
M I C K A F
M I C K G
M H
M I
M I O N J
M I C K
M L
M
M I O N
M I O
M L P
M L P Q
M I C K A R
N J A
N J B
N J C
N E D
N E
N J A F
N E G
N H
N J C K I
N J
N J C K
N E D L
N M
N
N J C O
N E D L P
N J B Q
N J B R
O C K A
O N J B
O C
O D
O E
O D F
O E G
O H
O D L I
O N J
O C K
O D L
O D M
O N
O
O D L P
O D L P Q
O N J B R
P Q K A
P J B
P L I C
P Q O D
P N E
P F
P Q K G
P Q H
P L I
P J
P Q K
P L
P M
P N
P Q O
P
P Q
P L R
Q K A
Q J B
Q K I C
Q O D
Q O E
Q K A F
Q K G
Q H
Q K I
Q J
Q K
Q O D L
Q M
Q O N
Q O
Q O D L P
Q
Q K A R
R C K A
R C B
R C
R C D
R E
R C K A F
R C K G
R H
R C K I
R E N J
R C K
R C L
R M
R E N
R C O
R C L P
R C L P Q
R
*/