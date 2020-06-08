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
	//创建能显示的哈夫曼树的元素
	map<int, char> CharandWeight;
	for (int num = 1; num <= n; num++)
	{
		char c;
		cout << "权值数组的第" << num << "个为" << w[num] << "并且与之联系的元素输入为:";
		cin >> c;
		cout << c << endl;
		CharandWeight.insert({ w[num],c });
	}
	createHuffmanTree(&HT, w, n);
	Printf(&HT,m, CharandWeight);
	createHuffmanCode(&HT,&HC,n);
	return 0;
}