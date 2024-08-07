#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

string s;

int f(int l, int r, int cnt) {
    if (l >= r) return cnt;

    int ret = 4;
    if (s[l] == s[r]) {
        ret = min(ret, f(l + 1, r - 1, cnt));
    }
    else if (cnt < 3) {
        ret = min(ret, f(l + 1, r, cnt + 1));
        ret = min(ret, f(l, r - 1, cnt + 1));
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

    cin >> s;

    int ans = f(0, sz(s) - 1, 0);
    cout << (ans == 4 ? -1 : ans);

    return 0;
}