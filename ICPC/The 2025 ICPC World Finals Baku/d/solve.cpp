#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int) (x).size()
typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;

constexpr int INF = 1e9 + 7;
constexpr int dy[4] = {-1, 1, 0, 0};
constexpr int dx[4] = {0, 0, 1, -1};

int r, c;
vector<string> a;

string s;

vector<vector<int>> ords;
vector<vector<int>> dp;

int f(int bit, int i, int y, int x) {
    int &ret = dp[bit][i];
    if (i == sz(s)) return ret = 0;
    if (ret != -1) return ret;

    ret = INF;

    for (int nbit = 0; nbit < 24; nbit++) {
        int ny, nx;
        bool yes = 0;
        for (int d : ords[nbit]) {
            ny = y + dy[d], nx = x + dx[d];
            if (ny < 0 || r <= ny || nx < 0 || c <= nx) continue;
            if (a[ny][nx] == '#') continue;

            yes = s[i] == "NSEW"[d];
            break;
        }
        if (!yes) continue;
        ret = min(ret, (bit != nbit) + f(nbit, i + 1, ny, nx));
    }

    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    cin >> r >> c;

    a.assign(r, string());
    for (auto &i : a) cin >> i;

    cin >> s;

    vector<int> ord(4);
    iota(all(ord), 0);
    do {
        ords.push_back(ord);
    } while (next_permutation(all(ord)));

    assert(sz(ords) == 24);

    dp.assign(24, vector<int>(sz(s) + 1, -1));

    int st_y = -1, st_x = -1;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (a[i][j] == 'S') {
                st_y = i, st_x = j;
            }
        }
    }

    int ans = INF;
    for (int bit = 0; bit < 24; bit++) {
        ans = min(ans, f(bit, 0, st_y, st_x));
    }
    cout << ans << '\n';
}
