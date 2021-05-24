#include<iostream>
#include <string>
#include <vector>
using namespace std;
int B[100][100];
string str;
string X = "ABCDE", Y = "BCD";
int findLCS(string X, int n, string Y, int m)
{
    if (n == 0 || m == 0)//��������
        return 0;
    int c[100][100];//����״̬����
    for (int i = 0; i <= n; i++)//��ʼ״̬
        c[i][0] = 0;
    for (int i = 0; i <= m; i++)
        c[0][i] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            if (X[i - 1] == Y[j - 1]) {//�ж�A�ĵ�i���ַ���B�ĵ�j���ַ��Ƿ���ͬ
                c[i][j] = c[i - 1][j - 1] + 1;
                B[i][j] = 2;
            }
            else {
                c[i][j] = max(c[i - 1][j], c[i][j - 1]);
                if (c[i - 1][j] >= c[i][j - 1]) {
                    B[i][j] = 0;
                }
                else {
                    B[i][j] = 1;
                }
            }
        }
        return c[n][m];
}
void putLCS(int i, int j) {
        if (i == 0 || j == 0)
            return;
        if (B[i][j] == 0) {
            putLCS(i - 1, j);
        }
        else if (B[i][j] == 1) {
            putLCS(i, j - 1);
        }
        else if (B[i][j] == 2) {
            str += X[j];
            putLCS(i - 1, j - 1);
        }
}
int main() {
    cout<<findLCS(X, 5, Y, 3)<<"\n";
    putLCS(5, 3);
   reverse(str.begin(), str.end());
   cout << str;

}