#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int N = 202020;

int n;
vector<int> a, psum, ssum;

void init() {
    a.clear();
    psum.clear();
    ssum.clear();
}

void input() {
    cin >> n;
    a.resize(n + 1);
    psum.resize(n + 1);
    ssum.resize(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
}

void build_psum(int st, int en, vector<int>& sum) {
    priority_queue<int> pq;

    set<int> vis;
    for (int i = st; 1 <= i && i <= n; i += (st < en ? 1 : -1)) vis.insert(i);

    for (int i = st; 1 <= i && i <= n; i += (st < en ? 1 : -1)) {
        pq.push(a[i]);

        int x = pq.top(); pq.pop();
        auto it = vis.upper_bound(x);
        if (it != vis.begin()) {
            it--;
            vis.erase(it);
        }

        sum[i] = n - sz(vis);
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        build_psum(1, n, psum);
        build_psum(n, 1, ssum);

        ll ans = 0;
        for (int i = 1; i + 1 <= n; i++) {
            ans += min(psum[i], ssum[i + 1]);
        }

        cout << ans << '\n';
    }
}
