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

void mqsort(int arr[],int length)
{
	int *buff=malloc(sizeof(int)*2*length);
	int count=1,index,temp,tem,key;
	buff[0]=0;
	buff[1]=length-1;
	for(int i=0;i<count;i++)
	{
		temp=buff[i*2+1];
		if(buff[i]==temp)
			continue;
		index=buff[i]-1;
		key=arr[temp];
		for(int j=buff[i];j<temp;j++)
		{
			if(arr[j]<=key)
			{
				++index;
				if(index!=j&&arr[j]!=key)
				{
					tem=arr[j];
					arr[j]=arr[index];
					arr[index]=tem;
				}
			}
		}
		arr[temp]=arr[++index];
		arr[index]=key;
		
	}
		
}
