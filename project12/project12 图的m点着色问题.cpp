#include<iostream>
#include<math.h>
#include<cstring>
using namespace std;
#define MAX 100
int m;//��ɫ����
int n;//�������
int k;//�ߵ�����
int sum = 0;
int x[MAX] = {0}; //ÿ������Ϳ����ɫ
int a[MAX][MAX] = { 0 };//������ڽӾ���
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
			if (judge(v)) {//�ܹ�Ϳɫ
				tintage(v + 1);//ִ���¸�����
			}
			x[v] = 0;
		}
	}
	else {
		sum++;//Ϳɫ������++
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