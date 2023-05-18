#include <bits/stdc++.h>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    string s; cin >> s;

    int ans = 0;
    int cnt = 0;
    for (auto& i : s) {
        if (i == '(') cnt++;
        if (i == ')') {
            if (cnt) cnt--;
            else ans++;
        }
    }
    ans += cnt;

    cout << ans;
}