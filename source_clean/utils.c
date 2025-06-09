#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void clearScreen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}
