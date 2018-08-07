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

void processOrder(std::string instruction);

void processOrder(std::string instruction) { cout << instruction; }

int main() {
  std::string instruction;

  while (true) {
    cin >> instruction;
    processOrder(instruction);
  }

  return 0;
}