#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

using shape = uint32_t;
using board = uint32_t;

constexpr int INF = 1e9 + 7;

const vector<vector<shape>> SHAPES = {
    {0b010111010,},
    {0b111100100, 0b111001001, 0b100100111, 0b001001111,},
    {0b110011001, 0b001011110, 0b100110011, 0b011110100,},
    {0b011010110, 0b100111001,},
    {0b110010011, 0b001111100,},
    {0b111010010, 0b010010111, 0b100111100, 0b001111001,},
    {0b010111011, 0b010111110, 0b011111010, 0b110111010,},
    {0b010011110, 0b010111001, 0b011110010, 0b100111010,},
    {0b110111011, 0b011111110,},
    {0b001111110, 0b110011011, 0b011111100, 0b110110011,},
};

board action(board now, shape sh) {
    int opt = 8;
    for (int cent = 7; cent >= 1; cent--) {
        if (now & (sh << (3 * (cent - 1)))) break;
        opt = cent;
    }

    board nxt = now | (sh << (3 * (opt - 1)));

    ll mask = 7 << (3 * (opt - 1));
    for (int y = opt - 1; y <= opt + 1; y++) {
        while ((nxt & mask) == mask) {
            ll res = 0;
            res += nxt & ((1 << (3 * y)) - 1);
            res += (nxt - res - mask) >> 3;
            nxt = res;
        }
        mask <<= 3;
    }
    return nxt;
}

int n; 
vector<int> a;

int dp[(1 << 21) * 50 + 50];
char color[(1 << 21) * 50 + 50];

int f(const board now, const int i) {
    if (color[now * n + i] == 2) return dp[now * n + i];
    if (color[now * n + i] == 1) return INF;

    int &ret = dp[now * n + i];
    ret = 1;

    color[now * n + i] = 1;

    const int j = (i + 1 == n ? 0 : i + 1);
    for (const shape sh : SHAPES[a[i]]) {
        const board nxt = action(now, sh);
        if ((1 << 21) <= nxt) continue;
        ret = max(ret, 1 + f(nxt, j));
    }

    color[now * n + i] = 2;
    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    a.assign(n, 0);
    for (auto &i : a) cin >> i;

    int ans = f(board{}, 0);
    cout << (ans >= INF ? -1 : ans) << '\n';
}
