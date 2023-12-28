#ifndef LCSTESTCASE_H
#define LCSTESTCASE_H

#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include "LCSMatrix.h"

// LCSTestCase represents a test for LCSMatrix class functionality. Expected
// vs. actual LCS strings sets are compared and optionally the numerical
// matrices as well.
class LCSTestCase {
private:
   std::string string1;
   std::string string2;
   std::unordered_set<std::string> expectedLCSSet;
   std::vector<std::vector<int>> expectedMatrix;
   
   // Converts an LCSMatrix to a vector of integer vectors, representing the
   // numerical matrix. Uses an LCSMatrix's GetEntry() function to retrieve
   // each entry.
   std::vector<std::vector<int>> ConvertLCSMatrix(LCSMatrix& userMatrix) {
      using namespace std;
      vector<vector<int>> result;
      for (int rowIndex = 0; rowIndex < userMatrix.GetRowCount(); rowIndex++) {
         vector<int> row;
         for (int colIndex = 0; colIndex < userMatrix.GetColumnCount(); colIndex++) {
            int value = userMatrix.GetEntry(rowIndex, colIndex);
            row.push_back(value);
         }
         result.push_back(row);
      }
      return result;
   }

   void PrintMatrix(std::ostream& output,
      const std::vector<std::vector<int>>& matrix, std::string indent="") {
      for (auto& row : matrix) {
         output << indent << "[";
         for (int value : row) {
            output << " " << value;
         }
         output << " ]" << std::endl;
      }
   }
   
   void PrintStringSet(std::ostream& output,
      const std::unordered_set<std::string>& stringSet,
      std::string separator = ", ") {
      // Each string requires a preceeding separator, except the first string.
      // So printedFirst indicates whether or not the first string has been
      // printed.
      bool printedFirst = false;
      for (const std::string& str : stringSet) {
         if (printedFirst) {
            output << separator;
         }
         else {
            printedFirst = true;
         }
         output << "\"" << str << "\"";
      }
   }

public:
   // If true, executing the test case will only test the matrix entries and
   // not the longest common subsequences. If false, both the matrix and the
   // longest common subsequences functionality will be tested.
   bool matrixOnly;
   
   LCSTestCase(std::string string1, std::string string2,
      std::unordered_set<std::string> expectedLCSs) :
      expectedLCSSet(expectedLCSs) {
      this->string1 = string1;
      this->string2 = string2;
      matrixOnly = false;
   }
   
   LCSTestCase(std::string string1, std::string string2,
      const std::vector<std::vector<int>>& expectedLCSMatrix,
      std::unordered_set<std::string> expectedLCSs,
      bool testMatrixFunctionalityOnly = false) :
      expectedLCSSet(expectedLCSs), expectedMatrix(expectedLCSMatrix) {
      this->string1 = string1;
      this->string2 = string2;
      this->matrixOnly = testMatrixFunctionalityOnly;
   }
   
   bool Execute(std::ostream& output) {
      using namespace std;
      
      // Build the LCSMatrix
      LCSMatrix userMatrix(string1, string2);
      
      // Get the set of longest common subsequences from the matrix
      unordered_set<string> actual =
         userMatrix.GetLongestCommonSubsequences();
      
      // If this test case includes an expected matrix, then build the
      // numerical matrix from userMatrix and compare the result against the
      // expected matrix
      vector<vector<int>> actualMatrix;
      if (expectedMatrix.size() > 0) {
         // Build the numerical matrix from the user's LCSMatrix object
         actualMatrix = ConvertLCSMatrix(userMatrix);
         
         // The test fails if the matrices are not equal
         if (expectedMatrix != actualMatrix) {
            output << "FAIL: \"" << string1 << "\" and \"" << string2 << "\"" << endl;
            
            // Show expected and actual numerical matrices
            output << "  Expected matrix:" << endl;
            PrintMatrix(output, expectedMatrix, "    ");
            output << "  Actual matrix:" << endl;
            PrintMatrix(output, actualMatrix, "    ");
            return false;
         }
      }
      
      // Compare the expected and actual LCS sets
      bool pass = true;
      if (!matrixOnly) {
         if (expectedLCSSet != actual) {
            pass = false;
         }
      }
      
      // Output final results
      output << (pass ? "PASS" : "FAIL");
      output << ": \"" << string1 << "\" and \"" << string2 << "\"";
      if (matrixOnly) {
         output << " (matrix generation only)" << endl;
      }
      else {
         output << endl;
      }
      if (expectedMatrix.size() > 0) {
         // Show expected and actual numerical matrices
         output << "  Expected matrix:" << endl;
         PrintMatrix(output, expectedMatrix, "    ");
         output << "  Actual matrix:" << endl;
         PrintMatrix(output, actualMatrix, "    ");
      }
      if (!matrixOnly) {
         output << "  Expected LCS set:" << endl << "    {";
         PrintStringSet(output, expectedLCSSet);
         output << "}" << endl;
         output << "  Actual LCS set:" << endl << "    {";
         PrintStringSet(output, actual);
         output << "}" << endl;
      }
      
      return pass;
   }
};

#endif