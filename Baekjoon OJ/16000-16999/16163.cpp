#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

int n;
string s;

vector<int> p; // p[i]: the radius of the palindrome at the current position i
void manacher() {
    // Preprocessing for determining even-length pelindromes
    n = sz(s);
    s.resize(n << 1 | 1);
    p.resize(n << 1 | 1);
    for (int i = n - 1; i >= 0; i--) {
        s[i << 1 | 1] = s[i];
        s[i << 1] = '#';
    }
    n <<= 1;
    s[n++] = '#';
    // Processing
    int r = -1, c = -1;
    // r: end of palindrome
    // c: center of palindrome
    for (int i = 0; i < n; i++) {
        if (i <= r) p[i] = min(r - i, p[c * 2 - i]);
        else p[i] = 0;
        while (1) {
            if (i - p[i] - 1 < 0 || i + p[i] + 1 >= n) break;
            if (s[i + p[i] + 1] != s[i - p[i] - 1]) break;
            p[i]++;
        }
        if (i + p[i] > r) {
            r = i + p[i], c = i;
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> s;

    manacher();

    ll ans = 0;
    for (int i = 0; i < sz(p); i++) {
        ans += (p[i] + 1) / 2;
    }
    cout << ans;
}
