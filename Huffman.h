#ifndef _HUFFMAN_H
#define _HUFFMAN_H
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <map>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
//huffman 树的结构
typedef struct
{
	//叶子结点权值
	unsigned int weight;
	//指向双亲和孩子结点的指针
	unsigned int parent;
	unsigned int lchild;
	unsigned int rchild;
}Node,*HuffmanTree;

//动态分配数组，存储哈夫曼编码
typedef char *HuffmanCode;

//选择两个parent为0，且weight最小的结点S1和S2的方法实现
//n为叶子节点的总数，S1和S2两个指针参数指向要选取出来的权值最小的结点
void select(HuffmanTree* huffmanTree, int n, int* s1, int* s2)
{
	//标记i
	int i = 0;
	//记录最小权值
	int min;
	//遍历全部结点，找出单节点
	for (i = 1; i <= n; i++)
	{
		//如果此结点的父亲没有，那么把结点号赋值给min，跳出循环
		if ((*huffmanTree)[i].parent == 0)
		{
			min = i;
			break;
		}
	}
	//继续遍历全部结点，找出权值最小的单节点
	for (i = 1; i <= n; i++)
	{
		//如果此结点的父亲为空，则进入if
		if ((*huffmanTree)[i].parent == 0)
		{
			//如果此结点的权值比min结点的权值小，那么更新min结点，否则就是最开始的min
			if ((*huffmanTree)[i].weight < (*huffmanTree)[min].weight)
			{
				min = i;
			}
		}
	}
	//找到了最小权值的结点，s1指向
	*s1 = min;
	//遍历全部结点
	for (i = 1; i <= n; i++)
	{
		//找出下一个单节点，且没有被s1指向，那么i赋值给min，跳出循环
		if ((*huffmanTree)[i].parent == 0 && i != (*s1))
		{
			min = i;
			break;
		}
	}
	//继续遍历全部结点，找出权值最小的那一个
	for (i = 1; i <= n; i++)
	{
		if ((*huffmanTree)[i].parent == 0 && i != (*s1))
		{
			if ((*huffmanTree)[i].weight < (*huffmanTree)[min].weight)
			{
				min = i;
			}
		}
	}
	//s2指针指向第二个权值最小的叶子节点
	*s2 = min;
}


//创建哈夫曼树并求哈夫曼编码的算法如下，w数组存放已知的n个权值
void createHuffmanTree(HuffmanTree *huffmanTree,int w[],int n)
{
	//m为哈夫曼树总共的结点数，n为叶子结点数
	int m = 2 * n - 1;
	//s1和s2为两个当前结点里，要选取的最小权值的结点
	int s1;
	int s2;
	//标记
	int i;
	//创建哈夫曼树的结点所需的空间,m+1，代表其中包含的一个头结点
	*huffmanTree = (HuffmanTree)malloc((m+1)*sizeof(Node));
	//1--n号存放叶子结点，初始化叶子结点，结构数组来初始化每个叶子结点，初始的时候看做一个个单个结点的二叉树
	for (i =1;i<=n;i++)
	{
		//其中叶子结点的权值是w[n]数组来保存
		(*huffmanTree)[i].weight = w[i];
		//初始化叶子结点（单个节点二叉树）的孩子和双亲，单个结点，也就是没有孩子和双亲，==0
		(*huffmanTree)[i].lchild = 0;
		(*huffmanTree)[i].rchild = 0;
		(*huffmanTree)[i].parent = 0;
	}

	//非叶子结点的初始化
	for (i = n +1;i<=m;i++)
	{
		(*huffmanTree)[i].weight = 0;
		(*huffmanTree)[i].lchild = 0;
		(*huffmanTree)[i].rchild = 0;
		(*huffmanTree)[i].parent = 0;
	}
	//创建非叶子结点，建哈夫曼树
	for (i = n+1;i<=m;i++)
	{
		//在(*huffmanTree)[1]-(*huffmanTree)[i-1]的范围内选择两个parent为0
		//且weight最小的结点，其序号分别赋值s1,s2
		select(huffmanTree, i - 1, &s1, &s2);
		//选出的两个权值最小的叶子结点，组成一个新的二叉树，根为i结点
		(*huffmanTree)[s1].parent = i;//保证了下次选最小权值的时候，s1和s2已经拥有父结点了，可以放心迭代
		(*huffmanTree)[s2].parent = i;//保证了下次选最小权值的时候，s1和s2已经拥有父结点了，可以放心迭代
		(*huffmanTree)[i].lchild = s1;
		(*huffmanTree)[i].rchild = s2;
		//新的结点的权值为
		(*huffmanTree)[i].weight = (*huffmanTree)[s1].weight + (*huffmanTree)[s2].weight;
	}
}

