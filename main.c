#include <stdio.h>
#include <windows.h>  
#include <stdlib.h>
#include <time.h>
#include "listtest.h"
#include "linklist.h"
#include "Mystr.h"
#include "BiTree.h"
#include "SearchAlgorithm.h"
#include "SqStack.h"

void test1()
{
	LinkList lista = (LinkList)malloc(sizeof(LNode));
	lista->next = NULL;
	LinkList listb = (LinkList)malloc(sizeof(LNode));
	listb->next = NULL;
	LinkList listc = NULL;

	ListInsert_L(lista, 1, 7);
	ListInsert_L(lista, 1, 5);
	ListInsert_L(lista, 1, 3);
	ListInsert_L(lista, 1, 1);

	ListInsert_L(listb, 1, 8);
	ListInsert_L(listb, 1, 6);
	ListInsert_L(listb, 1, 4);
	ListInsert_L(listb, 1, 2);


	MergeList_L(lista, listb, &listc);
	free(lista);
}
void test2()
{
	DuLinkList lista = (DuLinkList)malloc(sizeof(DuLNode));
	lista->next = lista;
	lista->prior = lista;

	ListInsert_DuL(lista, 1, 1);
	ListInsert_DuL(lista, 1, 2);
	ListInsert_DuL(lista, 1, 3);
	ListInsert_DuL(lista, 1, 4);

	printf("%d\n", ListInsert_DuL(lista, 5, 5));

}
void strtest()
{
	printf("%d\n", IndexStr1("aaaaabbaddd", "bbadddd"));
	printf("%d\n", IndexStr_KMP("aaabaabcacdd", "abaabcac"));
}

Status visit(TElemType e)
{
	printf("%d ", e);
	return OK;
}

void treeTest()
{
	BiTree bt = NULL;
	CreateBiTree(&bt);
	InOrderTraverse_II(bt, visit);
}
void huffmanCodeTest()
{
	HuffmanTree ht = NULL;
	unsigned int w[8] = { 5,29,7,8,14,23,3,11 };
	char** code = NULL;
	HuffmanCoding(&ht, &code, w, 8);
	printf("%d %d\n", ht[15].parent, ht[15].weight);
	for (int i = 0; i < 8; i++)
	{
		printf("%s\n", code[i]);
	}
}

//���Ų���������
void SecondOptimalTest()
{
	BiTree tree = NULL;
	int dat[] = { ' ','A','B','C','D','E','F','G','H','I' };
	float sw[] = { 0,1.0,2.0,4.0,9.0,12.0,16.0,20.0,23.0,28.0 };
	SecondOptimal(&tree, dat, sw, 1, 9);
}
//�������������
Status BSTreeTraverse(BSTree t, VISIT visit)
{
	if (!t)
		return ERROR;
	SqStack S;
	InitStack(&S);
	BSTree p = t;
	while (p || !StackEmpty(S))
	{
		if (p)
		{
			Push(&S, p);
			p = p->lchild;
		}
		else {
			Pop(&S, &p);
			if (!visit(p->data))
				return ERROR;
			p = p->rchild;
		}
	}
	DestoryStack(&S);
	return OK;
}
//�������������
void TreeTest()
{
	BiTree tree = NULL;
	int data[] = { 8,10,19,18,12,26,27,15,16,24,22 };
	for (int i = 0; i < 11; i++)
	{
		InsertBST(&tree, data[i]);
	}
	InOrderTraverse_II(tree,visit);
}
//����ƽ��������
void BSTreeTest()
{
	BSTree tree = NULL;
	//int data[] = {8,10,19,18,12,26,27,15,16,24,22};
	int data[] = { 41,38,31,12,19,8 };
	for (int i=0;i<6;i++)
	{
		InsertAVL(&tree, data[i]);
	}
	BSTreeTraverse(tree, visit);
}

Status RBTreeTraverse(RBTree t, VISIT visit)
{
	if (t.root==t.nil)
		return ERROR;
	SqStack S;
	InitStack(&S);
	RBNode *p = t.root;
	while ((p!=t.nil)|| !StackEmpty(S))
	{
		if (p != t.nil)
		{
			Push(&S, p);
			p = p->lchild;
		}
		else {
			Pop(&S, &p);
			if (!visit(p->data))
				return ERROR;
			p = p->rchild;
		}
	}
	DestoryStack(&S);
	return OK;
}

#define ARRLEN 5000000
void RBtest1()
{
	RBTree tree;
	tree.nil = tree.root = NULL;
	initRBTree(&tree);
	srand(time(0));
	int* arr = (int*)malloc(sizeof(int) * ARRLEN);

	for (int i = 0; i < ARRLEN; ++i)
		arr[i] = i;
	for (int i = ARRLEN - 1; i >= 1; --i)
	{
		int index = rand() % i;
		int temp = arr[index];
		arr[index] = arr[i];
		InsertRBTree(&tree, temp);
		//arr[i] = temp;
	}
	PRBNode tem = NULL;
	int va = 0;
	scanf("%d", &va);
	double time = 0;
	LARGE_INTEGER nFreq;
	LARGE_INTEGER nBeginTime;
	LARGE_INTEGER nEndTime;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);//��ʼ��ʱ  
//	tem = DeleteRBTree(&tree, va);
	int a= SearchRBTree(tree, va,&tem);
	QueryPerformanceCounter(&nEndTime);//ֹͣ��ʱ  
	time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs  
	printf("����ʱ��: %f ms", time * 1000);
}
//���������
void RBTreeTest()
{
	RBTree tree;
	tree.nil = tree.root = NULL;
	initRBTree(&tree);
	int data[] = { 8,27,19,18,12,26,10,15,16,24,22 };
	//int data[] = {41,38,31,12,19,8};
	for (int i = 0; i < 11; i++)
	{
		InsertRBTree(&tree, data[i]);
	}
	RBTreeTraverse(tree, visit);
	InsertRBTree(&tree, 23);
	PRBNode p=DeleteRBTree(&tree,23);
	printf("\n");
	//RBTreeTraverse(tree, visit);
}
#include"huffman.h"
int convertstr(char* dest, int *size,char* str,int len)
{
	int m = len;
	int sub_zero = 8 - (m % 8);
	memset(dest, 0, *size);
	int sum = m / 8;
	int i = 0;
	for (i = 0; i < sum; i++)
	{
		int temp = i * 8;
		dest[i] |= str[temp] << 7;
		dest[i] |= str[temp + 1] << 6;
		dest[i] |= str[temp + 2] << 5;
		dest[i] |= str[temp + 3] << 4;
		dest[i] |= str[temp + 4] << 3;
		dest[i] |= str[temp + 5] << 2;
		dest[i] |= str[temp + 6] << 1;
		dest[i] |= str[temp + 7];
	}
	for (int j = 0; j < m % 8; j++)
	{
		dest[i] |= str[sum * 8 + j] << (7 - j);
	}
	*size = (sub_zero == 0 ? sum : sum + 1);
	return sub_zero;
}
void testconvertstr()
{
	char code[1024];
	char str[26] = { 0,1,1,0,1,0,1,1,1,0,1,1,1,1,1,1,0,0,0,0,1,1,1,0,1,0 };
	int len = 1024;
	printf("subzero: %d \n", convertstr(code, &len, str, 26));
}
int main()
{
	HuffmanEnCoding("D:\\downloads\\MediaCreationTool1909.exe","D:\\downloads\\qMediaCreationTool1909");
	HuffmanDeCoding("D:\\downloads\\qMediaCreationTool1909", "D:\\downloads\\qMediaCreationTool1909-1.exe");
	getchar();
}