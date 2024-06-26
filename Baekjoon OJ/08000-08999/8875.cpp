// parametric search ??
#include <bits/stdc++.h>
using namespace std;
#define ll long long

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
    priority_queue<ll> pq;

    int cp = 0;
    for (auto& i : a) {
        while (cp < T && c[cp].first < i)
            pq.push(c[cp++].second);

        for (int j = 0; j < mid && !pq.empty(); j++) pq.pop();
    }

    while (cp < T) 
        pq.push(c[cp++].second);

    for (auto& i : b) {
        for (int j = 0; j < mid && !pq.empty(); j++) {
            if (!(pq.top() < i)) return 0;
            pq.pop();
        }
    }
    return pq.empty();
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

    sort(a.begin(), a.end());
    sort(b.rbegin(), b.rend());
    sort(c.begin(), c.end());

    int l = 1, r = T;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (f(mid)) r = mid;
        else l = mid + 1;
    }

    cout << l;
}