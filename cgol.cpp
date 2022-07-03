#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

class Board {
  public:
    Board(std::vector < std::vector < char >> inputboard) {
      for (std::vector < char > row: inputboard) board.push_back(row);
    }

  void iterate() {
    std::vector < std::vector < char >> tmpboard = board;

    for (int row = 0; row < board.size(); row++) {
      for (int col = 0; col < board[row].size(); col++) {
        char node = board[row][col];
        int pos[2] = {
          row,
          col
        };
        int numNeighbours = getNumAliveNeighbours(pos);

        // Changes node depending on its state and how many neighbours are alive
        // - Any live cell with two or three live neighbours survives.
        // - Any dead cell with three live neighbours becomes a live cell.
        // - All other live cells die in the next generation. Similarly, all other dead cells stay dead.
        if (node == 'x') {
          if (numNeighbours < 2 || numNeighbours > 3) {
            tmpboard[row][col] = '-';
          } else {
            tmpboard[row][col] = 'x';
          }
        } else {
          if (numNeighbours == 3) {
            tmpboard[row][col] = 'x';
          } else {
            tmpboard[row][col] = '-';
          }
        }
      }
    }

    board = tmpboard;
  }

  void printBoard() {
    for (std::vector < char > row: board) {
      std::cout << std::endl;
      for (char node: row) std::cout << node << " ";
    }
    std::cout << std::endl;
  }

  private:
    std::vector < std::vector < char >> board;

  bool isValidNode(int rowID, int colID) {
    // Is valid if the rowID and colID falls within the bounds of the board
    return rowID >= 0 && rowID < board.size() && colID >= 0 && colID < board[0].size();
  }

  int getNumAliveNeighbours(int position[2]) {
    int numAlive = 0;
    int row = position[0];
    int col = position[1];

    // Set positions for the nodes surrounding current node
    int neighbourPositions[8][2] = {
      {
        row,
        col - 1
      },
      {
        row - 1,
        col - 1
      },
      {
        row - 1,
        col
      },
      {
        row - 1,
        col + 1
      },
      {
        row,
        col + 1
      },
      {
        row + 1,
        col + 1
      },
      {
        row + 1,
        col
      },
      {
        row + 1,
        col - 1
      }
    };

    for (int i = 0; i < 8; i++) {
      int rowID = neighbourPositions[i][0];
      int colID = neighbourPositions[i][1];

      // If the node is valid and alive, increment numAlive counter
      if (isValidNode(rowID, colID) && board[rowID][colID] == 'x') numAlive++;
    }

    return numAlive;
  }
};

int main(int argc, char ** argv) {
  if (argc == 1) {
    std::cout << "Please enter a valid filename\nUsage cgol.exe <filename> <iterations>\n";
    return -1;
  }

  int numIterations = 1;

  // Check for user inputted iterations
  if (argc == 3) {
    std::string striterations(argv[2]);
    // If iterations entered is valid, change  the number of iterations.
    // Else use the default values
    if (striterations.find_first_not_of("0123456789") == std::string::npos) {
      numIterations = std::stoi(striterations);
    } else {
      std::cout << "Invalid number of iterations entered\n";
    }
  }

  std::string filename = argv[1];

  // Open file
  std::ifstream boardfile;
  boardfile.open(filename);

  if (!boardfile.good()) {
    std::cout << "File not found\n";
    return -1;
  }

  // Board setup
  std::vector < std::vector < char >> board;
  int previousSize = 0;

  for (std::string line; std::getline(boardfile, line);) {
    // Exit of the board size is invalid
    if (previousSize > 0 && line.length() != previousSize) {
      std::cout << "All rows in board file must be of the same length. Exiting\n";
      return -1;
    }

    // Exit of the board file does not contain valid characters
    if (line.find_first_not_of("-x") != std::string::npos) {
      std::cout << "File contains invalid characters\n";
      return -1;
    }

    std::vector < char > row;
    for (char c: line) row.push_back(c);

    board.push_back(row);
  }

  // Start Game of Life loop
  Board cgol(board);
  cgol.printBoard();

  for (int i = 0; i < numIterations; i++) {
    cgol.iterate();
    cgol.printBoard();
  }
}