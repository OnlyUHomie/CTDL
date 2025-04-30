#include <iostream>
#include <string>

using namespace std;

struct Table {
  int tableNumber;
  int status; // 0: Available, 1: Occupied
  string customerName;
  string orderDetails[100];
  Table *next;
};

// Initate a new table list
void init_Table(Table *&table) { table = nullptr; }

// Add new table to table list
void add_Table(Table *&table, int tableNumber, int status) {
  Table *newTable = new Table;
  newTable->tableNumber = tableNumber;
  newTable->status = status;
  newTable->customerName = "";
  newTable->orderDetails[1] = "Empty";
  newTable->next = table;
  table = newTable;
}

// Delete table out of table list
void delete_Table(Table *&table, Table *temp) {
  if (temp == nullptr) {
    cout << "Table not found!" << endl;
    return;
  }

  Table *current = table;
  Table *prev = nullptr;

  // If its the first table
  if (current != nullptr && current->tableNumber == temp->tableNumber) {
    table = current->next;
    delete current;
    cout << "Table deleted successfully!" << endl;
    return;
  }

  // Find table which need to delete
  while (current != nullptr && current != temp) {
    prev = current;
    current = current->next;
  }

  // Cant find table
  if (current == nullptr) {
    cout << "Table not found!" << endl;
    return;
  }

  // Delete table
  prev->next = current->next;
  delete current;
  cout << "Table deleted successfully!" << endl;
}

// Find table by number
Table *search_Table(Table *table, int tableNumber) {
  Table *current = table;
  while (current != nullptr) {
    if (current->tableNumber == tableNumber) {
      return current;
    }
    current = current->next;
  }
  return nullptr; // Cant find table
}

// Show table list
void show_Table(Table *table) {
  Table *current = table;
  if (current == nullptr) {
    cout << "No tables available!" << endl;
    return;
  }
  while (current != nullptr) {
    cout << "Table Number: " << current->tableNumber
         << ", Status: " << (current->status == 0 ? "Available" : "Occupied")
         << endl;
    for (auto &order : current->orderDetails) {
      cout << order << " ";
    }
    cout << endl;
    current = current->next;
  }
}

// Free table list
void free_TableList(Table *&table) {
  while (table != nullptr) {
    Table *temp = table;
    table = table->next;
    delete temp;
  }
}

// Book new table by number
void book_NewTable(Table *&table, int num) {
  Table *temp = search_Table(table, num);
  if (temp->status == 0) {
    printf("Table is full\nPlease book a new one\n");
    return;
  } else {
    temp->status = 1;
    string s, x;
    int i = 0;
    scanf("%s", s);
    temp->customerName = s;
    while (x != "X" || x != "x") {
      cin >> x;
      temp->orderDetails[i] = x;
      i++;
    }
  }
}

int main() {
  Table *tableList;
  init_Table(tableList); // Khởi tạo danh sách bàn

  // Thêm các bàn vào danh sách
  add_Table(tableList, 1, 0); // Bàn 1: Available
  add_Table(tableList, 2, 1); // Bàn 2: Occupied
  add_Table(tableList, 3, 0); // Bàn 3: Available

  // Hiển thị danh sách bàn
  cout << "Initial Table List:" << endl;
  show_Table(tableList);

  // Đặt bàn mới
  int tableToBook = 1;
  cout << "\nBooking table number " << tableToBook << "..." << endl;
  book_NewTable(tableList, tableToBook);

  // Hiển thị danh sách bàn sau khi đặt
  cout << "\nTable List after booking:" << endl;
  show_Table(tableList);

  // Tìm kiếm bàn số 2
  int tableToSearch = 2;
  cout << "\nSearching for table number " << tableToSearch << "..." << endl;
  Table *searchResult = search_Table(tableList, tableToSearch);
  if (searchResult != nullptr) {
    cout << "Found table number: " << searchResult->tableNumber << endl;
  } else {
    cout << "Table not found!" << endl;
  }

  // Xóa bàn số 2
  cout << "\nDeleting table number " << tableToSearch << "..." << endl;
  delete_Table(tableList, searchResult);

  // Hiển thị danh sách bàn sau khi xóa
  cout << "\nTable List after deletion:" << endl;
  show_Table(tableList);

  // Giải phóng bộ nhớ
  free_TableList(tableList);

  return 0;
}