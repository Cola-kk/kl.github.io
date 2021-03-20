#include<stdio.h>
#define max 99999
int main() {
	int vexnum, edgenum,cust;
	int init, end, weight,u;
	int dis[10],sign[10];
	int e[10][10];
	printf("请输入顶点个数和边数：\n");
	scanf_s("%d %d", &vexnum, &edgenum);
	printf("请输入源点：\n");
	scanf_s("%d", &cust);
	//初始化邻接矩阵
	for (int i = 1; i <= vexnum; i++)
		for (int j = 1; j <= vexnum; j++)
			if (i == j) e[i][j] = 0;
			else e[i][j] = max;
	printf("请输入各边起点、终点和权重：\n");
	//矩阵赋值
	for (int i = 0; i < edgenum; i++) {
		scanf_s("%d %d %d", &init, &end, &weight);
		e[init][end] = weight;
	}
	//以cust为源点初始化dis数组
	for (int i = 1; i <= vexnum; i++)
		dis[i] = e[cust][i];
	//初始化sign数组
	for (int i = 1; i <= vexnum; i++)
		sign[i] = 1;
	sign[cust] = 0;//已经是最短路径集合内的点为0
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