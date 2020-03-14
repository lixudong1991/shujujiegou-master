#include "huffman.h"
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
static void findMinNode(HTN *HT, int end, int* l, int* r)
{
	unsigned int w1 = 0xffffffff, w2 = 0xffffffff;
	for (int i = 1; i <= end; i++)
	{
		if ((HT + i)->parent == 0&& (HT + i)->weight!=0)
		{
			if (w1 > (HT + i)->weight)
			{
				*r = *l;
				*l = i;
				w2 = w1;
				w1 = (HT + i)->weight;
			}
			else if (w2 > (HT + i)->weight)
			{
				*r = i;
				w2 = (HT + i)->weight;
			}
		}
	}
}

 static int readbuff(unsigned char *buff,int len,FILE *file,unsigned long long filesize,unsigned char *ret)
{
	 static int realen = 0,index=0,finish=0;
	 static unsigned long long sumlen = 0;
	if (realen==0)
	{
		if (finish)
		{
			return 1;
		}
		memset(buff, 0, len);
		index = 0;
		realen = fread(buff, sizeof(char), len, file);
		if (realen< len)
		{
			if (realen + sumlen < filesize)
				return -1;
			else
				finish = 1;
		}
		sumlen += realen;
	}
	realen--;
	*ret = buff[index++];
	return 0;
}
 static int convertCodestr(char* dest, char* str, int len)
 {
	 int m = len;
	 int sub_zero = 8 - (m % 8);
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
	 return sub_zero;
 }
