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
void ProcessInstruction(string instruction);

class Order {
  friend ostream &operator<<(ostream &out, Order &order);

 private:
  string id_;
  bool isbuy_;
  bool isgfd_;
  int price_;
  int quantity_;
  time_t time_;

 public:
  Order(string id, bool isbuy, bool isgfd, int price, int quantity);
  ~Order();
};

// Order constructor.
Order::Order(string id, bool isbuy, bool isgfd, int price, int quantity)
    : id_{id},
      isbuy_{isbuy},
      isgfd_{isgfd},
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

class Orderbook final {
  friend ostream &operator<<(ostream &out, Orderbook &book);

 private:
  static map<int, int> buys_;
  static map<int, int> sells_;
  static unordered_map<string, Order> orders_;
  static void add(string order_id, bool isgfd, int price, int quantity);

 public:
  static void buy(string order_id, bool isgfd, int price, int quantity);
  static void sell(string order_id, bool isgfd, int price, int quantity);
  static void modify(string order_id, bool isbuy, int price, int quantity);
  static void cancel(string order_id);
  static void print();
};

// Initialise our static member variables.
map<int, int> buys_;
map<int, int> sells_;
unordered_map<string, Order> orders_;

void Orderbook::buy(string order_id, bool isgfd, int price, int quantity) {
  // unique_ptr<Order> order =
  // make_unique<Order>(order_id, true, isgfd, price, quantity);
  Order *order = new Order{order_id, true, isgfd, price, quantity};
  Orderbook::orders_.insert(make_pair(order_id, *order));
}

void Orderbook::sell(string order_id, bool isgfd, int price, int quantity) {}

void Orderbook::modify(string order_id, bool isbuy, int price, int quantity) {}

void Orderbook::cancel(string order_id) {}

void Orderbook::print() {}

// Overload the output stream operator, so we can print the Orderbook.
ostream &operator<<(ostream &out, Orderbook &book) { return out; }

// Process our market instruction.
void ProcessInstruction(string instruction) {
  string ins{};
  string type{};
  string id{};
  bool isgfd{true};
  bool isbuy{true};
  int price{0};
  int quantity{0};
  stringstream ss(instruction);

  // Get our instruction e.g. BUY/SELL/MODIFY etc.
  ss >> ins;

  if (ins == "BUY") {
    ss >> type >> price >> quantity >> id;
    if (type == "IOC") isgfd = false;
    Orderbook::buy(id, isgfd, price, quantity);
  } else if (ins == "SELL") {
    ss >> type >> price >> quantity >> id;
    if (type == "IOC") isgfd = false;
    Orderbook::sell(id, isgfd, price, quantity);
  } else if (ins == "MODIFY") {
    ss >> id >> type >> price >> quantity;
    if (type == "SELL") isbuy = false;
    Orderbook::modify(id, isbuy, price, quantity);
  } else if (ins == "CANCEL") {
    ss >> id;
    Orderbook::cancel(id);
  } else if (ins == "PRINT") {
    Orderbook::print();
  }
}

int main() {
  while (true) {
    string instruction;
    getline(cin, instruction);
    ProcessInstruction(instruction);
  }

  return 0;
}