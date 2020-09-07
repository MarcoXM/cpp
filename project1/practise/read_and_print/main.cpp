#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using std::cout;
using std::vector;
using std::string;
using std::ifstream;

// TODO: Add PrintBoard function here.
void PrintBoard(const vector<vector<int>> board) {
    for (int i = 0 ; i < board.size(); i++){
        for (int j = 0; j < board[0].size(); j++) {
            cout << board[i][j];
        }
        cout << "\n";
    }

}
void ReadBoardFile(string path) {
    ifstream myfile (path);
    if (myfile){
        string line;
        while (getline(myfile, line)){
            cout << line <<"\n";
        }
    }
}

vector<vector<int>> ReadBoardFile2(string path) {
  ifstream myfile (path);
  vector<vector<int>> board{};
  if (myfile) {
    string line;
    while (getline(myfile, line)) {
      vector<int> row = ParseLine(line);
      board.push_back(row);
    }
  }
  return board;
}



int main() {
    vector<vector<int>> board{{0, 1, 0, 0, 0, 0},
                            {0, 1, 0, 0, 0, 0},
                            {0, 1, 0, 0, 0, 0},
                            {0, 1, 0, 0, 0, 0},
                            {0, 0, 0, 0, 1, 0}};

    // print out the  board 
    PrintBoard(board);
}
