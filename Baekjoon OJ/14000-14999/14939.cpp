#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 7;
const int dy[] = { 0, 1, 0, -1, 0 };
const int dx[] = { 0, 0, 1, 0, -1 };

vector<string> a(10);
vector<int> arr;

void modify(int y, int x, vector<string>& b) {
    for (int k = 0; k < 5; k++) {
        int ny = y + dy[k], nx = x + dx[k];
        if (ny < 0 || 10 <= ny || nx < 0 || 10 <= nx) continue;
        if (b[ny][nx] == 'O') b[ny][nx] = '#';
        else if (b[ny][nx] == '#') b[ny][nx] = 'O';
    }
}

int cal() {
    int ret = 0;

    vector<string> b = a;

    for (auto& i : arr) {
        int y = 0, x = i;
        modify(y, x, b);
        ret++;
    }

    for (int y = 1; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            if (b[y - 1][x] == 'O') {
                modify(y, x, b);
                ret++;
            }
        }
    }

    int pos = 1;
    for (auto& i : b)
        for (auto& j : i) if (j == 'O') pos = 0;
    
    return (pos ? ret : INF);
}

int bt(int v) {
    if (v == 10) return cal();
    int ret = bt(v + 1);
    arr.push_back(v);
    ret = min(ret, bt(v + 1));
    arr.pop_back();
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    for (auto& i : a) cin >> i;

    int ans = bt(0);
    cout << (ans != INF ? ans : -1);
}