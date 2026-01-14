#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const ll inf = 1LL << 62;

int n;
vector<ll> a, ra;

void floydWarshall(vector<vector<ll>> &m) {
    rep(i, 1, n + 1) m[i][i] = min(m[i][i], 0LL);
    rep(i, 1, n + 1) rep(j, 1, i + 1) rep(k, 1, i + 1)
        if (m[i][k] != inf && m[k][j] != inf) {
            auto newDist = m[i - 1][k] + m[k][j] + abs(ra[i] - ra[k]);
            m[i][j] = min(m[i][j], newDist);
        }
    // rep(k, 1, n + 1) if (m[k][k] < 0) rep(i, k, n + 1) rep(j, 1, k + 1)
    //     if (m[i][k] != inf && m[k][j] != inf) m[i][j] = -inf;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    cin >> n;
    a.assign(n + 1, 0), ra.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        ra[a[i]] = i;
    }

    // base case
    vector<vector<ll>> m(n + 1, vector<ll>(n + 1, inf));
    for (int i = 1; i <= n; i++) {
        m[i][i] = 0;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i - 1; j++) {
            m[i][j] = 0;

            // ll lb = ra[j], ub = ra[j];
            for (int k = j + 1; k <= i; k++) {
                // lb = min(lb, ra[k]);
                // ub = max(ub, ra[k]);
                m[i][j] += abs(ra[k] - ra[j]);
            }
            // m[i][j] = ub - lb;
        }
    }

    // inductive step
    floydWarshall(m);

    // for (int i = 1; i <= n; i++) {
    //     for (int j = 1; j < i; j++) {
    //         cout << "from: " << i << ", to: " << j << ", dist: " << m[i][j] << '\n';
    //     }
    // }

    cout << m[n][1] << '\n';
}
