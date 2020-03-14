#include "listtest.h"
#include <stdlib.h>
Status InitList_Sq(SqList* L)
{
	if (L == NULL)
		return ERROR;
	L->elem = (ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if (!L->elem) exit(OVERFLOW);
	L->length = 0;
	L->listsize = LIST_INIT_SIZE;
	return OK;
}
Status ListInsert_Sq(SqList* L, int i, ElemType e)
{
	if(L==NULL)
		return ERROR;
	if (i<1 || i>L->length + 1) return ERROR;
	if (L->length >= L->listsize)
	{
		ElemType* newbase = (ElemType*)realloc(L->elem, (L->listsize + LISTINCREMENT) * sizeof(ElemType));
		if (!newbase) exit(OVERFLOW);
		L->elem = newbase;
		L->listsize += LISTINCREMENT;
	}
	ElemType* q = L->elem + (i - 1);
	for (ElemType* p = L->elem + (L->length - 1); p >= q; --p)
		*(p + 1) = *p;
	*q = e;
	++L->length;
	return OK;
}
Status ListDelete_Sq(SqList* L, int i, ElemType* e)
{
	if (L == NULL)
		return ERROR;
	if (i<1 || i>L->length ) return ERROR;
	ElemType* p= L->elem +(i-1);
	if (e != NULL) *e = *p;
	ElemType* q = L->elem + L->length - 1;
	for (p++; p <= q; ++p) *(p - 1) = *p;
	--L->length;
	return OK;
}