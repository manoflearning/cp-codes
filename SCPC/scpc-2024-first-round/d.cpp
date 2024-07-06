// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(c) (c).begin(), (c).end()

const int N = 101010;
const ll INF = 1e18;

int n, mx;
ll a[N], b[N];
vector<pii> rng;

void input() {
    cin >> n >> mx;
    a[0] = b[0] = -INF;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    a[n + 1] = b[n + 1] = INF;
}

void get_range() {
    int s = 0, e = 1;
    rng.clear();
    rng.push_back({ -10, -10 });
    for (int i = 1; i <= n; i++) {
        while (e <= n && a[i] + mx >= b[e]) e++;
        while (s <= n && b[s] < a[i] - mx) s++;
        rng.push_back({ s, e - 1 }); // [s, e - 1]
    }
    rng.push_back({ -10, -10 });
}

bool is_possible() {
    for (int i = 1; i <= n; i++) {
        if (!(rng[i].fr <= i && i <= rng[i].sc)) return 0;
    }
    return 1;
}

ll solve() {
    ll ret = 0;

    {
        for (int i = 1; i <= n; i++)
            ret = max(ret, abs(b[i] - a[i]));
    }
    {
        vector<pii> ptt;
        int rm = 0, st = 0;
        for (int i = 1; i <= n + 1; i++) {
            if (rng[i].fr <= i - 1 && i - 1 <= rng[i].sc) {
                rm = i;
                if (st == 0) st = max(1, i - 1);
            }
            else {
                if (rm != 0) {
                    ptt.push_back({ st, rm });
                    st = rm = 0;
                }
            }
        }
        
        for (auto& [s, e] : ptt) {
            for (int i = s; i < e; i++) {
                if (i + 1 <= rng[i].sc) 
                    ret = max(ret, abs(b[min(e, rng[i].sc)] - a[i]));
            }
        }
    }   
    {
        vector<pii> ptt;
        int lm = 0, st = 0;
        for (int i = n; i >= 0; i--) {
            if (rng[i].fr <= i + 1 && i + 1 <= rng[i].sc) {
                lm = i;
                if (st == 0) st = min(n, i + 1);
            }
            else {
                if (lm != 0) {
                    ptt.push_back({ lm, st });
                    lm = st = 0;
                }
            }
        }

        for (auto& [s, e] : ptt) {
            for (int i = e; i > s; i--) {
                if (rng[i].fr <= i - 1)
                    ret = max(ret, abs(b[max(s, rng[i].fr)] - a[i]));
            }
        }
    }

    return ret;
}

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        cout << "Case #" << tt << '\n';

        input();

        sort(a + 1, a + 1 + n);
        sort(b + 1, b + 1 + n);

        get_range();

        if (is_possible()) cout << solve() << '\n';
        else cout << -1 << '\n';

        cout << flush;
    }
}