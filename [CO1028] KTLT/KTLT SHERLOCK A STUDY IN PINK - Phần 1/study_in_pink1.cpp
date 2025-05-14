#include "study_in_pink1.h"

bool readFile(
    const string &filename,
    int &HP1,
    int &HP2,
    int &EXP1,
    int &EXP2,
    int &M1,
    int &M2,
    int &E1,
    int &E2,
    int &E3)
{
    // This function is used to read the input file,
    // DO NOT MODIFY THIS FUNTION
    ifstream ifs(filename);
    if (ifs.is_open())
    {
        ifs >> HP1 >> HP2 >> EXP1 >> EXP2 >> M1 >> M2 >> E1 >> E2 >> E3;
        return true;
    }
    else
    {
        cerr << "The file is not found" << endl;
        return false;
    }
}

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////
int cliHP(int abc)
{
    if (abc > 666)
        return 666;
    if (abc < 0)
        return 0;
    return abc;
}
int cliEXP(int abc)
{
    if (abc > 600)
    {
        abc = 0;
        return 600;
    }
    if (abc < 0)
    {
        abc = 0;
        return 0;
    }
    return abc;
}

int cliM(int abc)
{
    if (abc > 3000)
    {
        abc = 3000;
        return 3000;
    }
    if (abc < 0)
    {
        abc = 0;
        return 0;
    }
    return abc;
}
int upto(float abc)
{
    if (abc - (static_cast<int>(abc)) > 0)
        return abc + 1;
    return abc;
}
// Task 1
int firstMeet(int &exp1, int &exp2, int e1)
{
    // TODO: Complete this function
    if ((e1 < 0) || (e1 > 99))
        return -99;
    exp1 = cliEXP(exp1);
    exp2 = cliEXP(exp2);
    //
    if (e1 <= 3)
    {
        if (e1 == 0)
            exp2 = cliEXP(exp2 + 29);
        if (e1 == 1)
            exp2 = cliEXP(exp2 + 45);
        if (e1 == 2)
            exp2 = cliEXP(exp2 + 75);
        if (e1 == 3)
            exp2 = cliEXP(exp2 + 29 + 45 + 75);
        int D = e1 * 3 + exp1 * 7;
        if ((D % 2 == 0))
        {
            exp1 = cliEXP(exp1 + upto(D / 200.0));
        }
        else
            exp1 = cliEXP(upto(exp1 - D / 100.0));
    }
    else
    {
        if (e1 >= 4 && e1 <= 19)
            exp2 = cliEXP(exp2 + upto(e1 / 4.0) + 19);
        if (e1 >= 20 && e1 <= 49)
            exp2 = cliEXP(exp2 + upto(e1 / 9.0) + 21);
        if (e1 >= 50 && e1 <= 65)
            exp2 = cliEXP(exp2 + upto(e1 / 16.0) + 17);
        if (e1 >= 66 && e1 <= 79)
        {
            exp2 = cliEXP(exp2 + upto(e1 / 4.0) + 19);
            if (exp2 > 200)
                exp2 = cliEXP(exp2 + upto(e1 / 9.0) + 21);
        }
        if (e1 >= 80 && e1 <= 99)
        {
            exp2 = cliEXP(exp2 + upto(e1 / 4.0) + 19 + upto(e1 / 9.0) + 21);
            if (exp2 > 400)
            {
                exp2 = cliEXP(exp2 + upto(e1 / 16.0) + 17);
                exp2 = cliEXP(upto(exp2 * 1.15));
            }
        }
        exp1 = cliEXP(exp1 - e1);
    }
    return exp1 + exp2;
}

