#ifndef SUPERVISOR_H
#define SUPERVISOR_H

/**
 * @brief Get the Pid By Name object
 *
 * @param process_name
 * @return int
 */
int GetPidByName(const char* process_name);

/**
 * @brief Relaunches the IMU-Driver
 *
 */
void RelaunchImuDriver();

/**
 * @brief Supervices the driver every 1.5 seconds according to the timer.
 *
 */
void ProcessDriverSupervision();

/**
 * @brief Detaches the process to wait for it when it terminates asynchronously.
 *
 */
void DetachProcessWaiting();

/**
 * @brief Waits for the process to end in a separate thread.
 *
 * @param param
 * @return void*
 */
void* WaitForImuTermination(void* param);

#endif  // SUPERVISOR_H