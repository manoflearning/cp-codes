#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second
#define ll long long

int n, m, k;
vector<pii> a;

int main() {
    #ifndef ONLINE_JUDGE
	// Enter the absolute path of the local file input.txt, output.txt
	// Or just enter the "input.txt", "output.txt"
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m >> k;
    a.resize(n);
    for (auto& i : a) cin >> i.fr >> i.sc;

    sort(a.begin(), a.end(), [&](pii u, pii v) {
        return u.sc > v.sc;
    });

    ll ans = 0;
    for (int i = 0; i < k; i++) ans += a[i].fr;

    sort(a.begin() + k, a.end(), [&](pii u, pii v) {
        return u.fr > v.fr;
    });

    for (int i = k; i < k + m; i++) {
        ans += a[i].fr;
    }

    cout << ans;

    return 0;
}