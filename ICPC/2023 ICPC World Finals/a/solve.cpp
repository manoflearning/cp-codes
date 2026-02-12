#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

int query(int a, int b, int c) {
    cout << a << ' ' << b << ' ' << c << '\n';
    cout.flush();

    int ret; cin >> ret;
    return ret;
}

void f(int x1, int x2, int x3, int x4) {
    if (x4 == 0) {
        cout << x1 << ' ' << x2 << ' ' << x3 << '\n';
        exit(0);
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    const int x1 = query(1, 0, 0);
    const int x2 = query(0, 1, 0);
    const int x3 = query(0, 0, 1);
    const int x4 = query(1, 1, 1);
    const int x5 = query(1, 2, 3);

    f(x1, x2, x3, x4 - (1 * x1 + 1 * x2 + 1 * x3));
    f(x1, x2, x3, x5 - (1 * x1 + 2 * x2 + 3 * x3));
    if ((x5 - (x1 + 2 * x2)) % 3 == 0) {
        f(x1, x2, (x5 - (x1 + 2 * x2)) / 3, x4 - (x1 + x2 + (x5 - (x1 + 2 * x2)) / 3));
    }
    f(x1, x4 - (x1 + x3), x3, x5 - (x1 + 2 * (x4 - (x1 + x3)) + 3 * x3));
    f(x4 - (x2 + x3), x2, x3, x5 - ((x4 - (x2 + x3)) + 2 * x2 + 3 * x3));
}
