#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ORDER 100
#define MAX_NAME_LEN 100
#define MAX 50

// ======================== Struct định nghĩa ========================

typedef struct Table {
  int tableNumber;
  int status; // 0: Available, 1: Occupied
  char customerName[MAX_NAME_LEN];
  char orderDetails[MAX_ORDER][MAX_NAME_LEN];
  struct Table *next;
} Table;

typedef struct {
  char name[50];
  char phone[15];
  char time[30];
} Customer;

typedef struct {
  Customer data[MAX];
  int F, R;
} Queue;

typedef struct {
  Customer list[MAX];
  int count;
} List;

// ======================== Thời gian ========================
void getCurrentTime(char *buffer, int size) {
  time_t now = time(NULL);
  struct tm *t = localtime(&now);
  strftime(buffer, size, "%d/%m/%Y %H:%M:%S", t);
}

// ======================== Quản lý bàn ========================
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
    printf("Không tìm thấy bàn!\n");
    return;
  }
  if (temp->status == 1) {
    printf("Bàn đã được đặt.\n");
    return;
  }
  temp->status = 1;
  char name[MAX_NAME_LEN], order[MAX_NAME_LEN];
  int i = 0;

  printf("Nhập tên khách: ");
  scanf("%s", name);
  strcpy(temp->customerName, name);

  printf("Nhập món ăn (gõ X để kết thúc):\n");
  while (1) {
    scanf("%s", order);
    if (strcmp(order, "X") == 0 || strcmp(order, "x") == 0)
      break;
    if (i < MAX_ORDER) {
      strcpy(temp->orderDetails[i], order);
      i++;
    } else {
      printf("Danh sách món đầy!\n");
      break;
    }
  }
  for (int j = i; j < MAX_ORDER; ++j)
    strcpy(temp->orderDetails[j], "");
}

void show_Table(Table *table) {
  if (table == NULL) {
    printf("Không có bàn nào.\n");
    return;
  }
  while (table != NULL) {
    printf("Bàn số: %d - %s\n", table->tableNumber,
           table->status == 0 ? "Trống" : "Đã đặt");
    if (table->status == 1) {
      printf("  Khách: %s\n  Gọi món: ", table->customerName);
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

// ======================== Hàng đợi ========================
void initQueue(Queue *q) { q->F = q->R = -1; }
int isEmptyQueue(Queue *q) { return q->F == -1; }
int isFullQueue(Queue *q) { return q->R == MAX - 1; }

void enqueue(Queue *q) {
  if (isFullQueue(q)) {
    printf("Hàng đợi đầy.\n");
    return;
  }
  Customer c;
  printf("Tên KH: ");
  getchar();
  fgets(c.name, sizeof(c.name), stdin);
  c.name[strcspn(c.name, "\n")] = '\0';

  printf("SĐT: ");
  fgets(c.phone, sizeof(c.phone), stdin);
  c.phone[strcspn(c.phone, "\n")] = '\0';

  getCurrentTime(c.time, sizeof(c.time));
  if (isEmptyQueue(q))
    q->F = q->R = 0;
  else
    q->R++;
  q->data[q->R] = c;
  printf("✅ Đã thêm vào hàng đợi.\n");
}

void dequeue(Queue *q) {
  if (isEmptyQueue(q)) {
    printf("Hàng đợi rỗng.\n");
    return;
  }
  printf("🗑️ Đã xoá: %s\n", q->data[q->F].name);
  if (q->F == q->R)
    q->F = q->R = -1;
  else
    q->F++;
}

void displayQueue(Queue *q) {
  if (isEmptyQueue(q)) {
    printf("Không có khách nào.\n");
    return;
  }
  printf("📋 Danh sách hàng đợi:\n");
  for (int i = q->F; i <= q->R; i++)
    printf("%d. %s | SĐT: %s | Thời gian: %s\n", i - q->F + 1, q->data[i].name,
           q->data[i].phone, q->data[i].time);
}

// ======================== Danh sách đơn giản ========================
void addToList(List *l, Customer c) {
  if (l->count >= MAX) {
    printf("Danh sách đầy.\n");
    return;
  }
  l->list[l->count++] = c;
}

void displayList(List *l, const char *title) {
  if (l->count == 0) {
    printf("Không có KH trong %s.\n", title);
    return;
  }
  printf("📋 %s:\n", title);
  for (int i = 0; i < l->count; i++)
    printf("%d. %s | SĐT: %s | Thời gian: %s\n", i + 1, l->list[i].name,
           l->list[i].phone, l->list[i].time);
}

void addScheduledCustomer(List *l) {
  if (l->count >= MAX) {
    printf("Danh sách đầy.\n");
    return;
  }
  Customer c;
  printf("Tên KH: ");
  getchar();
  fgets(c.name, sizeof(c.name), stdin);
  c.name[strcspn(c.name, "\n")] = '\0';
  printf("SĐT: ");
  fgets(c.phone, sizeof(c.phone), stdin);
  c.phone[strcspn(c.phone, "\n")] = '\0';
  printf("Thời gian hẹn (vd: 19:00): ");
  fgets(c.time, sizeof(c.time), stdin);
  c.time[strcspn(c.time, "\n")] = '\0';
  l->list[l->count++] = c;
  printf("✅ Đã thêm khách hẹn giờ.\n");
}

void moveToDiningList(Queue *q, List *diningList) {
  if (isEmptyQueue(q)) {
    printf("Không có khách trong hàng chờ.\n");
    return;
  }
  Customer c = q->data[q->F];
  getCurrentTime(c.time, sizeof(c.time));
  addToList(diningList, c);
  dequeue(q);
  printf("✅ Đã chuyển khách sang 'Đang dùng bữa'.\n");
}

// ======================== Main ========================
int main() {
  Queue waitingQueue;
  List diningList = {.count = 0};
  List scheduledList = {.count = 0};
  Table *tableList;
  initQueue(&waitingQueue);
  init_Table(&tableList);

  // Thêm một số bàn sẵn
  add_Table(&tableList, 1, 0);
  add_Table(&tableList, 2, 0);

  int choice;
  do {
    printf("\n===== MENU CHÍNH =====\n");
    printf("1. Thêm khách vào hàng chờ\n");
    printf("2. Hiển thị hàng chờ\n");
    printf("3. Xoá khách đầu hàng chờ\n");
    printf("4. Chuyển khách sang 'Đang dùng bữa'\n");
    printf("5. Thêm khách hẹn giờ\n");
    printf("6. Hiển thị khách hẹn giờ\n");
    printf("7. Hiển thị bàn\n");
    printf("8. Đặt bàn\n");
    printf("0. Thoát\n");
    printf("Chọn: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      enqueue(&waitingQueue);
      break;
    case 2:
      displayQueue(&waitingQueue);
      break;
    case 3:
      dequeue(&waitingQueue);
      break;
    case 4:
      moveToDiningList(&waitingQueue, &diningList);
      break;
    case 5:
      addScheduledCustomer(&scheduledList);
      break;
    case 6:
      displayList(&scheduledList, "khách hẹn giờ");
      break;
    case 7:
      show_Table(tableList);
      break;
    case 8: {
      int num;
      printf("Nhập số bàn muốn đặt: ");
      scanf("%d", &num);
      book_NewTable(&tableList, num);
      break;
    }
    case 0:
      printf("Tạm biệt!\n");
      break;
    default:
      printf("Lựa chọn không hợp lệ!\n");
    }
  } while (choice != 0);

  free_TableList(&tableList);
  return 0;
}
  