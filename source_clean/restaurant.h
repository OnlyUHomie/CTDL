#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ORDER 100
#define MAX_NAME_LEN 100
#define MAX 50

// ==== Structs ====
typedef struct Table {
  int tableNumber;
  int status;
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

// ==== Function Declarations ====
void getCurrentTime(char *buffer, int size);

// Table
void init_Table(Table **table);
void add_Table(Table **table, int tableNumber, int status);
Table *search_Table(Table *table, int tableNumber);
void book_NewTable(Table **table, int num);
void show_Table(Table *table);
void free_TableList(Table **table);

// Queue
void initQueue(Queue *q);
int isEmptyQueue(Queue *q);
int isFullQueue(Queue *q);
void enqueue(Queue *q);
void dequeue(Queue *q);
void displayQueue(Queue *q);

// Customer list
void addToList(List *l, Customer c);
void displayList(List *l, const char *title);
void addScheduledCustomer(List *l);
void moveToDiningList(Queue *q, List *diningList);

#endif // RESTAURANT_H
