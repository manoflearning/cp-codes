#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

struct Frac {
    ll n, d; // n / d
    ll gcd(ll x, ll y) {
        if (!y) return x;
        return gcd(y, x % y);
    }
    ll lcm(ll x, ll y) { return x * y / gcd(x, y); }
    void reduce() {
        ll g = gcd(n, d);
        n /= g, d /= g;
    }
    Frac operator+(const Frac& rhs) const {
        Frac ret;
        ret.n = n * rhs.d + rhs.n * d;
        ret.d = d * rhs.d;
        ret.reduce();
        return ret;
    }
    Frac operator/(const Frac& rhs) const {
        Frac ret;
        ret.n = n * rhs.d;
        ret.d = d * rhs.n;
        ret.reduce();
        return ret;
    }
};

int n;
vector<char> a;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    a.resize(n);
    for (auto& i : a) cin >> i;

    if (a[0] != '(') {
        cout << -1;
        exit(0);
    }

    stack<vector<Frac>> stk;
    stk.push(vector<Frac>(0));
    for (auto& c : a) {
        if (c == '(') stk.push(vector<Frac>(0));
        else if (c == ')') {
            if (sz(stk.top()) == 3) {
                auto tmp = stk.top();
                stk.pop();
                stk.top().push_back(tmp[0] + tmp[1] / tmp[2]);
            } else {
                cout << -1;
                exit(0);
            }
        } else {
            stk.top().push_back({ c - '0', 1 });
        }
    }

    if (sz(stk) != 1) {
        cout << -1;
        exit(0);
    }
    if (sz(stk.top()) != 1) {
        cout << -1;
        exit(0);
    }

    cout << stk.top()[0].n << ' ' << stk.top()[0].d;
}
