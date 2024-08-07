//#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second

int n;
vector<pll> arr;

void input() {
    cin >> n;
    arr.resize(n);
    for (auto& i : arr)
        cin >> i.fr >> i.sc;
}

void erase() {
    sort(arr.rbegin(), arr.rend());

    vector<pll> tmp;
    set<ll> s;
    for (auto& i : arr) {
        if (s.lower_bound(i.sc) == s.end()) 
            tmp.push_back(i);
        s.insert(i.sc);
    }

    arr = tmp;
    n = arr.size();
}

struct lf { // f(x) = px + q, x >= s
    ll p, q; 
    double s;
    lf(): lf(1, 0) {}
    lf(ll sp, ll sq): p(sp), q(sq), s(0) {}
};
double cross(const lf& u, const lf& v) {
    return (double)(v.q - u.q) / (u.p - v.p);
}

ll a[50505], b[50505];
ll dp[50505];
lf ch[50505];

void convexHullTrick() {
    for (int i = 0; i < n; i++)
        a[i + 1] = arr[i].sc, b[i + 1] = arr[i].fr;
    dp[0] = 0;

    int top = 1;
    for (int i = 1; i <= n; i++) {
        lf g(b[i], dp[i - 1]);
        while (top > 1) {
            g.s = cross(ch[top - 1], g);
            if (ch[top - 1].s < g.s) break;
            --top;
        }
        ch[top++] = g;
        int l = 1, r = top - 1;
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if (a[i] < ch[mid].s) r = mid - 1;
            else l = mid;
        }
        int fpos = l;
        dp[i] = ch[fpos].p * a[i] + ch[fpos].q;
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    
    erase();

    sort(arr.rbegin(), arr.rend());

    convexHullTrick();
    
    cout << dp[n];
}