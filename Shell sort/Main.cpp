#include <iostream>
#include <stdlib.h>	
#include <random>
#include <chrono>

int shellSort(int arr[], int n)
{
	for(int gap = n/2; gap > 0; gap /= 2)
	{
		for(int i = gap; i < n; i += 1)
		{
			int temp = arr[i];
			int j;
			for(j = i; j >= gap && arr[j - gap] > temp; j -= gap)
			{
				arr[j] = arr[j - gap];
			}
			arr[j] = temp;
		}
	}
	return 0;
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
	shellSort(numArray, arrSize);
	std::chrono::steady_clock::time_point timeStop(std::chrono::steady_clock::now());

	std::cout << "Time: " << std::chrono::duration_cast<std::chrono::duration<double, std::nano>>(timeStop - timeStart).count() << " ns" << std::endl;

	return 0;
}

