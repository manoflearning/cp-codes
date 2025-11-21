#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;

#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

#define M_PI 3.14159265358979323846

constexpr int INF = 1e9 + 7;
constexpr int N = 202020;
constexpr int M = 202020;

struct point {
    ll x, y;
    bool operator<(const point &rhs) const {
        if (y ^ rhs.y) return y < rhs.y;
        return x < rhs.x;
    }
};

int n;
ll r;
vector<point> p;
vector<int> st;

ll ccw(const point &a, const point &b, const point &c) {
    ll res = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
    return res;
}
ll dist(const point &p1, const point &p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}
bool cmp(const point &p1, const point &p2) {
    return (ccw(p[0], p1, p2) > 0 || (ccw(p[0], p1, p2) == 0 && dist(p[0], p1) < dist(p[0], p2)));
}
void graham() {
    sort(all(p));
    sort(p.begin() + 1, p.end(), cmp);
    st.push_back(0);
    st.push_back(1);
    for (int next = 2; next < n; next++) {
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

ld f(point p1, point p2) {
    ld h = abs(ccw({0, 0}, p1, p2) / sqrt(dist(p1, p2)));
    ld theta = acos(h / r);
    return r * (r * theta - h * sin(theta));
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> r;
    p.resize(n);
    for (auto &i : p)
        cin >> i.x >> i.y;

    graham();

    cout << fixed;
    cout.precision(20);

    ld ans = 0;
    for (int i = 0; i < sz(st); i++) {
        ld res = f(p[st[i]], p[st[(i + 1) % sz(st)]]);
        if (ccw({0, 0}, p[st[i]], p[st[(i + 1) % sz(st)]]) <= 0) {
            ans = max<ld>(ans, r * r * M_PI / 2);
        }
        ans = max(ans, res);
    }

    cout << ans;
}