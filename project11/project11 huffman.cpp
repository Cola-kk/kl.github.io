#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

#define NUM_CHARS 256   //读取的字符串中最多出现这么多种字符
#define MAX_FREQ  10000   //最大频率必须小于这个数
#define MAX_SIZE  512

//Huffman Tree结点
typedef struct HuffNode
{
    char data;
    unsigned int freq;
    int parent;
    int lchild;
    int rchild;
}HuffNode;
//编码结点
typedef struct HuffCode
{
    char data;//保存字符
    string s;//保存字符对应的编码
}HuffCode;

//给定一个字符串，把字符的出现频率保存到freqs数组中
//注意字符出现的频率不能超出unsigned int所能表示的范围
int Create_freq_array(unsigned int(&freqs)[NUM_CHARS], string s, int& char_size)//传入数组的引用,
{
    int i, maxfreq = 0;
    for (int i = 0; i < NUM_CHARS; i++)
        freqs[i] = 0;//注意传入的数组的各元素先赋值为0
    for (auto iter = s.begin(); iter != s.end(); iter++)
    {
        freqs[*iter]++;   //*iter为char型，这里转换成了int型,即以某个字符的ASCII码作为
        if (freqs[*iter] > maxfreq)//它在freq数组中的下标，注意这种方式不能表示非ASCII码字符！
            maxfreq = freqs[*iter];//每次记得更新maxfreq的值
    }
    for (i = 0; i < NUM_CHARS; i++)//计算char_size值
    {
        if (freqs[i])
        {
            char_size++;
        }
    }
    return 0;
}

//打印字符频率表
int Print_freqs(unsigned int(&freqs)[NUM_CHARS], int n)
{
    int i;
    char c;
    for (i = 0; i < NUM_CHARS; i++)
    {
        if (freqs[i])
        {
            c = i;//把i以ASCII码值还原出对应的字符
            cout << "字符 " << c << " 出现的频率为：" << freqs[i] << endl;
        }

    }
    cout << endl << "以上共出现" << n << "种字符" << endl << endl;
    return 0;
}

int Build_Huffman_tree(unsigned int(&freqs)[NUM_CHARS], HuffNode(&Huffman_array)[MAX_SIZE], int n)
{                                                          //n表示freqs数组中实际包含的字符种类数
    char c;
    int k = 0, x1, x2;
    unsigned int m1, m2;

    for (int i = 0; i < NUM_CHARS; i++)//把前n个叶结点的信息输入Huffman_array数组
    {
        if (freqs[i])
        {
            c = i;//还原字符
            Huffman_array[k].data = c;
            Huffman_array[k].freq = freqs[i];
            Huffman_array[k].parent = 0;
            Huffman_array[k].lchild = 0;
            Huffman_array[k].rchild = 0;
            k++;
        }
    }
    for (int i = n; i < 2 * n - 1; i++)//处理剩下n-1个非叶子结点
    {
        Huffman_array[i].data = '#';
        Huffman_array[i].freq = 0;
        Huffman_array[i].parent = 0;
        Huffman_array[i].lchild = 0;
        Huffman_array[i].rchild = 0;
    }
    // 循环构造 Huffman 树
    for (int i = 0; i < n - 1; i++)
    {
        m1 = m2 = MAX_FREQ; // m1、m2中存放两个无父结点且结点权值最小的两个结点
        x1 = x2 = 0;  //x1、x2：构造哈夫曼树不同过程中两个最小权值结点在数组中的序号
        /* 找出所有结点中权值最小、无父结点的两个结点，并合并之为一颗二叉树 */
        for (int j = 0; j < n + i; j++)
        {
            if (Huffman_array[j].freq < m1 && Huffman_array[j].parent == 0)//parent 来控制该点是否被选取过了
            {            //如果当前判断的结点的权值小于最小的m1，则把它赋给m1，同时
                m2 = m1;   //更新m1结点的下标， 保持m1是当前所有判断过的元素中是最小的
                x2 = x1;   //再把m1的信息赋给m2，保持m2是当前所有判断过的元素中是第二小的
                m1 = Huffman_array[j].freq;
                x1 = j;
            }
            else if (Huffman_array[j].freq < m2 && Huffman_array[j].parent == 0)
                //如果当前判断的结点的权值大于等于最小的m1，但是小于m2，
            {            //则只需把它赋给m2，更新m2,保持m2是当前所有判断过的元素中是第二小的
                m2 = Huffman_array[j].freq;
                x2 = j;
            }
        }
        /* 设置找到的两个子结点 x1、x2 的父结点信息 */
        Huffman_array[x1].parent = n + i;
        Huffman_array[x2].parent = n + i;
        Huffman_array[n + i].freq = Huffman_array[x1].freq + Huffman_array[x2].freq;
        Huffman_array[n + i].lchild = x1;
        Huffman_array[n + i].rchild = x2;
    }
    return 0;
}
//哈夫曼编码,输出string中各种字符对应的编码
int Huffman_code(HuffNode(&Huffman_array)[MAX_SIZE], HuffCode(&Huffman_code_array)[NUM_CHARS], int n)
{
    int temp;
    for (int i = 0; i < n; i++)
    {
        temp = i;//当前处理的Huffman_array数组下标
        Huffman_code_array[i].data = Huffman_array[i].data;
        while (Huffman_array[temp].parent)
        {
            if (Huffman_array[Huffman_array[temp].parent].lchild == temp)//左孩子为0
            {
                Huffman_code_array[i].s += '0';
            }
            else//右孩子为1
            {
                Huffman_code_array[i].s += '1';
            }
            temp = Huffman_array[temp].parent;
        }
        reverse(Huffman_code_array[i].s.begin(), Huffman_code_array[i].s.end());
    }   //注意翻转每一个string,这里用到了#include <algorithm>
    return 0;
}

int Print_huffman_code(HuffCode(&Huffman_code_array)[NUM_CHARS], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "字符 " << Huffman_code_array[i].data << " 对应的哈夫曼编码为：" << Huffman_code_array[i].s << endl;
    }
    cout << endl;
    return 0;
}

int main()
{
    string s;
    cin >> s;
    int char_size = 0;//用以保存string中所包含的字符种类
    unsigned int freqs[NUM_CHARS];
    HuffNode Huffman_array[MAX_SIZE];
    HuffCode Huffman_code_array[NUM_CHARS];

    cout << "输入的字符总数为: " << s.size() << endl << endl << "其中：" << endl;//string中包含的字符数
    Create_freq_array(freqs, s, char_size);
    Print_freqs(freqs, char_size);
    Build_Huffman_tree(freqs, Huffman_array, char_size);
    Huffman_code(Huffman_array, Huffman_code_array, char_size);
    Print_huffman_code(Huffman_code_array, char_size);
    return 0;
}