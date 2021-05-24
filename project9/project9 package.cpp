#include <iostream>
using namespace std;
int knapsack_complete(int* W, int* V, int* res, int n, int C)
{
    int value = 0;
    int** f = new int* [n];
    for (int i = 0; i < n; i++)
    {
        f[i] = new int[C + 1];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < C + 1; j++)
            f[i][j] = 0;
    }
    for (int y = 1; y < C + 1; y++)
    {
        f[0][y] = (y < W[0]) ? 0 : ((y / W[0]) * V[0]);
    }

    for (int i = 1; i < n; i++)
    {
        for (int y = 1; y < C + 1; y++)
        {
            if (y < W[i])
            {
                f[i][y] = f[i - 1][y];
            }
            else {
                f[i][y] = (f[i - 1][y] > (f[i][y - W[i]] + V[i])) ? f[i - 1][y] : (f[i][y - W[i]] + V[i]);
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < C + 1; j++)
            cout << f[i][j] << " ";
        cout << endl;
    }

    value = f[n - 1][C];
    int j = n - 1;
    int y = C;
    while (j)
    {
        if (f[j][y] == (f[j][y - W[j]] + V[j]))
        {
            res[j]++;
            y = y - W[j];
        }
        j--;
    }
    res[0] = f[0][y] / V[0];

    for (int i = 0; i < n; i++)
    {
        delete f[i];
        f[i] = 0;
    }
    delete[] f;
    f = 0;
    return value;
}
void test1()
{
    int n, C;
    while (cin >> n >> C)
    {
        int* W = new int[n];
        int* V = new int[n];
        int* res = new int[n];
        for (int i = 0; i < n; i++)
        {
            res[i] = 0;
        }
        int i = 0, w, v;
        while (i < n)
        {
            cin >> w >> v;
            W[i] = w;
            V[i] = v;
            i++;
        }
        int value = knapsack_complete(W, V, res, n, C);
        cout << value << endl;
        for (int i = 0; i < n; i++)
            cout << res[i] << " ";
        cout << endl;
        delete W; W = 0;
        delete V; V = 0;
        delete res; res = 0;
    }
}

int main()
{
    test1();
    return 0;
}
