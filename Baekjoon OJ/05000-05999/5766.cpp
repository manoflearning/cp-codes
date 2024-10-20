#include <bits/stdc++.h>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    while (1) {
        int n, m;
        cin >> n >> m;

        if (!n && !m) break;

        vector<int> cnt(101010);
        for (int i = 0; i < n * m; i++) {
            int x; cin >> x;
            cnt[x]++;
        }

        vector<pair<int, int>> a;
        for (int i = 1; i <= 100'000; i++) {
            a.push_back({ cnt[i], -i });
        }
        sort(a.rbegin(), a.rend());

        cout << -a[1].second << ' ';
        for (int i = 2; a[i].first == a[i - 1].first; i++) {
            cout << -a[i].second << ' ';
        }
        cout << '\n';
    }
}