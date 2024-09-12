#ifndef COUNTER_HANDLER_H
#define COUNTER_HANDLER_H

typedef int MenuSelection;

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

int HandleProcessSelection(InputArguments* arguments);

/**
 * @brief Handles the stop selection
 */
void HandleStopSelection(InputArguments* arguments);

void HandleContinueSelection(InputArguments* arguments);

void HandleChangeSelection(InputArguments* arguments);

void HandleKillSelection(InputArguments* arguments);

int AtleastOneAlive(InputArguments* arguments);

#endif  // COUNTER_HANDLER_H