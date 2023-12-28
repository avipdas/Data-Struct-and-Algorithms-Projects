#ifndef LCSMATRIX_H
#define LCSMATRIX_H

#include <string>
#include <unordered_set>

// Your code here
// - Include any required additional headers
// - Declare any desired classes/structs to be used by LCSMatrix

class LCSMatrix {
private:
   int rowCount;
   int columnCount;
   //
   // Your code here
   //
public:
   LCSMatrix(std::string& str1, std::string& str2) {
      this->rowCount = (int) str1.length();
      this->columnCount = (int) str2.length();
      
      // Your code here
   }
   
   // Your code here, if needed
   // - If matrix data is dynamically allocated, add destructor
   
   // Returns the number of columns in the matrix, which also equals the length
   // of the second string passed to the constructor.
   int GetColumnCount() {
      return columnCount;
   }
   
   // Returns the matrix entry at the specified row and column indices, or 0 if
   // either index is out of bounds.
   int GetEntry(int rowIndex, int columnIndex) {
      // Your code here (remove placeholder line below)
      return 0;
   }
   
   // Returns the number of rows in the matrix, which also equals the length
   // of the first string passed to the constructor.
   int GetRowCount() {
      return rowCount;
   }
   
   // Returns the set of distinct, longest common subsequences between the two
   // strings that were passed to the constructor.
   std::unordered_set<std::string> GetLongestCommonSubsequences() {
      // Your code here (remove placeholder line below)
      return std::unordered_set<std::string>();
   }
};

#endif