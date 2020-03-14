#include "linklist.h"


Status GetElem_L(LinkList L, int i, ElemType* e)
{
	LinkList p = L->next;
	int j = 1;
	while (p&&j<i)
	{
		p = p->next;
		++j;
	}
	if (!p || j > i) return ERROR;
	if(e) *e = p->data;
	return OK;
}
Status ListInsert_L(LinkList L, int i, ElemType e)
{
	
	LinkList p = L;
	int j = 0;
	while (p && j < i-1)
	{
		p = p->next;
		++j;
	}
	if (!p || j > i-1) return ERROR;
	LinkList s = (LinkList)malloc(sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;
	return OK;
}
Status ListDelete_L(LinkList L, int i, ElemType* e)
{
	LinkList p = L;
	int j = 0;
	while (p->next && j < i - 1)
	{
		p = p->next;
		++j;
	}
	if (!(p->next) || j > i - 1) return ERROR;
	
	LinkList q = p->next;
	if (e) *e = q->data;
	p->next = q->next;
	free(q);
	return OK;
}
void MergeList_L(LinkList La, LinkList Lb, LinkList *Lc)
{
	LinkList pa = La->next;
	LinkList pb = Lb->next;
	LinkList pc;
	*Lc = pc = La;
	while (pa && pb)
	{
		if (pa->data <= pb->data)
		{
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		}
		else
		{
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
	}
	pc->next = pa?pa : pb;
	free(Lb);
	Lb = 0;
}
DuLinkList GetElemP_DuL(DuLinkList L, int i)
{
	DuLinkList p = L;
	int j = 0;
	while (p->next!= L && j < i -1)
	{
		p = p->next;
		++j;
	}
	if (p->next == L)
	{
		if(j!=i-1)
			return 0;
	}		
	return p->next;
}
Status ListInsert_DuL(DuLinkList L, int i, ElemType e)
{
	DuLinkList p = 0,s=0;
	if (!(p = GetElemP_DuL(L, i)))return ERROR;
	if (!(s = (DuLinkList)malloc(sizeof(DuLNode)))) return ERROR;
	s->data = e;
	s->prior = p->prior;
	p->prior->next = s;
	s->next = p;
	p->prior = s;
	return OK;
}
Status ListDelete_DuL(DuLinkList L, int i, ElemType* e)
{

}