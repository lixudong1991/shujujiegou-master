#ifndef LIST_TEST_H
#define LIST_TEST_H

#include "head.h"

#define LIST_INIT_SIZE 100
#define LISTINCREMENT   10



typedef struct
{
	ElemType* elem;
	int		length;
	int		listsize;
}SqList;

Status InitList_Sq(SqList* L);
Status ListInsert_Sq(SqList* L,int i,ElemType e);
Status ListDelete_Sq(SqList* L, int i, ElemType *e);

#endif
