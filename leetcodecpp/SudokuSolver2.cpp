#include <iostream>
#include <vector>
#include <map>
#include <bitset>

using namespace std;

const unsigned short bitvec[] = 
  {0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x100};
map<unsigned short, int> bitvecMap;
const int len = 9;
const unsigned short bitmask = 0x1ff;

void initBitvecMap() {
  for (int i = 0;i < len;i++) {
    bitvecMap[bitvec[i]] = i;
  }
}

struct SudokuCell {
  char value;
  unsigned short candidates;
  int candidateCount;
  SudokuCell(char val) : value(val), candidates(), candidateCount(0) {}
};

//Unit represents a row/column/block
struct Unit {
  unsigned short status;
  int validCount;
  Unit() : status(0), validCount(0) {}
};

class SudokuSolver {
public:
  void solveSudoku(vector<vector<char> > &board) {
    unit(board);

    bool changed = true;
    while (changed) {
      changed = basicSolve();
    }

    //guessSolve();
  }

private:
  bool basicSolve() {
    bool changed = false;
    for (int i = 0;i < len;i++) {
      for (int j = 0;j < len;j++) {
	if (checkCell(i, j))
	  changed = true;
      }
    }
    return changed;
  }

  bool checkCell(int row, int col) {
    bool changed = false;
    if (cellBoard[row][col].candidateCount == 1) {
      updateCell(row, col);
      return true;
    }
  }

  void updateCell(int row, int col) {
    SudokuCell &cell = cellBoard[row][col];
    cell.value = '1' + bitvecMap[cell.candidates];
    
    rows[row].status |= cell.candidates;
    rows[row].validCount++;

    columns[col].status |= cell.candidates;
    columns[col].validCount++;

    int idx = (row/3)*3 + col/3;
    blocks[idx].status |= cell.candidates;
    blocks[idx].validCount++;

    //update the same row
    for (int i = 0;i < len;i++) {
      if (i != row) {
      }
    }
  }

  void calcCell(unsigned short cur, int row, int col) {
  }

  void copyToBoard(vector<vector<char> > &board) {
    for (int i = 0;i < len;i++) {
      for (int j = 0;j < len;j++) {
	board[i][j] = cellBoard[i][j].value;
      }
    }
  }

  void init(vector<vector<char> > &board) {
    initBitvecMap();

    rows = array<Unit, 9>();
    columns = array<Unit, 9>();
    blocks = array<Unit, 9>();

    //init cellBoard
    initCellBoard(board);

    //init Units(rows/columns/blocks)
    calcUnits();

    //calculate candidates in each cell
    calcCandidates();
  }

  void initCellBoard(vector<vector<char> > &board) {
    for (int i = 0;i < len;i++) {
      vector<SudokuCell> sudokuRow;
      for (int j = 0;j < len;j++) {
	SudokuCell cell(board[i][j]);
	sudokuRow.push_back(cell);
      }
      cellBoard.push_back(sudokuRow);
    }
  }

  void calcUnits() {
    //rows columns and blocks
    for (int i = 0;i < len;i++) {
      for (int j = 0;j < len;j++) {
	if (cellBoard[i][j].value == '.') {
	  unsigned short cur = 0;
	  if (bitvecMap.find(cellBoard[i][j].value) != bitvecMap.end())
	    cur = bitvecMap[cellBoard[i][j].value - '1'];

	  rows[i].status = rows[i].status | cur;
	  rows[i].validCount++;
	  columns[j].status = columns[j].status | cur;
	  rows[i].validCount++;
	  int blockIdx = (i/3)*3 + j/3;
	  blocks[blockIdx].status = blocks[blockIdx].status | cur;
	  blocks[blockIdx].validCount++;
	}
      }
    }
  }

  void calcCandidates() {
    for (int i = 0;i < len;i++) {
      for (int j = 0;j < len;j++) {
	SudokuCell &cell = cellBoard[i][j];
	if (cell.value == '.') {
	  cell.candidates = rows[i].status | columns[j].status | blocks[(i/3)*3 + j/3].status;
	  cell.candidateCount = countZeroOne(cell.candidates, false);
	} else {
	  cell.candidateCount = 1;
	  cell.candidates = bitvec[cell.value - '1'];
	}
      }
    }
  }

  int countZeroOne(unsigned short val, bool zero) {
    int count = 0;
    if (zero)
      val = ~val;
    while(val) {
      count++;
      val = val >> 1;
    }
    return count;
  }

private:
  vector<vector<SudokuCell> > cellBoard;
  array<Unit, 9> rows;
  array<Unit, 9> columns;
  array<Unit, 9> blocks;
};

#define SUDOKUSOLVER2_H
#ifdef SUDOKUSOLVER2_H
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
#endif //SUDOKUSOLVER2_H
