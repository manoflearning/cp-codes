#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int INF = 1e9 + 7;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int h, w;
    cin >> h >> w;
    vector<string> a(h);
    for (auto &i : a) cin >> i;

    if (h > w) {
        vector<string> tmp(w, string(h, '.'));
        for (int x = 0; x < h; x++) {
            for (int y = 0; y < w; y++) {
                tmp[y][x] = a[x][y];
            }
        }
        a = std::move(tmp);
        swap(h, w);
    }

    vector<vector<vector<int>>> b(h + 1, vector<vector<int>>(h + 1, vector<int>(w)));

    for (int y = 0; y < w; y++) {
        for (int x1 = 0; x1 < h; x1++) {
            int bit = 0;
            for (int x2 = x1 + 1; x2 <= h; x2++) {
                if (a[x2 - 1][y] == 'W') bit |= (1 << 0);
                if (a[x2 - 1][y] == 'A') bit |= (1 << 1);
                if (a[x2 - 1][y] == 'L') bit |= (1 << 2);
                if (a[x2 - 1][y] == 'D') bit |= (1 << 3);
                if (a[x2 - 1][y] == 'O') bit |= (1 << 4);

                b[x1][x2][y] = bit;
            }
        }
    }
    
    int ans = INF;
    for (int x1 = 0; x1 < h; x1++) {
        for (int x2 = x1 + 1; x2 <= h; x2++) {
            int y2 = 0;

            array<int, 5> cnt{};
            int acc = 0;
            for (int y1 = 0; y1 < w; y1++) {
                while (y2 < w && acc != 31) {
                    cnt[0] += (b[x1][x2][y2] & (1 << 0) ? 1 : 0);
                    cnt[1] += (b[x1][x2][y2] & (1 << 1) ? 1 : 0);
                    cnt[2] += (b[x1][x2][y2] & (1 << 2) ? 1 : 0);
                    cnt[3] += (b[x1][x2][y2] & (1 << 3) ? 1 : 0);
                    cnt[4] += (b[x1][x2][y2] & (1 << 4) ? 1 : 0);
                    if (cnt[0] > 0 && (~acc & (1 << 0))) acc |= (1 << 0);
                    if (cnt[1] > 0 && (~acc & (1 << 1))) acc |= (1 << 1);
                    if (cnt[2] > 0 && (~acc & (1 << 2))) acc |= (1 << 2);
                    if (cnt[3] > 0 && (~acc & (1 << 3))) acc |= (1 << 3);
                    if (cnt[4] > 0 && (~acc & (1 << 4))) acc |= (1 << 4);
                    y2++;
                }

                if (acc == 31) {
                    ans = min(ans, (x2 - x1) * (y2 - y1));
                }

                cnt[0] -= (b[x1][x2][y1] & (1 << 0) ? 1 : 0);
                cnt[1] -= (b[x1][x2][y1] & (1 << 1) ? 1 : 0);
                cnt[2] -= (b[x1][x2][y1] & (1 << 2) ? 1 : 0);
                cnt[3] -= (b[x1][x2][y1] & (1 << 3) ? 1 : 0);
                cnt[4] -= (b[x1][x2][y1] & (1 << 4) ? 1 : 0);
                if (cnt[0] == 0 && (acc & (1 << 0))) acc -= (1 << 0);
                if (cnt[1] == 0 && (acc & (1 << 1))) acc -= (1 << 1);
                if (cnt[2] == 0 && (acc & (1 << 2))) acc -= (1 << 2);
                if (cnt[3] == 0 && (acc & (1 << 3))) acc -= (1 << 3);
                if (cnt[4] == 0 && (acc & (1 << 4))) acc -= (1 << 4);
            }
        }
    }

    if (ans == INF) {
        cout << "impossible\n";
    } else {
        cout << ans << '\n';
    }
}
