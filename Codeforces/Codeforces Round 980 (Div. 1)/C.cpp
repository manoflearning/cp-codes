#include <bits/stdc++.h>
using namespace std;
#define ll long long

void yes() { cout << "YES\n"; }
void no() { cout << "NO\n"; }

const int MAXN = 202020;

int n, k;
bool a[MAXN], b[MAXN];
int m1, m2;
vector<int> adj1[MAXN], adj2[MAXN];

int in_a = 0, in_b = 0;
int out_a = 0, out_b = 0;

void init() {
    for (int i = 1; i <= n; i++) {
        a[i] = b[i] = 0;
        adj1[i].clear();
        adj2[i].clear();
    }
    in_a = in_b = 0;
    out_a = out_b = 0;
}

void input() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        out_a += a[i], in_a += !a[i];
    }
    cin >> m1;
    for (int i = 0; i < m1; i++) {
        int u, v;
        cin >> u >> v;
        adj1[u].push_back(v);
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        out_b += b[i], in_b += !b[i];
    }
    cin >> m2;
    for (int i = 0; i < m2; i++) {
        int u, v;
        cin >> u >> v;
        adj2[u].push_back(v);
    }
}

bool solve() {
    {
        vector<int> dist1(n + 1, -1);
        vector<int> dist2(n + 1, -1);
        queue<int> qu1, qu2;
        for (int i = 1; i <= n; i++) {
            if (!a[i]) { qu1.push(i); dist1[i] = 0; }
            if (!b[i]) { qu2.push(i); dist2[i] = 0; }
        }
        while (!qu1.empty()) {
            int v = qu1.front(); qu1.pop();
            for (auto& i : adj1[v]) {
                if (dist1[i] == -1) {
                    dist1[i] = 1 + dist1[v];
                    qu1.push(i);
                }
            }
        }
        while (!qu2.empty()) {
            int v = qu2.front(); qu2.pop();
            for (auto& i : adj2[v]) {
                if (dist2[i] == -1) {
                    dist2[i] = 1 + dist2[v];
                    qu2.push(i);
                }
            }
        }

        vector<int> cnt1(k), cnt2(k);
        for (int i = 1; i <= n; i++) {
            if (a[i]) cnt1[dist1[i] % k]++;
            if (b[i]) cnt2[dist2[i] % k]++;
        }

        for (int i = 0; i < k; i++) {
            // cout << cnt1[i] << ' ' << cnt2[((-2 - i) % k + k) % k] << '\n';
            if (cnt1[i] != cnt2[((-2 - i) % k + k) % k]) return 0;
        }
    }

    return 1;
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

        if (in_a != out_b || in_b != out_a) {
            no();
            continue;
        }
        
        solve() ? yes() : no();
    }
}
