#include "Set.h"
#include "Node.h"
#include <iostream>

// Use this file to test your Set class.
// This file won't be graded - do whatever you want.

int main() {
  Set set;
  set.insert("m");
  set.insert("o");
  set.insert("c");
  set.insert("e");
  set.insert("p");
  set.insert("z");
  set.insert("y");
  set.insert("q");
  set.print();
  set.remove("m");
  set.remove("o");
  set.print();

    

  set.~Set();
  return 0;
}
