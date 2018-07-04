#include "logger.h"

#include <time.h>
#include <stdio.h>

void serverLog(int level, const char* message, ...) {
  printf("LOG -- Level: %d, Message: %s", level, message);
  return;
}
