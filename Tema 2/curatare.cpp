#include <bits/stdc++.h>

class QItem {
 public:
    int row;
    int col;
    int dist;
    QItem(int x, int y, int w)
        : row(x), col(y), dist(w) {
    }
};

class Square {
 public:
    int row, col;
    bool is_clean;
    Square(int r, int c, bool ic) {
        row = r;
        col = c;
        is_clean = ic;
    }
};

int min_dist(std::vector<std::vector<char>> grid, int start_row, int start_col,
             int dest_row, int dest_col, int N, int M) {
    QItem source(0, 0, 0);
    source.row = start_row;
    source.col = start_col;

    bool visited[N][M];
    // mark the blocked squares as visited
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (grid[i][j] == 'X') {
                visited[i][j] = true;
            } else {
                visited[i][j] = false;
            }
        }
    }

    // apply BFS to find the shortest path
    std::queue<QItem> q;
    q.push(source);
    visited[source.row][source.col] = true;

    while (!q.empty()) {
        QItem p = q.front();
        q.pop();

        // if we have reached the destination, return the distance
        if (p.row == dest_row && p.col == dest_col) {
            return p.dist;
        }

        // check if the adjacent squares are valid and unvisited
        // moving up
        if (p.row - 1 >= 0 && !visited[p.row - 1][p.col]) {
            QItem qi(p.row - 1, p.col, p.dist + 1);
            q.push(qi);
            visited[p.row - 1][p.col] = true;
        }

        // moving down
        if (p.row + 1 < N && !visited[p.row + 1][p.col]) {
            QItem qi(p.row + 1, p.col, p.dist + 1);
            q.push(qi);
            visited[p.row + 1][p.col] = true;
        }

        // moving left
        if (p.col - 1 >= 0 && !visited[p.row][p.col - 1]) {
            QItem qi(p.row, p.col - 1, p.dist + 1);
            q.push(qi);
            visited[p.row][p.col - 1] = true;
        }

        // moving right
        if (p.col + 1 < M && !visited[p.row][p.col + 1]) {
            QItem qi(p.row, p.col + 1, p.dist + 1);
            q.push(qi);
            visited[p.row][p.col + 1] = true;
        }
    }

    return -1;
}

bool found_solution(std::vector<Square> dirty_squares) {
    bool all_clean = true;
    for (unsigned long i = 0; i < dirty_squares.size(); i++) {
        if (!dirty_squares[i].is_clean) {
            all_clean = false;
            break;
        }
    }

    return all_clean;
}

void update_result(int *result, std::vector<int> robot_traveled_dist) {
    int max_dist = 0;
    // find the maximum traveled distance
    for (unsigned long i = 0; i < robot_traveled_dist.size(); i++) {
        if (robot_traveled_dist[i] > max_dist) {
            max_dist = robot_traveled_dist[i];
        }
    }

    // find the minimum result
    if (max_dist < *result) {
        *result = max_dist;
    }
}

void back(int *result, std::vector<std::vector<int>> robot_to_dirty_dist,
          std::vector<std::vector<int>> dirty_to_dirty_dist,
          std::vector<Square> dirty_squares, std::vector<Square> robot_squares,
          std::vector<int> robot_traveled_dist) {
    // check if we found a solution <=> all squares have been cleaned
    if (found_solution(dirty_squares)) {
        update_result(result, robot_traveled_dist);
        return;
    }

    for (unsigned long i = 0; i < dirty_squares.size(); i++) {
        for (unsigned long j = 0; j < robot_squares.size(); j++) {
            if (!dirty_squares[i].is_clean) {
                // save the current state of the robot and the distances from
                // robot to dirty squares
                int old_r = robot_squares[j].row;
                int old_c = robot_squares[j].col;
                std::vector<std::vector<int>> old_robot_to_dirty_dist;
                old_robot_to_dirty_dist = robot_to_dirty_dist;

                 // update the robot's position
                robot_squares[j].row = dirty_squares[i].row;
                robot_squares[j].col = dirty_squares[i].col;

                // update the robot's traveled distance
                robot_traveled_dist[j] += robot_to_dirty_dist[j][i];

                // clean the square
                dirty_squares[i].is_clean = true;

                // update the distances from robot to dirty squares
                for (unsigned long k = 0; k < dirty_squares.size(); k++) {
                    if (k != i) {
                        robot_to_dirty_dist[j][k] = dirty_to_dirty_dist[i][k];
                    }
                }

                back(result, robot_to_dirty_dist, dirty_to_dirty_dist,
                     dirty_squares, robot_squares, robot_traveled_dist);

                // restore the robot's state
                robot_squares[j].row = old_r;
                robot_squares[j].col = old_c;
                dirty_squares[i].is_clean = false;
                robot_traveled_dist[j] -= robot_to_dirty_dist[j][i];
                robot_to_dirty_dist = old_robot_to_dirty_dist;
            }
        }
    }
}

int main() {
    std::ifstream fin("curatare.in");
    std::ofstream fout("curatare.out");

    int n, m;
    fin >> n >> m;
    std::vector<std::vector<char>> grid(n, std::vector<char>(m));

    std::vector<Square> dirty_squares;
    // robot squares are the starting squares
    std::vector<Square> robot_squares;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fin >> grid[i][j];

            if (grid[i][j] == 'R') {
                robot_squares.push_back(Square(i, j, true));
            } else if (grid[i][j] == 'S') {
                dirty_squares.push_back(Square(i, j, false));
            }
        }
    }

    std::vector<std::vector<int>> robot_to_dirty_dist(robot_squares.size(),
                                  std::vector<int>(dirty_squares.size(), 0));
    std::vector<std::vector<int>> dirty_to_dirty_dist(dirty_squares.size(),
                                  std::vector<int>(dirty_squares.size(), 0));

    // find the minimum distance between each dirty square and each dirty square
    for (unsigned long i = 0; i < dirty_squares.size(); i++) {
        for (unsigned long j = 0; j < dirty_squares.size(); j++) {
            if (i != j) {
                int min = min_dist(grid, dirty_squares[i].row,
                                   dirty_squares[i].col, dirty_squares[j].row,
                                   dirty_squares[j].col, n, m);
                dirty_to_dirty_dist[i][j] = min;
            }
        }
    }

    // find the minimum distance between each robot square and each dirty square
    for (unsigned long i = 0; i < robot_squares.size(); i++) {
        for (unsigned long j = 0; j < dirty_squares.size(); j++) {
            int min = min_dist(grid, robot_squares[i].row,
                               robot_squares[i].col, dirty_squares[j].row,
                               dirty_squares[j].col, n, m);
            robot_to_dirty_dist[i][j] = min;
        }
    }

    std::vector<int> robot_traveled_dist(robot_squares.size(), 0);
    int result = INT_MAX;

    back(&result, robot_to_dirty_dist, dirty_to_dirty_dist, dirty_squares,
         robot_squares, robot_traveled_dist);
    fout << result << '\n';

    fin.close();
    fout.close();

    return 0;
}
