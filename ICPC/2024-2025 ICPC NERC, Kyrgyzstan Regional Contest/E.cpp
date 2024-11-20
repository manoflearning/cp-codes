#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 202020;

int n, m, st1, st2;
set<int> adj[MAXN];
bool vis[MAXN];
int rem;
vector<int> ans1, ans2;

void add_ans(int v, vector<int> &ans) {
    ans.push_back(v);
    if (!vis[v]) rem--;
    vis[v] = 1;
}

void no() { cout << "NO"; exit(0); }
void yes() {
    cout << "YES\n";
    cout << sz(ans1) << '\n';
    for (auto &i : ans1) cout << i << ' ';
    cout << '\n';
    cout << sz(ans2) << '\n';
    for (auto &i : ans2) cout << i << ' ';
    cout << '\n';
    exit(0);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m >> st1 >> st2;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].insert(v);
    }

    rem = n;
    add_ans(st1, ans1);
    add_ans(st2, ans2);

    while (rem > 0) {
        int v1 = ans1.back(), v2 = ans2.back();

        vector<int> lzd1, lzd2;
        bool v1tov2 = 0, v2tov1 = 0;
        for (auto i : adj[v1])
            if (vis[i]) lzd1.push_back(i);
        for (auto i : adj[v2])
            if (vis[i]) lzd2.push_back(i);

        set<int> s1 = adj[v1], s2 = adj[v2];
        for (auto i : lzd1) s1.erase(i);
        for (auto i : lzd2) s2.erase(i);

        if (sz(s1) == 0 || sz(s2) == 0) {
            if (sz(s1) == 0 && sz(lzd1) == 1) add_ans(lzd1[0], ans1);
            else if (sz(s2) == 0 && sz(lzd2) == 1) add_ans(lzd2[0], ans2);
            else if (sz(s1) > 1 || sz(s2) > 1) no();
            else if (sz(s1) == 0 && sz(s2) == 0) no();
            else if (sz(s1) == 1) add_ans(*s1.begin(), ans1);
            else if (sz(s2) == 1) add_ans(*s2.begin(), ans2);
            else assert(0);
        } else if (sz(s1) == 1) {
            add_ans(*s1.begin(), ans1);
        } else if (sz(s2) == 1) {
            add_ans(*s2.begin(), ans2);
        } else if (sz(s1) == 2 && s1 == s2) {
            auto it = s1.begin();
            add_ans(*it, ans1);
            it++;
            add_ans(*it, ans2);
        } else no();
    }

    yes();
}
