#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int s; cin >> s;

    for (int a = -999; a <= 999; a++) {
        if (!a) continue;
        int b = s - a;
        if (!b) continue;
        if (b < -999 || 999 < b) continue;

        cout << a << ' ' << b << '\n';
        exit(0);
    }
}
