#include<stdio.h>
#include<memory.h>
const int Max=9999999;
const int N=50;
int Ncode, Nedges;
int w[N][N], dis[N], visited[N];
int prim();
void Init();
int Judge();
int main() {
	int v1, v2, weight;
	int i = 1, j = 1;
	int min = 0;
	printf("�����붥�����:\n");
	scanf_s("%d", &Ncode);
	printf("������ߵ�����:\n");
	scanf_s("%d", &Nedges);
	Init();
	printf("������ߵ����˵��Լ���ӦȨֵ:\n");
	for (i = 1; i <= Nedges; i++)
	{
		scanf_s("%d%d%d", &v1, &v2, &weight);
		w[v1][v2] = w[v2][v1] = weight;
	}
	min = prim();
	int flag=Judge();
	if (flag == 1){
		printf("��С��������Ȩֵ��:%d\n", min);
	}	
	else
		printf("��������С��������");
	return 0;
}
void Init() {
	int i, j;
	for (i = 1; i <= Ncode; i++)
		for ( j = 1; j <= Ncode; j++)
		{
			if (i == j)
				w[i][j] = 0;
			else
				w[i][j] = Max;
		}
}
int Judge() {
	for (int i = 1; i <=Ncode; i++) {
		if (visited[i] == 0)
			return 0;
	}
	return 1;
}
int prim() {
	int i, j;
	int pos=1, min;//��v1��ʼ����
	int ans = 0;
	memset(visited, 0, sizeof(visited));
	visited[1] = 1;
	for (i = 2; i <= Ncode; i++)
		dis[i] = w[pos][i];//posΪ�˵㣬iΪ��һ�˵�ıߵ�Ȩֵ
	for (i = 1; i < Ncode; i++)
	{
		min = Max;
		for (j = 1; j <= Ncode; j++)
		{
			if (visited[j] == 0 && min > dis[j])//δ�����ʹ��ĵ��ұ�ȨֵС��֮ǰ��Сֵ
			{
				min = dis[j];
				pos = j;
			}
		}
		visited[pos] = 1;
		printf("�������Ķ�����:%d\n", pos);
		ans += min;
		printf("����Ȩֵ��%d\n", ans);
		for (j = 1; j <=Ncode; j++)
			if (visited[j] == 0 && dis[j] > w[pos][j])
				dis[j] = w[pos][j];
	}
	return ans;
}
