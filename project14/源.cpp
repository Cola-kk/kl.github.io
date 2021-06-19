#include<iostream>
using namespace std;
int min(int a, int b, int c) {
    return (a < b ? a : b) < c ? (a < b ? a : b) : c;
}
int editDistance_iter(char* strA, int size_A, char* strB, int size_B);//动态规划实现

int EDM(int** C, char* strA, int i, int A_end, char* strB, int j, int B_end);

int editDistance_mem(char* strA, int size_A, char* strB, int size_B);//递归算法实现
int main() {
    string strA, strB;
    cout << "please enter source string：";
    cin >> strA;
    cout << "please enter target string：";
    cin >> strB;
    cout<<editDistance_iter(const_cast<char*>(strA.c_str()), strA.size(), const_cast<char*>(strB.c_str()), strB.size())<<endl;
    cout << editDistance_mem(const_cast<char*>(strA.c_str()), strA.size(), const_cast<char*>(strB.c_str()), strB.size());
    return 0;
}


int editDistance_iter(char* strA, int size_A, char* strB, int size_B) {
    int** C = new int* [size_A + 1];
    for (int i = 0; i <= size_A; i++) {
        C[i] = new int[size_B + 1]();
    }
    for (int i = 0; i <= size_A; i++)
        C[i][0] = i; //对边界进行初始化，下同。
    for (int j = 0; j <= size_B; j++)
        C[0][j] = j;
    for (int i = 1; i <= size_A; i++) {
        for (int j = 1; j <= size_B; j++) {
            if (strA[i-1] == strB[j-1])//若此处字符相同，则不用编辑        
                C[i][j] = C[i - 1][j - 1];
            else//否则，在原有的最小操作数的基础上加上1
                C[i][j] = min(C[i - 1][j - 1], C[i - 1][j], C[i][j - 1]) + 1;
        }
    }
    int res= C[size_A][size_B]; 
        for (int i = 0; i <= size_A; i++) {
            for (int j = 0; j <= size_B; j++)
                cout << C[i][j] << " ";
            cout << "\n";
        }
        for (int i = 0; i <= size_A; i++) {
            delete[] C[i];
        }
        delete[] C;
        return res;
}
int EDM(int** C, char* strA, int i, int A_end, char* strB, int j, int B_end) {
        if (C[i][j] < INT_MAX)//做备忘  
            return C[i][j];
        if (i > A_end) {
            if (j > B_end)//i==size_A&&j=size_B
                C[i][j] = 0;
            else
                C[i][j] = B_end - j + 1;//i==size_A&&j!=size_B
        }
        else if (j > B_end) {
            if (i > A_end)//j==size_B&&i==size_A
                C[i][j] = 0;
            else
                C[i][j] = A_end - i + 1;// j == size_B && i != size_A
        }
        else if (strA[i] == strB[j])
            C[i][j] = EDM(C, strA, i + 1, A_end, strB, j + 1, B_end);
        else {
            int a = EDM(C, strA, i + 1, A_end, strB, j + 1, B_end);
            int b = EDM(C, strA, i, A_end, strB, j + 1, B_end);
            int c = EDM(C, strA, i + 1, A_end, strB, j, B_end);
            C[i][j] = min(a, b, c) + 1;
        }
        return C[i][j];
}

int editDistance_mem(char* strA, int size_A, char* strB, int size_B) {
        int** C = new int* [size_A + 1];
        for (int i = 0; i <= size_A; i++) {
            C[i] = new int[size_B + 1]();
        }   //初始化 
        for (int i = 0; i <= size_A; i++) {
            for (int j = 0; j <= size_B; j++)
                C[i][j] = INT_MAX;
        }
        int res = EDM(C, strA, 0, size_A - 1, strB, 0, size_B - 1);
        //free memory 
        for (int i = 0; i <= size_A; i++) {
            delete[] C[i];
        }
        delete[] C;
        return res;
    }