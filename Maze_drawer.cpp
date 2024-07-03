#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "template_stack.h" // This stack implementation

using namespace std;

// Süleyman Berber

int number_of_walls = 0; // Global variable to track the number of walls

// Function to generate a random direction
int randomDirection(int num) {
    int randomNumber = (rand() % num) + 1; // Generate a random number in the range: 1 to count
    return randomNumber;
}

// Struct to represent individual cells in the maze
struct cells {
    bool visited;
    bool up;
    bool down;
    bool left;
    bool right;
    bool path;
    
    // Constructor to initialize cell properties
    cells() : visited(false), left(true), right(true), up(true), down(true), path(false) {};
};

// Function to check if there's a wall to knock down
bool check_wall(int &direction, int row, int column, vector<vector<cells>> &generated_maze) {
    int maze_row = generated_maze.size() - 1;
    int maze_column = generated_maze[0].size() - 1;
    vector<int> neighbours;

    // Check adjacent cells for unvisited neighbours
    // up
    if (row != maze_row && !generated_maze[maze_row - (row + 1)][column].visited) {
        neighbours.push_back(1);
    }
    // down
    if (row != 0 && !generated_maze[maze_row - (row - 1)][column].visited) {
        neighbours.push_back(2);
    }
    // left
    if (column != 0 && !generated_maze[maze_row - row][column - 1].visited) {
        neighbours.push_back(3);
    }
    // right
    if (column != maze_column && !generated_maze[maze_row - row][column + 1].visited) {
        neighbours.push_back(4);
    }
    
    // If there are unvisited neighbours, choose one randomly
    if (neighbours.size() != 0) {
        int i = randomDirection(neighbours.size());
        if (neighbours[i - 1] == 1) {
            direction = 1;
        } else if (neighbours[i - 1] == 2) {
            direction = 2;
        } else if (neighbours[i - 1] == 3) {
            direction = 3;
        } else if (neighbours[i - 1] == 4) {
            direction = 4;
        }
        return true;
    } else {
        return false;
    }
}

// Function to knock down walls based on chosen direction
void knock_walls(int direction, vector<vector<cells>> &generated_maze, int row, int column, pair<int, int> &added) {
    int maze_row = generated_maze.size() - 1;
    // Knock down walls based on direction after checking the cell which is visited or not
    
    if (direction == 1) { // up
        generated_maze[maze_row - row][column].up = false;
        generated_maze[maze_row - (row + 1)][column].down = false;
        generated_maze[maze_row - (row + 1)][column].visited = true;
        added = make_pair(row + 1, column);
        
    } else if (direction == 2) { // down
        generated_maze[maze_row - row][column].down = false;
        generated_maze[maze_row - (row - 1)][column].up = false;
        generated_maze[maze_row - (row - 1)][column].visited = true;
        added = make_pair(row - 1, column);
        
    } else if (direction == 3) { // left
        generated_maze[maze_row - row][column].left = false;
        generated_maze[maze_row - row][column - 1].right = false;
        generated_maze[maze_row - row][column - 1].visited = true;
        added = make_pair(row, column - 1);
        
    } else if (direction == 4) { // right
        generated_maze[maze_row - row][column].right = false;
        generated_maze[maze_row - row][column + 1].left = false;
        generated_maze[maze_row - row][column + 1].visited = true;
        added = make_pair(row, column + 1);
    }
}

// Function to generate the maze
void generate_maze(int m, int n, vector<vector<cells>> &generated_maze) {
    
    int number_of_walls = m * n - 1; // Total number of walls
    int visited_cell = 1; // Counter for visited cells
    Stack<pair<int, int>> maze; // Stack to store visited cells
    int row, column = 0;
    
    // Start generating maze from cell (0,0)
    maze.push(make_pair(0, 0));
    generated_maze[m - 1][0].visited = true;
     
    while (!maze.isEmpty()) {
        
        pair<int, int> current = maze.topAndPop();
        pair<int, int> added;
        row = current.first;
        column = current.second;
        int direction = 0;
        
        // Check for walls to knock down
        if (check_wall(direction, row, column, generated_maze)) {
            knock_walls(direction, generated_maze, row, column, added);
            visited_cell++;
            maze.push(current);
            maze.push(added);
            
        } else {
            // If no walls to knock down, backtrack
            pair<int, int> new_current = maze.topAndPop();
            pair<int, int> new_added;
            
            while (check_wall(direction, new_current.first, new_current.second, generated_maze) == false) {
                new_current = maze.topAndPop();
                row = new_current.first;
                column = new_current.second;
            }
            knock_walls(direction, generated_maze, new_current.first, new_current.second, new_added);
            visited_cell++;
            maze.push(new_current);
            maze.push(new_added);
        }
        number_of_walls--;
        if (number_of_walls == 0 && visited_cell == m * n)
            break;
    }
}

// Function to write maze information to file
void form_file(vector<vector<cells>> &mazes, int maze_number) {
    string name_of_file = "maze_" + to_string(maze_number + 1) + ".txt";
    ofstream out(name_of_file);
    out << mazes.size() << " " << mazes[0].size() << " ";

    for (int i = 0; i < mazes.size(); i++) {
        int row = mazes.size() - 1;
        for (int j = 0; j < mazes[0].size(); j++) {
            out << "\nx=" << j << " y=" << i << " l=" <<  mazes[row - i][j].left << " r=" << mazes[row - i][j].right
            << " u=" <<  mazes[row - i][j].up << " d=" << mazes[row - i][j].down << " ";
        }
    }
    out.close();
}

