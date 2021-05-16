#include<bits/stdc++.h>
using namespace std;
const double inf = 1e20;
const int maxn = 100005;

struct Point {
    double x, y;
}point[maxn];

int n, mp[maxn];

bool cmpx(const Point& a, const Point& b) {//��x�������� 
    if (a.x != b.x)
        return a.x < b.x;
    return a.y < b.y;
}

bool cmpy(const int& a, const int& b) {//��y�������� 
    return point[a].y < point[b].y;
}

double dis(int i, int j) {//������֮��ľ��� 
    return sqrt((point[i].x - point[j].x) * (point[i].x - point[j].x) + (point[i].y - point[j].y) * (point[i].y - point[j].y));
}

double Closest_Pair(int left, int right) {
    double d = inf;
    if (left == right)
        return d;
    if (left + 1 == right)
        return dis(left, right);
    int mid = (left + right) >> 1;
    double d1 = Closest_Pair(left, mid);
    double d2 = Closest_Pair(mid + 1, right);
    d = min(d1, d2);
    int i, j, k = 0;
    //��������Ϊd������  
    for (i = left; i <= right; i++) {
        if (fabs(point[mid].x - point[i].x) <= d)
            mp[k++] = i;
    }
    sort(mp, mp + k, cmpy);
    //����ɨ�裬������ս�� 
    for (i = 0; i < k; i++) {
        for (j = i + 1; j < k && point[mp[j]].y - point[mp[i]].y < d; j++) {
            double d3 = dis(mp[i], mp[j]);
            if (d > d3)    d = d3;
        }
    }
    return d;
}

int main() {
    while (~scanf_s("%d", &n) && n) {
        for (int i = 0; i < n; i++)
            scanf_s("%lf %lf", &point[i].x, &point[i].y);
        sort(point, point + n, cmpx);
        printf("%.2lf\n", Closest_Pair(0, n - 1) / 2);
    }
    return 0;
}