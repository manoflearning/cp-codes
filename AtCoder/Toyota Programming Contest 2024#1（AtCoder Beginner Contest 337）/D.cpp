// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int H, W, K;
vector<string> a;
vector<vector<int>> po, px;

int query(const vector<vector<int>>& psum, int sy, int ey, int sx, int ex) {
    return psum[ey][ex] - psum[ey][sx - 1] - psum[sy - 1][ex] + psum[sy - 1][sx - 1];
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> H >> W >> K;
    a.resize(H);
    for (auto& i : a) cin >> i;

    po.resize(H + 2, vector<int>(W + 2));
    px.resize(H + 2, vector<int>(W + 2));
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            po[i + 1][j + 1] = (a[i][j] == 'o');
            px[i + 1][j + 1] = (a[i][j] == 'x');
        }
    }

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            po[i + 1][j + 1] = po[i + 1][j + 1] + po[i + 1][j] + po[i][j + 1] - po[i][j];
            px[i + 1][j + 1] = px[i + 1][j + 1] + px[i + 1][j] + px[i][j + 1] - px[i][j];
        }
    }

    int ans = INF;
    for (int y = 1; y <= H; y++) {
        for (int x = 1; x <= W; x++) {
            if (y + K - 1 <= H) {
                if (query(px, y, y + K - 1, x, x) == 0) {
                    ans = min(ans, K - query(po, y, y + K - 1, x, x));
                }
            }
            if (x + K - 1 <= W) {
                if (query(px, y, y, x, x + K - 1) == 0) {
                    ans = min(ans, K - query(po, y, y, x, x + K - 1));
                }
            }
        }
    }

    cout << (ans == INF ? -1 : ans);
}