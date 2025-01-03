#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MOD = 1e9 + 7;

ll p2[101010];

int f(const vector<ll>& a) {
    int n = a.size();
    vector<int> cnt2(n);
    vector<int> pneg(n);
    int lastneg = -1;
    
    for (int i = 1; i < n; i++) {
        if (abs(a[i]) == 2) cnt2[i]++;
        if (a[i] < 0) { pneg[i]++; lastneg = i; }
        cnt2[i] += cnt2[i - 1];
        pneg[i] += pneg[i - 1];
    }

    int mx = -1;
    for (int l = 1; l < n; l++) {
        int r = n - 1;
        if ((pneg[r] - pneg[l - 1]) & 1) r = lastneg - 1;
        if (r < l) continue;
        mx = max(mx, cnt2[r] - cnt2[l - 1]);
    }
    return mx;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    p2[0] = 1;
    for (int i = 1; i < 101010; i++)
        p2[i] = 2 * p2[i - 1] % MOD;

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        vector<ll> a(n);
        for (auto& i : a) cin >> i;
        a.push_back(0);

        int mx = -1;

        vector<ll> arr(1, 0);
        for (auto& i : a) {
            if (i == 0) {
                if (arr.size() > 1) 
                    mx = max(mx, f(arr));
                arr.clear();
                arr.push_back(0);
            }
            else arr.push_back(i);
        }

        cout << (mx == -1 ? 0 : p2[mx]) << '\n';
    }
}