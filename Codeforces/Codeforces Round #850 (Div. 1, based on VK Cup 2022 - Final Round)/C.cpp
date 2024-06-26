//#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")

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
vector<ll> ans;
vector<set<ll>> cnt;

void init() {
    a.clear();
    b.clear();
    ans.clear();
    cnt.clear();
}

void getLastAnswer() {
    int now = 1;

    vector<pll> c;
    for (int i = 0; i < n; i++) {
        c.push_back({ a[i], i });
    }

    sort(all(c));

    for (auto& i : c) {
        int val = i.fr, idx = i.sc;
        if (val < now) {
            cnt[val].insert(idx);
            b[idx] = val;
        }
        else if (val == now) {
            cnt[val].insert(idx);
            b[idx] = val;
            now++;
        }
        else {
            ans[n - 1] += val - now;
            cnt[now].insert(idx);
            b[idx] = now;
            now++;
        }
    }
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int tc; cin >> tc;
	for (int tt = 1; tt <= tc; tt++) {
        init();

        // input
		cin >> n;
        a.resize(n); b.resize(n);
        ans.resize(n); cnt.resize(n + 1);
        for (auto& i : a) cin >> i;
        
        // solve
        getLastAnswer();

        set<int> s;
        int top = 0;
        for (int i = 1; i <= n; i++) {
            if (sz(cnt[i]) >= 2) s.insert(i);
            if (sz(cnt[i])) top = i;
        }

        // 관리해야 할 값들: b, cnt, s, top
        for (int i = n - 2; i >= 0; i--) {
            // update
            int v = b[i + 1];
            
            cnt[v].erase(i + 1);
            if (sz(cnt[v]) == 1) s.erase(v);

            ans[i] = ans[i + 1] - (a[i + 1] - v);
            if (top == v && cnt[v].empty()) top--; 
            
            // update 2
            if (top >= v && cnt[v].empty()) {
                auto it = s.upper_bound(v);
                
                if (it != s.end()) {
                    int idx = *cnt[*it].begin();

                    ans[i] += *it - v;
                    cnt[*it].erase(idx);
                    cnt[v].insert(idx);
                    b[idx] = v;
                    if (sz(cnt[*it]) == 1) s.erase(it);
                }
                else {
                    int idx = *cnt[top].begin();

                    ans[i] += top - v;
                    cnt[top].erase(idx);
                    cnt[v].insert(idx);
                    b[idx] = v;

                    if (sz(cnt[top]) == 1) s.erase(top);
                    else if (cnt[top].empty()) top--;
                }
            }

            /*for (int i = 1; i <= n; i++) {
                cout << i << ' ';
                for (auto& j : cnt[i])
                    cout << j << ' ';
                cout << '\n';
            }
            cout << '\n';*/
        }

        for (auto& i : ans)
            cout << i << ' ';
        cout << '\n';
	}

	return 0;
}