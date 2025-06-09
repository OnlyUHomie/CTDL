#include "ui.h"
#include "restaurant.h"
#include "utils.h"
#include <conio.h> // Nếu dùng Windows
#include <stdio.h>

int menuGiaoDien(const char *options[], int optionCount) {
  int selection = 0;
  char key;

  do {
    clearScreen();
    printf("+----------------------------------------------------------+\n");
    printf("|~~~~~~~~~~~~~~~~~~ NHA HANG 9YOK MINIONS ~~~~~~~~~~~~~~~~~|\n");
    printf("+----------------------------------------------------------+\n\n");

    for (int i = 0; i < optionCount; ++i) {
      if (i == selection)
        printf(">> %s <<\n", options[i]);
      else
        printf("   %s\n", options[i]);
    }

    key = _getch();

    if (key == 72) // ↑
      selection = (selection - 1 + optionCount) % optionCount;
    else if (key == 80) // ↓
      selection = (selection + 1) % optionCount;
    else if (key == 13) // Enter
      break;

  } while (1);

  return selection;
}

void runUI() {
  Queue q;
  List scheduledList = {.count = 0};
  List diningList = {.count = 0};
  Table *tableList;

  initQueue(&q);
  init_Table(&tableList);

  const char *menu[] = {"1. Them khach vao hang doi",
                        "2. Them khach hen gio",
                        "3. Hien thi hang doi",
                        "4. Hien thi danh sach hen",
                        "5. Chuyen khach sang dang dung bua",
                        "6. Hien thi danh sach dang dung bua",
                        "7. Dat ban",
                        "8. Hien thi cac ban",
                        "9. Thoat"};
  int menuCount = sizeof(menu) / sizeof(menu[0]);

  while (1) {
    int choice = menuGiaoDien(menu, menuCount);
    clearScreen();

    switch (choice) {
    case 0:
      enqueue(&q);
      break;
    case 1:
      addScheduledCustomer(&scheduledList);
      break;
    case 2:
      displayQueue(&q);
      break;
    case 3:
      displayList(&scheduledList, "Danh sach khach hen");
      break;
    case 4:
      moveToDiningList(&q, &diningList);
      break;
    case 5:
      displayList(&diningList, "Dang dung bua");
      break;
    case 6: {
      int tableNum;
      printf("Nhap so ban can dat: ");
      scanf("%d", &tableNum);
      book_NewTable(&tableList, tableNum);
      break;
    }
    case 7:
      show_Table(tableList);
      break;
    case 8:
      free_TableList(&tableList);
      return;
    }

    printf("\nNhan phim bat ky de tiep tuc...");
    getchar();
    getchar();
  }
}
