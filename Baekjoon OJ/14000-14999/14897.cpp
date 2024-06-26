#include <bits/stdc++.h>
using namespace std;

const int sq = 1218;
struct Query {
    int s, e, idx;
    bool operator<(const Query& rhs) const {
        if (s / sq != rhs.s / sq) return s / sq < rhs.s / sq;
        return e < rhs.e;
    }
};

int n, a[1010101], cnt[1010101], res;
vector<int> c;
int m;
vector<Query> q;
vector<int> ans;

void add(int idx) {
    int x = a[idx];
    if (!cnt[x]) res++;
    cnt[x]++;
}
void del(int idx) {
    int x = a[idx];
    cnt[x]--;
    if (!cnt[x]) res--;
}

void mo() {
    int s = q[0].s, e = q[0].e;
    for (int i = s; i <= e; i++) add(i);
    ans[q[0].idx] = res;

    for (int i = 1; i < m; i++) {
        auto it = q[i];
        while (s < it.s) del(s++);
        while (it.e < e) del(e--);
        while (it.s < s) add(--s);
        while (e < it.e) add(++e);
        ans[it.idx] = res;
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    for (int i = 1; i <= n; i++)
        c.push_back(a[i]);
    sort(c.begin(), c.end());
    c.erase(unique(c.begin(), c.end()), c.end());
    for (int i = 1; i <= n; i++)
        a[i] = lower_bound(c.begin(), c.end(), a[i]) - c.begin();

    cin >> m;
    q.resize(m);
    ans.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> q[i].s >> q[i].e;
        q[i].idx = i;
    }

    sort(q.begin(), q.end());

    mo();

    for (int i = 0; i < m; i++)
        cout << ans[i] << '\n';
}