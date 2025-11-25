#include <bits/stdc++.h>
using namespace std;
using ld = long double;
#define sz(x) (int)(x).size()

struct point {
    ld x, y;
};

ld dist(const point &i, const point &j) {
    return sqrt((i.x - j.x) * (i.x - j.x) + (i.y - j.y) * (i.y - j.y));
}

struct pointview {
    int idx; ld t;
    point to_point(const vector<point> &a) const {
        point u = a[idx], v = a[(idx + 1) % sz(a)];
        return point{u.x * (1. - t) + v.x * t, u.y * (1. - t) + v.y * t};
    }
};

ld get_area(const vector<point> &p) {
    ld ret = 0;
    for (int i = 0; i < sz(p); i++) {
        ret += p[i].x * p[(i + 1) % sz(p)].y;
        ret -= p[(i + 1) % sz(p)].x * p[i].y;
    }
    return abs(ret) / 2.;
}

ld get_len(const pointview &l, const pointview &r, const vector<point> &a) {
    if (l.idx == r.idx) {
        assert(l.t <= r.t);
        return dist(a[l.idx], a[(l.idx + 1) % sz(a)]) * (r.t - l.t);
    }

    ld ret = 0;
    ret += dist(a[l.idx], a[(l.idx + 1) % sz(a)]) * (1. - l.t);
    for (int i = (l.idx + 1) % sz(a); i != r.idx; i = (i + 1) % sz(a)) {
        ret += dist(a[i], a[(i + 1) % sz(a)]);
    }
    ret += dist(a[r.idx], a[(r.idx + 1) % sz(a)]) * r.t;
    return ret;
}

pointview get_opp(const pointview &pv, const ld len, const vector<point> &a) {
    point st = pv.to_point(a);

    ld tgt = len;
    ld di = dist(st, a[(pv.idx + 1) % sz(a)]);
    if (tgt < di) {
        return pointview{pv.idx, pv.t + (1.0f - pv.t) * (tgt / di)};
    }
    tgt -= di;
    for (int i = (pv.idx + 1) % sz(a); ; i = (i + 1) % sz(a)) {
        ld di = dist(a[i], a[(i + 1) % sz(a)]);
        if (tgt < di) {
            return pointview{i, tgt / di};
        } else tgt -= di;
    }
    return pointview{-1, 0};
}

pointview get_mid(const pointview &l, const pointview &r, const vector<point> &a) {
    ld len = get_len(l, r, a);
    pointview mid = get_opp(l, len / 2, a);
    return mid;
}

ld f(const pointview &st, const ld peri, const vector<point> &a) {
    pointview en = get_opp(st, peri / 2, a);
    assert(st.idx != en.idx);

    auto get_convex = [&](const pointview &st, const pointview &en) -> vector<point> {
        vector<point> ret;
        ret.push_back(st.to_point(a));
        for (int i = (st.idx + 1) % sz(a); i != en.idx; i = (i + 1) % sz(a)) {
            ret.push_back(a[i]);
        }
        ret.push_back(a[en.idx]);
        ret.push_back(en.to_point(a));
        return ret;
    };

    vector<point> rh = get_convex(st, en);
    vector<point> lh = get_convex(en, st);

    return get_area(rh) - get_area(lh);
}

pair<pointview, pointview> solve(const int n, const vector<point> &a) {
    ld peri{};
    for (int i = 0; i < n; i++) {
        peri += dist(a[i], a[(i + 1) % n]);
    }

    pointview l{0, 0}, r{get_opp(l, peri / 2, a)};
    if (f(l, peri, a) > 0) swap(l, r);

    for (int i = 0; i < 60; i++) {
        pointview mid{get_mid(l, r, a)};
        if (f(mid, peri, a) < 0) l = mid;
        else r = mid;
    }
    
    return {l, get_opp(l, peri / 2, a)};
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    int n; cin >> n;
    vector<point> a(n);
    for (auto &i : a) cin >> i.x >> i.y;

    auto [ans1, ans2] = solve(n, a);

    cout << fixed;
    cout.precision(20);

    cout << "YES\n";
    cout << ans1.idx + 1 << ' ' << ans1.t << '\n';
    cout << ans2.idx + 1 << ' ' << ans2.t << '\n';
}
