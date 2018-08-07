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

class Order {
 private:
 public:
};

void processOrder(string instruction);

void processOrder(string instruction) {
  // Process our order in sequence.
  cout << instruction << endl;
}

int main() {
  // Continously listen for instructions.
  while (true) {
    string instruction;
    getline(cin, instruction);
    processOrder(instruction);
  }

  return 0;
}