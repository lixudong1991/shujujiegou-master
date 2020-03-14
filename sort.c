#include "sort.h"

static int partition(int* arr, int start, int end)
{
	int key = arr[end], j = start-1,tem=0;
	for (int i = start; i <= end - 1; i++)
	{
		if (arr[i] <= key)
		{
			++j;
			if (j != i)
			{
				tem = arr[i];
				arr[i] = arr[j];
				arr[j] = tem;
			}
		}
	}
	arr[end] = arr[++j];
	arr[j] = key;
	return j;
}
static void myqsort(int* arr, int start, int end)
{
	if (start >= end)
		return;
	int val = partition(arr, start, end);
	myqsort(arr, start, val - 1);
	myqsort(arr, val + 1, end);
}
void quicksort(int* arr, int len)
{
	myqsort(arr, 0, len - 1);
}
