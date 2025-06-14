#pragma GCC optimize("O3")
#pragma GCC optmize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int h, w;
vector<string> s;
vector<vector<int>> psum;
int cntu[3030 * 3030 * 2];

void init() {}

void input() {
    cin >> h >> w;
    s.resize(h);
    for (auto &i : s) cin >> i;
}

void hw_swap() {
    if (h >= w) return;
    vector<string> tmp(w, string(h, '.'));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            tmp[j][i] = s[i][j];
        }
    }
    s = tmp;
    swap(h, w);
}

void build_psum() {
    psum.clear();
    psum.resize(h + 1, vector<int>(w + 1));
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            int val = (s[y][x] == '#' ? 1 : -1);
            psum[y + 1][x + 1] = val + psum[y + 1][x] + psum[y][x + 1] - psum[y][x];
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        hw_swap();

        build_psum();

        ll ans = 0;
        for (int l = 1; l <= w; l++) {
            for (int r = l; r <= w; r++) {
                for (int i = 1; i <= h; i++) {
                    cntu[psum[i - 1][r] - psum[i - 1][l - 1] + 3030 * 3030]++;
                    ans += cntu[psum[i][r] - psum[i][l - 1] + 3030 * 3030];
                }
                for (int i = 1; i <= h; i++) {
                    cntu[psum[i - 1][r] - psum[i - 1][l - 1] + 3030 * 3030]--;
                }
            }
        }

        cout << ans << '\n';
    }
}
