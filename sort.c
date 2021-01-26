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
	    int* buff = malloc(sizeof(int) * 2 * length), * buff1 = malloc(sizeof(int) * 2 * length), buff2 = NULL;
    int count, index, temp, tem, key, q = 1;
    buff[0] = 0;
    buff[1] = length - 1;
    while (q)
    {
        count = q;
        q = 0;
        for (int i = 0; i < count; i++)
        {
            temp = buff[i * 2 + 1];
            index = buff[i] - 1;
            key = arr[temp];
            for (int j = buff[i]; j < temp; j++)
            {
                if (arr[j] <= key)
                {
                    ++index;
                    if (index != j && arr[index] != key)
                    {
                        tem = arr[j];
                        arr[j] = arr[index];
                        arr[index] = tem;
                    }
                }
            }
            arr[temp] = arr[++index];
            arr[index] = key;
            if (buff[i] < index - 1)
            {
                buff1[q++] = buff[i];
                buff1[q++] = index - 1;
            }
            if (index + 1 < temp)
            {
                buff1[q++] = index + 1;
                buff1[q++] = temp;
            }
        }
        q /= 2;
        buff2 = buff;
        buff = buff1;
        buff1 = buff2;
    }
    free(buff1);
    free(buff);
}
