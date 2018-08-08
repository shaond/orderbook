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
#include <memory>
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
void buy_order(string type, int price, int quantity, string id);
void sell_order(string type, int price, int quantity, string id);
void modify_order(string id, string type, int price, int quantity);
void cancel_order(string id);
void print_orders();

enum class order_t { BUY, SELL };
enum class subtype_t { GFD, IOC };

class Order {
  friend ostream &operator<<(ostream &out, Order &order);

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

// Order constructor.
Order::Order(string id, order_t type, subtype_t subtype, int price,
             int quantity)
    : id_{id},
      type_{type},
      subtype_{subtype},
      price_{price},
      quantity_{quantity},
      time_{time(nullptr)} {}

// Order destructor.
Order::~Order() {}

// Output stream operator overload for the `Order` class.
ostream &operator<<(ostream &out, Order &order) {
  out << "OrderId: " << order.id_ << endl;
  out << "Price: " << order.price_ << endl;
  out << "Quantity: " << order.quantity_ << endl;
  out << "Time: " << order.time_ << endl;

  return out;
}

// OrderBook data structure class holds
// all our orders.
class OrderBook final {
 private:
  static unordered_map<string, shared_ptr<Order>> orderbook_;
  static queue<shared_ptr<Order>> buyq_;
  static queue<shared_ptr<Order>> sellq_;

 public:
  static void buy(string id, shared_ptr<Order> order);
  static void sell(string id, shared_ptr<Order> order);
  static void remove(string id);
};

void OrderBook::buy(string id, shared_ptr<Order> order) {
  // Add our order to the OrderBook and our buy/sell queues.
}

void buy_order(string type, int price, int quantity, string id) {
  // Input with price <= 0, quantity <= 0 or missing order ID should
  // be ignored.
  if ((price <= 0) || (quantity <= 0)) return;
  if (id == "") return;

  subtype_t subtype;

  // cout << type << " " << price << " " << quantity << " " << id << endl;

  if (type == "GFD") {
    subtype = subtype_t::GFD;
  } else {
    subtype = subtype_t::IOC;
  }

  // Create a new `Order`.
  shared_ptr<Order> ord =
      make_shared<Order>(id, order_t::BUY, subtype, price, quantity);

  // Add `Order` to our OrderBook.
  OrderBook::insert_buy(id, ord);
}

void sell_order(string type, int price, int quantity, string id) {
  // Input with price <= 0, quantity <= 0 or missing order ID should
  // be ignored.
  if ((price <= 0) || (quantity <= 0)) return;
  if (id == "") return;

  cout << type << " " << price << " " << quantity << " " << id << endl;
}

void modify_order(string id, string type, int price, int quantity) {
  cout << id << " " << type << " " << price << " " << quantity << endl;
}

void cancel_order(string id) { cout << id << " " << endl; }

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
    buy_order(type, price, quantity, id);
  } else if (ins == "SELL") {
    ss >> type >> price >> quantity >> id;
    sell_order(type, price, quantity, id);
  } else if (ins == "MODIFY") {
    ss >> id >> type >> price >> quantity;
    modify_order(id, type, price, quantity);
  } else if (ins == "CANCEL") {
    ss >> id;
    cancel_order(id);
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