void Printf(HuffmanTree *huffmanTree, int m,map<int,char> maps)
{
	bool flag = true;
	//显示哈夫曼树(递归)
	//判断有无左子树
	if ((*huffmanTree)[m].lchild != 0)
	{
		{
			//判断有无字符元素联系，若存在即输出来
			if (maps.count((*huffmanTree)[m].weight) == 0)
			{
				cout << "                                " << (*huffmanTree)[m].weight << endl << endl;
			}
			else
			{
				cout << "                                " << maps[(*huffmanTree)[m].weight] << "/" << (*huffmanTree)[m].weight << endl << endl;

			}
			flag = false;
		}

		Printf(huffmanTree, (*huffmanTree)[m].lchild,maps);
	}
	//判断有无左子树
	if ((*huffmanTree)[m].rchild != 0)
	{
		if(flag)
		{
			//判断有无字符元素联系，若存在即输出来
			if (maps.count((*huffmanTree)[m].weight) == 0)
			{
				cout << "                                " << (*huffmanTree)[m].weight << endl << endl;
			}
			else
			{
				cout << "                                " << maps[(*huffmanTree)[m].weight] << "/" << (*huffmanTree)[m].weight << endl << endl;

			}
		}

		Printf(huffmanTree, (*huffmanTree)[m].rchild, maps);
	}
	
	if (flag)
	{
		//判断有无字符元素联系，若存在即输出来
		if (maps.count((*huffmanTree)[m].weight) == 0)
		{
			cout << "                                " << (*huffmanTree)[m].weight << endl << endl;
		}
		else
		{
			cout << "                                " << maps[(*huffmanTree)[m].weight] << "/" << (*huffmanTree)[m].weight << endl << endl;

		}
	}
}
//哈夫曼树建立完毕，从n个叶子结点到根，逆向求每个叶子结点对应的哈夫曼编码
void createHuffmanCode(HuffmanTree *huffmanTree, HuffmanCode *huffmanCode, int n)
{
	//指示标记
	int i;
	//编码的起始指针
	int start;
	//指向当前结点的父节点
	int p;
	//遍历n个叶子结点的指示标记c
	unsigned int c;
	//分配n个编码的头指针
	huffmanCode = (HuffmanCode *)malloc((n+1)*sizeof(char *));
	//分配求当前编码的工作空间
	char *cd = (char*)malloc(n * sizeof(char));
	//从右向左逐位存放编码，首先存放编码结束符
	cd[n - 1] = '\0';
	//求n个叶子结点对应的哈夫曼编码
	for (i =1;i<=n;i++)
	{
		//初始化编码起始指针
		start = n - 1;
		//从叶子结点到根结点求编码
		for (c =i,p = (*huffmanTree)[i].parent;p!=0;c = p ,p = (*huffmanTree)[p].parent)
		{
			if ((*huffmanTree)[p].lchild == c)
			{
				//从右到左的顺序编码入数组内
				cd[--start] = '0';//左分支标0
			}
			else
			{
				cd[--start] = '1';//右分支标1
			}
		}

		huffmanCode[i] = (char*)malloc((n - start) * sizeof(char));
		strcpy_s(huffmanCode[i],strlen(&cd[start])+1,&cd[start]);
	}
	free(cd);
	//打印编码序列
	for (i =1;i<=n;i++)
	{
		std::cout << "HuffmanCode of " << (*huffmanTree)[i].weight << " of is" << huffmanCode[i] << std::endl;
	}
}
#endif // !_HUFFMAN_H
