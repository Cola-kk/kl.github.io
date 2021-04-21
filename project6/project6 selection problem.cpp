#include<iostream>
#include<algorithm>
#include<vector>
#define MAX 100
using namespace std;
bool cmp(int a, int b)
{
	return a > b;
}
void select(vector<int> s, int n, int k);

int main() {
	int n, k;
	vector<int> s;
	int L[MAX];
	cout<<"请输入元素个数:\n";
	cin >> n;
	cout<<"请输入k:\n";
	cin>>k;
	cout<<"请输入数组内元素:\n";
	for (int i = 0; i < n; i++) {
	    cin>>L[i];
		s.push_back(L[i]);
	}
	cout << "第" << k << "小的数是：\n";
	select(s, n,k);
}
void select(vector<int> S, int n, int k) {
	vector<int> s1, s2, m,s;
	s = S;
	for (int i = 0; i < n; i += 5) {
		int len = min(5,n-i);
		sort(s.begin() + i, s.begin() + i + len,cmp);
		m.push_back(s[i+(len-1)/2]);
	}
	sort(m.begin(), m.end(),cmp);
	int len = m.size();
	int m_star =m[(len-1)/2] ;
	for (int i = 0; i < n; i += 5) {
		if (n - i < 5) {
			for (int j = i; j < n; j++) {
				if (s[j] > m_star)
					s2.push_back(s[j]);
				else if (s[j] <m_star)
					s1.push_back(s[j]);
			}
			break;
		}
			if (s[i + 2] < m_star){
				for (int j = 0; j < 2; j++){
					if (s[i + j] < m_star)
						s1.push_back(s[i+j]);
					else
						s2.push_back(s[i+j]);
				}
				for (int j = 2; j < 5; j++)
					s1.push_back(s[i+j]);
		    }
			else if (s[i + 2] > m_star) {
				for(int j=3;j<5;j++){
					if (s[i + j] < m_star)
						s1.push_back(s[i+j]);
					else
						s2.push_back(s[i+j]);
				}
				for (int j = 0; j < 3; j++)
					s2.push_back(s[i + j]);
			}
			else {
				for (int j = 0; j < 2; j++)
					s2.push_back(s[i + j]);
				for(int j=3;j<5;j++)
					s1.push_back(s[i + j]);
				
			}
		
		
	}
	int len1 = s1.size();
	int len2 = s2.size();
	if (k == len1 + 1) { 
		cout << m_star<<endl;
		return;
	}
	else if (k <= len1) {
		select(s1, len1, k);
	}
	else {
		select(s2, len2, k - len1 - 1);
	}
}