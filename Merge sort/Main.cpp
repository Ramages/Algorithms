#include <iostream>
#include <stdlib.h>	
#include <random>
#include <chrono>

void merge(int arr[], int left, int mid, int right)
{
	int i, j, k;
	int node1 = mid - left + 1;
	int node2 = right - mid;

	int LNode[node1], RNode[node2];

	for(i = 0; i < node1; i++)
	{
		LNode[i] = arr[left + i];
	}

	for(j = 0; j < node2; j++)
	{
		RNode[j] = arr[mid + 1 + j];
	}

	i = 0;
	j = 0;
	k = left;

	while(i < node1 && j < node2)
	{
		if(LNode[i] <= RNode[j])
		{
			arr[k] = LNode[i];
			i++;
		}
		else
		{
			arr[k] = RNode[j];
			j++;
		}
		k++;
	}

	while(i < node1)
	{
		arr[k] = LNode[i];
		i++;
		k++;
	}

	while(j < node2)
	{
		arr[k] = RNode[j];
		j++;
		k++;
	}
}

void mergeSort(int arr[], int left, int right)
{
	if(left < right)
	{
		int mid = left + (right - left) / 2;

		mergeSort(arr, left, mid);
		mergeSort(arr, mid + 1, right);

		merge(arr, left, mid, right);
	}
}

void printArray(int arr[], int n)
{
	for(int i = 0; i < n; i++)
	{
		std::cout << arr[i] << ", ";
	}
	std::cout << std::endl;
}

int main()
{
	int numArray[10];

	for(int i = 0; i < 10; i++)
	{
		numArray[i] = rand() % 100;
	}

	int arrSize = sizeof(numArray)/sizeof(numArray[0]);

	std::chrono::steady_clock::time_point timeStart(std::chrono::steady_clock::now());
	mergeSort(numArray, 0, (arrSize - 1));
	std::chrono::steady_clock::time_point timeStop(std::chrono::steady_clock::now());

	std::cout << "Time: " << std::chrono::duration_cast<std::chrono::duration<double, std::nano>>(timeStop - timeStart).count() << " ns" << std::endl;

	return 0;
}

