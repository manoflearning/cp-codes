#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int INF = 1e9 + 7;

int n, k;
vector<int> adj[303030];
int dp[303030]; // dp[i]는 i를 루트로 하는 서브트리의 K-경로 분할의 경로 수
int dp2[303030]; 
// dp2[i]는 i를 루트로 하는 서브트리의 K-경로 분할에서 i를 포함하는 경로가 i를 끝점으로 가지고 있을 때,
// i를 포함하는 경로의 길이의 최솟값.

struct Node {
    int x1, x2;
    bool operator<(const Node& rhs) const {
        return x2 < rhs.x2;
    }
};

void init() {
    for (int i = 0; i < 303030; i++) dp2[i] = INF;
}

void dfs(int v, int prv) {
    if (prv != 0 && sz(adj[v]) == 1) {
        dp[v] = 1, dp2[v] = 0;
        return;
    }
    
    vector<Node> arr;

    for (auto& i : adj[v]) {
        if (i == prv) continue;
        dfs(i, v);

        arr.push_back({ dp[i], dp2[i] });
    }

    sort(arr.begin(), arr.end());

    int bit = 0;

    if (2 <= sz(arr) && arr[0].x2 + arr[1].x2 <= k - 2) {
        dp[v] += arr[0].x1 + arr[1].x1 - 1;
        arr.erase(arr.begin() + 1);
        arr.erase(arr.begin() + 0);
        bit = 1;
    }

    /*int mx = -INF, p = -1, q = -1;
    for (int i = 0; i < sz(arr); i++) {
        Node du = { 0, k - arr[i].x2 - 2 };
        int j = lower_bound(all(arr), du) - arr.begin();

        if (i != j && j < sz(arr) && arr[i].x2 + arr[j].x2 == k - 2) {
            if (mx < min(arr[i].x2, arr[j].x2)) {
                mx = min(arr[i].x2, arr[j].x2);
                p = i, q = j;
            }

            bit = 1;
        }
    }

    if (bit) {
        dp[v] += arr[p].x1 + arr[q].x1 - 1;
        if (p < q) swap(p, q);
        arr.erase(arr.begin() + p);
        arr.erase(arr.begin() + q);
    }*/
    
    for (auto& i : arr) {
        dp[v] += i.x1;
        if (!bit) {
            if (i.x2 < k) dp2[v] = min(dp2[v], i.x2 + 1);
        }
    }

    if (!bit && dp2[v] == INF) {
        dp[v]++, dp2[v] = 0;
    }

    //cout << v << ' ' << dp[v] << ' ' << dp2[v] << ' ' << bit<< '\n';
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    init();

    cin >> n >> k;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int r = -1;
    for (int i = 1; i <= n; i++) {
        if (sz(adj[i]) == 1) {
            r = i;
            dfs(r, 0);
            break;
        }
    }

    cout << dp[r];

    return 0;
}