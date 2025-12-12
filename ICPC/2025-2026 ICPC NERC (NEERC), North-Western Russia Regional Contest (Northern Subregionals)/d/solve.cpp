#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

void f(string &p, char c1, char c2, int x, int y) {
    while (x > y) {
        p.push_back(c2);
        x--;
    }
    while (x < y) {
        p.push_back(c1);
        y--;
    }
    while (x--) {
        p.push_back('d');
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int a, b, c;
    cin >> a >> b >> c;

    int sum = a + b + c;
    int mx = max({a, b, c});
    int mn = min({a, b, c});

    if (sum - mx < mx) {
        cout << "No";
        exit(0);
    }

    string p, q, r;
    p += "z", q += "z", r += "z";
    
    p += string(mn, 'a');
    q += string(mn, 'b');
    r += string(mn, 'c');
    a -= mn, b -= mn, c -= mn;

    if (!a) f(r, 'a', 'b', b, c);
    else if (!b) f(q, 'a', 'c', a, c);
    else if (!c) f(p, 'b', 'c', a, b);

    cout << "Yes\n";
    cout << p << '\n' << q << '\n' << r;
}