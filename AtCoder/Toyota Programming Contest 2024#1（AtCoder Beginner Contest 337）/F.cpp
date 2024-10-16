// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

const int MAXN = 202020;

int N, M, K;
int C[MAXN << 1], cnt[MAXN];

queue<int> q[MAXN];
int ans = 0;

void input() {
    cin >> N >> M >> K;
    for (int i = 1; i <= N; i++) {
        cin >> C[i];
        cnt[C[i]]++;
        C[i + N] = C[i];
    }
}

void solve() {
    for (int i = 1; i <= 2 * N; i++) {
        q[C[i]].push(i);
    }

    priority_queue<int, vector<int>, greater<int>> pq;
    for (int x = 1; x <= N; x++) {
        if (q[x].empty()) continue;
        pq.push(q[x].front());
        q[x].pop();
    }

    set<int> s;

    // base case
    int leftCnt = 0;
    while (sz(s) < M && !pq.empty()) {
        s.insert(C[pq.top()]);
        ans += min(K, cnt[C[pq.top()]]);
        leftCnt += max(0, cnt[C[pq.top()]] - K);
        pq.pop();
    }
    // for (auto& i : s) cout << i << ' ';
    // cout << '\n';
    cout << ans << '\n';

    for (int i = 2; i <= N; i++) {
        s.erase(C[i - 1]);
        ans -= min(K, cnt[C[i - 1]]);
        leftCnt -= max(0, cnt[C[i - 1]] - K);

        if (!q[C[i - 1]].empty()) {
            pq.push(q[C[i - 1]].front());
            q[C[i - 1]].pop();
        }

        while (!pq.empty() && pq.top() < i) pq.pop();

        if (!pq.empty()) {
            s.insert(C[pq.top()]);
            ans += min(K, cnt[C[pq.top()]]);
            leftCnt += max(0, cnt[C[pq.top()]] - K);
            pq.pop();
        }

        // for (auto& i : s) cout << i << ' ';
        // cout << '\n';
        cout << ans << '\n';
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    solve();    
}