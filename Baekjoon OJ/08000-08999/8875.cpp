// parametric search ??
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

int n, m, T;
vector<ll> a, b;
vector<pair<ll, ll>> c;

void input() {
    cin >> n >> m >> T;
    a.resize(n);
    b.resize(m);
    c.resize(T);
    for (auto& i : a) cin >> i;
    for (auto& i : b) cin >> i;
    for (auto& i : c) cin >> i.first >> i.second;
}

int isImpossible() {
    ll amx = -1, bmx = -1;
    for (auto& i : a) amx = max(amx, i);
    for (auto& i : b) bmx = max(bmx, i);
    for (auto& i : c) {
        if (amx <= i.first && bmx <= i.second) return 1;
    }
    return 0;
}

int f(int mid) {
    vector<ll> d;

    int ap = 0, ccnt = 0;
    for (auto& i : c) {
        while (ap < n && i.first < a[ap]) ap++;
        if (ap > 0 && (ccnt + ap) / ap <= mid) ccnt++;
        else d.push_back(i.second);
    }
    
    sort(d.rbegin(), d.rend());

    int bp = 0;
    for (int i = 0; i < sz(d); i++) {
        while (bp < sz(b) && d[i] < b[bp]) bp++;

        if (bp == 0 || ((i + 1) + bp - 1) / bp > mid) return 0;
    }
    return 1;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    if (isImpossible()) {
        cout << -1;
        return 0;
    }

    sort(a.rbegin(), a.rend());
    sort(b.rbegin(), b.rend());
    sort(c.begin(), c.end(), [&](const pair<ll, ll>& p1, const pair<ll, ll>& p2) {
        //return p1.second ^ p2.second ? p1.second < p2.second : p1.first > p2.first;
        return p1.first ^ p2.first ? p1.first > p2.first : p1.second > p2.second;
    });

    int l = 1, r = T;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (f(mid)) r = mid;
        else l = mid + 1;
    }

    cout << l;
}