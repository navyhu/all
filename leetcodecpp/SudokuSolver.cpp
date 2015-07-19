#include <iostream>
#include <vector>
#include <map>
#include <iomanip>

using namespace std;
  const unsigned short bitvec[] = 
    {0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x100};
  map<unsigned short, int> bitvecMap;
  unsigned short bitmap[9][9] = {{0}};
  unsigned short rows[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  unsigned short columns[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  unsigned short blocks[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  const int len = 9;
  const unsigned short bitMask = 0x1ff;

class SudokuSolver {
public:
  void solveSudoku(vector<vector<char> > &board) {
    init(board);
    printDebug(board, 0, 0, 0);

    //go through the resolve process
    bool changed = true;
    while(changed) {
      changed = goThroughSudoku(board);
    }

    //check if it is resolved
    if (!isResolved(board)) {
      guessSudoku(board);
    }

    printSudoku(board);
  }

private:
  void guessSudoku(vector<vector<char> > &board) {
    vector<vector<char> > board_backup;
    unsigned short bitmap_backup[9][9];
    unsigned short rows_backup[9];
    unsigned short columns_backup[9];
    unsigned short blocks_backup[9];

    backup(board, board_backup, bitmap_backup, rows_backup, columns_backup, blocks_backup);

    //find the cell contains least candidates
    int row = 0, column = 0;
    findShortestCell(row, column);

    //guess and continue
    unsigned short val = bitmap[row][column];
    int count = 0;
    while (val) {
      if ((val & 0x1)) {
	updateSudoku(board, bitvec[count], row, column);
	if (guessThroughSudoku(board)) {
	  return;
	}
	restore(board, board_backup, bitmap_backup, rows_backup, columns_backup, blocks_backup);
      }
      val = val >> 1;
      count++;
    }
  }

  bool guessThroughSudoku(vector<vector<char> > &board) {
  }

  void findShortestCell(int &row, int &column) {
    int countLeast = 9;
    for (int i = 0;i < len;i++) {
      for (int j = 0;j < len;j++) {
	int count = countZeroOne(val, false);
	if (count == 2) {
	  row = i;
	  column = j;
	  return;
	}
	if (count < countLeast) {
	  countLeast = count;
	  row = i;
	  column = j;
	}
      }
    }
  }

  int countZeroOne(unsigned short val, bool zero) {
    int count = 0;
    if (zero)
      val = ~val;
    while (val) {
      if ((val & 0x1))
	count++;
      val = val >> 1;
    }

    return count;
  }

  void backup(vector<vector<char> > &board, vector<vector<char> > &board_backup,
	      unsigned short **bitmap_backup, unsigned short *rows_backup, 
	      unsigned short *columns_backup, unsigned short *blocks_backup) {
    board_backup = board;
    for (int i = 0;i < len;i++) {
      rows_backup[i] = rows[i];
      columns_backup[i] = columns[i];
      blocks_backup[i] = blocks[i];
      for (int j = 0;j < len;j++) {
	bitmap_backup[i][j] = bitmap[i][j];
      }
    }
  }

  void restore(vector<vector<char> > &board, vector<vector<char> > &board_backup,
	      unsigned short **bitmap_backup, unsigned short *rows_backup, 
	      unsigned short *columns_backup, unsigned short *blocks_backup) {
    board = board_backup;
    for (int i = 0;i < len;i++) {
      rows[i] = rows_backup[i];
      columns[i] = columns_backup[i];
      blocks[i] = blocks_backup[i];
      for (int j = 0;j < len;j++) {
	bitmap[i][j] = bitmap_backup[i][j];
      }
    }
  }

  bool goThroughSudoku(vector<vector<char> > &board) {
    bool changed = false;
    for (int i = 0;i < len;i++) {
      for (int j = 0;j < len;j++) {
	if (board[i][j] <'1' || board[i][j] > '9') {
	  if (checkCell(board, i, j))
	    changed = true;
	}
      }
    }

    return changed;
  }

  bool checkCell(vector<vector<char> > &board, int row, int column) {
    if (bitvecMap.find(bitmap[row][column]) != bitvecMap.end()) {
      updateSudoku(board, bitmap[row][column], row, column);
      return true;
    }

    //check the row/column/block which the current cell belongs to
    bool changed =  processRowColumnBlock(board, row, column);

    return changed;
  }

  bool processRowColumnBlock(vector<vector<char> > &board, int row, int column) {
    unsigned short other = 0;
    unsigned short cur = 0;
    //process row
    for (int j = 0;j < len;j++) {
      if (j != column) {
	other |= bitmap[row][j];
      }
    }
    cur = bitmap[row][column] & (~other) & bitMask;
    if (bitvecMap.find(cur) != bitvecMap.end()) {
      cout<<"Row solve "<<hex<<other<<" "<<cur<<endl;
      updateSudoku(board, cur, row, column);
      return true;
    }

    //process column
    other = cur = 0;
    for (int i = 0;i < len;i++) {
      if (i != row)
	other |= bitmap[i][column];
    }
    cur = bitmap[row][column] & (~other) & bitMask;
    if (bitvecMap.find(cur) != bitvecMap.end()) {
      cout<<"Column solve "<<hex<<other<<" "<<cur<<endl;
      updateSudoku(board, cur, row, column);
      return true;
    }

    //process block
    other = cur = 0;
    for (int i = (row/3)*3;i < (row/3)*3 + 3;i++) {
      for (int j = (column/3)*3;j < (column/3)*3 + 3;j++) {
	if (i != row || j != column)
	  other |= bitmap[i][j];
      }
    }
    cur = bitmap[row][column] & (~other) & bitMask;
    if (bitvecMap.find(cur) != bitvecMap.end()) {
      cout<<"Block solve "<<hex<<other<<" "<<cur<<endl;
      cout<<(row/3)*3<<" "<<(column/3)*3<<endl;
      updateSudoku(board, cur, row, column);
      return true;
    }

    return false;
  }

  void updateSudoku(vector<vector<char> > &board, unsigned short cur, int row, int column) {
    rows[row] |= cur & bitMask;
    columns[column] |= cur & bitMask;
    blocks[(row/3)*3 + column/3] |= cur & bitMask;
    bitmap[row][column] = cur;
    board[row][column] = '1' + bitvecMap[cur];
    updateBitmap(cur, row, column);

    printDebug(board, cur, row, column);
  }

  void updateBitmap(unsigned short cur, int row, int column) {
    for (int i = 0;i < len;i++) {
      if (i != row)
	bitmap[i][column] -= (bitmap[i][column] & cur);
    }

    for (int j = 0;j < len;j++) {
      if (j != column) {
	bitmap[row][j] -= (bitmap[row][j] & cur);
      }
    }

    for (int i = (row/3)*3;i < (row/3)*3 + 3;i++) {
      for (int j = (column/3)*3;j < (column/3)*3 + 3;j++) {
	if (i != row || j != column)
	  bitmap[i][j] -= (bitmap[i][j] & cur);
      }
    }
  }

  bool isResolved(vector<vector<char> > &board) {
    for(int i = 0;i < len;i++) {
      for (int j = 0;j < len;j++) {
	if (board[i][j] > '9' || board[i][j] < '1')
	  return false;
      }
    }
    return true;
  }

  void init(vector<vector<char> > &board) {
    //init bitvecMap
    for (int i = 0;i < len;i++) {
      bitvecMap[bitvec[i]] = i;
    }

    //init bitmap and rows/columns/blocks
    for (int i = 0;i < len;i++) {
      for (int j = 0;j < len;j++) {
	if (board[i][j] != '.') {
	  int index = board[i][j] - '1';
	  bitmap[i][j] = bitvec[index];
	  rows[i] |= bitvec[index] & bitMask;
	  columns[j] |= bitvec[index] & bitMask;
	  blocks[(i/3)*3 + j/3] |= bitvec[index] & bitMask;
	} else {
	  bitmap[i][j] = 0;
	}
      }
    }

    //init bitmap blank celss
    for (int i = 0;i < len;i++) {
      for (int j = 0;j < len;j++) {
	if (board[i][j] == '.') {
	  bitmap[i][j] = (~(rows[i] | columns[j] | blocks[(i/3)*3 + j/3])) & bitMask;
	}
      }
    }
  }

  void printDebug(vector<vector<char> > &board, unsigned short cur, int row, int column) {
    int in;
    cin>>in;

    cout<<"Cur: "<<hex<<cur<<endl;
    cout<<"row: "<<dec<<row<<endl<<"col: "<<column<<endl;

    printSudoku(board);
    printBitmap();
    printOthers();
  }

  void printOthers() {
    cout<<"Rows: ";
    for (int i = 0;i < len;i++) {
      cout<<setw(3)<<hex<<rows[i]<<setw(1)<<" ";
    }
    cout<<endl<<"Columns: ";
    for (int i = 0;i < len;i++) {
      cout<<setw(3)<<hex<<columns[i]<<setw(1)<<" ";
    }
    cout<<endl<<"Blocks: ";
    for (int i = 0;i < len;i++) {
      cout<<setw(3)<<hex<<blocks[i]<<setw(1)<<" ";
    }
    cout<<endl;
  }

  void printBitmap() {
    cout<<"*****bitmap*****"<<endl;
    for (int i = 0;i < len;i++) {
      for (int j = 0;j < len;j++)
	cout<<setw(3)<<hex<<bitmap[i][j]<<setw(1)<<" ";
      cout<<endl;
    }
    cout<<endl;
  }

  void printSudoku(vector<vector<char> > &board) {
    cout<<"*****Sudoku*****"<<endl;
    for (int i = 0;i < len;i++) {
      for (int j = 0;j < len;j++)
	cout<<board[i][j]<<" ";
      cout<<endl;
    }
    cout<<endl;
  }
};

#define SUDOKUSOLVER_H
#ifdef SUDOKUSOLVER_H
void constructSudoku(vector<vector<char> > &board, string data[]) {
  for (int i = 0;i < len;i++) {
    vector<char> row;
    for (int j = 0;j < len;j++) {
      row.push_back(data[i][j]);
    }
    board.push_back(row);
  }
}
string data[] = {
"..9748...","7........",".2.1.9...",
"..7...24.",".64.1.59.",".98...3..",
"...8.3.2.","........6","...2759.."
};
int main() {
  vector<vector<char> > board;
  constructSudoku(board, data);

  SudokuSolver sudoku;

  sudoku.solveSudoku(board);
}
#endif //SUDOKUSOLVER_H
