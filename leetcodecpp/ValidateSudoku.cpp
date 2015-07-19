#include <iostream>
#include <vector>
#include <map>

using namespace std;

const char numbers[] = {'.', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
const unsigned int = 10;

class ValidateSudoku {
public:
  typedef vector<vector<char> >::size_type vvctype;
  typedef vector<char>::size_type vctype;

  bool isValidSudoku(vector<vector<char> > &board) {
    if (isValidRows(board) && isValidColumns(board) && isValidCells(board))
      return true;
    return false;
  }

private:
  bool isValidRows(vector<vector<char> > &board) {
    vvctype len = board.size();
    for (vvctype i = 0;i < len;i++) {
      map<char> validMap;
      for (vctype j = 0;j < len;j++) {

      }
    }
  }

  bool isValidColumns(vector<vector<char> > &board) {
  }

  bool isValidCells(vector<vector<char> > &board) {
  }
};

#define VALIDATESUDOKU_H
#ifdef VALIDATESUDOKU_H

#endif //VALIDATESUDOKU_H
