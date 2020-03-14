#include "SqStack.h"

Status InitStack(SqStack* S)
{
	if (S != NULL)
	{
		S->base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
		if (!S->base) exit(OVERFLOW);
		S->top = S->base;
		S->stacksize = STACK_INIT_SIZE;
		return OK;
	}
	return ERROR;
}
Status GetTop(SqStack S, SElemType* e)
{
	if (S.top ==NULL|| S.top == S.base)
		return ERROR;
	if (e)
		*e = *(S.top - 1);
	return OK;
}
Status Push(SqStack* S, SElemType e)
{
	if (S != NULL)
	{
		if (S->top - S->base >= S->stacksize)
		{
			S->base = (SElemType*)malloc((S->stacksize + STACKINCREMENT) * sizeof(SElemType));
			if (!S->base) exit(OVERFLOW);
			S->top = S->base + S->stacksize;
			S->stacksize += STACKINCREMENT;
		}
		*S->top++ = e;
		return OK;
	}
	return ERROR;
}
Status Pop(SqStack* S, SElemType* e)
{
	if (S != NULL)
	{
		if (S->top == S->base)
			return ERROR;
		if(e)
		*e = *--S->top;
		return OK;
	}
	return ERROR;
}
int StackLength(SqStack S)
{
	return S.stacksize;
}
Status StackEmpty(SqStack S)
{
	return S.base == S.top;
}
Status ClearStack(SqStack* S)
{
	if (S != NULL)
	{
		S->top = S->base;
		return OK;
	}
	return ERROR;
}
Status DestoryStack(SqStack* S)
{
	if (S != NULL)
	{
		free(S->base);
		S->top = NULL;
		S->base = NULL;
		S->stacksize = 0;
		return OK;
	}
	return ERROR;
}