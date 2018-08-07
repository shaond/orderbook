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
bool buy(order_t type, int price, int quantity, string order_id);
bool sell(order_t type, int price, int quantity, string order_id);
bool cancel(string order_id);
bool modify(string order_id, buy_t type, int price, int quantity);
void print_orders();

void process_instruction(string instruction) {
  // Process instructions in sequential order.
  string ins, tmp;
  stringstream ss(instruction);

  // Get the execution statement e.g. BUY/SELL/MODIFY etc.
  ss >> ins;

  if (ins == "BUY") {
    cout << "It's a buy" << endl;
    while (ss >> tmp) {
      cout << tmp;
    }
  }
  if (ins == "SELL") {
    cout << "It's a SELL" << endl;
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