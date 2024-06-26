#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int INF = 1e9 + 7;

int n, k;
vector<int> a;

int f(vector<int> b, int bit) {
    // base case
    int cnt = 0;
    for (int i = 1; i <= k; i++) {
        if (bit & (1 << i)) cnt++;
    }
    if (cnt == 1) return 0;

    // inductive step
    int ret = INF;
    for (int x = 1; x <= k; x++) {
        if (!(bit & (1 << x))) continue;

        int res = 0;

        int nbit = bit - (1 << x);
        vector<int> c;
        for (auto& i : b) {
            if (nbit & (1 << i)) {
                if (c.empty() || c.back() != i) {
                    c.push_back(i);
                }
            }
            else if (x == i) res++;
        }

        res += f(c, nbit);
        ret = min(ret, res);
    }

    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> k;
    a.resize(n);
    for (auto& i : a) cin >> i;

    vector<int> b;
    int bit = 0;
    for (auto& i : a) {
        if (b.empty() || b.back() != i) {
            b.push_back(i);
            bit |= (1 << i);
        }
    }

    cout << f(b, bit);
}