#include <iostream>
#include <stdlib.h>	
#include <random>
#include <chrono>

void heapify(int arr[], int n, int i)
{
	int root = i;
	int left = 2*i + 1;
	int right = 2*i + 2;

	if(left < n && arr[left] > arr[root])
	{
		root = left;
	}

	if(right < n && arr[right] > arr[root])
	{
		root = right;
	}

	if(root != i)
	{
		std::swap(arr[i], arr[root]);

		heapify(arr, n, root);
	}
}

void heapSort(int arr[], int n)
{
	for(int i = n / 2 - 1; i >= 0; i--)
	{
		heapify(arr, n, i);
	}

	for(int i = n - 1; i >= 0; i--)
	{
		std::swap(arr[0], arr[i]);

		heapify(arr, i, 0);
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
	int numArray[10000];

	for(int i = 0; i < 10000; i++)
	{
		numArray[i] = rand() % 100000;
	}

	std::chrono::steady_clock::time_point TimerStart(std::chrono::steady_clock::now());
	heapSort(numArray, 10000);
	std::chrono::steady_clock::time_point TimerStop(std::chrono::steady_clock::now());

	std::cout << "Time: " << std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(TimerStop - TimerStart).count() << " ms" << std::endl;

	return 0;
}

