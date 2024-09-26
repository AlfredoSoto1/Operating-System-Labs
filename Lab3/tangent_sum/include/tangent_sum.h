#ifndef TANGENT_SUM_H
#define TANGENT_SUM_H

#include "MyTime.h"

/**
 * @brief Definition of a partition's workload
 */
typedef struct PartitionWorkload {
  int start;
  int end;
  double* data;
  double result;
  unsigned int thread_num;
  MyTime time_taken;
} PartitionWorkload;

/**
 * @brief Stores the result of the workload
 */
typedef struct WorkloadResult {
  double computation_result;
  MyTime time_taken;
} WorkloadResult;

/**
 * @brief Prepares the workload to be delivered
 *
 * @param part_count number of partitions
 * @param data block of data in reference
 * @param data_length length of the block of data
 */
PartitionWorkload* PreparePW(int part_count, double* data, long data_length);

/**
 * @brief Processes partition workload initializing and starting each thread.
 *
 * @param param_count number of partitions
 * @param workload total workload from each partition
 */
void ProcessPartitionWorkload(int part_count, PartitionWorkload* workload);

/**
 * @brief Individial paritition that does the sum
 *
 * @param partition_workload
 * @return NULL
 */
void* PartitionSumWorkload(void* partition_workload);

/**
 * @brief Obtains the result of the partitions workload
 *
 * @param w_result stores the result
 * @param part_count partition count
 * @param workload total workload from each partition
 */
void ObtainResult(WorkloadResult* w_result, int part_count,
                  PartitionWorkload* workload);

#endif  // TANGENT_SUM_H
