// https://cses.fi/problemset/task/1192

#include <bits/stdc++.h>

using namespace std;

#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0)
#define SLOG(x) cout << x << endl;
#define ff first
#define ss second

typedef pair<int, int> iVec2;

struct square {
    char type;
    bool checked;
};

square maze[1000][1000];

int main() {
    FAST_IO;

    int lar, alt;
    cin >> alt >> lar;

    int i, j;
    int out = 0;

    for(i = 0; i < alt; i++) {
        for(j = 0; j < lar; j++) {
            cin >> maze[i][j].type;
        }
    }

    for(i = 0; i < alt; i++) {
        for(j = 0; j < lar; j++) {
            square* current = &maze[i][j];

            if(current->checked && current->type == '#') {
                continue;
            }

            out++;

            queue<iVec2> bfs;
            bfs.emplace(i, j);

            while(!bfs.empty()) {
                iVec2 front = bfs.front();
                bfs.pop();

                if(maze[front.ff][front.ss].checked && maze[front.ff][front.ss].type == '#') {
                    continue;
                }

                maze[front.ff][front.ss].checked = true;

                bfs.emplace(front.ff - 1, front.ss - 1);
                bfs.emplace(front.ff - 1, front.ss + 1);
                bfs.emplace(front.ff + 1, front.ss - 1);
                bfs.emplace(front.ff + 1, front.ss + 1);
            }
        }
    }

    cout << out;

    return 0;
}
