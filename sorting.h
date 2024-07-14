#pragma once
void BubbleSort(int A[], int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		int flag = 0;
		for (int j = 0; j < size - 1 - i; j++)
		{
			if (A[j] > A[j + 1])
			{
				int temp = A[j];
				A[j] = A[j + 1];
				A[j + 1] = A[j];
				flag = 1;
			}
		}

		if (flag == 0)//flag to break if the array is already sorted -- if the array is sorted, the swapping wont happen.
			break;
	}
}
void InsertionSort(int A[], int n)
{
	for (int i = 1; i < n; i++)
	{
		int j = i - 1;
		int x = A[i];

		while (j > -1 && A[j] > x)
		{
			A[j+1] = A[j];
			j--;
		}

		A[j+1] = x;
	}
}

void SelectionSort(int A[], int n)
{
	// index is selected for which you need to select the element appropriate element
	//i must point to the current index, k and j are incrementers, if (jth element is less than k, move k to jth position and increment j till end)
	//swap kth position with current i
	for (int i = 0; i < n-1; i++)
	{
		int k = i, j = i + 1;
		for (; j < n; j++)
		{
			if (A[k] > A[j])
			{
				k = j;
			}
		}

		int temp = A[k];
		A[k] = A[i];
		A[i] = temp;
	}
}

//Quick sort
int Partition(int A[], int l, int h)
{
	int pivot = A[l];
	int i = l, j = h;
	do
	{
		do { i++; } while (A[i] <= pivot);
		do { j--; } while (A[j] > pivot);

		if (i < j)
		{
			int temp = A[i];
			A[i] = A[j];
			A[j] = temp;
		}
	} while (i < j);

	int temp = A[l];
	A[l] = A[j];
	A[j] = temp;
	return j;
}

void QuickSort(int A[], int l, int h)
{
	if (l < h)
	{
		int j = Partition(A, l, h);
		QuickSort(A, l, j);
		QuickSort(A, j+1, h);
	}

	return;
}
void Merge(int A[], int l, int mid, int h)
{
	int i = l, j = mid+1, k = l;

	int B[100] = { 0 };
	while (i <= mid && j <= h)
	{
		if (A[i] < A[j])
			B[k++] = A[i++];
		else
			B[k++] = A[j++];
	}

	while (i <= mid) {
		B[k++] = A[i++];
	}
	while (j <= h) {
		B[k++] = A[j++];
	}


	for (int i = l; i <= h; i++) {
		A[i] = B[i];
	}
}

void IMergeSort(int A[], int n)
{
	int p = 0, l = 0, h = 0, mid = 0, i = 0;

	for (p = 2; p <= n; p = p * 2)
	{
		for (i = 0; i + p - 1 < n; i = i + p)
		{
			l = i;
			h = i + p - 1;
			mid = (l + h) / 2;

			Merge(A, l, mid, h);
		}
	}

	if (p / 2 < n)
		Merge(A, 0, (p / 2)-1, n);
}

//Google Jam Code contest - 2021. (Reversort) -- Sorting by reversing the array.
void Reversort(int A[], int n)
{
	int cost = 0;
	for (int i = 0; i < n - 1; i++)
	{
		int j = i+1;

		if (j >= n)
			continue;

		//Find the minimum element for the selected ith index
		while (j < n && A[j] > A[i])
		{
			j++;
		}

		cost = cost + (j - i + 1);
		//Reverse array
		int k = i;
		while (j < n && k < j)
		{
			int temp = A[k];
			A[k] = A[j];
			A[j] = temp;
			
			k++;
			j--;
		}
	}
}