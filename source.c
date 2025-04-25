#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int tableNumber;
  int status;
  char *customerName;
  char *orderDetails;
  TableInfo *next;
} TableInfo;

typedef struct {
  TableInfo *table;
} Table;

// Initialize the table list
void init_Table(Table *table) { table->table = NULL; }

// Add a new table to the list
void add_Table(Table *_table, int _tableNumber, int _status) {
  TableInfo *newTable = (TableInfo *)malloc(sizeof(TableInfo));
  newTable->tableNumber = _tableNumber;
  newTable->status = _status;
  newTable->customerName = NULL;
  newTable->orderDetails = NULL;
  newTable->next = NULL;
}

// Delete a table from the list
void delete_Table(Table *_table, int _tableNumber) {
  TableInfo *current = _table->table;
  TableInfo *previous = NULL;

  while (current != NULL && current->tableNumber != _tableNumber) {
    previous = current;
    current = current->next;
  }

  if (current == NULL)
    return; // Table not found

  if (previous == NULL) {
    _table->table = current->next; // Deleting the first table
  } else {
    previous->next = current->next; // Bypass the current table
  }

  free(current->customerName);
  free(current->orderDetails);
  free(current);
}

// Add customer information to a table
void add_CustomerInfo(Table *_table, int _tableNumber, char *_customerName,
                      char *_orderDetails) {
  TableInfo *current = _table->table;

  while (current != NULL && current->tableNumber != _tableNumber) {
    current = current->next;
  }

  if (current == NULL)
    return; // Table not found

  current->customerName = (char *)malloc(strlen(_customerName) + 1);
  strcpy(current->customerName, _customerName);

  current->orderDetails = (char *)malloc(strlen(_orderDetails) + 1);
  strcpy(current->orderDetails, _orderDetails);
}
