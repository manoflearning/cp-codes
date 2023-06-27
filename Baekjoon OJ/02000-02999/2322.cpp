// 초기에 기존 위치에 있었던 것 중 최솟값 하나를 임의로 옮기거나,
// 초기에 기존 위치에 없었던 것 중 최솟값 하나로 시작.

#include <bits/stdc++.h>
using namespace std;
#define ll long long

const ll INF = 1e10;

int n;
vector<ll> a, b, c;

void input() {
    cin >> n;
    a.resize(n);
    for (auto& i : a) cin >> i;
}

void valueCompress() {
    b = a;
    c = a;
    sort(c.begin(), c.end());
    for (auto& i : a) {
        i = lower_bound(c.begin(), c.end(), i) - c.begin();
    }
}

/*ll solve() {
    ll swapSum = 0;

    vector<int> vi(n);
    for (int i = 0; i < n; i++) {
        if (vi[i]) continue;
        if (a[i] != i && a[a[i]] == i) {
            swapSum += c[i] + c[a[i]];
            vi[i] = vi[a[i]] = 1;
        }
    }
    
    ll mn = INF;
    ll sum = 0, cnt = 0;

    for (int i = 0; i < n; i++) {
        if (vi[i]) continue;
        if (a[i] != i) {
            mn = min(mn, c[a[i]]);
            sum += c[a[i]];
            cnt++;
        }
    }

    return swapSum + (cnt ? (cnt - 1) * mn + (sum - mn) : 0);
}*/

ll mn2 = INF;

int vi[101010];
ll mn = INF, sum = 0, cnt = 0;
void dfs(int v) {
    if (vi[v]) return;
    vi[v] = 1;
    mn = min(mn, b[v]);
    sum += b[v];
    cnt++;
    dfs(a[v]);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    valueCompress();

    for (int i = 0; i < n; i++) {
        mn2 = min(mn2, b[i]);
    }

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        if (!vi[i] && a[i] != i) {
            mn = INF, sum = 0, cnt = 0;
            dfs(i);
            ll res = (cnt - 1) * mn + (sum - mn);
            res = min(res, (cnt + 1) * mn2 + (sum + mn));
            ans += res;
        }
    }

    cout << ans;

    /*ll ans = solve();

    ll mn1 = INF, mn2 = INF;
    int idx1 = -1, idx2 = -1;

    for (int i = 0; i < n; i++) {
        if (a[i] == i && c[a[i]] < mn1) {
            mn1 = c[a[i]];
            idx1 = i;
        }
        if (a[i] != i && c[a[i]] < mn2) {
            mn2 = c[a[i]];
            idx2 = i;
        }
    }

    if (idx1 != -1 && idx2 != -1) {
        ll res = c[a[idx1]] + c[a[idx2]];
        swap(a[idx1], a[idx2]);
        res += solve();
        ans = min(ans, res);
    }

    cout << ans;*/
}