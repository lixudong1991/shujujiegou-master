#ifndef LINKLIST_TEST_H
#define LINKLIST_TEST_H
#include "head.h"


typedef struct LNode
{
	ElemType data;
	struct LNode *next;
}LNode,*LinkList;


//带头节点的单向线性链表操作
Status GetElem_L(LinkList L,int i,ElemType *e);
Status ListInsert_L(LinkList L, int i, ElemType e);
Status ListDelete_L(LinkList L, int i, ElemType* e);
void MergeList_L(LinkList La, LinkList Lb, LinkList *Lc);


typedef struct DuLNode
{
	ElemType data;
	struct DuLNode* prior;
	struct DuLNode* next;
}DuLNode, * DuLinkList;

//带头节点的双向线性循环链表操作
//Status GetElem_DuL(DuLinkList L, int i, ElemType* e);与单向一致
DuLinkList GetElemP_DuL(DuLinkList L, int i);
Status ListInsert_DuL(DuLinkList L, int i, ElemType e);
Status ListDelete_DuL(DuLinkList L, int i, ElemType* e);
#endif