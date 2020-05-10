#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "listtest.h"
#include "linklist.h"
#include "Mystr.h"
#include "BiTree.h"
#include "SearchAlgorithm.h"
#include "SqStack.h"
#include "B_tree.h"
#include "NumberAlg.h"
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>  
#endif
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

//次优查找树测试
void SecondOptimalTest()
{
	BiTree tree = NULL;
	int dat[] = { ' ','A','B','C','D','E','F','G','H','I' };
	float sw[] = { 0,1.0,2.0,4.0,9.0,12.0,16.0,20.0,23.0,28.0 };
	SecondOptimal(&tree, dat, sw, 1, 9);
}
//二叉树中序遍历
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
//二叉查找树测试
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
//二叉平衡树测试
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
#if defined(_WIN32) || defined(_WIN64)
	double time = 0;
	LARGE_INTEGER nFreq;
	LARGE_INTEGER nBeginTime;
	LARGE_INTEGER nEndTime;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);//开始计时  
#endif
//	tem = DeleteRBTree(&tree, va);
	int a= SearchRBTree(tree, va,&tem);
#if defined(_WIN32) || defined(_WIN64)
	QueryPerformanceCounter(&nEndTime);//停止计时  
	time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位为s  
	printf("运行时间: %f ms", time * 1000);
#endif
}
//红黑树测试
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
//B树测试
void B_treeTest()
{
	BTree tree=NULL;
	char* rec[26] = { "A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z" };
	for (int i=0;i<26;i++)
	{
		InsertBTree(&tree, i+1, rec[i]);
	}

}



