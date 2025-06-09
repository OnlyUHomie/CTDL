#include "restaurant.h"

void init_Table(Table **table) { *table = NULL; }

void add_Table(Table **table, int tableNumber, int status) {
  Table *newTable = (Table *)malloc(sizeof(Table));
  newTable->tableNumber = tableNumber;
  newTable->status = status;
  strcpy(newTable->customerName, "");
  strcpy(newTable->orderDetails[0], "Empty");
  for (int i = 1; i < MAX_ORDER; ++i)
    strcpy(newTable->orderDetails[i], "");
  newTable->next = *table;
  *table = newTable;
}

Table *search_Table(Table *table, int tableNumber) {
  while (table != NULL) {
    if (table->tableNumber == tableNumber)
      return table;
    table = table->next;
  }
  return NULL;
}

void book_NewTable(Table **table, int num) {
  Table *temp = search_Table(*table, num);
  if (temp == NULL) {
    printf("Khong tim thay ban\n");
    return;
  }
  if (temp->status == 1) {
    printf("Ban da duoc dat\n");
    return;
  }
  temp->status = 1;
  char name[MAX_NAME_LEN], order[MAX_NAME_LEN];
  int i = 0;

  printf("Nhap ten khach: ");
  scanf("%s", name);
  strcpy(temp->customerName, name);

  printf("Nhap mon an (go X de ket thuc):\n");
  while (1) {
    scanf("%s", order);
    if (strcmp(order, "X") == 0 || strcmp(order, "x") == 0)
      break;
    if (i < MAX_ORDER) {
      strcpy(temp->orderDetails[i], order);
      i++;
    } else {
      printf("Danh sach mon day\n");
      break;
    }
  }
  for (int j = i; j < MAX_ORDER; ++j)
    strcpy(temp->orderDetails[j], "");
}

void show_Table(Table *table) {
  if (table == NULL) {
    printf("Khong co ban nao\n");
    return;
  }
  while (table != NULL) {
    printf("Ban so: %d - %s\n", table->tableNumber,
           table->status == 0 ? "Trong" : "Da dat");
    if (table->status == 1) {
      printf("  Khach: %s\n  Goi mon: ", table->customerName);
      for (int i = 0; i < MAX_ORDER && strlen(table->orderDetails[i]) > 0; ++i)
        printf("%s ", table->orderDetails[i]);
      printf("\n");
    }
    table = table->next;
  }
}

void free_TableList(Table **table) {
  while (*table != NULL) {
    Table *temp = *table;
    *table = (*table)->next;
    free(temp);
  }
}
