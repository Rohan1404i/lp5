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

void average_seq(const vector<int>& arr) {
  int sum = 0;
  for (int i = 0; i < arr.size(); i++) {
    sum += arr[i];
  }
  cout << "Sequential Average: " << (double)sum / arr.size() << endl;
}

void average_reduction(vector<int>& arr) {
  int sum = 0;
  #pragma omp parallel for reduction(+: sum)
  for (int i = 0; i < arr.size(); i++) {
    sum += arr[i];
  }
  cout << "Average: " << (double)sum / arr.size() << endl;
}

int main() {
  int n;
  cout << "Enter the number of elements: ";
  cin >> n;

  vector<int> arr;
  generate_random_input(arr, n);
// Sequential reductions
  clock_t start_time = std::clock();
  average_seq(arr);
  clock_t end_time = std::clock();
  double sequential_time = double(end_time - start_time) / CLOCKS_PER_SEC;
  cout << "Time taken for sequential reductions: " << sequential_time << " seconds" << endl;
// Parallel reductions
  start_time = std::clock();
  average_reduction(arr);
  end_time = std::clock();
  double parallel_time = double(end_time - start_time) / CLOCKS_PER_SEC;
  cout << "Time taken for parallel reductions: " << parallel_time << " seconds" << endl;
  cout<<endl;



  return 0;
}