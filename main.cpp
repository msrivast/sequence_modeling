#include "BRT.h"
#include <iostream>

using namespace std;

int main(void)
{ 
  BRT tree;
  tree.insert(0,49);
  tree.insert(0,51);
  cout<< tree.select(1);
  // tree.print_inorder();
}