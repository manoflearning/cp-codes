#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MOD = 1'000;

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

        if (n == 2) {
            cout << "027\n";
            continue;
        }

        Matrix bc;
        bc.a.resize(2, vector<ll>(2));
        bc.a[0][0] = 6, bc.a[0][1] = -4;
        bc.a[1][0] = 1, bc.a[1][1] = 0;

        Matrix ans = po(bc, n - 2);

        ll num = (ans.a[0][0] * 28 + ans.a[0][1] * 6) % MOD;
        num = (num + MOD - 1) % MOD;        
        cout << getAns(num) << '\n';
    }
}