// Task 2
int traceLuggage(int &HP1, int &EXP1, int &M1, int E2)
{
    // TODO: Complete this function
    if ((E2 < 0) || (E2 > 99))
        return -99;
    HP1 = cliHP(HP1);
    EXP1 = cliEXP(EXP1);
    M1 = cliM(M1);

    // Case 4.2.1
    int S = pow(round(sqrt(EXP1)), 2);
    float P1, P2, P3;
    if (EXP1 >= S)
        P1 = 100;
    else
        P1 = ((float)EXP1 / S + 80.0) / 123.0 * 100.0;
    // Case 4.2.2
    int M_Sp = 0, M_St = M1; // Money Spend // Money Start
    while ((E2 % 2 == 1) && M1 != 0)
    {
        // food
        if (HP1 < 200)
        {
            HP1 = cliHP(upto(HP1 * 1.3));
            M1 = cliM(M1 - 150);
            M_Sp = M_Sp + 150;
        }
        else
        {
            HP1 = cliHP(upto(HP1 * 1.1));
            M1 = cliM(M1 - 70);
            M_Sp = M_Sp + 70;
        }
        if (M_Sp > M_St / 2.0 || M1 == 0)
            break;
        // animal
        if (EXP1 < 400)
        {
            M1 = cliM(M1 - 200);
            M_Sp = M_Sp + 200;
        }
        else
        {
            M1 = cliM(M1 - 120);
            M_Sp = M_Sp + 120;
        }
        EXP1 = cliEXP(upto(EXP1 * 1.13));
        if (M_Sp > M_St / 2.0 || M1 == 0)
            break;
        // homeless
        if (EXP1 < 300)
        {
            M1 = cliM(M1 - 100);
            M_Sp = M_Sp + 100;
        }
        else
        {
            M1 = cliM(M1 - 120);
            M_Sp = M_Sp + 120;
        }

        EXP1 = cliEXP(upto(EXP1 * 0.9));
        if (M_Sp > M_St / 2.0 || M1 == 0)
            break;
        //
    }
    int count = 0;
    while ((E2 % 2 == 0) && count == 0)
    {
        if ((E2 % 2 == 0) && M1 != 0)
        {
            // food
            if (HP1 < 200)
            {
                HP1 = cliHP(upto(HP1 * 1.3));
                M1 = cliM(M1 - 150);
                M_Sp = M_Sp + 150;
            }
            else
            {
                HP1 = cliHP(upto(HP1 * 1.1));
                M1 = cliM(M1 - 70);
                M_Sp = M_Sp + 70;
            }
            if (M1 == 0)
                break;

            // animal
            if (EXP1 < 400)
            {
                M1 = cliM(M1 - 200);
                M_Sp = M_Sp + 200;
            }
            else
            {
                M1 = cliM(M1 - 120);
                M_Sp = M_Sp + 120;
            }
            EXP1 = cliEXP(upto(EXP1 * 1.13));
            if (M1 == 0)
                break;

            // homeless
            if (EXP1 < 300)
            {
                M1 = cliM(M1 - 100);
                M_Sp = M_Sp + 100;
            }
            else
            {
                M1 = cliM(M1 - 120);
                M_Sp = M_Sp + 120;
            }

            EXP1 = cliEXP(upto(EXP1 * 0.9));
            if (M1 == 0)
                break;

            //
        }
        count = 1;
    }

    HP1 = cliHP(upto(HP1 * 0.83));
    EXP1 = cliEXP(upto(EXP1 * 1.17));

    S = pow(round(sqrt(EXP1)), 2);
    if (EXP1 >= S)
        P2 = 100.0;
    else
        P2 = ((float)EXP1 / S + 80) / 123.0 * 100.0;

    // Case 4.2.3
    int P[10] = {32, 47, 28, 79, 100, 50, 22, 83, 64, 11};
    if (E2 / 10 == 0)
        P3 = P[E2];
    else
        P3 = P[(E2 / 10 + E2 % 10) % 10];

    // Conlusion of three path
    if (P1 == 100 && P2 == 100 && P3 == 100)
        EXP1 = cliEXP(upto(EXP1 * 0.75));
    else if ((P1 + P2 + P3) / 3.0 < 50)
    {
        HP1 = cliHP(upto(HP1 * 0.85));
        EXP1 = cliEXP(upto(EXP1 * 1.15));
    }
    else
    {
        HP1 = cliHP(upto(HP1 * 0.9));
        EXP1 = cliEXP(upto(EXP1 * 1.2));
    }
    return HP1 + EXP1 + M1;
}