#include"huffman.h"
int convertstr(char* dest, int *size,char* str,int len)
{
	int n = len;
	int sub_zero = 8 - (n % 8);
	memset(dest, 0, *size);
	int sum = n / 8;
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

	for (int j = 0; j < n % 8; j++)
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
int cmpfile(const char* file, const char* file1)
{
	FILE* pFile = fopen(file, "rb");
	if (!pFile)
		return -1;
	FILE* pFile1 = fopen(file1, "rb");
	if (!pFile1)
		return -1;
	char buff[4096];
	char buff1[4096];
	int len = 0, len1 = 0;
	long long size = 0;
	while (1)
	{
		memset(buff,0,4096);
		memset(buff1, 0, 4096);
		len = fread(buff, 1, 4096, pFile);
		len1 = fread(buff1, 1, 4096, pFile1);
		if (len!=len1)
		{

			return -1;
		}
		for (int i=0;i<len;i++)
		{
			char c = buff[i], c1 = buff1[i];
			if (c!=c1)
			{
				//fclose(pFile);
				//fclose(pFile1);
				//return size + i;
				printf("aaa : %d\n", i);
			}
		}
		size += len;
		if (len<4096)
		{
			fclose(pFile);
			fclose(pFile1);
			return 0;
		}
	}

}
void huffman(int argc, char* argv[])
{
	if (argc < 4)
	{
		printf("usage : 'program -e srcfilename destfilename' encoding file\n"
			"        'program -d srcfilename destfilename' decoding file\n");
		return;
	}
	if (memcmp(argv[1], "-e", 3) == 0)
	{

		printf("encoding....\n");
#if defined(_WIN32) || defined(_WIN64)
		double time = 0;
		LARGE_INTEGER nFreq;
		LARGE_INTEGER nBeginTime;
		LARGE_INTEGER nEndTime;
		QueryPerformanceFrequency(&nFreq);
		QueryPerformanceCounter(&nBeginTime);//开始计时 
#endif
		HuffmanEnCoding(argv[2], argv[3]);
#if defined(_WIN32) || defined(_WIN64)
		QueryPerformanceCounter(&nEndTime);//停止计时  
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位为s  
		printf("压缩时间: %f ms\n", time * 1000);
#else
		printf("压缩完成\n");
#endif
	}
	else if (memcmp(argv[1], "-d", 3) == 0)
	{
		printf("decoding....\n");
#if defined(_WIN32) || defined(_WIN64)
		double time = 0;
		LARGE_INTEGER nFreq;
		LARGE_INTEGER nBeginTime;
		LARGE_INTEGER nEndTime;
		QueryPerformanceFrequency(&nFreq);
		QueryPerformanceCounter(&nBeginTime);//开始计时 
#endif
		HuffmanDeCoding(argv[2], argv[3]);
#if defined(_WIN32) || defined(_WIN64)
		QueryPerformanceCounter(&nEndTime);//停止计时  
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位为s  
		printf("解压时间: %f ms\n", time * 1000);
#else
		printf("解压完成\n");
#endif
	}
	else {
		printf("usage : 'program -e srcfilename destfilename' encoding file\n"
			"        'program -d srcfilename destfilename' decoding file\n");
	}
}
/*
求解模线性方程测试
*/
void testmodule_linerar()
{
/*
	ui64 a = 35, n = 50, b = 10;
	ui64* ret = NULL;
	ui64 size = modular_linear_equation_solver(a, b, n, &ret);
	for (ui64 i = 0; i < size; i++)
	{
		printf("%llu  ", ret[i]);
	}*/
}
/*
	反复平方法求 a^b mod n,a>=0,b>=0,n>0;测试
*/
void test_modular_exponentiation()
{
	ui64 a = 2, b = 64, n = 3;
	//ui64 ret = modular_exponentiation(a, b, n);
//	printf("%llu\n", ret);
}
/*
伪素数测试
*/
void testpseudoprime()
{
	ui64 n = 1105;
	if (pseudoprime(n))
		printf("%llu 是素数\n", n);
	else
		printf("%llu 不是素数\n", n);
}

int main(int argc,char * argv[])
{
	RsaKey prikey, pubkey;
	mpz_init_set_ui(prikey.val, 0);
	mpz_init_set_ui(prikey.n, 0);
	mpz_init_set_ui(pubkey.val, 0);
	mpz_init_set_ui(pubkey.n, 0);
	if (createKey(&prikey, &pubkey))
	{
		printf("创建key成功\n");
	}
	else
		printf("创建key失败\n");

	printf("prikey d = %s\n", mpz_get_str(NULL, 16, prikey.val));
	printf("prikey n = %s\n", mpz_get_str(NULL, 16, prikey.n));
	printf("pubkey e = %s\n", mpz_get_str(NULL, 16, pubkey.val));
	printf("pubkey n = %s\n", mpz_get_str(NULL, 16, pubkey.n));
	char* message = "373057086";

	mpz_t ecode, dcode,mess;
	mpz_init_set_ui(ecode, 0);
	mpz_init_set_ui(dcode, 3);
	mpz_init_set_str(mess, message,10);
	mpz_powm(ecode, mess, pubkey.val,pubkey.n);
	printf("加密后的消息= %s\n", mpz_get_str(NULL, 16, ecode));
	mpz_powm(dcode, ecode, prikey.val, prikey.n);
	printf("解密后的消息= %s\n", mpz_get_str(NULL, 10, dcode));

	/*
	mpz_t n;
	mpz_init_set_str(n, "a337836a31f574713f1bfb972b967fcb23a6f916130c9ab31bad3201bc7efbadefd4bdd1c3ca067fe9096466e5883efe5e71456c5e78bc403b45c52152e13c05876f0170eabc0adfecf6d31b0b0b6b0971aa017d54ac5dd7a527e58b5d515b035b377d7a307799bba375d25ba18ffede166f6845f09ae7ddccb053c409244a69", 16);
	if (miller_rabin(&n, 10))
	{
		printf("是素数\n");
	}
	else
		printf("不是素数\n");
	mpz_init_set_str(n, "e0383dcdd78f9d8fb3978b346f999a95f0ed8fbcde4aa9b230ee7f518a46d6d12cc79e922772fdcc1ffd6bd783b2ff42049edae5c0ad70ed1231885ad9e397e0cd8f861d5c5828db945f77bde479718b21fb3759b0e846c349a51dd3a408c2d7826900189baef63127c649f8be0b904483a93f05cdc885d7aa86d3b0e91a51c5", 16);
	if (miller_rabin(&n, 10))
	{
		printf("是素数\n");
	}
	else
		printf("不是素数\n");
	mpz_init_set_str(n, "8ef46e8922256d5b50ad8a3b72b369af3eafb92ff65ad7d2602d72d796e299895df53c4e1e1a71ddb104586ee27f59648ea875d481049555919a9cc38d2481e225f573c231186483771666ee1848fc9bfec1bda6d8e1781edc58d5a3600271f6f4f60a6476e315c29c81b0994d4188a866d27433a32a77a573286cdda9cdb4e0e4405daacaccdaac40443b78a324db8d78f4a08add04a3af567c9a225c680ff8d358c7263411548ef734a1526beacaff647fbbb4e8c1ff08158230b8984712d15f4c5959c3fb738889022d0352d74ad2c0ac7b7dbd256971900542636e9ab432b8af5dad8aa52c5674d79a1676419b2168dcf1366a82f97f1baa2558a4227bcd", 16);
	if (miller_rabin(&n, 10))
	{
		printf("是素数\n");
	}
	else
		printf("不是素数\n");
*/
	/*
	mpz_t a, b, n,val;
	mpz_init_set_ui(a,3);
	mpz_init_set_ui(b,1);
	mpz_init_set_ui(n,17);
	mpz_init_set_ui(val,0);
	if (modular_linear_equation_solver(a, b, n, &val, 0))
		printf("val= %s", mpz_get_str(NULL, 10, val));
	else
		printf("不存在");*/
	return 0;
}