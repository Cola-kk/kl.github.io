#include<stdio.h>
#define max 99999
int main() {
	int vexnum, edgenum,cust;
	int init, end, weight,u;
	int dis[10],sign[10];
	int e[10][10];
	printf("�����붥������ͱ�����\n");
	scanf_s("%d %d", &vexnum, &edgenum);
	printf("������Դ�㣺\n");
	scanf_s("%d", &cust);
	//��ʼ���ڽӾ���
	for (int i = 1; i <= vexnum; i++)
		for (int j = 1; j <= vexnum; j++)
			if (i == j) e[i][j] = 0;
			else e[i][j] = max;
	printf("�����������㡢�յ��Ȩ�أ�\n");
	//����ֵ
	for (int i = 0; i < edgenum; i++) {
		scanf_s("%d %d %d", &init, &end, &weight);
		e[init][end] = weight;
	}
	//��custΪԴ���ʼ��dis����
	for (int i = 1; i <= vexnum; i++)
		dis[i] = e[cust][i];
	//��ʼ��sign����
	for (int i = 1; i <= vexnum; i++)
		sign[i] = 1;
	sign[cust] = 0;//�Ѿ������·�������ڵĵ�Ϊ0
	for (int i = 1; i < vexnum; i++) {
		int min = max;
		for (int j = 1; j <= vexnum; j++) {
			if (sign[j] == 1 && dis[j] < min) {
				min = dis[j];
				u = j;
			}
		}
		sign[u] = 0;
		for (int v = 1; v <=vexnum;v++) {
			if(e[u][v]<max)
			if (dis[v] > dis[u] + e[u][v])
				dis[v] = dis[u] + e[u][v];
		}
	}
	for (int i = 1; i <= vexnum; i++)
		printf("%d  ", dis[i]);
}