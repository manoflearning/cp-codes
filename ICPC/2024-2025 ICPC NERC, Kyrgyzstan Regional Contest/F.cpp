#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 303030;

int n, s, f;
int b[MAXN], e[MAXN];

vector<int> cc(1, -1);

ll psum[MAXN << 1], ans[MAXN];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> s >> f;
    for (int i = 1; i <= n; i++) {
        cin >> b[i] >> e[i];
        b[i] = max(b[i], s);
        e[i] = max(e[i], s);
        b[i] = min(b[i], f);
        e[i] = min(e[i], f);
    }

    cc.push_back(s);
    cc.push_back(f);
    for (int i = 1; i <= n; i++) {
        cc.push_back(b[i]);
        cc.push_back(e[i]);
    }

    sort(all(cc));
    cc.erase(unique(all(cc)), cc.end());

    s = lower_bound(all(cc), s) - cc.begin();
    f = lower_bound(all(cc), f) - cc.begin();
    for (int i = 1; i <= n; i++) {
        b[i] = lower_bound(all(cc), b[i]) - cc.begin();
        e[i] = lower_bound(all(cc), e[i]) - cc.begin();

        psum[b[i]]++;
        psum[e[i]]--;
    }
    
    for (int i = 1; i < sz(cc); i++) {
        psum[i] += psum[i - 1];
        if (i + 1 < sz(cc)) {
            // cout << psum[i] << ' ' << cc[i + 1] - cc[i] << '\n';
            ans[psum[i] + 1] += cc[i + 1] - cc[i];
        }
    }

    // for (int i = 1; i < sz(cc); i++) {
    //     cout << psum[i] << ' ';
    // }
    // cout << '\n';

    for (int i = 1; i <= n; i++) {
        ans[i] += ans[i - 1];
        cout << ans[i] << ' ';
    }
}
