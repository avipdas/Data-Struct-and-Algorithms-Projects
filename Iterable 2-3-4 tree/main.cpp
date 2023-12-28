#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include "Tree234.h"
#include "Tree234Iterator.h"
using namespace std;

void PrintVector(const vector<int>& vectorToPrint, string separator=", ",
   string prefix = "", string suffix = "");

int main() {
   // Seed random number generation
   srand(time(NULL));
   
   // Create a new Tree234 instance
   Tree234<Tree234Iterator> tree;

   // Generate and insert random integers
   vector<int> expected;
   unordered_set<int> added;
   while (expected.size() < 20) {
      int randomInteger = rand() % 900 + 100;
      if (0 == added.count(randomInteger)) {
         added.insert(randomInteger);
         expected.push_back(randomInteger);
         tree.Insert(randomInteger);
      }
   }
   sort(expected.begin(), expected.end());
   
   // Build the actual vector of integers by iterating through the tree. Keep
   // track of the number of iterations and if more iterations occur than
   // expected, then stop.
   vector<int> actual;
   int iterationCount = 0;
   for (int actualInt : tree) {
      actual.push_back(actualInt);
      iterationCount++;
      
      // If this iteration exceeded the expected number of iterations then
      // print a failure message
      if (iterationCount > (int) expected.size()) {
         cout << "FAIL: More than the expected " << expected.size();
         cout << " iterations occurred." << endl;
         return 1;
      }
   }
   
   // Print the pass or fail messsage
   cout << ((expected == actual) ? "PASS" : "FAIL");
   cout << ": Iteration through tree's keys:" << endl;
   PrintVector(actual,   ", ", "  Actual:   ", "\n");
   PrintVector(expected, ", ", "  Expected: ", "\n");
   
   return 0;
}

void PrintVector(const vector<int>& vectorToPrint, string separator,
   string prefix, string suffix) {
   cout << prefix;
   if (vectorToPrint.size() > 0) {
      // Print first item without separator
      cout << vectorToPrint[0];
      
      // Print remaining items, each preceeded by the separator
      for (int i = 1; i < (int) vectorToPrint.size(); i++) {
         cout << separator << vectorToPrint[i];
      }
   }
   
   // End with the suffix string
   cout << suffix;
}