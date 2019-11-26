/* Bobitan Denisa-Ioana

   Task:

   Implement efficiently 3 direct sorting methods (Bubble Sort, Insertion Sort, Selection Sort).
   Compare them.

   Observations: 

   In the best case, there are no assignments for the bubble sort implementation, because no swap is made.
   In the comaprisons graph, the line representing bubble sort and the one representing insertion sort are the same. They have a slight increase, although they seem constant (because of the small values represented).
   The total operations graph does not display the bubble sort line and the one representing insertion sort seems a constant value, also because of the small values.

   In the worst case, the assignments graph shows all the sorting methods.
   The comparisons graph does not allow the line representing the insertion sort to show, because it has similar values to the ones of the selection sort line.
   The graph showing the total operations draws all 3 lines.

   In the average case, the assignments results for selection sort seem continuous, because of their small values.
   The total operations graph shows that the insetion sort and the selection sort results are very similar.

   Conclusions:

   From the graphs and the tables created, using the Profiler, we can conclude that bubble sort is the least efficient sorting method in all 3 cases (shown by its fast increase).
   The other 2 methods look like they have similar performance over all. Some variations appear in the exceptional cases (best and worst), where selection sort seems the least efficient of these 3 (in the best case). 

*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>
#include "Profiler.h"

#define MAX_SIZE 2000
int assignBS, assignIS, assignSS, compBS, compIS, compSS;

Profiler profiler("Best Case");

void BubbleSort(int n, int a[])
{
	int aux;
	bool ok=true;
	while (ok) //while swap is done
	{
		ok = false;
		for (int j = 0; j < n-1; j++)
		{
			profiler.countOperation("C_bubble_sort", n);
			compBS++;
			if (a[j] > a[j+1])
			{
				//swap
				aux = a[j];
				a[j] = a[j+1];
				a[j+1] = aux;
				profiler.countOperation("A_bubble_sort", n, 3);
				assignBS += 3;
				ok = true;
			}
		}
	}
}

void InsertionSort(int n, int a[])
{
	int buff, j;
	for (int i = 1; i < n; i++)
	{
		buff = a[i];
		profiler.countOperation("A_insertion_sort", n);
		assignIS++;
		j = i - 1;
		while (j >= 0 && a[j] > buff)
		{
			profiler.countOperation("C_insertion_sort", n);
			compIS++;
			a[j + 1] = a[j];
			profiler.countOperation("A_insertion_sort", n);
			assignIS++;
			j--;
		}
		profiler.countOperation("C_insertion_sort", n);
		compIS++;
		a[j + 1] = buff;
		profiler.countOperation("A_insertion_sort", n);
		assignIS++;
	}
}

void SelectionSort(int n, int a[])
{
	int aux, b;
	for (int i = 0; i < n - 1; i++)
	{
		aux = i;
		for (int j = i + 1; j < n; j++)
		{
			profiler.countOperation("C_selection_sort", n);
			compSS++;;
			if (a[j] < a[aux])
			{
				aux = j;
			}
		}
		b = a[i];
		a[i] = a[aux];
		a[aux] = b;
		profiler.countOperation("A_selection_sort", n, 3);
		assignSS += 3;
	} 
}

void printArray(int *arr, int n, FILE *f)
{
	for (int i = 0; i < n; i++)
	{
		fprintf(f, "%d ", arr[i]);
	}
	fprintf(f, "\n");
}

int main()
{	
	
	/* //test
	int n, x[20], y[20];
	
	FILE *f = fopen("output.txt", "w");

	printf("Insert the number of elements: ");
	scanf("%d", &n);
	printf("Insert the array: ");
	for (int i = 0; i < n; i++)
		scanf("%d", &y[i]);

	CopyArray(x, y, n);
	BubbleSort(n, x);
	fprintf(f, "Sirul sortat cu BUBBLE SORT: ");
	printArray(x, n, f);

	CopyArray(x, y, n);
	SelectionSort(n, x);
	fprintf(f, "Sirul sortat cu SELECTION SORT: ");
	printArray(x, n, f);

	CopyArray(x, y, n);
	InsertionSort(n, x);
	fprintf(f, "Sirul sortat cu INSERTION SORT: ");
	printArray(x, n, f);

	fprintf(f, "\n");

	*/

	//for the best case scenario, when the arrays are already sorted increasingly

	int a[MAX_SIZE], v[MAX_SIZE];

	FillRandomArray(a, MAX_SIZE, 10, 50000, true, 1);
	
	for (int i = 100; i < MAX_SIZE; i += 100)
	{
		CopyArray(v, a, i);
		printf("%d bub\n", i);
		BubbleSort(i, v);

		CopyArray(v, a, i);
		printf("%d ins\n", i);
		InsertionSort(i, v);

		CopyArray(v, a, i);
		printf("%d sel\n", i);
		SelectionSort(i, v);
	}

	profiler.createGroup("Assignments", "A_insertion_sort", "A_selection_sort");
	profiler.createGroup("Comparisons", "C_bubble_sort", "C_insertion_sort", "C_selection_sort");
	profiler.addSeries("Insertion Sort", "A_insertion_sort", "C_insertion_sort");
	profiler.addSeries("Selection Sort", "A_selection_sort", "C_selection_sort");
	profiler.createGroup("Operations", "C_bubble_sort", "Insertion Sort", "Selection Sort");
	profiler.createGroup("Comparisons_bs", "C_bubble_sort");
	profiler.createGroup("Comparisons_ss", "C_selection_sort");
	profiler.createGroup("Comaprisons_is", "C_insertion_sort");
	profiler.createGroup("TotalOp_bs", "C_bubble_sort");
	profiler.createGroup("TotalOp_is", "Insertion Sort");
	profiler.createGroup("TotalOp_ss", "Selection Sort");



	//for the worst case scenario, when the arrays are sorted decreasingly

	profiler.reset("Worst Case");

	FillRandomArray(a, MAX_SIZE, 10, 50000, true, 2);

	for (int i = 100; i < MAX_SIZE; i += 100)
	{
		CopyArray(v, a, MAX_SIZE);
		printf("%d bub\n", i);
		BubbleSort(i, v);

		CopyArray(v, a, MAX_SIZE);
		printf("%d ins\n", i);
		InsertionSort(i, v);

		CopyArray(v, a, MAX_SIZE);
		printf("%d sel\n", i);
		SelectionSort(i, v);
	}

	profiler.addSeries("Bubble Sort", "A_bubble_sort", "C_bubble_sort");
	profiler.addSeries("Insertion Sort", "A_insertion_sort", "C_insertion_sort");
	profiler.addSeries("Selection Sort", "A_selection_sort", "C_selection_sort");

	profiler.createGroup("Assignments", "A_bubble_sort", "A_insertion_sort", "A_selection_sort");
	profiler.createGroup("Comparisons", "C_bubble_sort", "C_insertion_sort", "C_selection_sort");
	profiler.createGroup("Operations", "Bubble Sort", "Insertion Sort", "Selection Sort");
	profiler.createGroup("Assignments_bs", "A_bubble_sort");
	profiler.createGroup("Assignments_ss", "A_selection_sort");
	profiler.createGroup("Assignments_is", "A_insertion_sort");
	profiler.createGroup("Comparisons_bs", "C_bubble_sort");
	profiler.createGroup("Comparisons_ss", "C_selection_sort");
	profiler.createGroup("Comparisons_is", "C_insertion_sort");


	//for average cases, we use random generated arrays - the elements are not sorted in any specific way

	profiler.reset("Average Case");

	for (int j = 100; j < MAX_SIZE; j += 100) //the array length
	{
		assignBS = assignIS = assignSS = compBS = compIS = compSS = 0; //global variables to keep track of operations (assignments & comparisons)
		//we have to initialize them for each length j

		for (int i = 0; i < 5; i++) //to generate 5 arrays
		{
			FillRandomArray(a, j, 10, 50000, true, 0);

			CopyArray(v, a, MAX_SIZE);
			printf("%d bub\n", j);
			BubbleSort(j, v);

			CopyArray(v, a, MAX_SIZE);
			printf("%d ins\n", j);
			InsertionSort(j, v);

			CopyArray(v, a, MAX_SIZE);
			printf("%d sel\n", j);
			SelectionSort(j, v);
		}

		assignBS /= 5;
		compBS /= 5;

		assignIS /= 5;
		compIS /= 5;

		assignSS /= 5;
		compSS /= 5;

		int totalOpBS = assignBS + compBS;
		int totalOpIS = assignIS + compIS;
		int totalOpSS = assignSS + compSS;

		profiler.countOperation("A_avg_bs", j, assignBS);
		profiler.countOperation("C_avg_bs", j, compBS);
		profiler.countOperation("T_avg_bs", j, totalOpBS);

		profiler.countOperation("A_avg_is", j, assignIS);
		profiler.countOperation("C_avg_is", j, compIS);
		profiler.countOperation("T_avg_is", j, totalOpIS);

		profiler.countOperation("A_avg_ss", j, assignSS);
		profiler.countOperation("C_avg_ss", j, compSS);
		profiler.countOperation("T_avg_ss", j, totalOpSS);
	}

	profiler.createGroup("Assignments", "A_avg_bs", "A_avg_is", "A_avg_ss");
	profiler.createGroup("Comparisons", "C_avg_bs", "C_avg_is", "C_avg_ss");
	profiler.createGroup("Operations", "T_avg_bs", "T_avg_is", "T_avg_ss");
	profiler.createGroup("Assignments_bs", "A_avg_bs");
	profiler.createGroup("Assignments_ss", "A_avg_ss");
	profiler.createGroup("Assignments_is", "A_avg_is");
	profiler.createGroup("Comparisons_bs", "C_avg_bs");
	profiler.createGroup("Comparisons_ss", "C_avg_ss");
	profiler.createGroup("Comparisons_is", "C_avg_is");

	profiler.showReport();


	return 0;
}