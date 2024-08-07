#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define lll __int128_t

void YES() { cout << "YES"; exit(0); }
void NO() { cout << "NO"; exit(0); }

lll a, b, S;

void input() {
    ll dua, dub, duS;
    cin >> dua >> dub >> duS;
    a = dua, b = dub, S = duS;
}

lll gcd(lll a, lll b) {
    if (!b) return a;
    return gcd(b, a % b);
}
pair<pair<lll, lll>, lll> egcd(lll a, lll b) { 
    lll s = 0, olds = 1;
    lll t = 1, oldt = 0;
    lll r = b, oldr = a;
    while (r != 0) {
        lll q = oldr / r;
        lll tmp = oldr - q * r;
        oldr = r, r = tmp;
        tmp = olds - q * s;
        olds = s, s = tmp;
        tmp = oldt - q * t;
        oldt = t, t = tmp;
    }
    // a * olds + b * oldt = d
    // oldr = gcd(a, b)
    return { { olds, oldt }, oldr };
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    if (a == 0 && b == 0) {
        if (S == 0) YES();
        else NO();
    }
    else if (a == 0 || b == 0) {
        if (S % max(a, b) == 0) YES();
        else NO();
    }

    auto eg = egcd(a, b);
    auto [x, y] = eg.first;
    lll d = eg.second;
    
    if (S % d) NO();
    
    a /= d, b /= d, S /= d;

    x *= S, y *= S;
    
    if (x > 0) {
        lll t = x / b;
        x -= t * b;
        y += t * a;
    }
    if (x < 0) {
        lll t = -x / b + 1;
        x += t * b;
        y -= t * a;
    }
    
    while (1) {
        assert(a * x + b * y == S);
        if (x >= 0 && y >= 0 && gcd(x, y) == 1) YES();
        x += b, y -= a;
        if (y < 0) break;
    }
    NO();
}