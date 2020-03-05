#include <iostream>
#include <stdlib.h>	
#include <random>
#include <chrono>

void insertionSort(int arr[], int n)
{
	int key, j;
	for(int i = 1; i < n; i++)
	{
		key = arr[i];
		j = i - 1;

		while(j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
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

	std::chrono::steady_clock::time_point timeStart(std::chrono::steady_clock::now());
	insertionSort(numArray, sizeof(numArray)/sizeof(numArray[0]));
	std::chrono::steady_clock::time_point timeStop(std::chrono::steady_clock::now());

	std::cout << "Time: " << std::chrono::duration_cast<std::chrono::duration<double, std::nano>>(timeStop - timeStart).count() << " ns" << std::endl;

	return 0;
}

