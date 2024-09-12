#ifndef COUNTER_HANDLER_H
#define COUNTER_HANDLER_H

typedef int MenuSelection;

/**
 * @brief Contains the input arguments as a list of processes
 */
typedef struct InputArguments {
  int count;
  int* program_ids;
} InputArguments;

/**
 * @brief Enum of the selection that this program has
 */
enum Selection { STOP = 1, CONTINUE, CHANGE, KILL, EXIT };

/**
 * @brief Displays a small prompt for the user to choose from
 *
 * @return MenuSelection
 */
MenuSelection DisplayMenu();

/**
 * @brief Handles the process selection
 *
 * @param arguments
 */
int HandleProcessSelection(InputArguments* arguments);

/**
 * @brief Handles the stop selection
 *
 * @param arguments
 */
void HandleStopSelection(InputArguments* arguments);

/**
 * @brief Handles the continue selection
 *
 * @param arguments
 */
void HandleContinueSelection(InputArguments* arguments);

/**
 * @brief Hanbdles the change direction selection
 *
 * @param arguments
 */
void HandleChangeSelection(InputArguments* arguments);

/**
 * @brief Handles the killing of a process section
 *
 * @param arguments
 */
void HandleKillSelection(InputArguments* arguments);

/**
 * @brief Checks if any of the given processes are alive
 *
 * @return 1 if atleast one process is alive
 */
int AtleastOneAlive(InputArguments* arguments);

#endif  // COUNTER_HANDLER_H