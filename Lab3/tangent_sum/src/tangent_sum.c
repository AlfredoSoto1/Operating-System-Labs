#include "tangent_sum.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

PartitionWorkload* PreparePW(int part_count, double* data, long data_length) {
  PartitionWorkload* workload = malloc(sizeof(PartitionWorkload) * part_count);

  // Fill the partition workload structure with the required fields that tell
  // the workload from start to end which blocks of data to modify.
  for (int i = 0; i < part_count; i++) {
    workload[i].thread_num = i + 1;
    workload[i].data = data;
    workload[i].result = 0;

    workload[i].start = i * data_length / part_count;
    workload[i].end = (i + 1) * data_length / part_count;
  }

  return workload;
}

void ProcessPartitionWorkload(int part_count, PartitionWorkload* workload) {
  pthread_t* partitions = malloc(sizeof(pthread_t) * part_count);

  // Spawn and start threads
  for (int i = 0; i < part_count; i++) {
    pthread_create(&partitions[i], NULL, PartitionSumWorkload, &workload[i]);
  }

  // Wait for each thread to finish
  for (int i = 0; i < part_count; i++) {
    pthread_join(partitions[i], NULL);
  }

  free(partitions);
}

void* PartitionSumWorkload(void* partition_workload) {
  PartitionWorkload* workload = (PartitionWorkload*)partition_workload;

  MyTime start = CurrentTimeMillis();
  for (int i = workload->start; i < workload->end; i++) {
    workload->result += workload->data[i];
  }
  MyTime end = CurrentTimeMillis();

  workload->time_taken = end - start;

  // Provide debug feedback
  printf("Thread %d, lasted: %lldms\n", workload->thread_num, end - start);

  return NULL;
}

void ObtainResult(WorkloadResult* w_result, int part_count,
                  PartitionWorkload* workload) {
  MyTime total_time = 0;
  double total_sum = 0;

  // Collect sum of each sub process computation
  for (int i = 0; i < part_count; i++) {
    total_sum += workload[i].result;
    total_time += workload[i].time_taken;
  }

  w_result->time_taken = total_time;
  w_result->computation_result = total_sum;
}