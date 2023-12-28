#include <iostream>
#include <string>
#include <vector>
#include "LCSTestCase.h"
using namespace std;

int main(int argc, char *argv[]) {
   vector<LCSTestCase> testCases = {
      LCSTestCase(
         "ALASKAN",
         "BANANAS",
         {
            { 0, 1, 1, 1, 1, 1, 1 },
            { 0, 1, 1, 1, 1, 1, 1 },
            { 0, 1, 1, 2, 2, 2, 2 },
            { 0, 1, 1, 2, 2, 2, 3 },
            { 0, 1, 1, 2, 2, 2, 3 },
            { 0, 1, 1, 2, 2, 3, 3 },
            { 0, 1, 2, 2, 3, 3, 3 }
         },
         { "AAA", "AAS", "AAN"}
      ),
      LCSTestCase(
         "BAAB",
         "ABBA",
         {
            //A  B  B  A
            { 0, 1, 1, 1 }, // B
            { 1, 1, 1, 2 }, // A
            { 1, 1, 1, 2 }, // A
            { 1, 2, 2, 2 }  // B
         },
         { "AA", "BB", "AB", "BA" }
      ),
      LCSTestCase(
         "ABBA",
         "BAAB",
         {
            //B  A  A  B
            { 0, 1, 1, 1 }, // A
            { 1, 1, 1, 2 }, // B
            { 1, 1, 1, 2 }, // B
            { 1, 2, 2, 2 }  // A
         },
         { "AA", "BB", "AB", "BA" }
      ),
      LCSTestCase(
         "lower case",
         "UPPER CASE",
         {
            //U  P  P  E  R     C  A  S  E
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // l
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // o
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // w
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // e
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // r
            { 0, 0, 0, 0, 0, 1, 1, 1, 1, 1 }, //
            { 0, 0, 0, 0, 0, 1, 1, 1, 1, 1 }, // c
            { 0, 0, 0, 0, 0, 1, 1, 1, 1, 1 }, // a
            { 0, 0, 0, 0, 0, 1, 1, 1, 1, 1 }, // s
            { 0, 0, 0, 0, 0, 1, 1, 1, 1, 1 }  // e
         },
         { " " }
      ),
      LCSTestCase(
         "PROGRAMMING",
         "PROBLEM",
         {
            { 1, 1, 1, 1, 1, 1, 1 },
            { 1, 2, 2, 2, 2, 2, 2 },
            { 1, 2, 3, 3, 3, 3, 3 },
            { 1, 2, 3, 3, 3, 3, 3 },
            { 1, 2, 3, 3, 3, 3, 3 },
            { 1, 2, 3, 3, 3, 3, 3 },
            { 1, 2, 3, 3, 3, 3, 4 },
            { 1, 2, 3, 3, 3, 3, 4 },
            { 1, 2, 3, 3, 3, 3, 4 },
            { 1, 2, 3, 3, 3, 3, 4 },
            { 1, 2, 3, 3, 3, 3, 4 }
         },
         { "PROM" }
      ),
      LCSTestCase(
         "LOOK",
         "ZYBOOKS",
         {
            { 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 1, 1, 1, 1 },
            { 0, 0, 0, 1, 2, 2, 2 },
            { 0, 0, 0, 1, 2, 3, 3 }
         },
         { "OOK" },
         true
      ),
      LCSTestCase(
         "ZYBOOKS",
         "LOOK",
         { "OOK" }
      ),
      LCSTestCase(
         "A_B_C",
         "X_Y_Z",
         { "__" }
      ),
      LCSTestCase(
         "ABCEDEFGHIJKL",
         "MNOPQRSTUVWXYZ",
         { }
      ),
      LCSTestCase(
         "DATA STRUCTURES",
         "ALGORITHMS",
         { "ARTS" }
      ),
      LCSTestCase(
         "",
         "",
         { }
      ),
      LCSTestCase(
         "RELATIVELY",
         "ACTIVE",
         { "ATIVE" }
      ),
      LCSTestCase(
         "ACTIVE",
         "RELATIVELY",
         { "ATIVE" }
      ),
      LCSTestCase(
         "very very very very very very very very very long string",
         "short string",
         { "o string", "r string" }
      ),
      LCSTestCase(
         "five food groups",
         "dairy, vegetables, fruits, grains, and protein",
         { "ive f grp", "ive fd ro", "ive f gro", "ive f grs" }
      ),
      LCSTestCase(
         "A MAN A PLAN A CANAL PANAMA",
         "THE RAIN IN SPAIN STAYS MAINLY IN THE PLAIN",
         { " AN  PAN A ANL PAN" }
      )
   };
   
   // Execute each test case and count the number that pass
   int passCount = 0;
   for (LCSTestCase& testCase : testCases) {
      if (testCase.Execute(std::cout)) {
         passCount++;
      }
      cout << endl;
   }
   
   // Print the summary
   cout << passCount << " of " << testCases.size();
   cout << " test cases passed" << endl << endl;
   
   return 0;
}