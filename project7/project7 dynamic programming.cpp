#include<iostream>
#include<vector>

using namespace std;

int main() {

	int m, n;//m元钱，n项投资
	int k, x;//循环辅助变量
	int xk, temp= 0;//xk代表给第k个项目投入的钱数  0<=tmp<=j;temp代表一次循环中的钱数
	cout << "please enter total money and the number of project:";
	cin >> m >> n;
	vector<vector<int>> f(n, vector<int>(m + 1));//f[i][x], 0<i<=n,0<=x<=m,第i个项目投入x元钱，其值为收益，这是需要自己输入的；
	vector<vector<int>> F(n, vector<int>(m + 1));//F[i][x]，将x元钱投入到前i个项目上最大的收益
	//给f[i][x]赋值
	for (k = 0; k < n; ++k) {
		f[k][0] = 0;//在第(i+1)个项目上投入0元，收益为0，注意i从0开始
	}
	for (k = 0; k < n; ++k) {
		for (x = 1; x < m + 1; ++x) {//j从1开始，也就是从f[0][1]开始
			cin >> f[k][x];
		}
	}
	//给F[0][0-m]赋值
	for (x = 0; x < m + 1; ++x) {
		F[0][x] = f[0][x];//第一个项目上投入0-m元钱的最大收益等于f[0][0-m]
	}
	for (k = 1; k < n; ++k) {//项目循环，从1开始,也就是从前2个项目开始算，因为第一个项目已经赋值
		for (x = 0; x < m + 1; ++x) {//钱数循环 从0开始
			for (xk = 0; xk <= x; ++xk) {
				temp = F[k - 1][x - xk] + f[k][xk];
				if (temp> F[k][x])
					F[k][x] =temp;
			}
		}
	}
	cout << "the max profit is : " << F[n - 1][m] << endl;
}