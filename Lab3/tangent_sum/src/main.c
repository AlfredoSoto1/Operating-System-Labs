#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "tangent_sum.h"

#define WORKLOAD_P 5         // Workload partition count
#define DATA_LENGTH 1000000  // One million

int main() {
  // Initialize array of one million integers
  // Fill out the array from numbers of [1, 1000000]
  double* numbers = malloc(DATA_LENGTH * sizeof(double));

  for (int i = 0; i < DATA_LENGTH; i++) {
    numbers[i] = tan(i + 1.0);
  }

  // Prpeare the partition workload to where to distribute the workload to each
  // partition created.
  PartitionWorkload* workload = PreparePW(WORKLOAD_P, numbers, DATA_LENGTH);

  // Process each partition through each workload
  ProcessPartitionWorkload(WORKLOAD_P, workload);

  // Obtain the results from combining the results of each partition workload.
  WorkloadResult results;
  ObtainResult(&results, WORKLOAD_P, workload);

  printf("Total sum: %lf in %lldms collectively\n", results.computation_result,
         results.time_taken);

  free(workload);
  free(numbers);

  return 0;
}