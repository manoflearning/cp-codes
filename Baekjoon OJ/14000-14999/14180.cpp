#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 202020;
const ll INF = 1e18;

int n;
ll a[MAXN], psum[MAXN], noMoveRes;
ll ans = 0;

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
}

void buildPsum() {
    for (int i = 1; i <= n; i++) 
        psum[i] = a[i] + psum[i - 1];
}

ll noMove() {
    ll ret = 0;
    for (int i = 1; i <= n; i++) ret += i * a[i];
    return ret;
}

struct Point {
    ll x, y;
    bool operator<(const Point& rhs) const {
        return tie(y, x) < tie(rhs.y, rhs.x);
    }
};
vector<Point> p;
vector<int> st;
ll ccw(const Point& a, const Point& b, const Point& c) {
    ll res = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
    return (res > 0 ? 1 : (res < 0 ? -1 : 0));
}
ll dist(const Point& p1, const Point& p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}
bool cmp(const Point& p1, const Point& p2) {
    return (ccw(p[0], p1, p2) > 0 || (ccw(p[0], p1, p2) == 0 && dist(p[0], p1) < dist(p[0], p2)));
}

void grahamScan() {
    for (int x = 0; x <= n; x++) {
        p.push_back({ x, -psum[x] });
    }
    sort(all(p));
    sort(p.begin() + 1, p.end(), cmp);

    st.push_back(0);
    st.push_back(1);
    for (int next = 2; next < sz(p); next++) {
        while (sz(st) >= 2) {
            int first = st.back();
            st.pop_back();
            int second = st.back();
            if (ccw(p[second], p[first], p[next]) > 0) {
                st.push_back(first);
                break;
            }
        }
        st.push_back(next);
    }
}

struct Line {
    ll dx, dy; // y = (dy/dx)x, dx >= 0
    int idx;
    bool operator<(const Line& rhs) const {
        return dy * rhs.dx < rhs.dy * dx;
    }
    bool operator<=(const Line& rhs) const {
        return dy * rhs.dx <= rhs.dy * dx;
    }
    bool operator==(const Line& rhs) const {
        return dy * rhs.dx == rhs.dy * dx;
    }
};
vector<Line> line;

ll cal(const Point& p, const Line& li) {
    return noMoveRes + p.y - li.dy * p.x + (psum[li.idx] + li.dy * li.idx);
}

void solve() {
    for (int i = 1; i <= n; i++)
        line.push_back({ 1, -a[i], i });
    sort(all(line));

    int opt = 0;
    for (auto& li : line) {
        while (1) {
            const Point& i = p[st[(opt + sz(st) - 1) % sz(st)]];
            const Point& j = p[st[opt]];
            const Point& k = p[st[(opt + 1) % sz(st)]];

            ll di = cal(i, li);
            ll dj = cal(j, li);
            ll dk = cal(k, li);

            if (max(di, dk) <= dj) break;
            else opt = (opt + 1) % sz(st);
        }

        Point optp = p[st[opt]];
        ll res = optp.y - li.dy * optp.x + (psum[li.idx] + li.dy * li.idx);
        ans = max(ans, noMoveRes + res);
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

    buildPsum();

    noMoveRes = noMove();
    ans = noMoveRes;

    grahamScan();

    solve();

    cout << ans;
}