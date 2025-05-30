// p[i] = p[i - 1] ^ a[i]
// press i -> swap(p[i - 1], p[i])

// A = "0101"
// pA = "00110"
// B = "0100"
// pB = "00111" or "11000"

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n;
        string s, t;
        cin >> n >> s >> t;
        
        int cnts = 0, cntt = 0;
        int ps = 0, pt = 0;
        for (auto& c : s) {
            if (c == '1') ps ^= 1;
            cnts += ps;
        }
        for (auto& c : t) {
            if (c == '1') pt ^= 1;
            cntt += pt;
        }
        
        if (cnts == cntt || cnts == n + 1 - cntt) cout << "YES\n";
        else cout << "NO\n";
    }
}