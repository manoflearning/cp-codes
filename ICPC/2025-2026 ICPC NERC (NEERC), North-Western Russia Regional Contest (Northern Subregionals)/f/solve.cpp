#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    string s, c;
    cin >> s >> c;

    int r = sz(c);
    for (int p = 1; p < sz(s); p++) {
        int q = sz(s) - p;

        if (p <= q + r && q + r <= p + 1) {
            cout << s.substr(0, p) << ' ' << s.substr(p, q);
            exit(0);
        }
    }
}