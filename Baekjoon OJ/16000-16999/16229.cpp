#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

int n, k, z[101010];
string s;

void zfunction() {
    int l = 0, r = 0;
    for (int i = 1; i < sz(s); i++) {
        if (r < i) {
            l = r = i;
            while (r < sz(s) && s[r - l] == s[r]) r++;
            z[i] = r - l; r--;
        }
        else {
            if (z[i - l] < r - i + 1) z[i] = z[i - l];
            else {
                l = i;
                while (r < sz(s) && s[r - l] == s[r]) r++;
                z[i] = r - l; r--;
            }
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

    cin >> n >> k >> s;

    if (n <= k) {
        cout << n;
        return 0;
    }

    zfunction();

    int ans = 0;
    for (int i = 1; i < sz(s); i++) {
        int len = i;
        if (z[i] + len != sz(s)) continue;
        
        int res = (len - z[i] % len) % len;

        if (res <= k) ans = len;
    }

    cout << ans;

    return 0;
}