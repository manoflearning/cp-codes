#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXT = 1'000'000;

int flag;
struct Seg {
    vector<ll> t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
    }
    void add(int p, ll val) {
        for (t[p += flag - 1] += val; p > 1; p >>= 1)
            t[p >> 1] = t[p] + t[p ^ 1];
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (r < nl || nr < l) return 0;
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
        if (i.op == '?') {
            int l = i.x, r = MAXT;
            while (l < r) {
                int mid = (l + r) >> 1;
                if (seg.query(i.x, mid) > mid - i.x) l = mid + 1;
                else r = mid;
            }
            cout << l - i.x << '\n';
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

    solve();
}