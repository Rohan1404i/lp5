%%writefile Bubble.cpp


#include <iostream>
#include <omp.h>

using namespace std;

void sequentialBubbleSort(int *, int);
void parallelBubbleSort(int *, int);
void swap(int &, int &);

void sequentialBubbleSort(int *a, int n)
{
    int swapped;
    for (int i = 0; i < n; i++)
    {
        swapped = 0;
        for (int j = 0; j < n - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]);
                swapped = 1;
            }
        }

        if (!swapped)
            break;
    }
}

void parallelBubbleSort(int *a, int n)
{
    int swapped;
    for (int i = 0; i < n; i++)
    {
        swapped = 0;
        int first = i % 2;
        #pragma omp parallel for shared(a, first)
        for (int j = first; j < n - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]);
                swapped = 1;
            }
        }

        if (!swapped)
            break;
    }
}

void swap(int &a, int &b)
{
    int test;
    test = a;
    a = b;
    b = test;
}

int main()
{
    int *a, n;
    cout << "\nEnter total number of elements for bubble sort: ";
    cin >> n;
    a = new int[n];

    for (int i = 0; i < n; i++)
    {
        a[i] = rand() % 100; // Generate random numbers between 0 and 99
    }
    for (int i = 0; i < n; ++i){
      cout<<a[i]<<" ";
    }
    cout<<endl;


    // Perform sequential bubble sort
    double start_time = omp_get_wtime();
    sequentialBubbleSort(a, n);
    double end_time = omp_get_wtime();
    cout << "\nSorted array after sequential bubble sort:\n";
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    cout << "\nTime taken by sequential bubble sort: " << end_time - start_time << " seconds" << endl;

    // Perform parallel bubble sort
    start_time = omp_get_wtime();
    parallelBubbleSort(a, n);
    end_time = omp_get_wtime();
    cout << "\nSorted array after parallel bubble sort:\n";
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    cout << "\nTime taken by parallel bubble sort: " << end_time - start_time << " seconds" << endl;

    delete[] a; // Don't forget to free the allocated memory

    return 0;
}

!g++ Bubble.cpp -o Bubble -fopenmp
!./Bubble