#include<iostream>
#include<vector>

using namespace std;

int main() {

	int m, n;//mԪǮ��n��Ͷ��
	int k, x;//ѭ����������
	int xk, temp= 0;//xk�������k����ĿͶ���Ǯ��  0<=tmp<=j;temp����һ��ѭ���е�Ǯ��
	cout << "please enter total money and the number of project:";
	cin >> m >> n;
	vector<vector<int>> f(n, vector<int>(m + 1));//f[i][x], 0<i<=n,0<=x<=m,��i����ĿͶ��xԪǮ����ֵΪ���棬������Ҫ�Լ�����ģ�
	vector<vector<int>> F(n, vector<int>(m + 1));//F[i][x]����xԪǮͶ�뵽ǰi����Ŀ����������
	//��f[i][x]��ֵ
	for (k = 0; k < n; ++k) {
		f[k][0] = 0;//�ڵ�(i+1)����Ŀ��Ͷ��0Ԫ������Ϊ0��ע��i��0��ʼ
	}
	for (k = 0; k < n; ++k) {
		for (x = 1; x < m + 1; ++x) {//j��1��ʼ��Ҳ���Ǵ�f[0][1]��ʼ
			cin >> f[k][x];
		}
	}
	//��F[0][0-m]��ֵ
	for (x = 0; x < m + 1; ++x) {
		F[0][x] = f[0][x];//��һ����Ŀ��Ͷ��0-mԪǮ������������f[0][0-m]
	}
	for (k = 1; k < n; ++k) {//��Ŀѭ������1��ʼ,Ҳ���Ǵ�ǰ2����Ŀ��ʼ�㣬��Ϊ��һ����Ŀ�Ѿ���ֵ
		for (x = 0; x < m + 1; ++x) {//Ǯ��ѭ�� ��0��ʼ
			for (xk = 0; xk <= x; ++xk) {
				temp = F[k - 1][x - xk] + f[k][xk];
				if (temp> F[k][x])
					F[k][x] =temp;
			}
		}
	}
	cout << "the max profit is : " << F[n - 1][m] << endl;
}