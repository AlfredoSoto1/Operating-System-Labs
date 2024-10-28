#ifndef TASK_MEASURER_H
#define TASK_MEASURER_H

typedef struct {
  int samples;              // Number of samples
  int children;             // Number of children per sample
  int* priorities;          // Priorities assigned for each children.
  double* avrg_time_taken;  // Time taken for each child process in avrg
  long** child_time_taken;  // List of sample times for each child.
} ScheduleSampleTest;

void GenerateSamples(ScheduleSampleTest* test);

void FreeSamples(ScheduleSampleTest* test);

void HandleChildrenSample(ScheduleSampleTest* test, int sample);

void CpuBoundTask();

#endif  // TASK_MEASURER_H