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

int n, a[202020];
vector<pii> ans;

void cal(int s, int e) {
    int idx1 = -1, idx2 = -1;
    for (int i = s; i <= e; i++) {
        if (a[i] != 0) {
            if (idx1 == -1) idx1 = i;
            else idx2 = i;
        }
    }

    if ((idx1 & 1) == (idx2 & 1) && a[idx1] != a[idx2]) {
        ans.push_back({ s, e });
    }
    if ((idx1 & 1) != (idx2 & 1) && a[idx1] == a[idx2]) {
        ans.push_back({ s, e });
    }

    if ((idx1 & 1) == (idx2 & 1) && a[idx1] == a[idx2]) {
        for (int i = s; i <= e; i++) {
            if (i == idx2 - 1) 
                ans.push_back({ idx2 - 1, idx2 });
            else if (i == idx2) continue;
            else ans.push_back({ i, i });
        }
    }
    if ((idx1 & 1) != (idx2 & 1) && a[idx1] != a[idx2]) {
        for (int i = s; i <= e; i++) {
            ans.push_back({ i, i });
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
		cin >> n;
        int sum = 0;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            sum += a[i];
        }
        
        if (sum % 2) {
            cout << -1 << '\n';
            continue;
        }
        
        for (int i = 1; i <= n; i++) {
            int s = i, e = i;

            int cnt = (a[i] != 0);
            while (e + 1 <= n && cnt < 2) {
                e++;
                cnt += (a[e] != 0);
            }

            cal(s, e);
            i = e;
        }

        cout << sz(ans) << '\n';
        for (auto& i : ans)
            cout << i.fr << ' ' << i.sc << '\n';
        ans.clear();
	}

	return 0;
}