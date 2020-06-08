#include "KMP.h"
#include "Huffman.h"

int main()
{
	//string t = "ababaaabcdedsdfefdfsd";
	//string p = "edsd";
	//int location = KMP(t,p);
	HuffmanTree HT;
	HuffmanCode HC;
	int *w, i, n, wei, m;
	std::cout << "n = ";
	std::cin >> n;
	cout << n << endl;
	m = 2 * n - 1;
	w = (int *)malloc((n + 1) * sizeof(int));
	cout << "input the " << n << " element's weight:\n";
	for (i = 1;i<n+1;i++)
	{
		cout << i;
		fflush(stdin);
		cin >> wei;
		w[i] = wei;
	}
	//��������ʾ�Ĺ���������Ԫ��
	map<int, char> CharandWeight;
	for (int num = 1; num <= n; num++)
	{
		char c;
		cout << "Ȩֵ����ĵ�" << num << "��Ϊ" << w[num] << "������֮��ϵ��Ԫ������Ϊ:";
		cin >> c;
		cout << c << endl;
		CharandWeight.insert({ w[num],c });
	}
	createHuffmanTree(&HT, w, n);
	Printf(&HT,m, CharandWeight);
	createHuffmanCode(&HT,&HC,n);
	return 0;
}