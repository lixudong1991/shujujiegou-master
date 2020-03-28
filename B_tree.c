#include "B_tree.h"
#include <stdio.h>
static int inline Search(BTNode* p, KeyType k)
{
	for (int j = 1; j <= p->keynum; j++)
	{
		if (p->key[j] == k)
			return j;
		else if (p->key[j] > k)
		{
			return j-1;
		}
	}
	return p->keynum;
}
Result SearchBTree(BTree T, KeyType K)
{
	BTNode* p = T,*q=NULL;
	int found = 0,i=0;
	while (p&&!found)
	{
	
		i = Search(p,K);
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

static inline void Insert(BTree q, int i, KeyType v,Record * rec, BTree aq)
{
	for (int j =q->keynum; j > i; j--)
	{
		q->key[j + 1] = q->key[j];
		q->ptr[j + 1] = q->ptr[j];
		q->recptr[j + 1] = q->recptr[j];
	}
	q->key[i + 1] = v;
	q->ptr[i + 1] = aq;
	q->recptr[i + 1] = rec;
	if(aq)
	aq->parent = q;
	(q->keynum)++; 
}
static void split(BTree q, int i, BTree *ap)
{
	*ap = malloc(sizeof(BTNode));
	if (!*ap)
		exit(OVERFLOW);
	memset(*ap, 0, sizeof(BTNode));
	for (int j=i+1,index=1;j<= BTREE_M;j++,index++)
	{
		(*ap)->key[index] = q->key[j];
		q->key[j] = 0;
		(*ap)->ptr[index] = q->ptr[j];
		if(q->ptr[j])
		q->ptr[j]->parent = (*ap);
		q->ptr[j] = NULL;
		(*ap)->recptr[index] = q->recptr[j];
		q->recptr[j] = NULL;
		q->keynum--;
		(*ap)->keynum++;
	}
	(*ap)->ptr[0] = q->ptr[i];
	if(q->ptr[i])
	q->ptr[i]->parent = (*ap);
	q->ptr[i] = NULL;
}
static inline void createNewRoot(BTree* T, BTree q, KeyType x,Record *rec, BTree ap)
{
	q = (*T);
	*T = malloc(sizeof(BTNode));
	if (!(*T))
		exit(OVERFLOW);
	memset(*T, 0, sizeof(BTNode));
	(*T)->keynum = 1;
	(*T)->key[1] = x;
	(*T)->recptr[1] = rec;
	(*T)->ptr[0] = q;
	(*T)->ptr[1] = ap;
	if(q)
		q->parent = (*T);
	if(ap)
		ap->parent = (*T);
}

Status InsertBTree(BTree* T, KeyType K, Record* rec)
{
	KeyType x = K;
	BTree ap = NULL;
	Record* r = rec;

	int finished = FALSE;
	Result res = SearchBTree(*T,K);
	if (res.tag)
	{
		res.pt->recptr[res.index] = rec;
		return OK;
	}
	BTree q = res.pt;
	int i = res.index;
	int s = (BTREE_M % 2 == 0 ? BTREE_M / 2 : BTREE_M / 2 + 1);
	while (q&&!finished)
	{
		Insert(q, i, x, r,ap);
		if (q->keynum < BTREE_M)
			finished = TRUE;
		else {
			split(q, s, &ap);
			x = q->key[s];
			r = q->recptr[s];
			q->key[s] = 0;
			q->recptr[s] = NULL;
			q->keynum--;
			q = q->parent;
			if (q)
				i = Search(q, x);
		}

	}
	if (!finished)
		createNewRoot(T, q, x, r,ap);
	return OK;
}