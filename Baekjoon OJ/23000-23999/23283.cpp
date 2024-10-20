#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second

int n;
vector<pair<pll, int>> a;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    for (int tc = 0; tc < 2; tc++) {
        cin >> n;
        a.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i].fr.fr >> a[i].fr.sc;
            a[i].sc = i + 1;
        }

        int bit1 = 0, bit2 = 0;
        for (auto& i : a) 
            bit1 |= (i.fr.fr != 0), bit2 |= (i.fr.sc != 0);
        
        if (!bit1 || !bit2) {
            cout << -1 << '\n';
            continue;
        }

        sort(a.begin(), a.end(), [&](const pair<pll, int>& p1, const pair<pll, int>& p2) {
            return p1.fr.fr > p2.fr.fr;
        });

        vector<int> ans;

        ans.push_back(a[0].sc);
        for (int i = 1; i < n; i += 2) {
            if (a[i].fr.sc >= a[i + 1].fr.sc) ans.push_back(a[i].sc);
            else ans.push_back(a[i + 1].sc);
        }
        
        sort(ans.begin(), ans.end());
        for (auto& i : ans)
            cout << i << ' ';
        cout << '\n';
    }
}