// Function to convert path to file
void convert_path_to_file(int entry_x, int entry_y, int exit_x, int exit_y, vector<vector<cells>> &mazes, int maze_number,
                   Stack<pair<int, int>> path) {
    Stack<pair<int, int>> temp_path;
    
    while (!path.isEmpty()) {
        pair<int,int> temp = path.topAndPop();
        temp_path.push(temp);
    }
    string filename = "maze_" + to_string(maze_number) + "_path_" + to_string(entry_y) + "_" + to_string(entry_x) + "_" + to_string(exit_y) + "_" + to_string(exit_x) + ".txt";
    ofstream out(filename);

    while (!temp_path.isEmpty()) {
        pair<int,int> temp = temp_path.topAndPop();
        out << temp.second  << " " << temp.first  << endl;
    }
    out.close();
}

// Function to check if a path can pass through a wall
bool pass_wall(int &direction, int row, int column, vector<vector<cells>> &generated_maze) {
    
    int maze_row = generated_maze.size() - 1;
    vector<int> neighbours;
    // Check adjacent cells for passages
    // up
    if (!generated_maze[maze_row - row][column].up && !generated_maze[maze_row - (row + 1)][column].path) {
        neighbours.push_back(1);
    }
    // down
    if (!generated_maze[maze_row - row][column].down && !generated_maze[maze_row - (row - 1)][column].path) {
        neighbours.push_back(2);
    }
    // left
    if (!generated_maze[maze_row - row][column].left && !generated_maze[maze_row - row][column - 1].path) {
        neighbours.push_back(3);
    }
    // right
    if (!generated_maze[maze_row - row][column].right && !generated_maze[maze_row - row][column + 1].path) {
        neighbours.push_back(4);
    }
    
    // If there are passages, choose one randomly
    if (neighbours.size() != 0) {
        int i = randomDirection(neighbours.size());
        if (neighbours[i - 1] == 1) {
            direction = 1;
        } else if (neighbours[i - 1] == 2) {
            direction = 2;
        } else if (neighbours[i - 1] == 3) {
            direction = 3;
        } else if (neighbours[i - 1] == 4) {
            direction = 4;
        }
        return true;
    } else {
        return false;
    }
}

// Function to find path from entry to exit
void find_path(vector<vector<cells>> &searched_maze, int num_of_maze, int entry_row, int entry_column, int exit_row, int exit_column) {
    
    Stack<pair<int, int>> path;
    pair<int, int> entry_cell, exit_cell;
    entry_cell = make_pair(entry_row, entry_column);
    exit_cell = make_pair(exit_row, exit_column);
    int row, column;
    
    searched_maze[searched_maze.size() - 1 - entry_row][entry_column].path = true;
    path.push(make_pair(entry_row, entry_column));
    
    while (!path.isEmpty()) {
        
        pair<int, int> current = path.topAndPop();
        pair<int, int> next_cell;
        row = current.first;
        column = current.second;
        
        if (row == exit_row && column == exit_column) {
            path.push(current);
            convert_path_to_file(entry_row, entry_column, exit_row, exit_column, searched_maze, num_of_maze, path);
            break;
        }
        int direction = -1;
        
        if (pass_wall(direction, row, column, searched_maze)) {
            
            if (direction == 1) {
                next_cell = make_pair(row + 1, column);
            } else if (direction == 2) {
                next_cell = make_pair(row - 1, column);
            } else if (direction == 3) {
                next_cell = make_pair(row, column - 1);
            } else if (direction == 4) {
                next_cell = make_pair(row, column + 1);
            }
            
            searched_maze[searched_maze.size() - 1 - next_cell.first][next_cell.second].path = true;
            path.push(current);
            path.push(next_cell);
        } 
        else {
            path.push(current);
            path.pop();
        }
    }
}

// Function to generate a new maze
void generate_new_maze(int row, int col, int num_of_maze, vector<vector<cells>> &maze) {
    generate_maze(row, col, maze); // Generate the maze
    form_file(maze, num_of_maze); // Write maze information to file
}

// Main function
int main() {
    
    int maze_number, columns, rows, maze, entry_row, entry_column, exit_row, exit_column;
    vector<vector<vector<cells>>> all_mazes;
    // Input number of mazes to generate
    cout << "Enter the number of mazes: ";
    cin >> maze_number;
    // Input number of rows and columns for each maze
    cout << "Enter the number of rows and columns (M and N): ";
    cin >> rows >> columns;
    // Generate mazes
    for (int i = 0; i < maze_number; i++) {
        all_mazes.push_back(vector<vector<cells>>(rows, vector<cells>(columns)));
        generate_new_maze(rows, columns, i, all_mazes[i]);
    }
    cout << "All mazes are generated." << endl;
    // Input maze ID to find a path
    cout << "Enter a maze ID between 1 to 5 inclusive to find a path: ";
    cin >> maze;
    // Input entry and exit points
    cout << "Enter x and y coordinates of the entry points (x,y) or (column,row): ";
    cin >> entry_column >> entry_row;
    cout << "Enter x and y coordinates of the exit points (x,y) or (column,row): ";
    cin >> exit_column >> exit_row;
    // Find path in the chosen maze
    find_path(all_mazes[maze - 1], maze, entry_row, entry_column, exit_row, exit_column);
    return 0;
}
