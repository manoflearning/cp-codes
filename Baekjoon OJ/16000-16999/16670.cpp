#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXT = 1'000'000;

struct Node {
    ll mx, sum;
    Node operator+(const Node& rhs) const {
        Node ret;
        ret.mx = max(rhs.mx, mx + rhs.sum);
        ret.sum = sum + rhs.sum;
        return ret;
    }
};

int flag;
struct Seg {
    vector<Node> t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
        for (int i = flag; i < flag + n; i++) t[i] = { i - flag + 1, 0 };
        for (int i = flag - 1; i >= 1; i--)
            t[i] = t[i << 1] + t[i << 1 | 1];
    }
    void add(int p, ll val) {
        t[p + flag - 1].mx += val;
        t[p + flag - 1].sum += val;
        for (p += flag - 1; p > 1; p >>= 1) {
            t[p >> 1] = t[min(p, p ^ 1)] + t[max(p, p ^ 1)];
        }
    }
    Node query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (r < nl || nr < l) return { 0, 0 };
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
    }
}seg;

struct Event { char op; int x, y; };

int q;
vector<Event> event;

void input() {
    cin >> q;
    event.resize(q);
    for (auto& i : event) {
        cin >> i.op >> i.x;
        if (i.op == '+') cin >> i.y;
    }
}

void solve() {
    seg.build(MAXT);
    for (auto& i : event) {
        if (i.op == '+') seg.add(i.x, i.y);
        if (i.op == '-') seg.add(event[i.x - 1].x, -event[i.x - 1].y);
        if (i.op == '?') cout << seg.query(1, i.x).mx - i.x << '\n';
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

    solve();
}