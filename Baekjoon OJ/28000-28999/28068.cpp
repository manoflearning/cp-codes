#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int INF = 1e9 + 7;

int n;
vector<pair<ll, ll>> in, de;

struct Seg {  // 0-indexed
    int n;  // array size
    pair<ll, ll> t[202020];
    void build() {
        n = 100'000;
        for (int i = 0; i < 202020; i++) t[i] = { INF, INF };
    }
    void modify(int p, ll value) {  // set value at position p
        t[p + n] = { value, p };
        for (p += n; p > 1; p >>= 1) t[p >> 1] = min(t[p], t[p ^ 1]);
    }
    pair<ll, ll> query(int l, int r) {  // sum on interval [l, r)
        pair<ll, ll> ret = { INF, INF };
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ret = min(ret, t[l++]);
            if (r & 1) ret = min(ret, t[--r]);
        }
        return ret;
    }
}seg;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        ll x, y;
        cin >> x >> y;
        if (x <= y) in.push_back({ x, y });
        else de.push_back({ x, y });
    }

    // solve if a[i] <= b[i]
    ll joy = 0;

    sort(in.begin(), in.end());

    for (auto& i : in) {
        if (joy < i.first) {
            cout << 0;
            return 0;
        }
        joy += i.second - i.first;
    }

    // solve if a[i] > b[i]
    sort(de.begin(), de.end(), [&](const pair<ll, ll>& p1, const pair<ll, ll>& p2) {
        return p1.first ^ p2.first ? p1.first > p2.first : p1.second > p2.second;
    });

    seg.build();
    for (int i = 0; i < sz(de); i++) {
        seg.modify(i, de[i].first - de[i].second);
    }

    vector<int> vi(sz(de));
    for (int i = 0; i < sz(de); i++) {
        while (1) {
            pair<ll, ll> sg = seg.query(0, sz(de));
            if (joy - sg.first < de[i].first) break;
            joy -= sg.first;
            seg.modify(sg.second, INF);
            vi[sg.second] = 1;
        }

        if (!vi[i]) {
            if (joy < de[i].first) {
                cout << 0;
                return 0;
            }
            joy -= de[i].first - de[i].second;
            seg.modify(i, INF);
            vi[i] = 1;
        }
    }

    cout << 1;
}