int  HuffmanEnCoding(const char* filename, const char* outfile)
{

	HuffmanFileHead head;
	memset(&head, 0, sizeof(HuffmanFileHead));
	memcpy(head.head,"HUFFMAN",7);
	FILE* pFile = fopen(filename, "rb");
	if (!pFile)
		return -1;
	unsigned char buff[4096];
	unsigned long long len = 0, size =0;
	fseek(pFile, 0, SEEK_SET);
	while (1)
	{
		memset(buff, 0, 4096);
		len = fread(buff, sizeof(char), 4096, pFile);
		size += len;
		for (int i = 0; i < len; i++)
			head.tree[buff[i] + 1].weight++;
		if (len < 4096)
			break;
	}
	printf("read size: %llu \n",size);
	int sum = 0;
	for (int i=1;i<257;i++)
	{
		if (head.tree[i].weight!=0)
			sum ++ ;
	}
	sum =sum+255;
	for (int index=257; index <=sum; index++)
	{
		unsigned int lc = 0, rc = 0;
		findMinNode(head.tree, index - 1, &lc, &rc);
		head.tree[index].lchild = lc;
		head.tree[index].rchild = rc;
		head.tree[index].weight = head.tree[lc].weight + head.tree[rc].weight;
		head.tree[lc].parent = index;
		head.tree[rc].parent = index;
	}
	head.tree[0].parent = sum ;
	typedef struct CodeStr {
		char len;
		char* str;
	}CodeStr;
	CodeStr code[256];
	memset(code, 0, sizeof(CodeStr) * 256);
	char* cd = malloc(256* sizeof(char));
	cd[255] = '\0';
	unsigned int start;
	for (int index = 1; index < 257; index++)
	{
		if (head.tree[index].weight == 0)
			continue;
		start = 256;
		for (int i = index, j = head.tree[index].parent; j != 0; i = j, j = head.tree[j].parent)
		{
			if (head.tree[j].lchild == i)
				cd[--start] = 0;
			else
				cd[--start] = 1;			
		}
		code[index - 1].str = malloc((256 - start) * sizeof(char));
		code[index - 1].len = (256 - start);
		memcpy(code[index - 1].str, cd + start, 256- start);
	}
	free(cd);
	for (int i=0;i<256;i++)
	{
		if (head.tree[i+1].weight>0)
		{
			convertCodestr(head.code[i].dat,code[i].str,code[i].len);
			head.code[i].len = code[i].len;
		}
	}
	FILE* pFileout = fopen(outfile, "w");
	if (!pFileout)
	{
		return -2;
	}
/*	fwrite("HUFFMANC0000000000000000",1,8, pFileout);
	for (size_t i = 0; i < 512; i++)
	{
		fwrite(&tree[i], sizeof(NTNode), 1, pFileout);
	}*/
	head.sub_zero = 7;
	fseek(pFileout, 0, SEEK_SET);
	fwrite(&head, 1, sizeof(HuffmanFileHead), pFileout);
#if 0
	fseek(pFile, 0, SEEK_SET);
	fseek(pFileout, sizeof(HuffmanFileHead),SEEK_SET);
	unsigned char codedata[1024];
	char *codestr = malloc(8192);
	memset(codedata, 0, 1024);
	unsigned char ch = 0;
	int m = 0;
	char sub_zero = 0;;
	while (1)
	{
		int readstatus = 0; 
		if ((readstatus = readbuff(buff, 4096, pFile, size, &ch)) < 0)
			return -1;
		if (readstatus == 1)
		{
			sub_zero = 8 - (m % 8);
			memset(codedata, 0, 1024);
			sum = m / 8;
			int i = 0;
			for (i = 0; i < sum; i++)
			{
				int temp = i * 8;
				codedata[i] |= codestr[temp] << 7;
				codedata[i] |= codestr[temp + 1] << 6;
				codedata[i] |= codestr[temp + 2] << 5;
				codedata[i] |= codestr[temp + 3] << 4;
				codedata[i] |= codestr[temp + 4] << 3;
				codedata[i] |= codestr[temp + 5] << 2;
				codedata[i] |= codestr[temp + 6] << 1;
				codedata[i] |= codestr[temp + 7];
			}
			for (int j=0;j<m%8;j++)
			{
				codedata[i] |= codestr[sum * 8 + j] << (7 - j);
			}
			fwrite(codedata, 1, (sub_zero==0?sum:sum+1), pFileout);
			fflush(pFileout);
			head.sub_zero = sub_zero;
			fseek(pFileout, 0, SEEK_SET);
			fwrite(&head, sizeof(HuffmanFileHead), 1, pFileout);
			fflush(pFileout);
			break;
		}
		else {
			if (code[ch].len+m>8192)
			{
				memcpy(codestr+m,code[ch].str,8192-m);
				memset(codedata, 0, 1024);
				for (int i = 0; i <1024 ; i++)
				{
					int temp = i * 8;
					codedata[i] |= codestr[temp] << 7;
					codedata[i] |= codestr[temp + 1] << 6;
					codedata[i] |= codestr[temp + 2] << 5;
					codedata[i] |= codestr[temp + 3] << 4;
					codedata[i] |= codestr[temp + 4] << 3;
					codedata[i] |= codestr[temp + 5] << 2;
					codedata[i] |= codestr[temp + 6] << 1;
					codedata[i] |= codestr[temp + 7];
				}
				fwrite(codedata, 1, 1024, pFileout);
				fflush(pFileout);
				memset(codestr,0,8192);
				m = code[ch].len - (8192 - m);
				memcpy(codestr,code[ch].str+(8192-m),m);
			}
			else {
				memcpy(codestr+m,code[ch].str,code[ch].len);
				m += code[ch].len;
			}
		}
	}
#endif
	fclose(pFile);
	fclose(pFileout);
	return 0;
}

int HuffmanDeCoding(const char* filename, const char* outfile)
{
	HuffmanFileHead head;
	memset(&head,0,sizeof(HuffmanFileHead));
	FILE* pFile = fopen(filename, "rb");
	if (!pFile)
		return - 1;
	fseek(pFile, 0, SEEK_SET);

	int headsize = fread(&head, 1, sizeof(HuffmanFileHead), pFile);
	fclose(pFile);
//	fclose(pFileout);
	return 0;
}