#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

#define sz(x) (int)(x).size()

constexpr int N = 50505;

// INPUT: ln: A vector of directed lines (half-planes).
// - IMPORTANT: The valid region is to the LEFT of the line (s -> t).
// - Tip: Add a bounding box (4 lines) if the area might be unbounded.
// OUTPUT: A vector of vertices representing the intersection polygon.
// - Order: Counter-Clockwise (CCW).
// - Returns an empty vector if the intersection is empty or degenerate.
// TIME COMPLEXITY: O(nlogn)
constexpr ld EPS = 1e-9;
struct Point {
  ld x, y;
  bool operator<(const Point &rhs) const {
    if (abs(x - rhs.x) < EPS) return x < rhs.x;
    return y < rhs.y;
  }
};
struct Line {
  Point s, t;
};
inline bool equals(ld a, ld b) { return abs(a - b) < EPS; }
bool line_intersect(Point &s1, Point &e1, Point &s2, Point &e2, Point &v) {
  ld vx1 = e1.x - s1.x, vy1 = e1.y - s1.y;
  ld vx2 = e2.x - s2.x, vy2 = e2.y - s2.y;
  ld det = vx1 * (-vy2) - (-vx2) * vy1;
  if (equals(det, 0)) return 0;
  ld s = (ld)((s2.x - s1.x) * (-vy2) + (s2.y - s1.y) * vx2) / det;
  v.x = s1.x + vx1 * s;
  v.y = s1.y + vy1 * s;
  return 1;
}
bool bad(Line &a, Line &b, Line &c) {
  Point v;
  if (!line_intersect(a.s, a.t, b.s, b.t, v)) return 0;
  ld crs = (c.t.x - c.s.x) * (v.y - c.s.y) - (c.t.y - c.s.y) * (v.x - c.s.x);
  return crs < 0 || equals(crs, 0);
}
vector<Point> hpi(vector<Line> &ln) {
  auto lsgn = [&](const Line &a) {
    if (a.s.y == a.t.y) return a.s.x > a.t.x;
    return a.s.y > a.t.y;
  };
  sort(ln.begin(), ln.end(), [&](const Line &a, const Line &b) {
    if (lsgn(a) != lsgn(b)) return lsgn(a) < lsgn(b);
    return (a.t.x - a.s.x) * (b.t.y - b.s.y) - (a.t.y - a.s.y) * (b.t.x - b.s.x) > 0;
  });
  deque<Line> dq;
  for (int i = 0; i < sz(ln); i++) {
    while (dq.size() >= 2 && bad(dq[dq.size() - 2], dq.back(), ln[i]))
      dq.pop_back();
    while (dq.size() >= 2 && bad(dq[0], dq[1], ln[i]))
      dq.pop_front();
    if (dq.size() < 2 || !bad(dq.back(), ln[i], dq[0]))
      dq.push_back(ln[i]);
  }
  vector<Point> ret;
  if (dq.size() >= 3)
    for (int i = 0; i < sz(dq); i++) {
      int j = (i + 1) % sz(dq);
      Point v;
      if (!line_intersect(dq[i].s, dq[i].t, dq[j].s, dq[j].t, v)) continue;
      ret.push_back(v);
    }
  return ret;
}

int n;
Point a[N];
vector<Point> res, ch;

ll ccw(const Point &a, const Point &b, const Point &c) {
  // res > 0 -> ccw, res < 0 -> cw, res = 0 -> colinear
  ld res = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
  return (res > 0 ? 1 : (res < 0 ? -1 : 0));
}
ll cccw(Point a, Point b, Point c, Point d) {
  d.x -= c.x - b.x;
  d.y -= c.y - b.y;
  return ccw(a, b, d);
}
ld dist(const Point &p1, const Point &p2) {
  return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}
bool cmp(const Point &p1, const Point &p2) {
  return (ccw(res[0], p1, p2) > 0 || (ccw(res[0], p1, p2) == 0 && dist(res[0], p1) < dist(res[0], p2)));
}

bool f(ld len) {
    vector<Line> lns;
    for (int i = 0; i < n; i++) {
        Line ln{a[i], a[(i + 1) % n]};

        Point d{ln.t.x - ln.s.x, ln.t.y - ln.s.y};
        d.x /= sqrt((ln.t.x - ln.s.x) * (ln.t.x - ln.s.x) + (ln.t.y - ln.s.y) * (ln.t.y - ln.s.y));
        d.y /= sqrt((ln.t.x - ln.s.x) * (ln.t.x - ln.s.x) + (ln.t.y - ln.s.y) * (ln.t.y - ln.s.y));
        swap(d.x, d.y);
        d.x *= -1;
        d.x *= len;
        d.y *= len;

        ln.s.x += d.x;
        ln.t.x += d.x;
        ln.s.y += d.y;
        ln.t.y += d.y;

        lns.push_back(ln);
    }

  res = hpi(lns);

  if (sz(res) <= 1) return 0;

  ch.resize(sz(res));

  Point ans1, ans2;
  sort(res.begin(), res.end());
  sort(res.begin() + 1, res.end(), cmp);
  ch[0] = res[0];
  ch[1] = res[1];
  ll fl = 2, cnt = 2;
  for (int i = 2; i < sz(res); i++) {
    while (fl >= 2 && ccw(ch[fl - 2], ch[fl - 1], res[i]) <= 0) fl--;
    ch[fl] = res[i], fl++;
  }
  ll fl2 = 1;
  ld mx = 0;
  for (int i = 0; i < fl; i++) {
    while ((fl2 + 1) != i && cccw(ch[i], ch[i + 1], ch[fl2 % fl], ch[(fl2 + 1) % fl]) > 0) {
      if (mx < dist(ch[i], ch[fl2 % fl])) {
        ans1 = ch[i], ans2 = ch[fl2 % fl];
        mx = dist(ch[i], ch[fl2 % fl]);
      }
      fl2++;
    }
    if (mx < dist(ch[i], ch[fl2 % fl])) {
      ans1 = ch[i], ans2 = ch[fl2 % fl];
      mx = dist(ch[i], ch[fl2 % fl]);
    }
  }

  return mx >= 4 * len * len;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    ch.resize(n);
    for (int i = 0; i < n; i++)
        cin >> a[i].x >> a[i].y;

    ld l = 0, r = 1e8;
    for (int cnt = 0; cnt < 60; cnt++) {
        ld mid = (l + r) / 2;
        if (f(mid)) l = mid;
        else r = mid;
    }
    cout << fixed;
    cout.precision(3);
    cout << l;
}