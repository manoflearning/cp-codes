#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	string s; cin >> s;

    int h = 0, mx = 0;
    ll ans = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(') {
            h++;
            mx = h;
        }
        else {
            if (mx == h) ans += mx - 1;
            h--;
        }
    }

    cout << ans;

	return 0;
}