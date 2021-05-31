#include <stdio.h>
#include <stdlib.h>
int m[7][7] = { 0 };
int s[7][7] = { 0 };
void Print_Optimal_Parens(int s[][7], int i, int j)  //�������Ž�
{
    if (i == j)
    {
        printf("A%d", i);
    }
    else
    {
        printf("(");
        Print_Optimal_Parens(s, i, s[i][j]);
        Print_Optimal_Parens(s, s[i][j] + 1, j);
        printf(")");
    }
}
void Matrix_Chain_Order(int p[], int n)
{
    int i, j, L, k, q;
    for (i = 1; i <= n; i++)      //�ȶԵ��������������⣬��ȫ��m[i][i] =0;
    {
        m[i][i] = 0;
    }
    for (L = 2; L <= n; L++)     //�������������_ʼ�������Ӿ������ĳ���
        for (i = 1; i <= n - L + 1; i++)  //�ڸ���p[]�еľ������У���ȫ���ֳ���ΪL���������
        {
            j = i + L - 1;
            m[i][j] = -1;
            for (k = i; k <= j - 1; k++)   //����ȫ�����ܵĻ��ֵ�k����������ŵĻ��ַ�����
            {
                q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j] || m[i][j] == -1)
                {
                    m[i][j] = q;     //���ŵĴ���q������m[i][j]��
                    s[i][j] = k;     //���ŵĻ���λ��k������s[i][j]��
                }
            }
        }

}
void main()
{
    int p[] = { 30,35,15,5,10,20,25 };    //���������
    int length = sizeof(p) / sizeof(p[0]) - 1;   //���󳤶�
    int i, j;
    Matrix_Chain_Order(p, length);

    for (i = 1; i <= 6; i++)
    {
        for (j = 1; j <= 6; j++)
        {
            printf("%8d", m[i][j]);
        }
        printf("\n");
    }

    Print_Optimal_Parens(s, 1, 6);
    printf("\n");
}