#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
using namespace std;
using namespace std::chrono;

/*
Swaps two values in a vector, by-reference.
@ param A is a vector of integers. By-reference.
@ index1 and index2 are both integers, signifying the indices of the values being swapped.
*/
void swap(vector<int>& A, int index1, int index2) {
	int temp;
	temp = A.at(index1);
	A.at(index1) = A.at(index2);
	A.at(index2) = temp;
}

/*
Merges two sorted vectors together into one larger sorted vector.
@ param leftSide is the first vector of integers
@ param rightSide is the second vector of integers
*/
vector<int> merge(vector<int> leftSide, vector<int> rightSide) {
	int i = 0;
	int j = 0;
	int leftNum = leftSide.size() - 1;
	int rightNum = rightSide.size() - 1;
	vector<int> mergedVector;

	// Compare vector values and push the smallest to the merged vector
	// until one vector is exhausted. 
	while ((i <= leftNum) && (j <= rightNum)) {
		if (leftSide.at(i) <= rightSide.at(j)) {
			mergedVector.push_back(leftSide.at(i));
			i++;
		}
		else {
			mergedVector.push_back(rightSide.at(j));
			j++;
		}
	}


	// Push the non-depleted vector onto the merged vector when the other vector has been depleted
	if (i > leftNum) {
		while (j <= rightNum) {
			mergedVector.push_back(rightSide.at(j));
			j++;
		}
	}
	else {
		while (i <= leftNum) {
			mergedVector.push_back(leftSide.at(i));
			i++;
		}
	}

	return mergedVector;
}

/*
Uses Merge Sort divide and conquer method to sort an array of integers from smallest to largest.
@param A is the vector of integers that will be sorted.
@param L is an integer. It represents the index of the left-most integer in the array we are sorting.
@param R is an integer. It represents the index of the right-most integer in the array we are sorting.
@ Returns sorted version of the given vector of integers.
*/
vector<int> mergeSort(vector<int> A, int L, int R) {
	// Base case: Array does not have multiple elements
	if (L == R) {
		vector<int> oneValue = { A.at(L) };
		return oneValue;
	}
	else {
		int mid = (L + R) / 2;
		vector<int> leftSide = mergeSort(A, L, mid);
		vector<int> rightSide = mergeSort(A, mid + 1, R);
		return merge(leftSide, rightSide);
	}
}

/*
Sorts a vector of integers using the bubblesort method
@ param A is a vector of integers. By-reference.
*/
void bubbleSort(vector<int>& A) {
	for (int i = 1; i < A.size() - 1; i++) {
		for (int j = 0; j < A.size() - i; j++) {
			if (A[j] > A[j + 1]) {
				swap(A, j, j + 1);
			}
		}
	}
}

/*
In-place, divide-and-conquer, recursive sorting algorithm.
@ param A, by-reference, is a vector of integers which is being sorted.
@ param L is an integer. It is the leftmost index of the section of A which will be sorted. The pivot will equal this value.
@ param R is an integer. It is the rightmost index of the section of A which will be sorted.

*/
void quickSort(vector<int>& A, int L, int R) {
	// If the section being sorted has at least two entries
	if (L < R) {
		int pivot = L;
		int i = pivot + 1;
		int j = R;

		// Loop until i and j cross each other
		while (i < j) {

			// Increment i until it reaches the end of A or until it finds a value greater than the pivot value.
			while ((A.at(i) <= A.at(pivot)) && (i < R)) {
				i++;
			}

			// Decrement j until it reaches the pivot or until it finds a value less than the pivot value.
			while ((A.at(j) > A.at(pivot)) && (j > L)) {
				j--;
			}

			// Swap i and j if their values are not on their proper side of the pivot, and if they haven't yet crossed each other
			if ((A.at(i) > A.at(pivot)) && (A.at(j) <= A.at(pivot)) && (i < j)) {
				swap(A, i, j);
			}
		}
		// Swap the value of j after it crosses i with the pivot if they need to be swapped.
		if (A.at(j) < A.at(pivot)) {
			swap(A, pivot, j);
		}

		// Once the pivot is sorted, sort the array on both sides of the pivot.
		if (j != L) {
			quickSort(A, L, j - 1);
		}

		if (j != R) {
			quickSort(A, j + 1, R);
		}
	}
}

/*
Creates a vector of size s with random values, each ranging from 0 to 99
@ param int s is the size of the new vector
*/
vector<int> createRandomVector(int s) {
	vector<int> v;
	for (int i = 0; i < s; i++) {
		v.push_back(rand() % 10000000);
	}
	return v;
}

int main() {
	//Randomize seed
	srand(time(0));

	// Define variables
	vector<int> v1;
	vector<int> v2;
	vector<int> v1Sorted;
	vector<int> ascendingVector;
	vector<int> descendingVector;
	int size;

	// Fill vectors
	size = 10000;

	// Fill ascending vector
	for (int i = 0; i < size; i++) {
		ascendingVector.push_back(i);
	}

	// Fill descending vector
	for (int i = size - 1; i >= 0; i--) {
		descendingVector.push_back(i);
	}

	// Get average of many merge sorts
	/*int sum = 0;
	int trials = 500;
	for (int i = 0; i < trials; i++) {

		// Create vector
		v1 = ascendingVector;

		// Create timer
		auto start = high_resolution_clock::now();

		// Sort vector
		v1Sorted = mergeSort(v1, 0, v1.size() - 1);

		// Stop timer
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);
		sum += duration.count();

		// Display this cycle's duration
		cout << duration.count() << endl;
	}
	cout << endl << "Average execution time is " << sum / trials << " microseconds.";
	*/

	// Get average of many bubble sorts
	/*
	int sum = 0;
	int trials = 100;
	for (int i = 0; i < trials; i++) {

		// Create vector
		v1 = descendingVector;

		// Create timer
		auto start = high_resolution_clock::now();

		// Sort vector
		bubbleSort(v1);

		// Stop timer
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);
		sum += duration.count();

		// Display this cycle's duration
		cout << duration.count() << endl;
	}
	cout << endl << "Average execution time is " << sum / trials << " microseconds.";
	*/

	// Get average of many quick sorts
	/*
	int sum = 0;
	int trials = 10000;
	for (int i = 0; i < trials; i++) {

		// Create vector
		v1 = createRandomVector(size);

		// Create timer
		auto start = high_resolution_clock::now();

		// Sort vector
		quickSort(v1, 0, v1.size() - 1);

		// Stop timer
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);
		sum += duration.count();

		// Display this cycle's duration
		cout << duration.count() << endl;
	}
	cout << endl << "Average execution time is " << sum / trials << " microseconds.";
	*/
}