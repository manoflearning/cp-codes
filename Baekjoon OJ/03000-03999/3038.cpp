#include <bits/stdc++.h>
using namespace std;

vector<int> t[16];

void bfs(int i, int st, int bit) {
    queue<int> q;
    q.push(st);
    int idx = 1;
    while (!q.empty()) {
        int v = q.front(); q.pop();
        t[i][v] = 2 * t[i - 1][idx++] + (bit ^ (v < (1 << (i - 1))) ? 1 : 0);
        if ((1 << (i - 1)) <= v) continue;
        q.push(v << 1);
        q.push(v << 1 | 1);
    }
}

int n;
void dfs(int v) {
    cout << t[n][v] << ' ';
    if ((1 << (n - 1)) <= v) return;
    dfs(v << 1);
    dfs(v << 1 | 1);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    for (int i = 1; i <= 15; i++) t[i].resize(1 << i);

    t[1][1] = 1;
    for (int i = 2; i <= 15; i++) {
        t[i][1] = 1;
        bfs(i, 2, 0);
        bfs(i, 3, 1);
    }

    cin >> n;
    dfs(1);
}