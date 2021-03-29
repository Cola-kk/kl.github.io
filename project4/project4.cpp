#include<iostream>
using namespace std;
#define MAX 1000
void Merge(int A[],int start ,int middle,int end,int temp[]) {
	int i = start, j = middle + 1, k = 0;
	for (; i <= middle && j <= end;) {
		if (A[i] < A[j])
			temp[k++] = A[i++];
		else
			temp[k++] = A[j++];
	}
	while (i <= middle )
		temp[k++] = A[i++];
	while (j <= end)
		temp[k++] = A[j++];
	for(int i=0;i<k;i++)
		A[start + i] = temp[i];
}
void MergeSort(int A[],int start ,int end,int temp[]) {
	if (start < end) {
		int middle = (start + end) / 2;
		MergeSort(A, start, middle,temp);
		MergeSort(A, middle + 1, end,temp);
		Merge(A, start, middle, end,temp);
	}
}
int main() {
	int n;
	cin >> n;
	int A[MAX],temp[MAX];
	for (int i = 0; i < n; i++)
		cin >> A[i];
	MergeSort(A, 0, n - 1, temp);
	for (int i = 0; i < n; i++)
		cout << A[i]<<" ";
}