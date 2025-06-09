#include "restaurant.h"

void addToList(List *l, Customer c) {
  if (l->count >= MAX) {
    printf("Danh sach day\n");
    return;
  }
  l->list[l->count++] = c;
}

void displayList(List *l, const char *title) {
  if (l->count == 0) {
    printf("Khong co KH trong %s\n", title);
    return;
  }
  printf("%s:\n", title);
  for (int i = 0; i < l->count; i++)
    printf("%d. %s | SDT: %s | Thoi gian: %s\n", i + 1, l->list[i].name,
           l->list[i].phone, l->list[i].time);
}

void addScheduledCustomer(List *l) {
  if (l->count >= MAX) {
    printf("Danh sach day\n");
    return;
  }
  Customer c;
  printf("Ten KH: ");
  getchar();
  fgets(c.name, sizeof(c.name), stdin);
  c.name[strcspn(c.name, "\n")] = '\0';
  printf("SDT: ");
  fgets(c.phone, sizeof(c.phone), stdin);
  c.phone[strcspn(c.phone, "\n")] = '\0';
  printf("Thoi gian hen (vd: 19:00): ");
  fgets(c.time, sizeof(c.time), stdin);
  c.time[strcspn(c.time, "\n")] = '\0';
  l->list[l->count++] = c;
  printf("Da them khach hen gio\n");
}

void moveToDiningList(Queue *q, List *diningList) {
  if (isEmptyQueue(q)) {
    printf("Khong co khach trong hang cho\n");
    return;
  }
  Customer c = q->data[q->F];
  getCurrentTime(c.time, sizeof(c.time));
  addToList(diningList, c);
  dequeue(q);
  printf("Khach hang %s dang dung bua\n", c.name);
}
