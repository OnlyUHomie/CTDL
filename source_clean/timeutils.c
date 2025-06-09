#include "restaurant.h"

void getCurrentTime(char *buffer, int size) {
  time_t now = time(NULL);
  struct tm *t = localtime(&now);
  strftime(buffer, size, "%d/%m/%Y %H:%M:%S", t);
}