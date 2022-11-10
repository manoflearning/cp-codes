#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size() 
#define fr first
#define sc second

int n;
vector<int> a;

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    cin >> n;
    a.resize(n);
    for (auto& i : a) cin >> i;

    sort(all(a));

    int ans = 0;

    int cnt = 0;
    for (int i = 0; i < sz(a); i++) {
        if (i > 0 && a[i] != a[i - 1]) cnt = 0;

        cnt++;
        ans = max(ans, cnt);
    }

    a.erase(unique(all(a)), a.end());

    vector<pair<int, int>> diff;
    set<pair<int, int>> vi;
    
    for (int i = 0; i < sz(a); i++) {
        for (int j = i + 1; j < sz(a); j++) {
            auto it = vi.find({ a[j] - a[i], j % (a[j] - a[i]) });

            if (it == vi.end()) {
                diff.push_back({ a[j] - a[i], j });
                vi.insert({ a[j] - a[i], j % (a[j] - a[i]) });
            }
        }
    }

    for (auto& i : diff) {
        int len = i.fr, now = i.sc;

        int res = 2;
        while (1) {
            int x = a[now] + len;

            int idx = lower_bound(all(a), x) - a.begin();
            if (idx == sz(a) || a[idx] != x) break;

            res++;
            now = idx; 
        }
        
        ans = max(ans, res);
    }

    cout << ans;

	return 0;
}