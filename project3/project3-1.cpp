#include<iostream>
using namespace std;
#define MAX 10
int sort_1(int x,int T[]);
int sort_2(int x, int T[], int low, int high);
int main() {
	int T[MAX];
	int low = 0, high = MAX;
	for (int i = 0; i < MAX; i++) {
		cin >> T[i];
	}
	int x;
	cin >> x;
	cout<<sort_1(x,T)<<"\n";
	cout << sort_2(x, T, low, high);
	return 0;
}
int sort_1(int x, int T[]) {
	for (int i = 0; i < MAX; i++)
		if (x == T[i])
			return i;
	return 0;
}
int sort_2(int x, int T[],int low,int high) {
	int mid = (low + high) / 2;
	if (T[mid] == x)
		return mid;
	else if (x < T[mid]) {
		high = mid - 1;
		return sort_2(x, T, low, high);
	}
	else {
		low = mid + 1;
		return sort_2(x, T, low, high);
	}
}