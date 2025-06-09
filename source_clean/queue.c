#include "restaurant.h"

void initQueue(Queue *q) { q->F = q->R = -1; }
int isEmptyQueue(Queue *q) { return q->F == -1; }
int isFullQueue(Queue *q) { return q->R == MAX - 1; }

void enqueue(Queue *q) {
  if (isFullQueue(q)) {
    printf("Hang doi day\n");
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

  getCurrentTime(c.time, sizeof(c.time));
  if (isEmptyQueue(q))
    q->F = q->R = 0;
  else
    q->R++;
  q->data[q->R] = c;
  printf("Da them vao hang doi\n");
}

void dequeue(Queue *q) {
  if (isEmptyQueue(q)) {
    printf("Hang doi rong\n");
    return;
  }
  printf("Da xoa: %s\n", q->data[q->F].name);
  if (q->F == q->R)
    q->F = q->R = -1;
  else
    q->F++;
}

void displayQueue(Queue *q) {
  if (isEmptyQueue(q)) {
    printf("Khong co khach nao\n");
    return;
  }
  printf("Danh sach hang doi:\n");
  for (int i = q->F; i <= q->R; i++)
    printf("%d. %s | SDT: %s | Thoi gian: %s\n", i - q->F + 1, q->data[i].name,
           q->data[i].phone, q->data[i].time);
}
