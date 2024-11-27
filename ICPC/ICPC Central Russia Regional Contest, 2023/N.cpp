#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const double EPS = 5e-9;
const ll INF = 1e18;

int n, tot;
ll a[1010], l[1010], r[1010];
int psum[2020];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        string s; cin >> s;
        if (s == "?") a[i] = -1;
        else {
            a[i] = stoll(s);
            tot++;
        }
    }

    if (tot == 0) {
        cout << 0;
        exit(0);
    }

    vector<ll> cc(1, -INF);
    for (int i = 1; i <= n; i++) {
        if (a[i] == -1) continue;

        if (i & 1) {
            l[i] = i * a[i] - i / 2;
            r[i] = i * a[i] + i / 2;
        } else {
            l[i] = i * a[i] - i / 2;
            r[i] = i * a[i] + i / 2 - 1;
        }
        // cout << l[i] << ' ' << r[i] << '\n';
        cc.push_back(l[i]);
        cc.push_back(r[i]);
    }

    sort(all(cc));
    cc.erase(unique(all(cc)), cc.end());

    for (int i = 1; i <= n; i++) {
        if (a[i] == -1) continue;
        int x = lower_bound(all(cc), l[i]) - cc.begin();
        int y = lower_bound(all(cc), r[i]) - cc.begin();
        psum[x]++;
        psum[y + 1]--;
    }

    for (int i = 1; i < sz(cc); i++) {
        psum[i] += psum[i - 1];
        if (psum[i] == tot) {
            cout << max(0ll, cc[i]);
            exit(0);
        }
    }
}
