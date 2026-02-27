#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using i128 = __int128_t;
using pii = pair<int, int>;
using vi = vector<int>;

struct Num {
    ll p{}, q{}; // represent (p + q * sqrt(2)) / 2

    bool operator<(Num rhs) const {
        // (rhs.p - p) + sqrt(2) * (rhs.q - q) > 0?
        if (*this == rhs) return false;

        if (p >= rhs.p && q >= rhs.q) return false;
        if (p <= rhs.p && q <= rhs.q) return true;

        bool x1 = ((i128)(p - rhs.p) * (p - rhs.p) < (i128)2 * (q - rhs.q) * (q - rhs.q));
        if (q <= rhs.q) return x1;
        else return !x1;
    }
    bool operator==(Num rhs) const {
        return tie(p, q) == tie(rhs.p, rhs.q);
    }
    bool operator!=(Num rhs) const {
        return tie(p, q) != tie(rhs.p, rhs.q);
    }

    Num operator+(Num rhs) const { return Num{p + rhs.p, q + rhs.q}; }
    Num operator-(Num rhs) const { return Num{p - rhs.p, q - rhs.q}; }
};

struct Point {
    Num x{}, y{};

    bool operator<(Point p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator==(Point p) const { return tie(x, y) == tie(p.x, p.y); }
    bool operator!=(Point p) const { return tie(x, y) != tie(p.x, p.y); }

    Point operator+(Point p) const { return Point{x + p.x, y + p.y}; }
    Point operator-(Point p) const { return Point{x - p.x, y - p.y}; }

    Point rotate45() const {
        Point ret{};
        ret.x.p = (x - y).q, ret.x.q = (x - y).p / 2;
        ret.y.p = (x + y).q, ret.y.q = (x + y).p / 2;
        return ret;
    }

    Point move(ll d, int ang) const {
        assert(0 <= ang && ang < 360 && ang % 45 == 0);

        Point ret{*this};

        if (ang == 0) ret.x.p += 2 * d;
        else if (ang == 45) ret.x.q += d, ret.y.q += d;
        else if (ang == 90) ret.y.p += 2 * d;
        else if (ang == 135) ret.x.q -= d, ret.y.q += d;
        else if (ang == 180) ret.x.p -= 2 * d;
        else if (ang == 225) ret.x.q -= d, ret.y.q -= d;
        else if (ang == 270) ret.y.p -= 2 * d;
        else if (ang == 315) ret.x.q += d, ret.y.q -= d;

        return ret;
    }
};

struct Line {
    Point u, v;

    Line(Point _u, Point _v) : u(_u), v(_v) {
        if (v < u) swap(u, v);
    }

    bool operator<(Line l) const { return tie(u, v) < tie(l.u, l.v); }
    bool operator==(Line l) const { return tie(u, v) == tie(l.u, l.v); }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n; cin >> n;

    Point now{};
    int ang{};
    vector<vector<Line>> lines_ang(4);
    for (int i = 0; i < n; i++) {
        string op;
        ll d;
        cin >> op >> d;

        if (op == "rotate") {
            ang = (ang + d) % 360;
        } else {
            const Point nxt = now.move(64 * d, ang);
            
            if (op == "draw") {
                if (ang == 0 || ang == 180) {
                    lines_ang[0].push_back(Line{now, nxt});
                } else if (ang == 45 || ang == 225) {
                    lines_ang[1].push_back(Line{now, nxt});
                } else if (ang == 90 || ang == 270) {
                    lines_ang[2].push_back(Line{now, nxt});
                } else if (ang == 135 || ang == 315) {
                    lines_ang[3].push_back(Line{now, nxt});
                } else { assert(0); }
            }

            now = nxt;
        }
    }

    vector<Line> lines;
    for (int i = 0; i < 4; i++) {
        map<Num, vector<Line>> mp;
        if (i == 0) for (auto &j : lines_ang[i]) mp[j.u.y].push_back(j);
        else if (i == 1) for (auto &j : lines_ang[i]) mp[j.u.x - j.u.y].push_back(j);
        else if (i == 2) for (auto &j : lines_ang[i]) mp[j.u.x].push_back(j);
        else if (i == 3) for (auto &j : lines_ang[i]) mp[j.u.x + j.u.y].push_back(j);

        for (auto &[_, v] : mp) {
            sort(all(v));

            vector<Line> tmp;
            for (const auto &j : v) {
                if (tmp.empty() || tmp.back().v != j.u) {
                    tmp.push_back(j);
                } else {
                    tmp.back().v = j.v;
                }
            }

            lines.insert(lines.end(), all(tmp));
        }
    }

    sort(all(lines));

    // for (auto &[u, v] : lines) {
    //     cout << u.x.p << ' ' << u.x.q << ' ' << u.y.p << ' ' << u.y.q << ' ';
    //     cout << v.x.p << ' ' << v.x.q << ' ' << v.y.p << ' ' << v.y.q << '\n';
    // }

    vector<Line> rotated = lines;
    for (int ang = 45; ang <= 360; ang += 45) {
        vector<Line> tmp;
        for (auto &i : rotated) {
            tmp.push_back(Line{i.u.rotate45(), i.v.rotate45()});
        }
        rotated.swap(tmp);

        sort(all(rotated));

        const Point d = lines[0].u - rotated[0].u;
        
        bool yes = 1;
        for (int i = 0; i < sz(rotated); i++) {
            yes &= (rotated[i].u + d == lines[i].u);
            yes &= (rotated[i].v + d == lines[i].v);
        }

        if (yes) {
            cout << ang << '\n';
            exit(0);
        }
    }

    assert(0);
}
