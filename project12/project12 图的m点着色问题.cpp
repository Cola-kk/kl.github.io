#include<iostream>
#include<math.h>
#include<cstring>
using namespace std;
#define MAX 100
int m;//颜色数量
int n;//顶点个数
int k;//边的条数
int sum = 0;
int x[MAX] = {0}; //每个顶点涂的颜色
int a[MAX][MAX] = { 0 };//顶点的邻接矩阵
bool judge(int v) {
	for (int i = 0; i < v; i++) {
		if (a[i][v] == 1 && x[i] == x[v])
			return false;
	}
	return true;
}
void tintage(int v) {
	if (v <= n) {
		for (int i = 1; i <= m; i++) {
			x[v] = i;
			if (judge(v)) {//能够涂色
				tintage(v + 1);//执行下个顶点
			}
			x[v] = 0;
		}
	}
	else {
		sum++;//涂色方案数++
	    for(int k=1;k<=n;k++)
			cout<<x[k]<<" ";
	    cout<<endl;
		return;
	}
}
int main(){
	int x, y;
	cout << "please enter the number of edge ,vertex and color:";
	cin >>n>>k>>m;
	cout << "please enter the edges:\n";
	for (int i = 0; i < k; i++) {
	cin >> x >> y;
	a[x][y] = a[y][x] = 1;
	}
	tintage(1);
	if (sum == 0)
		cout << "NO!\n";
	else cout << sum;
}