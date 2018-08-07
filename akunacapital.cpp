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

// Order type, which can either be:
// IOC: Insert or cancel,
// GFD: Good for the day.
enum class order_t { IOC, GFD };

// Buy type, can only be either a BUY or SELL.
enum class buy_t { BUY, SELL };

// Function prototypes.
void process_instruction(string instruction);
void buy(string type, int price, int quantity, string id);
void sell(string type, int price, int quantity, string id);
void modify(string id, string type, int price, int quantity);
void cancel(string id);
void print_orders();

void buy(string type, int price, int quantity, string id) {
  cout << type << " " << price << " " << quantity << " " << id << endl;
}

void sell(string type, int price, int quantity, string id) {
  cout << type << " " << price << " " << quantity << " " << id << endl;
}

void process_instruction(string instruction) {
  // Process instructions in sequential order.
  string ins;
  stringstream ss(instruction);

  // Get the execution statement e.g. BUY/SELL/MODIFY etc.
  ss >> ins;

  // TODO optimise into a switch statement.
  if (ins == "BUY") {
    string type, id;
    int price, quantity;
    ss >> type >> price >> quantity >> id;
    buy(type, price, quantity, id);
  } else if (ins == "SELL") {
    string type, id;
    int price, quantity;
    ss >> type >> price >> quantity >> id;
    sell(type, price, quantity, id);
  } else if (ins == "MODIFY") {
  } else if (ins == "CANCEL") {
  } else if (ins == "PRINT") {
  } else {
    // TODO handle invalid instruction.
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