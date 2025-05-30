// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int n;
vector<ll> a, b;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    a.resize(n);
    b.resize(n);
    for (auto& i : a) cin >> i;
    for (auto& i : b) cin >> i;

    sort(all(a));
    sort(all(b));

    vector<int> vi(n);

    ll ans = 0;
    int p = 0;
    priority_queue<ll> pq;

    for (int i = 0; i < n; i++) {
        while (p < n && b[p] < a[i]) pq.push(b[p++]);

        if (!pq.empty()) {
            pq.pop();
            ans += 100;
            vi[i] = 1;
        }
    }
    while (p < n) pq.push(b[p++]);

    map<ll, ll> mp;
    while (!pq.empty()) {
        mp[pq.top()]++;
        pq.pop();
    }

    for (int i = 0; i < n; i++) {
        if (vi[i]) continue;
        if (mp[a[i]]) mp[a[i]]--, ans += 20;
        else ans -= 50;
    }

    cout << ans;
}