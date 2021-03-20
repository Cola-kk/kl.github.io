#include<stdio.h>
#define max 99999
int main() {
	int vexnum, edgenum;
	int init, end, weight;
	int e[10][10];
	printf("请输入顶点个数和边数：\n");
	scanf_s("%d %d", &vexnum, &edgenum);
	for (int i = 1; i <= vexnum; i++)
		for (int j = 1; j <= vexnum; j++)
			if (i == j) e[i][j] = 0;
			else e[i][j] = max;
	printf("请输入各边起点、终点和权重：\n");
	for (int i = 0; i < edgenum; i++) {
		scanf_s("%d %d %d", &init, &end, &weight);
		e[init][end] = weight;
	}
	for (int k = 1; k <= vexnum; k++)
		for (int i = 1; i <= vexnum; i++)
			for (int j = 1; j <= vexnum; j++)
				if (e[i][j] > e[i][k] + e[k][j])
					e[i][j] = e[i][k] + e[k][j];
	printf("最短路径矩阵为：\n");
	for (int i = 1; i <= vexnum; i++) {
		for (int j = 1; j <= vexnum; j++) {
			if (e[i][j] == max)
				printf("∞ ");
			else
				printf("%d ", e[i][j]);
		}
		printf("\n");
	}

}