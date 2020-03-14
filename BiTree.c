#include "BiTree.h"
#include "SqStack.h"
#include <stdio.h>

Status CreateBiTree(BiTree* t)
{
	char ch;
	scanf("%c", &ch);
	if (ch == ' ') *t = NULL;
	else {
		if (!(*t = (BiTNode*)malloc(sizeof(BiTNode))))
			exit(OVERFLOW);
		(*t)->data = ch;
		CreateBiTree(&((*t)->lchild));
		CreateBiTree(&((*t)->rchild));
	}
	return OK;
}


Status PreOrderTraverse(BiTree t, VISIT visit)
{
	if (t)
	{
		if (visit(t->data))
			if (PreOrderTraverse(t->lchild, visit))
				if (PreOrderTraverse(t->rchild, visit))
					return OK;
		return ERROR;
	}
	else
		return OK;
}

Status InOrderTraverse(BiTree t, VISIT visit)
{
	if (t)
	{
		if (InOrderTraverse(t->lchild, visit))
			if (visit(t->data))
				if (InOrderTraverse(t->rchild, visit))
					return OK;
		return ERROR;
	}
	else
		return OK;
}
Status InOrderTraverse_I(BiTree t, VISIT visit)
{
	if (!t)
		return ERROR;
	SqStack S;
	InitStack(&S);
	Push(&S, t);
	BiTree p = NULL;
	while (!StackEmpty(S))
	{
		while (GetTop(S, &p) && p)
			Push(&S, p->lchild);
		Pop(&S, &p);
		if (!StackEmpty(S))
		{
			Pop(&S, &p);
			if (!visit(p->data)) return ERROR;
			Push(&S, p->rchild);
		}
	}
	DestoryStack(&S);
	return OK;
}
Status InOrderTraverse_II(BiTree t, VISIT visit)
{
	if (!t)
		return ERROR;
	SqStack S;
	InitStack(&S);
	BiTree p = t;
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
Status PostOrderTraverse(BiTree t, VISIT visit)
{
	if (t)
	{
		if (PostOrderTraverse(t->lchild, visit))
			if (PostOrderTraverse(t->rchild, visit))
				if (visit(t->data))
					return OK;
		return ERROR;
	}
	else
		return OK;
}


Status LevelOrderTraverse(BiTree t, VISIT visit)
{
	return OK;
}

static BiThrTree pre = NULL;
static void InThreading(BiThrTree p)
{
	
	if (p)
	{
		InThreading(p->lchild);
		if (!p->lchild)
		{
			p->LTag = Thr;
			p->lchild = pre;
		}
		if (!pre->rchild)
		{
			pre->RTag = Thr;
			pre->rchild = p;
		}
		pre = p;
		InThreading(p->rchild);
	}
}
Status InOrderThreading(BiThrTree* thr, BiThrTree t)
{
	if (!(*thr = (BiThrTree)malloc(sizeof(BiThrNode))))
		exit(OVERFLOW);
	(*thr)->LTag = Link;
	(*thr)->RTag = Thr;
	(*thr)->rchild = *thr;
	if(!t)
		(*thr)->lchild = *thr;
	else {
		(*thr)->lchild = t;
		pre = *thr;
		InThreading(t);
		pre->rchild = *thr;
		pre->RTag = Thr;
		(*thr)->rchild = pre;
	}
	return OK;
}
Status InOrderTraverse_Thr(BiThrTree t, VISIT visit)
{
	BiThrTree p = t->lchild;
	while (p != t)
	{
		while (p->LTag == Link)
			p = p->lchild;
		if (!visit(p->data)) return ERROR;
		while (p->RTag == Thr && p->rchild != t)
		{
			p = p->rchild;
			if (!visit(p->data))
				return ERROR;
		}
		p = p->rchild;
	}
	return OK;
}
static void findMinNode(HuffmanTree HT,int end,int *l,int *r)
{
	unsigned int w1 =0xffffffff,w2= 0xffffffff;
	for (int i=1;i<=end;i++)
	{
		if ((HT+i)->parent==0)
		{
			if (w1>(HT + i)->weight)
			{
				*r = *l;
				*l = i;
				w2 = w1;
				w1 = (HT + i)->weight;
			}
			else if (w2> (HT + i)->weight)
			{
				*r = i;
				w2 = (HT + i)->weight;
			}
		}
	}
}
void HuffmanCoding(HuffmanTree* HT, HuffmanCode* HC, unsigned int* w, unsigned int n)
{
	if (n <=1||w==NULL)
		return;
	unsigned int treeSize = 2 * n - 1;
	if (!(*HT = (HuffmanTree)malloc((treeSize + 1) * sizeof(HTNode))))
		exit(OVERFLOW);
	memset(*HT,0, (treeSize + 1) * sizeof(HTNode));
	unsigned int index = 1;
	
	for (;index<n+1;index++)
	{
		(*HT)[index].weight=w[index-1];
	}
	for (;index< treeSize + 1;index++)
	{
		unsigned int lc = 0, rc = 0;
		findMinNode((*HT), index - 1,&lc,&rc);
		(*HT)[index].lchild = lc;
		(*HT)[index].rchild = rc;
		(*HT)[index].weight = (*HT)[lc].weight+ (*HT)[rc].weight;
		(*HT)[lc].parent = index;
		(*HT)[rc].parent = index;
	}
	*HC = malloc((n)*sizeof(char*));
	char* cd = malloc(n*sizeof(char));
	cd[n - 1] = '\0';
	unsigned int start;
	for (index=1;index<n+1;index++)
	{
		start = n-1;
		for (int i= index,j= (*HT)[index].parent;j!=0;i= j,j= (*HT)[j].parent)
		{
			if ((*HT)[j].lchild==i)
				cd[--start] = '0';
			else
				cd[--start] = '1';		
		}
		(*HC)[index - 1] = malloc((n - start)*sizeof(char));
		memcpy((*HC)[index - 1], cd+start, n - start);
	}
	free(cd);
}
