
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9;

struct Point {
    int r, c;
};

int main() {
    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<int>> grid(m, vector<int>(n));
    Point start, home;
    vector<Point> shops;

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grid[i][j];
            if (grid[i][j] == 2) {
                start = {i, j};
            } else if (grid[i][j] == 3) {
                home = {i, j};
            } else if (grid[i][j] == 4) {
                shops.push_back({i, j});
            }
        }
    }

    auto bfs = [&](Point s) {
        vector<vector<int>> dist(m, vector<int>(n, INF));
        queue<Point> q;
        dist[s.r][s.c] = 0;
        q.push(s);

        int dr[] = {0, 0, 1, -1};
        int dc[] = {1, -1, 0, 0};

        while (!q.empty()) {
            Point curr = q.front();
            q.pop();

            for (int i = 0; i < 4; ++i) {
                int nr = curr.r + dr[i];
                int nc = curr.c + dc[i];

                if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] != 1) {
                    if (dist[nr][nc] == INF) {
                        dist[nr][nc] = dist[curr.r][curr.c] + 1;
                        q.push({nr, nc});
                    }
                }
            }
        }
        return dist;
    };

    vector<vector<int>> dist_start = bfs(start);
    vector<vector<int>> dist_home = bfs(home);

    int min_dist = INF;
    for (const auto& shop : shops) {
        if (dist_start[shop.r][shop.c] != INF && dist_home[shop.r][shop.c] != INF) {
            min_dist = min(min_dist, dist_start[shop.r][shop.c] + dist_home[shop.r][shop.c]);
        }
    }

    if (min_dist == INF) {
        // This case might not happen based on problem description, but good to handle
        cout << -1 << endl;
    } else {
        cout << min_dist << endl;
    }

    return 0;
}
