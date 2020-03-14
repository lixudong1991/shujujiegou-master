#ifndef LINKLIST_TEST_H
#define LINKLIST_TEST_H
#include "head.h"


typedef struct LNode
{
	ElemType data;
	struct LNode *next;
}LNode,*LinkList;


//��ͷ�ڵ�ĵ��������������
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

//��ͷ�ڵ��˫������ѭ���������
//Status GetElem_DuL(DuLinkList L, int i, ElemType* e);�뵥��һ��
DuLinkList GetElemP_DuL(DuLinkList L, int i);
Status ListInsert_DuL(DuLinkList L, int i, ElemType e);
Status ListDelete_DuL(DuLinkList L, int i, ElemType* e);
#endif