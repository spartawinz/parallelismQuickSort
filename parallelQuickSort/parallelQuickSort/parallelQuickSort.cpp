// parallelQuickSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <omp.h>
#include <time.h>

using namespace std;

vector<int> random_vector(size_t size);
void sort_median(std::vector<int>& arr, int first, int last);
int partitionB(int first, int last, std::vector<int>& arr);
void middle_quick_sort(int first, int last, std::vector<int>& arr);
void middle_quick_sort_wrapper(vector<int>& arr);


int main()
{
	vector<int> random1 = random_vector(1000000);
	int start = clock();
	middle_quick_sort_wrapper(random1);
	int result = clock() - start;
	
	cout << "The Algorithm took " << result / 1000 << " Seconds. \n";

	system("pause");

	return 0;
}

vector<int> random_vector(size_t size){
	vector<int> v1;
	for (int i = 0; i < size; i++)
		v1.push_back(rand() % size); //put a random number between 0 and size
	return v1;
}

void sort_median(std::vector<int>& arr, int first, int last){

	bool exchanges = true;
	int middle = (first + last) / 2;
	if (arr[first]>arr[middle])
		swap(arr[first], arr[middle]);
	if (arr[middle] > arr[last])
		swap(arr[middle], arr[last]);
	if (arr[first] > arr[middle])
		swap(arr[first], arr[middle]);


	//swap the middle with the left 
	swap(arr[middle], arr[first]);
}

int partitionB(int first, int last, std::vector<int>& arr) {
	// Start up and down at either end of the sequence.
	// The first table element is the pivot value.


	int up = first + 1;
	int down = last - 1;
	sort_median(arr, first, last - 1);
	int mid = first;
	do {
		while ((up != last - 1) && !(arr[mid] < arr[up])) {
			++up;
		}
		while (arr[mid] < arr[down]) {
			--down;
		}
		if (up < down) {
			// if up is to the left of down,
			swap(arr[up], arr[down]);
		}
	} while (up < down); // Repeat while up is left of down.

	swap(arr[mid], arr[down]);

	return down;
}

void middle_quick_sort(int first, int last, std::vector<int>& arr) {
	if (last - first > 1) {
		// There is data to be sorted.
		// Partition the table.
		int pivot = partitionB(first, last, arr);

		// Sort the left half.
#pragma omp sections
		{
	#pragma omp section
		
			middle_quick_sort(first, pivot, arr);

			// Sort the right half.
	#pragma omp section
			middle_quick_sort(pivot + 1, last, arr);
		}
	}
}

void middle_quick_sort_wrapper(vector<int>& arr){
	middle_quick_sort(0, arr.size(), arr);
}