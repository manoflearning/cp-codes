#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

struct Deposit { int sx, ex, y; };
struct Point { ll x, y; int w, idx; };

int n;
vector<Deposit> a;
vector<Point> p;

void input() {
    cin >> n;
    a.resize(n);
    for (auto& i : a) {
        cin >> i.sx >> i.ex >> i.y;
        if (i.sx > i.ex) swap(i.sx, i.ex);
    }
}

void getPoints() {
    for (int i = 0; i < n; i++) {
        auto& it = a[i];
        p.push_back({ it.sx, it.y, it.ex - it.sx, i });
        p.push_back({ it.ex, it.y, it.ex - it.sx, i });
    }
}

ll ans = 0;

void solve() {
    for (int i = 0; i < sz(p); i++) {
        const Point& o = p[i];
        if (o.w == 0) continue;

        vector<Point> pSorted;
        for (auto& j : p) {
            if (j.y == o.y) continue;
            Point now = { j.y - o.y, j.x - o.x, j.w, j.idx };
            if (now.x < 0) now.x *= -1, now.y *= -1;
            pSorted.push_back(now);
        }

        sort(all(pSorted), [&](const Point& p1, const Point& p2) {
            return p1.y * p2.x < p2.y * p1.x;
        });

        vector<bool> vi(n);

        ll res = o.w;
        ans = max(ans, res);
        ll lazySub = 0;
        for (int j = 0; j < sz(pSorted); j++) {
            const Point& now = pSorted[j];
            if (!vi[now.idx]) { res += now.w; vi[now.idx] = true; }
            else lazySub += now.w;

            if (j + 1 < sz(pSorted)) {
                const Point& nxt = pSorted[j + 1];
                if (now.y * nxt.x != nxt.y * now.x) {
                    ans = max(ans, res);
                    res -= lazySub;
                    lazySub = 0;
                }
            }
            else ans = max(ans, res);
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    getPoints();

    solve();

    cout << ans;
}