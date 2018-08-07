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

// Buy type, which can either be -
// IOC: Insert or cancel,
// GFD: Good for the day.
enum class buy_t { IOC, GFD };

// Order type, represents either a BUY or a SELL.
enum class order_t { BUY, SELL };

// Function prototypes.
void process_instruction(string instruction);
bool buy(buy_t type, int price, int quantity, string order_id);
bool sell(buy_t type, int price, int quantity, string order_id);
bool cancel(string order_id);
bool modify(string order_id, order_t type, int price, int quantity);
void print_orders();

void process_instruction(string instruction) {
  // Process instructions in sequential order.
  cout << instruction << endl;
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