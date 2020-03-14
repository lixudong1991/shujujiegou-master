#include "Mystr.h"
int  IndexStr(char* str1, const char* str2)
{
	int size = strlen(str1);
	for (int index = 0; index < size; index++)
	{
		char* p1 = str1 + index;
		char* p2 = str2;
		while (*p1 != '\0' && (*p1) == (*p2))
		{
			p1++;
			p2++;
			if (*p2 == '\0')
				return index;
		}

	}
	return -1;
}
int  IndexStr1(char* str1, const char* str2)
{
	int size = strlen(str1);
	int size1 = strlen(str2);
	int i = 0, j = 0;
	while (i < size && j < size1)
	{
		if (str1[i] == str2[j])
		{
			++i;
			++j;
		}
		else {
			i = i - j + 1;
			j = 0;
		}
	}
	if (j == size1) return i - size1;
	return -1;
}
static void getnext_KMP(const char *dest,int next[],int len)
{
	int i = 0, j = -1;
	next[0] = j;
	while (i<len-1)
	{
		if (j==-1||dest[i]==dest[j])
		{
			++i; 
			++j;
			if (dest[i] != dest[j])
			{
				next[i] = j;
			}
			else 
				next[i] = next[j];	
		}
		else
			j = next[j];
	}
}
int IndexStr_KMP(char* str, const char* dest)
{
	int len = strlen(dest);
	int *next= malloc(len *sizeof(int));
	memset(next, 0, len * sizeof(int));
	getnext_KMP(dest, next, len);
	int size1 = strlen(str);
	int i = 0, j = 0;
	while (i < size1 && j < len)
	{
		if (j==-1||str[i] == dest[j])
		{
			++i;
			++j;
		}
		else {
			j =next[j];
		}
	}

	free(next);

	if (j == len) return i - len;

	return -1;
}