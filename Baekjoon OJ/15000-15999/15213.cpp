#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAX = 202020;

int n;
vector<int> p1(MAX), p2(MAX);
vector<vector<int>> t1(MAX), t2(MAX);

int cnt;
vector<int> in1(MAX), in2(MAX), out1(MAX), out2(MAX);

void input() {
    cin >> n;
    for (int v = 2; v <= n; v++) {
        cin >> p1[v];
        t1[p1[v]].push_back(v);
    }
    for (int v = 2; v <= n; v++) {
        cin >> p2[v];
        t2[p2[v]].push_back(v);
    }
}

void dfs(int v, const vector<vector<int>>& t, vector<int>& in, vector<int>& out) {
    in[v] = ++cnt;
    for (auto& i : t[v]) {
        dfs(i, t, in, out);
    }
    out[v] = cnt;
}

struct Query {
    ll mnx, mxx, mny, mxy;
    int idx;
};
vector<Query> q;
vector<int> ans(MAX);

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    dfs(1, t1, in1, out1);
    cnt = 0;
    dfs(1, t2, in2, out2);

    for (int v = 1; v <= n; v++) {
        q.push_back({ in1[v], out1[v], in2[v], out2[v], v });
    }

    sort(q.begin(), q.end(), [&](const Query& lhs, const Query& rhs) {
        return lhs.mnx ^ rhs.mnx ? lhs.mnx > rhs.mnx : lhs.mxx > rhs.mxx;
    });
}