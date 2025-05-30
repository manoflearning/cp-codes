#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int INF = 1e9 + 7;

struct Point { ll x, y; };
int n, m;
vector<Point> p;
ll mnx, mxx, mny, mxy;

void init() {
    mnx = mny = INF;
    mxx = mxy = -INF;
}
void input() {
    cin >> n >> m;
    p.resize(n);
    for (auto& i : p) 
        cin >> i.x >> i.y;
}
void rotate() {
    for (auto& i : p) {
        auto [x, y] = i;
        i.x = x + y; i.y = x - y;
        mnx = min(mnx, i.x); mny = min(mny, i.y);
        mxx = max(mxx, i.x); mxy = max(mxy, i.y);
    }
}

int vi[2][101010];
void reachable(ll x, ll y, ll len, int bit) {
    for (int i = 0; i < sz(p); i++) {
        ll res = max(abs(p[i].x - x), abs(p[i].y - y));
        if (res <= len) vi[bit][i] = 1;
    }
}
int f(ll x) {
    memset(vi[0], 0, sizeof(vi[0]));
    memset(vi[1], 0, sizeof(vi[1]));
    reachable(mnx, mny, x, 0);
    reachable(mxx, mxy, x, 1);
    int cnt0 = 0, cnt1 = 0, cnt01 = 0;
    for (int i = 0; i < sz(p); i++) {
        cnt0 += vi[0][i], cnt1 += vi[1][i];
        cnt01 += (vi[0][i] && vi[1][i]);
    }
    if (cnt0 + cnt1 - cnt01 == n && cnt0 - cnt01 <= m && cnt1 - cnt01 <= m) return 1;

    memset(vi[0], 0, sizeof(vi[0]));
    memset(vi[1], 0, sizeof(vi[1]));
    reachable(mnx, mxy, x, 0);
    reachable(mxx, mny, x, 1);
    cnt0 = 0, cnt1 = 0, cnt01 = 0;
    for (int i = 0; i < sz(p); i++) {
        cnt0 += vi[0][i], cnt1 += vi[1][i];
        cnt01 += (vi[0][i] && vi[1][i]);
    }
    if (cnt0 + cnt1 - cnt01 == n && cnt0 - cnt01 <= m && cnt1 - cnt01 <= m) return 1;

    return 0;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        rotate();

        ll l = 0, r = max(mxx - mnx, mxy - mny);
        while (l < r) {
            ll mid = (l + r) >> 1;
            if (f(mid)) r = mid;
            else l = mid + 1;
        }
        cout << l / 2 << '\n';
    }
}