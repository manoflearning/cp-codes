#include <bits/stdc++.h>
using namespace std;
#define ll long long

/*struct Node {
    ll a, b; // a + b * sqrt(5)
    Node operator*(const Node& rhs) const {
        Node ret;
        ret.a = (a * rhs.a + 5 * b * rhs.b) % 5'000'000;
        ret.b = (a * rhs.b + b * rhs.a) % 5'000'000;
        return ret;
    }
};

const Node bc = { 3, 1 };
Node f(ll x) {
    if (x == 1) return bc;
    Node res = f(x >> 1);
    Node ret = res * res;
    if (x & 1) ret = ret * bc;
    return ret;
}

string getAns(Node x) {
    int num = (ll)(x.a + sqrt((long double)5) * x.b) % 1'000;
    string ret = to_string(num);
    while (ret.size() < 3) {
        ret.insert(0, "0");
    }
    return ret;
}*/

const int MOD = 5'000'000;

struct Matrix {
    vector<vector<ll>> a;
    Matrix operator*(const Matrix& rhs) const {
        Matrix ret;
        ret.a.resize(a.size(), vector<ll>(rhs.a[0].size()));
        for (int y = 0; y < ret.a.size(); y++) {
            for (int x = 0; x < ret.a[y].size(); x++) {
                ll sum = 0;
                for (int i = 0; i < a[y].size(); i++) {
                    sum = (sum + a[y][i] * rhs.a[i][x]) % MOD;
                }
                ret.a[y][x] = sum;
            }
        }
        return ret;
    }
};

Matrix po(const Matrix& val, ll exp) {
    if (exp == 1) return val;
    Matrix res = po(val, exp / 2);
    Matrix ret = res * res;
    if (exp & 1) ret = ret * val;
    return ret;
}

string getAns(int num) {
    string ret = to_string(num);
    while (ret.size() < 3) {
        ret.insert(0, "0");
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

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        cout << "Case #" << tt << ": ";

        int n; cin >> n;
        Matrix bc;
        bc.a.resize(2, vector<ll>(2));
        bc.a[0][0] = 3, bc.a[0][1] = 5;
        bc.a[1][0] = 1, bc.a[1][1] = 3;

        Matrix ans = po(bc, n - 1);

        ll num = (ans.a[0][0] + ans.a[0][1]) % MOD;
        num += (ll)(sqrt((long double)5) * (ans.a[1][0] + ans.a[1][1])) % MOD;
        
        cout << getAns(num) << '\n';
    }
}