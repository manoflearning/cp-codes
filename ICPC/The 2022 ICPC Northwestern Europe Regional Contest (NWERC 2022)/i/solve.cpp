#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

int gcd(int x, int y) {
    if (!y) return x;
    return gcd(y, x % y);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int c, d;
    cin >> c >> d;

    int a{}, b{};
    for (int i = c; i <= d; i++) {
        string s; cin >> s;

        if (s == "FizzBuzz") {
            a = gcd(a, i);
            b = gcd(b, i);
        }
        if (s == "Fizz") { a = gcd(a, i); }
        if (s == "Buzz") { b = gcd(b, i); }
    }

    if (!a) a = (int)1e6;
    if (!b) b = (int)1e6;

    cout << a << ' ' << b << '\n';
}
