#include <algorithm>
#include <bitset>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Function prototypes.
void process_instruction(string instruction);
void buy(string type, int price, int quantity, string id);
void sell(string type, int price, int quantity, string id);
void modify(string id, string type, int price, int quantity);
void cancel(string id);
void print_orders();

enum class order_t { BUY, SELL };
enum class subtype_t { GFD, IOC };

class Order {
 private:
  string id_;
  time_t time_;
  order_t type_;
  subtype_t subtype_;
  int price_;
  int quantity_;

 public:
  Order(string id, order_t type, subtype_t subtype, int price, int quantity);
  ~Order();
};

Order::Order(string id, order_t type, subtype_t subtype, int price,
             int quantity)
    : id_{id},
      type_{type},
      subtype_{subtype},
      price_{price},
      quantity_{quantity} {
  time_ = time(nullptr);
}

Order::~Order() {
  // Destructor.
}

void buy(string type, int price, int quantity, string id) {
  // Input with price <= 0, quantity <= 0 or missing order ID should
  // be ignored.
  if ((price <= 0) || (quantity <= 0)) return;
  if (id == "") return;

  cout << type << " " << price << " " << quantity << " " << id << endl;
}

void sell(string type, int price, int quantity, string id) {
  // Input with price <= 0, quantity <= 0 or missing order ID should
  // be ignored.
  if ((price <= 0) || (quantity <= 0)) return;
  if (id == "") return;

  cout << type << " " << price << " " << quantity << " " << id << endl;
}

void modify(string id, string type, int price, int quantity) {
  cout << id << " " << type << " " << price << " " << quantity << endl;
}

void cancel(string id) { cout << id << " " << endl; }

void print_orders() { cout << "Print all our orders here..." << endl; }

void process_instruction(string instruction) {
  // Process instructions in sequential order.
  string ins{};
  string type{};
  string id{};
  int price{0};
  int quantity{0};
  stringstream ss(instruction);

  // Get our instruction e.g. BUY/SELL/MODIFY etc.
  ss >> ins;

  // TODO optimise into a switch statement.
  if (ins == "BUY") {
    ss >> type >> price >> quantity >> id;
    buy(type, price, quantity, id);
  } else if (ins == "SELL") {
    ss >> type >> price >> quantity >> id;
    sell(type, price, quantity, id);
  } else if (ins == "MODIFY") {
    ss >> id >> type >> price >> quantity;
    modify(id, type, price, quantity);
  } else if (ins == "CANCEL") {
    ss >> id;
    cancel(id);
  } else if (ins == "PRINT") {
    print_orders();
  }
}

int main() {
  // Continously listen and process instructions.
  while (true) {
    string instruction;
    getline(cin, instruction);
    process_instruction(instruction);
  }

  return 0;
}