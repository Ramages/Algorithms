#include <iostream>
#include <stdlib.h>	
#include <random>
#include <chrono>

void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

int partition(int arr[], int low, int high)
{
	int pivot = arr[high];
	int i = (low - 1);

	for(int j = low; j <= high - 1; j++)
	{
		if(arr[j] <= pivot)
		{
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
	if(low < high)
	{
		int partIndx = partition(arr, low, high);

		quickSort(arr, low, partIndx - 1);
		quickSort(arr, partIndx + 1, high);
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
	quickSort(numArray, 0, arrSize - 1);
	std::chrono::steady_clock::time_point timeStop(std::chrono::steady_clock::now());

	std::cout << "Time: " << std::chrono::duration_cast<std::chrono::duration<double, std::nano>>(timeStop - timeStart).count() << " ns" << std::endl;

	return 0;
}

