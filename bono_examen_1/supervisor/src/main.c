#include "MyTimer.h"
#include "Supervisor.h"

int main() {
  // Create timer
  PrepareTimer();
  // Start the supervisor
  ProcessDriverSupervision();
  return 0;
}