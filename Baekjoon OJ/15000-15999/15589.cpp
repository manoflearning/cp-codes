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
#define vt vector
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int n;
ll cnt[202020], w[202020], psum[202020];
vector<ll> c;
pll a[101010];

void cc() {
    c.push_back(-INF);
    for (auto& i : a) {
        c.push_back(i.fr);
        c.push_back(i.sc);
    }

    sort(all(c));
    c.erase(unique(all(c)), c.end());
    
    for (auto& i : a) {
        i.fr = lower_bound(all(c), i.fr) - c.begin();
        i.sc = lower_bound(all(c), i.sc) - c.begin();
    }

    for (int i = 1; i + 1 < sz(c); i++) {
        w[i] = c[i + 1] - c[i];
    }
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i].fr >> a[i].sc;

    cc();

    for (int i = 1; i <= n; i++) {
        cnt[a[i].fr]++, cnt[a[i].sc]--;
    }

    for (int i = 1; i < sz(c); i++)
        cnt[i] += cnt[i - 1];

    ll sum = 0;

    for (int i = 1; i < sz(c); i++) {
        if (cnt[i] == 1) psum[i] += w[i];
        psum[i] += psum[i - 1];
        if (cnt[i]) sum += w[i];
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = max(ans, sum - psum[a[i].sc - 1] + psum[a[i].fr - 1]);
    }

    cout << ans;

	return 0;
}

// using mo's algorithm
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
#define vt vector
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int n;
vector<pll> a;
vector<ll> c;
ll w[202020], cnt[202020];

void cc() {
    c.push_back(-INF);
    for (auto& i : a) {
        c.push_back(i.fr);
        c.push_back(i.sc);
    }

    sort(all(c));
    c.erase(unique(all(c)), c.end());
    
    for (auto& i : a) {
        i.fr = lower_bound(all(c), i.fr) - c.begin();
        i.sc = lower_bound(all(c), i.sc) - c.begin();
    }

    for (int i = 1; i + 1 < sz(c); i++) {
        w[i] = c[i + 1] - c[i];
    }
}

int sq = 332;
struct se {
	ll s, e;
	bool operator<(const se& rhs) const {
		if (s / sq != rhs.s / sq) return s / sq < rhs.s / sq;
		return e < rhs.e;
	}
};
vector<se> q;
ll ans = 0, res;
void input() {
	// TODO: 1. receive input 2. resize q, ans 3. calculate sq 
    for (auto& i : a) {
        q.push_back({ i.fr, i.sc - 1 });
    }
}
void add(int idx) {
	// TODO: add value at idx from data structure
    cnt[idx]--;
    if (!cnt[idx]) res -= w[idx];
}
void del(int idx) {
	// TODO: remove value at idx from data structure
    if (!cnt[idx]) res += w[idx];
    cnt[idx]++;
}
void f() {
	int s = q[0].s, e = q[0].e;
	// TODO: initialize data structure
    for (int i = 0; i < sz(q); i++) {
        cnt[q[i].s]++;
        cnt[q[i].e + 1]--;
    }
    for (int i = 1; i < sz(c); i++) {
        cnt[i] += cnt[i - 1];
        if (cnt[i]) res += w[i];
    }
    for (int i = s; i <= e; i++) add(i);
	ans = max(ans, res);
	for (int i = 1; i < q.size(); i++) {
		while (q[i].s < s) add(--s);
		while (e < q[i].e) add(++e);
		while (s < q[i].s) del(s++);
		while (q[i].e < e) del(e--);
		ans = max(ans, res);
	}
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n;
    a.resize(n);
    for (auto& i : a)
        cin >> i.fr >> i.sc;

    cc();

    input();

    sort(q.begin(), q.end());
	f();
	cout << ans;

	return 0;
}*/