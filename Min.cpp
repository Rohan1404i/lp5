#include <iostream>
#include <vector>
#include <omp.h>
#include <climits>

#include <ctime>
#include <chrono>
#include <cstdlib>

using namespace std;
void generate_random_input(vector<int>& arr, int n)
{
    for (int i = 0; i < n; ++i)
    {
        arr.push_back(rand() % 1000);
    }
    for (int i = 0; i < n; ++i)
    {
      cout<<arr[i]<<" ";
    }
    cout<<endl;
}


void min_seq(const vector<int>& arr) {
  int min_value = INT_MAX;
  for (int i = 0; i < arr.size(); i++)
  {
    if (arr[i] < min_value)
    {
      min_value = arr[i];
    }
  }
  cout << "Sequential Minimum value: " << min_value << endl;
}

void min_reduction(vector<int>& arr) {
  int min_value = INT_MAX;
  #pragma omp parallel for reduction(min: min_value)
  for (int i = 0; i < arr.size(); i++) {
    if (arr[i] < min_value) {
      min_value = arr[i];
    }
  }
  cout << "Minimum value: " << min_value << endl;
}

int main() {
  int n;
  cout << "Enter the number of elements: ";
  cin >> n;

  vector<int> arr;
  generate_random_input(arr, n);

// Parallel reductions
  clock_t start_time = std::clock();
  min_reduction(arr);
  clock_t end_time = std::clock();
  double parallel_time = double(end_time - start_time) / CLOCKS_PER_SEC;
  cout << "Time taken for parallel reductions: " << parallel_time << " seconds" << endl;
  cout<<endl;

  // Sequential reductions
  start_time = std::clock();
  min_seq(arr);
  end_time = std::clock();
  double sequential_time = double(end_time - start_time) / CLOCKS_PER_SEC;
  cout << "Time taken for sequential reductions: " << sequential_time << " seconds" << endl;

  return 0;
}