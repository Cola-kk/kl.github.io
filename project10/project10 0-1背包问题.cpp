#include <iostream>
#include <cmath>
#include <cstring>
#define num 100
using namespace std;
float p1 = 0.0, w1 = 0.0;
int all = 0;
void bagloading(int x[], float p[], float w[], float c, int n)
{
    //x[]取值为0或1，x[i]=1当且仅当背包i背装载；
    //p[]是物品价值；
    //w[]是物品重量；
    //c表示背包的容量；
    //n表示物品的件数；

    float t, k, pw[num];
    int i, j, m, kk;
    for (i = 0; i < n; i++)
        pw[i] = p[i] / w[i];
    //对各个点的坐标按由大到小进行排序(使用改进的冒泡排序)
    m = n - 1;
    while (m > 0)
    {
        kk = 0;
        for (j = 0; j < m; j++)
            if (pw[j] < pw[j + 1])
            {
                t = p[j];
                p[j] = p[j + 1];
                p[j + 1] = t;
                k = w[j];
                w[j] = w[j + 1];
                w[j + 1] = k;
                kk = j;
            }
        m = kk;
    }

    //按p/w次序从大到小选择物品
}

int main()
{
    int n;
    float c;
    float p[num];
    float w[num];
    int x[num];
    int i;
    cout << "请输入物品的件数：";
    cin >> n;
    cout << "请依次输入各物品的价值与重量 \n每个物品的价值与重量之间用空格隔开，回车后输入另一个物品：" << endl;
    //通过键盘依次输入各物品的价值与重量  
    for (i = 0; i < n; i++)
    {
        cin >> p[i] >> w[i];
    }
    cout << "请输入背包的最大容量：";
    cin >> c;
    //调用函数
    bagloading(x, p, w, c, n);
    //统计物品的总价值、总重量以及件数并输出
    //统计装入物品的价值及重量并输出
    for (i = 0; i < n; i++)
    {
        if (c >= w[i]) {
            cout << w[i] << "放入背包" << endl;
            c -= w[i];
            p1 = p1 + p[i];
            w1 = w1 + w[i];
            x[i] = 1;
            all++;
        }

    }
    if (all > 0)
    {
        cout << "该背包共装入的这" << all << "件物品" << endl;
        for (i = 0; i < n; i++)
            if (x[i] == 1)
                cout << p[i] << " " << w[i] << endl;
    }
    cout << "所装物品总的价值为：" << p1 << endl;
    cout << "所装物品总的重量为：" << w1 << endl;
    cout << endl;
    system("pause");
    return 0;
}