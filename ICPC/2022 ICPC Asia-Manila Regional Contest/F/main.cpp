#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int INF = 1e9 + 7;
constexpr int N = 202020;

int n;

ll w[N], w_all;
int nxt[N], prv[N];
priority_queue<pair<ll, int>> pq_mx;
priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq_mn;
bool vis[N];

void upd(int idx) {
    cout << idx << ' ' << w[idx] << '\n';

    w_all -= w[idx];
    if (prv[idx] != -1) {
        w[prv[idx]] += w[idx] / 2;
        w_all += w[idx] / 2;
    }
    if (nxt[idx] != -1) {
        w[nxt[idx]] += w[idx] / 2;
        w_all += w[idx] / 2;
    }
    w[idx] = 0;
    vis[idx] = 1;

    if (prv[idx] != -1) nxt[prv[idx]] = nxt[idx];
    if (nxt[idx] != -1) prv[nxt[idx]] = prv[idx];

    if (prv[idx] != -1) {
        pq_mx.push({w[prv[idx]], -prv[idx]});
        pq_mn.push({w[prv[idx]], prv[idx]});
    }
    if (nxt[idx] != -1) {
        pq_mx.push({w[nxt[idx]], -nxt[idx]});
        pq_mn.push({w[nxt[idx]], nxt[idx]});
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
        w_all += w[i];
    }

    memset(nxt, -1, sizeof(nxt));
    memset(prv, -1, sizeof(prv));
    for (int i = 1; i <= n; i++) {
        if (i + 1 <= n) nxt[i] = i + 1;
        if (1 <= i - 1) prv[i] = i - 1;
    }

    for (int i = 1; i <= n; i++) {
        pq_mx.push({w[i], -i});
        pq_mn.push({w[i], i});
    }

    while (!pq_mx.empty()) {
        auto [d, idx] = pq_mx.top();
        idx *= -1;
        pq_mx.pop();
        if (w[idx] != d || vis[idx]) continue;

        if (w_all - w[idx] >= w[idx]) {
            upd(idx);
        } else {
            pq_mx.push({d, -idx});
            while (!pq_mn.empty()) {
                auto [d_mn, idx_mn] = pq_mn.top();
                pq_mn.pop();
                if (w[idx_mn] != d_mn || vis[idx_mn]) continue;
                upd(idx_mn);
                break;
            }
        }
    }
}
