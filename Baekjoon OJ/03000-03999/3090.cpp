// solution 2 : binary search (O(n) for each search)

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
ll t;
vector<ll> a, b;

ll f(ll x) {
    ll ret = 0;

    for (int i = 1; i < n; i++) {
        if (b[i - 1] + x < b[i]) {
            ret += b[i] - (b[i - 1] + x);
            b[i] = b[i - 1] + x;
        }
    }

    for (int i = n - 2; i >= 0; i--) {
        if (b[i] > b[i + 1] + x) {
            ret += b[i] - (b[i + 1] + x);
            b[i] = b[i + 1] + x;
        }
    }

    return ret;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n >> t;
    a.resize(n);
    for (auto& i : a) cin >> i;

    ll l = 0, r = 1e9;
    while (l < r) {
        ll mid = (l + r) >> 1;

        b = a;
        if (f(mid) <= t) r = mid;
        else l = mid + 1;
    }
    
    b = a;
    f(l);

    for (auto& i : b) 
        cout << i << ' ';

	return 0;
}

// solution 1 : binary search (O(nlogn) for each search)

//#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")

/*#include <bits/stdc++.h>
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
ll t;
vector<ll> a, b;
vector<int> st;

ll f(ll mid) {
    ll ret = 0;

    vector<int> in(n), out(n);
    priority_queue<pll, vector<pll>, greater<pll>> pq;

    for (auto& i : st) {
        pq.push({ b[i], i });
        in[i] = 1;
    }
        
    while (sz(pq)) {
        auto [w, v] = pq.top();
        pq.pop();
        
        if (out[v]) continue;
        out[v] = 1;
        
        int bl = 0, br = 0;
        if (0 < v && b[v - 1] > b[v] + mid) {
            ret += b[v - 1] - (b[v] + mid);
            b[v - 1] = b[v] + mid;
            bl = 1;
        }
        if (v < n - 1 && b[v] + mid < b[v + 1]) {
            ret += b[v + 1] - (b[v] + mid);
            b[v + 1] = b[v] + mid;
            br = 1;
        }
        
        if (0 < v && (!in[v - 1] || bl)) {
            in[v - 1] = 1;
            pq.push({ b[v - 1], v - 1 });
        }
        if (v < n - 1 && (!in[v + 1] || br)) {
            in[v + 1] = 1;
            pq.push({ b[v + 1], v + 1 });
        }
    }

    return ret;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n >> t;
    a.resize(n);
    for (auto& i : a) cin >> i;

    int down = 1, up = 0;
    for (int i = 0; i < n; i++) {
        if (i == n - 1) {
            if (down) st.push_back(i);
        }
        else {
            if (down && a[i] < a[i + 1]) {
                st.push_back(i);
                down = 0, up = 1;
            }
            if (a[i] > a[i + 1]) down = 1, up = 0;
        }
    }

    ll l = 0, r = 1e9;
    while (l < r) {
        ll mid = (l + r) >> 1;

        b = a;
        if (f(mid) <= t) r = mid;
        else l = mid + 1;
    }
    
    b = a;
    f(l);

    for (auto& i : b) 
        cout << i << ' ';

	return 0;
}*/