#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()

const int INF = 1e9 + 7;

int flag;
struct Seg {
    struct Node {
        int l, r, tot, mx;
        Node operator+(const Node& rhs) const {
            Node ret;
            ret.l = max(l, tot + rhs.l);
            ret.r = max(rhs.r, r + rhs.tot);
            ret.mx = max({ mx, rhs.mx, r + rhs.l });
            ret.tot = tot + rhs.tot;
            return ret;
        }
    };
    vector<Node> t;
    void build(int N) {
        t.clear();
        for (flag = 1; flag < N; flag <<= 1);
        t.resize(flag << 1);
    }
    void add(int p, int val) {
        p += flag - 1;
        t[p].tot += val;
        t[p].l = t[p].r = t[p].mx = max(0, t[p].tot);
        for (; p > 1; p >>= 1) {
            if (p & 1) t[p >> 1] = t[p ^ 1] + t[p];
            else t[p >> 1] = t[p] + t[p ^ 1];
        }
    }
    int query() { return t[1].mx; }
}seg;

int n1, n2, c1, c2, X, Y;
struct Node { int x, y; };
vector<Node> a, b;
struct Node2 { int y, w; };
vector<Node2> idx[2020];

void input() {
    cin >> n1;
    a.resize(n1);
    for (auto& i : a) cin >> i.x >> i.y;
    cin >> n2;
    b.resize(n2);
    for (auto& i : b) cin >> i.x >> i.y;
    cin >> c1 >> c2;
}

void coordinateCompression() {
    vector<int> xx(1, -INF), yy(1, -INF);
    for (auto& i : a) {
        xx.push_back(i.x);
        yy.push_back(i.y);
    }
    for (auto& i : b) {
        xx.push_back(i.x);
        yy.push_back(i.y);
    }
    sort(all(xx));
    xx.erase(unique(all(xx)), xx.end());
    sort(all(yy));
    yy.erase(unique(all(yy)), yy.end());
    for (auto& i : a) {
        i.x = lower_bound(all(xx), i.x) - xx.begin();
        i.y = lower_bound(all(yy), i.y) - yy.begin();
    }
    for (auto& i : b) {
        i.x = lower_bound(all(xx), i.x) - xx.begin();
        i.y = lower_bound(all(yy), i.y) - yy.begin();
    }

    X = xx.size() - 1;
    Y = yy.size() - 1;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    coordinateCompression();

    for (auto& i : a)
        idx[i.x].push_back({ i.y, c1 });
    for (auto& i : b)
        idx[i.x].push_back({ i.y, -c2 });

    int ans = 0;
    for (int sx = 1; sx <= X; sx++) {
        seg.build(Y);
        for (int ex = sx; ex <= X; ex++) {
            for (auto& i : idx[ex]) seg.add(i.y, i.w);
            ans = max(ans, seg.query());
        }
    }

    cout << ans;
}