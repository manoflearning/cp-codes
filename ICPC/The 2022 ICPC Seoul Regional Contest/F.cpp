#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second
#define ll long long

vector<pii> a, b;
vector<int> c;
int num[101010];
ll psum[101010];

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    int n, k;
    cin >> n >> k;

	a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].fr >> a[i].sc;
    }

    int s = a[0].fr, e = a[0].sc;
    for (int i = 1; i < n; i++) {
        if (e < a[i].fr) {
            b.push_back({ s, e });
            s = a[i].fr, e = a[i].sc;
        }
        else {
            e = max(e, a[i].sc);
        }
        num[i] = b.size();
    }
    b.push_back({ s, e });

    for (int i = 1; i < b.size(); i++) {
        psum[i] = psum[i - 1];
        psum[i] += b[i].fr - b[i - 1].sc;
    }

    c.resize(k + 1, 0);
    for (int i = 1; i <= k; i++) {
        cin >> c[i];
        c[i]--;
    }

    ll ans = 0;
    for (int i = 1; i <= k; i++) {
        int u = num[c[i]], v = num[c[i - 1]];
        if (u > v) swap(u, v);
        ans += psum[v] - psum[u];
    }

    cout << ans;

	return 0;
}