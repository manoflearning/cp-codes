#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

const int D = 7, H = 24;

string a[7];
int d, h;

inline int popcount(int bit, int mx) {
    int ret = 0;
    for (int i = 0; i < mx; i++)
        if ((1 << i) & bit) ret++;
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    for (int i = 0; i < D; i++) cin >> a[i];
    cin >> d >> h;

    vector<int> b1s, b2s;
    for (int b1 = 0; b1 < (1 << D); b1++)
        if (popcount(b1, D) == d) b1s.push_back(b1);
    // for (int b2 = 0; b2 < (1 << H); b2++)
    //     if (popcount(b2, H) == h) b2s.push_back(b2);

    // cout << sz(b1s) << ' ' << sz(b2s) << ' ' << sz(b1s) * sz(b2s) << '\n';

    double ans = 0;
    for (int b1 : b1s) {
        vector<int> res;
        for (int x = 0; x < H; x++) {
            int p = 0;
            for (int y = 0; y < D; y++) {
                if (b1 & (1 << y)) if (a[y][x] == '.') p++;
            }
            res.push_back(p);
        }
        sort(res.rbegin(), res.rend());

        int p = 0;
        for (int i = 0; i < h; i++) p += res[i];

        ans = max(ans, (double)p / (d * h));
    }

    cout << fixed;
    cout.precision(8);
    cout << ans;
}
