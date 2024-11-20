#ifndef BELLMAN_H
#define BELLMAN_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <limits>
#include <fstream>
#include <iomanip>
const int Nbell = 20;

using namespace std;

void Check(int G[][Nbell], int n, char origi, int BFValue[], int BFPrev[]);
void Print(int A[20], int n);
void BF(int G[][Nbell], int n, char origi, int BFValue[], int BFPrev[]);
void BF2(int G[][Nbell], int n, char origi, int BFValue[], int BFPrev[]);
string BF_Path(int G[][Nbell], int n, char start, char end);

extern int stepp;
extern int BFPrev_min[Nbell];

#endif 
