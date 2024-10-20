#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second
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
        int n; cin >> n;
        vector<pii> a(n);
        for (auto& i : a)
            cin >> i.fr >> i.sc;

        sort(all(a), [](pii p1, pii p2) {
            if (p1.fr > p1.sc) swap(p1.fr, p1.sc);
            if (p2.fr > p2.sc) swap(p2.fr, p2.sc);

            if (p1.fr ^ p2.fr) return p1.fr < p2.fr;
            else return p1.sc < p2.sc;

            // int res1 = 0, res2 = 0;
            // res1 += (p1.fr > p2.fr);
            // res1 += (p1.sc > p2.fr);
            // res1 += (p1.fr > p2.sc);
            // res1 += (p1.sc > p2.sc);
            // res2 += (p1.fr < p2.fr);
            // res2 += (p1.sc < p2.fr);
            // res2 += (p1.fr < p2.sc);
            // res2 += (p1.sc < p2.sc);
            // return res1 < res2;
        });

        for (auto& i : a)
            cout << i.fr << ' ' << i.sc << ' ';
        cout << '\n';
    }
}
