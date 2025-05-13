#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void dfs(vector<vector<int>>& grid, int i, int j, int n) {
    stack<pair<int, int>> st;
    st.push({i, j});
    grid[i][j] = -1; // Помечаем как посещенный

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (!st.empty()) {
        auto current = st.top();
        st.pop();
        int x = current.first;
        int y = current.second;

        for (int k = 0; k < 4; ++k) {
            int nx = x + dx[k];
            int ny = y + dy[k];

            if (nx >= 0 && nx < n && ny >= 0 && ny < n && grid[nx][ny] == 0) {
                grid[nx][ny] = -1;
                st.push({nx, ny});
            }
        }
    }
}

int count_water_bodies(vector<vector<int>>& grid, int n) {
    int count = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 0) {
                dfs(grid, i, j, n);
                count++;
            }
        }
    }
    return count;
}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> grid(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grid[i][j];
        }
    }

    cout << count_water_bodies(grid, n) << endl;

    return 0;
}