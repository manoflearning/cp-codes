#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

const int INF = 1e9 + 7;

const int dy[] = { 0, 1, 0, -1 };
const int dx[] = { 1, 0, -1, 0 };

vector<string> a(8);
int dist[8][8][4][1 << 10];
string inst[8][8][4][1 << 10];
int ice[8][8], ice_cnt;

int eny = -1, enx = -1;

void bfs() {
    memset(dist, -1, sizeof(dist));

    struct State { int y, x, dir, melted; };
    queue<State> qu;

    dist[7][0][0][0] = 0;
    qu.push({ 7, 0, 0, 0 });

    while (!qu.empty()) {
        auto [y, x, dir, melted] = qu.front();
        qu.pop();

        // cout << y << ' ' << x << ' ' << dir << ' ' << melted << '\n';
        // cout << inst[y][x][dir][melted] << '\n';

        // move forward
        {
            int ny = y + dy[dir], nx = x + dx[dir];
            
            bool is_valid = 1;
            if (ny < 0 || 8 <= ny || nx < 0 || 8 <= nx) is_valid = 0;
            if (is_valid && a[ny][nx] == 'C') is_valid = 0;
            if (is_valid && a[ny][nx] == 'I' && !(melted & (1 << ice[ny][nx]))) is_valid = 0;
            if (is_valid && dist[ny][nx][dir][melted] != -1) is_valid = 0;

            if (is_valid) {
                dist[ny][nx][dir][melted] = 1 + dist[y][x][dir][melted];
                inst[ny][nx][dir][melted] = inst[y][x][dir][melted] + 'F';
                qu.push({ ny, nx, dir, melted });
            }
        }
        // turn left or right
        for (int i = 1; i < 4; i += 2) {
            int ndir = (dir + i) % 4;

            bool is_valid = 1;
            if (dist[y][x][ndir][melted] != -1) is_valid = 0;

            if (is_valid) {
                dist[y][x][ndir][melted] = 1 + dist[y][x][dir][melted];
                inst[y][x][ndir][melted] = inst[y][x][dir][melted] + (i == 1 ? 'R' : 'L');
                qu.push({ y, x, ndir, melted });
            }
        }
        // shoot laser
        {
            int icey = y + dy[dir], icex = x + dx[dir];
            int nmelted = melted | (1 << ice[icey][icex]);
            
            bool is_valid = 1;
            if (icey < 0 || 8 <= icey || icex < 0 || 8 <= icex) is_valid = 0;
            if (is_valid && a[icey][icex] != 'I' || (melted & (1 << ice[icey][icex]))) is_valid = 0;
            if (is_valid && dist[y][x][dir][nmelted] != -1) is_valid = 0;

            if (is_valid) {
                dist[y][x][dir][nmelted] = 1 + dist[y][x][dir][melted];
                inst[y][x][dir][nmelted] = inst[y][x][dir][melted] + 'X';
                qu.push({ y, x, dir, nmelted });
            }
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    for (auto& i : a) cin >> i;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (a[i][j] == 'D') eny = i, enx = j;
            if (a[i][j] == 'I') ice[i][j] = ice_cnt++;
        }
    }

    bfs();

    string ans = "*";
    for (int melted = 0; melted < (1 << ice_cnt); melted++) {
        for (int dir = 0; dir < 4; dir++) {
            if (dist[eny][enx][dir][melted] == -1) continue;
            if (ans == "*" || sz(inst[eny][enx][dir][melted]) < sz(ans)) {
                ans = inst[eny][enx][dir][melted];
            }
        }
    }

    if (ans != "*") cout << ans;
    else cout << "no solution";
}
