#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int dx[] = {1, -1, 0, 0};
constexpr int dy[] = {0, 0, 1, -1};

constexpr int N = 202020;
constexpr int Q = 202020;

struct point {
    ll x, y;
    bool operator<(const point &rhs) const {
        if (x != rhs.x) return x < rhs.x;
        else return y < rhs.y;
    }
};

int n;
point p[N];
vector<int> dh;
int q, d[Q];
point ans[Q];

ll ccw(const point &a, const point &b, const point &c) {
    ll res = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
    return (res > 0 ? 1 : (res < 0 ? -1 : 0));
}

ll gcd(ll x, ll y) {
    if (!y) return x;
    return gcd(y, x % y);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> p[i].x >> p[i].y;

    sort(p, p + n);

    dh.push_back(0);
    dh.push_back(1);

    for (int next = 2; next < n; next++) {
        while (sz(dh) >= 2) {
            int first = dh.back();
            dh.pop_back();
            int second = dh.back();
            if (ccw(p[second], p[first], p[next]) > 0) {
                dh.push_back(first);
                break;
            }
        }
        dh.push_back(next);
    }

    cin >> q;
    for (int i = 0; i < q; i++) cin >> d[i];
    vector<int> ord(q);
    iota(all(ord), 0);
    sort(all(ord), [&](int i, int j) {
        return d[i] < d[j];
    });

    int now = 0;
    for (const auto &i : ord) {
        while (p[dh[now + 1]].x < d[i]) now++;

        ll v = (p[dh[now + 1]].x - p[dh[now]].x);
        ll u = (p[dh[now + 1]].y - p[dh[now]].y) * (d[i] - p[dh[now]].x) + p[dh[now]].y * v;

        ll g = gcd(u, v);
        u /= g, v /= g;

        ans[i] = {u, v};
    }

    for (int i = 0; i < q; i++) {
        cout << ans[i].x << ' ' << ans[i].y << '\n';
    }
}
