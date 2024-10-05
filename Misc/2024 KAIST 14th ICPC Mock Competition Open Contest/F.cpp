#include <bits/stdc++.h>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        vector<string> a(n);
        for (auto& i : a) cin >> i;

        int ans = 0;
        for (int i = 1; i < n; i++) {
            string t = a[i];
            if (t == "110") t = "011";

            if (t == "010") ans ^= 0;
            else if (t == "101") ans ^= 0;
            else if (t == "011") ans ^= 1;
            else if (t == "111") ans ^= 2;
        }

        if (ans) cout << "Yesyes\n";
        else cout << "Nono\n";
    }
}
