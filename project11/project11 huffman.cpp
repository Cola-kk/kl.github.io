#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

#define NUM_CHARS 256   //��ȡ���ַ�������������ô�����ַ�
#define MAX_FREQ  10000   //���Ƶ�ʱ���С�������
#define MAX_SIZE  512

//Huffman Tree���
typedef struct HuffNode
{
    char data;
    unsigned int freq;
    int parent;
    int lchild;
    int rchild;
}HuffNode;
//������
typedef struct HuffCode
{
    char data;//�����ַ�
    string s;//�����ַ���Ӧ�ı���
}HuffCode;

//����һ���ַ��������ַ��ĳ���Ƶ�ʱ��浽freqs������
//ע���ַ����ֵ�Ƶ�ʲ��ܳ���unsigned int���ܱ�ʾ�ķ�Χ
int Create_freq_array(unsigned int(&freqs)[NUM_CHARS], string s, int& char_size)//�������������,
{
    int i, maxfreq = 0;
    for (int i = 0; i < NUM_CHARS; i++)
        freqs[i] = 0;//ע�⴫�������ĸ�Ԫ���ȸ�ֵΪ0
    for (auto iter = s.begin(); iter != s.end(); iter++)
    {
        freqs[*iter]++;   //*iterΪchar�ͣ�����ת������int��,����ĳ���ַ���ASCII����Ϊ
        if (freqs[*iter] > maxfreq)//����freq�����е��±꣬ע�����ַ�ʽ���ܱ�ʾ��ASCII���ַ���
            maxfreq = freqs[*iter];//ÿ�μǵø���maxfreq��ֵ
    }
    for (i = 0; i < NUM_CHARS; i++)//����char_sizeֵ
    {
        if (freqs[i])
        {
            char_size++;
        }
    }
    return 0;
}

//��ӡ�ַ�Ƶ�ʱ�
int Print_freqs(unsigned int(&freqs)[NUM_CHARS], int n)
{
    int i;
    char c;
    for (i = 0; i < NUM_CHARS; i++)
    {
        if (freqs[i])
        {
            c = i;//��i��ASCII��ֵ��ԭ����Ӧ���ַ�
            cout << "�ַ� " << c << " ���ֵ�Ƶ��Ϊ��" << freqs[i] << endl;
        }

    }
    cout << endl << "���Ϲ�����" << n << "���ַ�" << endl << endl;
    return 0;
}

int Build_Huffman_tree(unsigned int(&freqs)[NUM_CHARS], HuffNode(&Huffman_array)[MAX_SIZE], int n)
{                                                          //n��ʾfreqs������ʵ�ʰ������ַ�������
    char c;
    int k = 0, x1, x2;
    unsigned int m1, m2;

    for (int i = 0; i < NUM_CHARS; i++)//��ǰn��Ҷ������Ϣ����Huffman_array����
    {
        if (freqs[i])
        {
            c = i;//��ԭ�ַ�
            Huffman_array[k].data = c;
            Huffman_array[k].freq = freqs[i];
            Huffman_array[k].parent = 0;
            Huffman_array[k].lchild = 0;
            Huffman_array[k].rchild = 0;
            k++;
        }
    }
    for (int i = n; i < 2 * n - 1; i++)//����ʣ��n-1����Ҷ�ӽ��
    {
        Huffman_array[i].data = '#';
        Huffman_array[i].freq = 0;
        Huffman_array[i].parent = 0;
        Huffman_array[i].lchild = 0;
        Huffman_array[i].rchild = 0;
    }
    // ѭ������ Huffman ��
    for (int i = 0; i < n - 1; i++)
    {
        m1 = m2 = MAX_FREQ; // m1��m2�д�������޸�����ҽ��Ȩֵ��С���������
        x1 = x2 = 0;  //x1��x2���������������ͬ������������СȨֵ����������е����
        /* �ҳ����н����Ȩֵ��С���޸�����������㣬���ϲ�֮Ϊһ�Ŷ����� */
        for (int j = 0; j < n + i; j++)
        {
            if (Huffman_array[j].freq < m1 && Huffman_array[j].parent == 0)//parent �����Ƹõ��Ƿ�ѡȡ����
            {            //�����ǰ�жϵĽ���ȨֵС����С��m1�����������m1��ͬʱ
                m2 = m1;   //����m1�����±꣬ ����m1�ǵ�ǰ�����жϹ���Ԫ��������С��
                x2 = x1;   //�ٰ�m1����Ϣ����m2������m2�ǵ�ǰ�����жϹ���Ԫ�����ǵڶ�С��
                m1 = Huffman_array[j].freq;
                x1 = j;
            }
            else if (Huffman_array[j].freq < m2 && Huffman_array[j].parent == 0)
                //�����ǰ�жϵĽ���Ȩֵ���ڵ�����С��m1������С��m2��
            {            //��ֻ���������m2������m2,����m2�ǵ�ǰ�����жϹ���Ԫ�����ǵڶ�С��
                m2 = Huffman_array[j].freq;
                x2 = j;
            }
        }
        /* �����ҵ��������ӽ�� x1��x2 �ĸ������Ϣ */
        Huffman_array[x1].parent = n + i;
        Huffman_array[x2].parent = n + i;
        Huffman_array[n + i].freq = Huffman_array[x1].freq + Huffman_array[x2].freq;
        Huffman_array[n + i].lchild = x1;
        Huffman_array[n + i].rchild = x2;
    }
    return 0;
}
//����������,���string�и����ַ���Ӧ�ı���
int Huffman_code(HuffNode(&Huffman_array)[MAX_SIZE], HuffCode(&Huffman_code_array)[NUM_CHARS], int n)
{
    int temp;
    for (int i = 0; i < n; i++)
    {
        temp = i;//��ǰ�����Huffman_array�����±�
        Huffman_code_array[i].data = Huffman_array[i].data;
        while (Huffman_array[temp].parent)
        {
            if (Huffman_array[Huffman_array[temp].parent].lchild == temp)//����Ϊ0
            {
                Huffman_code_array[i].s += '0';
            }
            else//�Һ���Ϊ1
            {
                Huffman_code_array[i].s += '1';
            }
            temp = Huffman_array[temp].parent;
        }
        reverse(Huffman_code_array[i].s.begin(), Huffman_code_array[i].s.end());
    }   //ע�ⷭתÿһ��string,�����õ���#include <algorithm>
    return 0;
}

int Print_huffman_code(HuffCode(&Huffman_code_array)[NUM_CHARS], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "�ַ� " << Huffman_code_array[i].data << " ��Ӧ�Ĺ���������Ϊ��" << Huffman_code_array[i].s << endl;
    }
    cout << endl;
    return 0;
}

int main()
{
    string s;
    cin >> s;
    int char_size = 0;//���Ա���string�����������ַ�����
    unsigned int freqs[NUM_CHARS];
    HuffNode Huffman_array[MAX_SIZE];
    HuffCode Huffman_code_array[NUM_CHARS];

    cout << "������ַ�����Ϊ: " << s.size() << endl << endl << "���У�" << endl;//string�а������ַ���
    Create_freq_array(freqs, s, char_size);
    Print_freqs(freqs, char_size);
    Build_Huffman_tree(freqs, Huffman_array, char_size);
    Huffman_code(Huffman_array, Huffman_code_array, char_size);
    Print_huffman_code(Huffman_code_array, char_size);
    return 0;
}