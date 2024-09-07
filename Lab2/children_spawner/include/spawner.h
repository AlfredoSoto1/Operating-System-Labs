
/**
 * @brief Spawns a new children using fork()
 *
 * @param *program
 * @return process id of the children spawned
 */
int SpawnChildren(const char* program);

/**
 * @brief Waits for all children spawned
 *
 * @param processes
 * @param process_count
 */
void WaitForChildren(int* processes, const unsigned int process_count);