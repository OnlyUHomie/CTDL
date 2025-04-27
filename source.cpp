#include <iostream>
#include <string>

using namespace std;

struct Table {
  int tableNumber;
  int status; // 0: Available, 1: Occupied
  string customerName;
  string orderDetails;
  Table *next;
};

// Khởi tạo danh sách bàn
void init_Table(Table *&table) { table = nullptr; }

// Thêm một bàn mới vào danh sách
void add_Table(Table *&table, int tableNumber, int status) {
  Table *newTable = new Table;
  newTable->tableNumber = tableNumber;
  newTable->status = status;
  newTable->customerName = "";
  newTable->orderDetails = "";
  newTable->next = table;
  table = newTable;
}

// Xóa một bàn khỏi danh sách
void delete_Table(Table *&table, Table *temp) {
  if (temp == nullptr) {
    cout << "Table not found!" << endl;
    return;
  }

  Table *current = table;
  Table *prev = nullptr;

  // Nếu bàn cần xóa là bàn đầu tiên
  if (current != nullptr && current->tableNumber == temp->tableNumber) {
    table = current->next;
    delete current;
    cout << "Table deleted successfully!" << endl;
    return;
  }

  // Tìm bàn cần xóa
  while (current != nullptr && current != temp) {
    prev = current;
    current = current->next;
  }

  // Không tìm thấy bàn
  if (current == nullptr) {
    cout << "Table not found!" << endl;
    return;
  }

  // Xóa bàn
  prev->next = current->next;
  delete current;
  cout << "Table deleted successfully!" << endl;
}

// Tìm kiếm một bàn theo số bàn
Table *search_Table(Table *table, int tableNumber) {
  Table *current = table;
  while (current != nullptr) {
    if (current->tableNumber == tableNumber) {
      return current;
    }
    current = current->next;
  }
  return nullptr; // Không tìm thấy
}

// Hiển thị danh sách bàn
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
    current = current->next;
  }
}

// Giải phóng danh sách bàn
void free_TableList(Table *&table) {
  while (table != nullptr) {
    Table *temp = table;
    table = table->next;
    delete temp;
  }
}

int main() {
  Table *tableList;
  init_Table(tableList);

  // Thêm các bàn vào danh sách
  add_Table(tableList, 1, 0);
  add_Table(tableList, 2, 1);
  add_Table(tableList, 3, 0);

  // Hiển thị danh sách bàn
  cout << "Table List:" << endl;
  show_Table(tableList);

  // Tìm kiếm bàn số 2
  Table *searchResult = search_Table(tableList, 2);
  if (searchResult != nullptr) {
    cout << "Found table number: " << searchResult->tableNumber << endl;
  } else {
    cout << "Table not found!" << endl;
  }

  // Xóa bàn số 2
  delete_Table(tableList, searchResult);

  // Hiển thị danh sách bàn sau khi xóa
  cout << "Table List after deletion:" << endl;
  show_Table(tableList);

  // Giải phóng bộ nhớ
  free_TableList(tableList);

  return 0;
}