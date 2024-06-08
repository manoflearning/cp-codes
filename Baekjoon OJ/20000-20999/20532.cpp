#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fr first
#define sc second
#define sz(x) (int)(x).size()

const int N = 101010;

int n, a[N], p[N];
vector<int> t[N];
vector<int> divs[N];
ll ans = 0;

void init() {
    for (int i = 1; i < N; i++) {
        for (int j = 1; j * j <= i; j++) {
            if (i % j) continue;
            divs[i].push_back(j);
            if (j != i / j) divs[i].push_back(i / j);
        }
    }
}

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 2; i <= n; i++) {
        cin >> p[i];
        t[p[i]].push_back(i);
    }
}

int cnt1[N], cnt2[N];
void dfs(int v) { // O(N^{3/2})
    for (auto& i : divs[a[v]]) ans += cnt1[i];
    ans += cnt2[a[v]];

    cnt1[a[v]]++;
    for (auto& i : divs[a[v]])
        if (i != a[v]) cnt2[i]++;
    for (auto& i : t[v]) dfs(i);
    cnt1[a[v]]--;
    for (auto& i : divs[a[v]])
        if (i != a[v]) cnt2[i]--;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    init();

    input();

    dfs(1);

    cout << ans;
}