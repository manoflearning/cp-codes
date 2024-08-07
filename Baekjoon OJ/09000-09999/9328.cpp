#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()

const int dy[] = { 1, -1, 0, 0 };
const int dx[] = { 0, 0, 1, -1 };

int n, m;
vector<string> a;
set<char> keys;
bool vi[111][111]; 

void init() {
    a.clear();
    keys.clear();
    memset(vi, 0, sizeof(vi));
}

void input() {
    cin >> n >> m;

    a.resize(n + 2);
    a[0].resize(m + 2, '.');
    for (int i = 1; i <= n; i++) {
        string s; cin >> s;
        a[i] = "." + s + ".";
    }
    a[n + 1].resize(m + 2, '.');

    string s; cin >> s;
    for (auto& c : s) 
        if (c != '0') keys.insert(c);
}

void solve() {
    vi[0][0] = true;
    while (1) {
        queue<pii> q;
        for (int y = 0; y <= n + 1; y++) {
            for (int x = 0; x <= m + 1; x++) {
                if (vi[y][x]) q.push({ y, x });
            }
        }

        set<char> newKeys;
        while (!q.empty()) {
            auto [y, x] = q.front();
            q.pop();

            for (int d = 0; d < 4; d++) {
                int ny = y + dy[d], nx = x + dx[d];
                if (ny < 0 || n + 1 < ny || nx < 0 || m + 1 < nx) continue;
                if (vi[ny][nx]) continue;
                char c = a[ny][nx];
                if (c == '*') continue;
                if ('A' <= c && c <= 'Z' && !keys.count(c - 'A' + 'a')) continue;
                
                vi[ny][nx] = true;
                q.push({ ny, nx });
                if ('a' <= c && c <= 'z') newKeys.insert(c);
            }
        }

        if (newKeys.empty()) break;

        for (auto c : newKeys) keys.insert(c);
    }
}

int getAnswer() {
    int ret = 0;
    for (int y = 1; y <= n; y++) {
        for (int x = 1; x <= m; x++) {
            if (vi[y][x] && a[y][x] == '$') ret++;
        }
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        solve();

        cout << getAnswer() << '\n';
    }
}