#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

#include <algorithm>

class Block {
public:
    int value;
    Block(int val = 0) : value(val) {}
};

class Tetromino {
public:
    vector<vector<int>> shape;
    Tetromino(vector<vector<int>> s) : shape(s) {}
    void rotate() {
        vector<vector<int>> rotated(shape[0].size(), vector<int>(shape.size()));
        for (int i = 0; i < shape.size(); i++) {
            for (int j = 0; j < shape[0].size(); j++) {
                rotated[j][shape.size() - 1 - i] = shape[i][j];
            }
        }
        shape = rotated;
    }
};

class Grid {
public:
    vector<vector<Block>> cells;
    int width, height;

    Grid(int w = 10, int h = 20) : width(w), height(h) {
        cells = vector<vector<Block>>(h, vector<Block>(w));
    }

    void print() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (cells[i][j].value == 0) {
                    cout << "  ";
                } else {
                    cout << cells[i][j].value << " ";
                }
            }
            cout << endl;
        }
    }

    bool mergeBlocks() {
        bool merged = false;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width - 1; j++) {
                if (cells[i][j].value != 0 && cells[i][j].value == cells[i][j + 1].value) {
                    cells[i][j].value *= 2;
                    cells[i][j + 1].value = 0;
                    merged = true;
                }
            }
        }
        return merged;
    }
};

class Game {
public:
    Grid grid;
    int score;
    Game() : grid(), score(0) {}

    void start() {
        srand(time(0));
        cout << "Tetris 2048 Game Started!" << endl;
        spawnBlock();
    }

    void spawnBlock() {
        int x = rand() % grid.width;
        int y = 0;
        if (grid.cells[y][x].value == 0) {
            grid.cells[y][x].value = 2;
        }
    }

    void moveLeft() {
        for (int i = 0; i < grid.height; i++) {
            for (int j = 1; j < grid.width; j++) {
                if (grid.cells[i][j].value != 0) {
                    int k = j;
                    while (k > 0 && grid.cells[i][k - 1].value == 0) {
                        grid.cells[i][k - 1].value = grid.cells[i][k].value;
                        grid.cells[i][k].value = 0;
                        k--;
                    }
                }
            }
        }
    }

    void moveRight() {
        for (int i = 0; i < grid.height; i++) {
            for (int j = grid.width - 2; j >= 0; j--) {
                if (grid.cells[i][j].value != 0) {
                    int k = j;
                    while (k < grid.width - 1 && grid.cells[i][k + 1].value == 0) {
                        grid.cells[i][k + 1].value = grid.cells[i][k].value;
                        grid.cells[i][k].value = 0;
                        k++;
                    }
                }
            }
        }
    }

    bool isGameOver() {
        for (int i = 0; i < grid.height; i++) {
            for (int j = 0; j < grid.width; j++) {
                if (grid.cells[i][j].value == 0) {
                    return false;
                }
            }
        }
        return true;
    }

    void updateScore(int points) {
        score += points;
        cout << "Score: " << score << endl;
    }
};

void dropBlock(Grid &grid) {
    for (int i = grid.height - 2; i >= 0; i--) {
        for (int j = 0; j < grid.width; j++) {
            if (grid.cells[i][j].value != 0 && grid.cells[i + 1][j].value == 0) {
                grid.cells[i + 1][j].value = grid.cells[i][j].value;
                grid.cells[i][j].value = 0;
            }
        }
    }
}

#include <thread>
#include <chrono>

int main() {
    Game game;
    game.start();

    char input;
    while (!game.isGameOver()) {
        game.grid.print();
        cout << "Enter command (l: left, r: right, q: quit): ";
        if (cin.peek() != EOF) {
            cin >> input;
        } else {
            input = '\0';
        }

        switch (input) {
            case 'l':
                game.moveLeft();
                break;
            case 'r':
                game.moveRight();
                break;
            case 'q':
                cout << "Game Over! Final Score: " << game.score << endl;
                return 0;
            default:
                break;
        }

        if (game.grid.mergeBlocks()) {
            game.updateScore(10);
        }
        dropBlock(game.grid);
        game.spawnBlock();
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    cout << "Game Over! Final Score: " << game.score << endl;
    return 0;
}
