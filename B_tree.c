#include "B_tree.h"
#include <stdio.h>
Result SearchBTree(BTree T, KeyType K)
{
	BTNode* p = T,*q=NULL;
	int found = 0,i=0;

	while (p&&!found)
	{
		int j = 1;
		for (;j<=p->keynum;j++)
		{
			if (p->key[j] ==K)
				break;
			else if (p->key[j] > K)
			{
				j--;
				break;
			}
		}
		i = j;
		if (i > 0 && p->key[i] == K)
			found = 1;
		else
		{
			q = p;
			p = p->ptr[i];
		}
	}
	Result ret;
	ret.pt = q;
	ret.index = i;
	ret.tag = 0;
	if (found)
	{
		ret.pt = p;
		ret.tag = 1;
	}

	return ret;
}

static inline void Insert(BTree q, int i, KeyType v, BTree aq)
{
	for (int j =q->keynum; j > i; j--)
	{
		q->key[j + 1] = q->key[j];
		q->ptr[j + 1] = q->ptr[j];
	}
	q->key[i + 1] = v;
	q->ptr[i + 1] = aq;
	(q->keynum)++; 
}
static void split(BTree q, int i, BTree qp)
{

}
static int Search(BTree q, KeyType x)
{

}
static inline void createNewRoot(BTree* T, BTree q, KeyType x, BTree ap)
{

}

Status InsertBTree(BTree* T, KeyType K, BTree q, int i)
{
	KeyType x = K;
	BTree ap = NULL;
	int finished = FALSE;
	while (q&&!finished)
	{
		Insert(q, i, x, ap);
		if (q->keynum < m)
			finished = TRUE;
		else {
			int s = (m % 2 == 0 ? m / 2 : m / 2 + 1);
			split(q, s, ap);
			x = q->key[s];
			q = q->parent;
			if (q)
				i = Search(q, x);
		}

	}
	if (!finished)
		createNewRoot(T, q, x, ap);
	return OK;
}