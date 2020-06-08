#ifndef _HUFFMAN_H
#define _HUFFMAN_H
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <map>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
//huffman ���Ľṹ
typedef struct
{
	//Ҷ�ӽ��Ȩֵ
	unsigned int weight;
	//ָ��˫�׺ͺ��ӽ���ָ��
	unsigned int parent;
	unsigned int lchild;
	unsigned int rchild;
}Node,*HuffmanTree;

//��̬�������飬�洢����������
typedef char *HuffmanCode;

//ѡ������parentΪ0����weight��С�Ľ��S1��S2�ķ���ʵ��
//nΪҶ�ӽڵ��������S1��S2����ָ�����ָ��Ҫѡȡ������Ȩֵ��С�Ľ��
void select(HuffmanTree* huffmanTree, int n, int* s1, int* s2)
{
	//���i
	int i = 0;
	//��¼��СȨֵ
	int min;
	//����ȫ����㣬�ҳ����ڵ�
	for (i = 1; i <= n; i++)
	{
		//����˽��ĸ���û�У���ô�ѽ��Ÿ�ֵ��min������ѭ��
		if ((*huffmanTree)[i].parent == 0)
		{
			min = i;
			break;
		}
	}
	//��������ȫ����㣬�ҳ�Ȩֵ��С�ĵ��ڵ�
	for (i = 1; i <= n; i++)
	{
		//����˽��ĸ���Ϊ�գ������if
		if ((*huffmanTree)[i].parent == 0)
		{
			//����˽���Ȩֵ��min����ȨֵС����ô����min��㣬��������ʼ��min
			if ((*huffmanTree)[i].weight < (*huffmanTree)[min].weight)
			{
				min = i;
			}
		}
	}
	//�ҵ�����СȨֵ�Ľ�㣬s1ָ��
	*s1 = min;
	//����ȫ�����
	for (i = 1; i <= n; i++)
	{
		//�ҳ���һ�����ڵ㣬��û�б�s1ָ����ôi��ֵ��min������ѭ��
		if ((*huffmanTree)[i].parent == 0 && i != (*s1))
		{
			min = i;
			break;
		}
	}
	//��������ȫ����㣬�ҳ�Ȩֵ��С����һ��
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
	//s2ָ��ָ��ڶ���Ȩֵ��С��Ҷ�ӽڵ�
	*s2 = min;
}


//���������������������������㷨���£�w��������֪��n��Ȩֵ
void createHuffmanTree(HuffmanTree *huffmanTree,int w[],int n)
{
	//mΪ���������ܹ��Ľ������nΪҶ�ӽ����
	int m = 2 * n - 1;
	//s1��s2Ϊ������ǰ����Ҫѡȡ����СȨֵ�Ľ��
	int s1;
	int s2;
	//���
	int i;
	//�������������Ľ������Ŀռ�,m+1���������а�����һ��ͷ���
	*huffmanTree = (HuffmanTree)malloc((m+1)*sizeof(Node));
	//1--n�Ŵ��Ҷ�ӽ�㣬��ʼ��Ҷ�ӽ�㣬�ṹ��������ʼ��ÿ��Ҷ�ӽ�㣬��ʼ��ʱ����һ�����������Ķ�����
	for (i =1;i<=n;i++)
	{
		//����Ҷ�ӽ���Ȩֵ��w[n]����������
		(*huffmanTree)[i].weight = w[i];
		//��ʼ��Ҷ�ӽ�㣨�����ڵ���������ĺ��Ӻ�˫�ף�������㣬Ҳ����û�к��Ӻ�˫�ף�==0
		(*huffmanTree)[i].lchild = 0;
		(*huffmanTree)[i].rchild = 0;
		(*huffmanTree)[i].parent = 0;
	}

	//��Ҷ�ӽ��ĳ�ʼ��
	for (i = n +1;i<=m;i++)
	{
		(*huffmanTree)[i].weight = 0;
		(*huffmanTree)[i].lchild = 0;
		(*huffmanTree)[i].rchild = 0;
		(*huffmanTree)[i].parent = 0;
	}
	//������Ҷ�ӽ�㣬����������
	for (i = n+1;i<=m;i++)
	{
		//��(*huffmanTree)[1]-(*huffmanTree)[i-1]�ķ�Χ��ѡ������parentΪ0
		//��weight��С�Ľ�㣬����ŷֱ�ֵs1,s2
		select(huffmanTree, i - 1, &s1, &s2);
		//ѡ��������Ȩֵ��С��Ҷ�ӽ�㣬���һ���µĶ���������Ϊi���
		(*huffmanTree)[s1].parent = i;//��֤���´�ѡ��СȨֵ��ʱ��s1��s2�Ѿ�ӵ�и�����ˣ����Է��ĵ���
		(*huffmanTree)[s2].parent = i;//��֤���´�ѡ��СȨֵ��ʱ��s1��s2�Ѿ�ӵ�и�����ˣ����Է��ĵ���
		(*huffmanTree)[i].lchild = s1;
		(*huffmanTree)[i].rchild = s2;
		//�µĽ���ȨֵΪ
		(*huffmanTree)[i].weight = (*huffmanTree)[s1].weight + (*huffmanTree)[s2].weight;
	}
}

void Printf(HuffmanTree *huffmanTree, int m,map<int,char> maps)
{
	bool flag = true;
	//��ʾ��������(�ݹ�)
	//�ж�����������
	if ((*huffmanTree)[m].lchild != 0)
	{
		{
			//�ж������ַ�Ԫ����ϵ�������ڼ������
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
	//�ж�����������
	if ((*huffmanTree)[m].rchild != 0)
	{
		if(flag)
		{
			//�ж������ַ�Ԫ����ϵ�������ڼ������
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
		//�ж������ַ�Ԫ����ϵ�������ڼ������
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
//��������������ϣ���n��Ҷ�ӽ�㵽����������ÿ��Ҷ�ӽ���Ӧ�Ĺ���������
void createHuffmanCode(HuffmanTree *huffmanTree, HuffmanCode *huffmanCode, int n)
{
	//ָʾ���
	int i;
	//�������ʼָ��
	int start;
	//ָ��ǰ���ĸ��ڵ�
	int p;
	//����n��Ҷ�ӽ���ָʾ���c
	unsigned int c;
	//����n�������ͷָ��
	huffmanCode = (HuffmanCode *)malloc((n+1)*sizeof(char *));
	//������ǰ����Ĺ����ռ�
	char *cd = (char*)malloc(n * sizeof(char));
	//����������λ��ű��룬���ȴ�ű��������
	cd[n - 1] = '\0';
	//��n��Ҷ�ӽ���Ӧ�Ĺ���������
	for (i =1;i<=n;i++)
	{
		//��ʼ��������ʼָ��
		start = n - 1;
		//��Ҷ�ӽ�㵽����������
		for (c =i,p = (*huffmanTree)[i].parent;p!=0;c = p ,p = (*huffmanTree)[p].parent)
		{
			if ((*huffmanTree)[p].lchild == c)
			{
				//���ҵ����˳�������������
				cd[--start] = '0';//���֧��0
			}
			else
			{
				cd[--start] = '1';//�ҷ�֧��1
			}
		}

		huffmanCode[i] = (char*)malloc((n - start) * sizeof(char));
		strcpy_s(huffmanCode[i],strlen(&cd[start])+1,&cd[start]);
	}
	free(cd);
	//��ӡ��������
	for (i =1;i<=n;i++)
	{
		std::cout << "HuffmanCode of " << (*huffmanTree)[i].weight << " of is" << huffmanCode[i] << std::endl;
	}
}
#endif // !_HUFFMAN_H