// Task 3
int chaseTaxi(int &HP1, int &EXP1, int &HP2, int &EXP2, int E3)
{
    // TODO: Complete this function
    if ((E3 < 0 || E3 > 99))
        return -99;
    int A[10][10], L[19], R[19], neg = 0, pos = 0;
    for (int i = 0; i < 19; i++)
    {
        L[i] = -8200;
        R[i] = -8200;
    }
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
        {
            A[i][j] = 0;
            A[i][j] = ((E3 * j) + (i * 2)) * (i - j);
            R[i + j] = (A[i][j] > R[i + j]) ? A[i][j] : R[i + j];
            L[i - j + 9] = (A[i][j] > L[i - j + 9]) ? A[i][j] : L[i - j + 9];
            if (A[i][j] > E3 * 2)
                pos++;
            if (A[i][j] < -E3)
                neg++;
        };
    pos = ((pos / 10 + pos % 10) % 10 + (pos / 10 + pos % 10) / 10) % 10;
    neg = ((neg / 10 + neg % 10) % 10 + (neg / 10 + neg % 10) / 10) % 10;
    int maxx = 0;
    maxx = (R[pos + neg] > L[pos - neg + 9]) ? R[pos + neg] : L[pos - neg + 9];
    if (sqrt(pow(A[pos][neg], 2)) > maxx)
    {
        HP1 = cliHP(upto(HP1 * 0.9));
        HP2 = cliHP(upto(HP2 * 0.9));
        EXP1 = cliEXP(upto(EXP1 * 0.88));
        EXP2 = cliEXP(upto(EXP2 * 0.88));
        maxx = A[pos][neg];
    }
    else
    {
        HP1 = cliHP(upto(HP1 * 1.1));
        HP2 = cliHP(upto(HP2 * 1.1));
        EXP1 = cliEXP(upto(EXP1 * 1.12));
        EXP2 = cliEXP(upto(EXP2 * 1.12));
    }
    return maxx;
}

// Task 4
int checkPassword(const char *s, const char *email)
{
    // TODO: Complete this function
    int se_len = 0;
    int s_len = strlen(s);
    for (int i = 0; i < strlen(email); i++)
    {
        if (email[i] == '@')
        {
            break;
        }
        se_len++;
    }
    //
    if (s_len < 8)
        return -1;
    //
    if (s_len > 20)
        return -2;
    //
    if (s_len >= se_len)
    {
        if (se_len == 0)
            return -300;
        for (int i = 0; i <= s_len - se_len; i++)
        {

            if (s[i] == email[0])
            {
                int count = 0;
                for (int j = 0; j < se_len; j++)
                    if (s[i + j] == email[0 + j])
                        count++;
                if (count == se_len)
                    return -(300 + i);
            }
        }
    }
    //
    for (int i = 0; i < s_len - 2; i++)
        if (s[i] == s[i + 1] && s[i] == s[i + 2])
            return -(400 + i);
    // – Nếu s không chứa ký tự đặc biệt thì trả về -5.

    bool tf = false;
    for (int i = 0; i < s_len; i++)
    {
        if (s[i] == '@' || s[i] == '#' || s[i] == '%' || s[i] == '$' || s[i] == '!')
        {
            tf = true;
            break;
        }
    }
    if (!tf)
        return -5;

    //  Tại đây có ghép thêm trường hợp tìm ký tự không hợp lý (khác ký tự đặc biệt)
    for (int i = 0; i < s_len; i++)
    {
        int a = (int)(s[i]);
        if ((a == 33) || (a >= 35 && a <= 37) || (a >= 48 && a <= 57) || (a >= 64 && a <= 90) || (a >= 97 && a <= 122))
            continue;
        return i;
    }
    return -10;
}

// Task 5
int findCorrectPassword(const char *arr_pwds[], int num_pwds)
{
    // TODO: Complete this function
    int C[num_pwds], B[num_pwds];
    for (int i = 0; i < num_pwds; i++)
    {
        C[i] = strlen(arr_pwds[i]);
        B[i] = 0;
    }
    for (int i = 0; i < num_pwds; i++)
    {
        for (int j = i + 1; j < num_pwds; j++)
        {
            if (strlen(arr_pwds[i]) == strlen(arr_pwds[j]))
            {
                int count = 0;
                for (int z = 0; z < strlen(arr_pwds[i]); z++)
                {
                    if (arr_pwds[i][z] == arr_pwds[j][z])
                        count++;
                }
                if (count == strlen(arr_pwds[i]))
                {
                    B[i]++;
                }
            }
        }
    }
    int maxb = 0, maxc = 0, count = 0, maxi = 0;
    for (int i = 0; i < num_pwds; i++)
    {
        if (maxb == B[i])
            count++;
        if (maxb < B[i])
        {
            maxb = B[i];
            maxc = C[i];
            maxi = i;
            count = 0;
        }
    }
    if (count == 0)
        return maxi;
    else
        for (int i = 0; i < num_pwds; i++)
        {
            if (B[i] == maxb && maxc < C[i])
            {
                maxc = C[i];
                maxi = i;
            }
        }
    return maxi;
}

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////