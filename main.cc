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

struct Order {
  friend ostream &operator<<(ostream &out, Order &order);

  string id_;
  bool isbuy_;
  bool isgfd_;
  int price_;
  int quantity_;
  time_t time_;

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
  out << "Is buy: " << order.isbuy_ << endl;
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
  static unordered_map<string, shared_ptr<Order>> orders_;
  static void add(string order_id, bool isgfd, int price, int quantity);

 public:
  Orderbook();
  ~Orderbook();
  static void buy(string order_id, bool isgfd, int price, int quantity);
  static void sell(string order_id, bool isgfd, int price, int quantity);
  static void modify(string order_id, bool isbuy, int price, int quantity);
  static void cancel(string order_id);
  static void print();
  static void debug();
};

// Initialise our static member variables.
map<int, int> Orderbook::buys_;
map<int, int> Orderbook::sells_;
unordered_map<string, shared_ptr<Order>> Orderbook::orders_;

Orderbook::~Orderbook() {
  // Need to free all our pointers to Orders.
}

void Orderbook::buy(string order_id, bool isgfd, int price, int quantity) {
  // Order *order = new Order{order_id, true, isgfd, price, quantity};
  // Orderbook::orders_.insert(make_pair(order_id, *order));
  shared_ptr<Order> order =
      make_shared<Order>(order_id, true, isgfd, price, quantity);

  Orderbook::orders_.insert(make_pair(order_id, order));

  // Add our price and quantity to the buys_ map.
  Orderbook::buys_[price] += quantity;
}

void Orderbook::sell(string order_id, bool isgfd, int price, int quantity) {
  // Order *order = new Order{order_id, false, isgfd, price, quantity};
  // Orderbook::orders_.insert(make_pair(order_id, *order));

  shared_ptr<Order> order =
      make_shared<Order>(order_id, true, isgfd, price, quantity);

  Orderbook::orders_.insert(make_pair(order_id, order));

  // Add our price to the sells_ map.
  Orderbook::sells_[price] += quantity;
}

void Orderbook::modify(string order_id, bool isbuy, int price, int quantity) {}

void Orderbook::cancel(string order_id) {
  shared_ptr<Order> ord = orders_.find(order_id)->second;

  if (ord->isbuy_) {
    buys_[ord->price_] -= ord->quantity_;
  } else {
    sells_[ord->price_] -= ord->quantity_;
  }

  orders_.erase(order_id);
}

void Orderbook::print() {
  cout << "SELL:" << endl;
  for (auto itr = sells_.rbegin(); itr != sells_.rend(); ++itr) {
    cout << itr->first << " " << itr->second << endl;
  }
  // Iterate over our buys.
  cout << "BUY:" << endl;
  for (auto itr = buys_.rbegin(); itr != buys_.rend(); ++itr) {
    cout << itr->first << " " << itr->second << endl;
  }
}

void Orderbook::debug() {
  for (auto itr = orders_.begin(); itr != orders_.end(); ++itr) {
    cout << itr->first << endl;
    cout << *(itr->second) << endl;
  }
}

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
  } else if (ins == "DEBUG") {
    Orderbook::debug();
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