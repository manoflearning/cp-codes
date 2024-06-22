#pragma GCC optimize ("O3")
#pragma GCC optimize ("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define fr first
#define sc second

const int N = 5050;

int n;
short al[N], ar[N], bl[N], br[N];
unordered_map<int, short> dp;
short tmp[N * N];
int lazy_upd[N * N], idx;

void input() {
    int ain, bin;
    cin >> n >> ain >> bin;
    for (int i = 1; i <= n; i++) {
        int x, y, p, q;
        cin >> x >> y >> p >> q;
        
        x -= ain, y -= ain;
        p -= bin, q -= bin;

        x = max(x, 0);
        y = max(y, 0);
        p = max(p, 0);
        q = max(q, 0);

        x = min(x, n);
        y = min(y, n);
        p = min(p, n);
        q = min(q, n);

        al[i] = x, ar[i] = y;
        bl[i] = p, br[i] = q;
    }
}

void naive_opt() {
    int i;
    for (i = 1; i <= n; i++) {
        if (al[i] <= 0 && 0 <= ar[i] && bl[i] <= 0 && 0 <= br[i]) {
            dp[1 * N + 0] = dp[0 * N + 1] = 1;
            break;
        }
    }

    for (i++; i <= n; i++) {
        for (auto& j : dp) {
            short aup = j.fr / N, bup = j.fr % N;
            if (al[i] <= aup && aup <= ar[i] && bl[i] <= bup && bup <= br[i]) {
                int h = (aup + 1) * N + bup;
                if (!tmp[h]) lazy_upd[idx++] = h;
                tmp[h] = max<short>(tmp[h], j.sc + 1);

                h = aup * N + (bup + 1);
                if (!tmp[h]) lazy_upd[idx++] = h;
                tmp[h] = max<short>(tmp[h], j.sc + 1);
            }
            else {
                if (!tmp[j.fr]) lazy_upd[idx++] = j.fr;
                tmp[j.fr] = max(tmp[j.fr], j.sc);
            }
        }

        dp.clear();
        for (int j = 0; j < idx; j++) {
            int k = lazy_upd[j];
            if (tmp[k]) {
                dp[k] = tmp[k];
                tmp[k] = 0;
            }
        }
        idx = 0;
    }

    short ans = 0;
    for (auto& i : dp) ans = max(ans, i.sc);

    cout << ans;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    naive_opt();
}