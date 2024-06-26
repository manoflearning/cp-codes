#include <bits/stdc++.h>
using namespace std;

int sq;
// Zigzag Mo's (faster than basic Mo's Algorithm)
struct se {
    int s, e, idx;
    bool operator<(const se &rhs) const {
        if(s / sq != rhs.s / sq) return s / sq < rhs.s / sq;
        else return (s / sq) & 1 ? e < rhs.e : e > rhs.e;
    }
};

int n, m, a[505050];
vector<se> q;
vector<int> ans;

int cnt[505050];
int res = 0;

void input() {
    // TODO: 1. receive input 2. resize q, ans 3. calculate sq 
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    q.resize(m);
    ans.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> q[i].s >> q[i].e;
        q[i].idx = i;
    }
    sq = sqrt(500'000);
}

void valueCompress() {
    vector<int> c(1, -1);
    for (int i = 1; i <= n; i++) c.push_back(a[i]);
    sort(c.begin(), c.end());
    c.erase(unique(c.begin(), c.end()), c.end());
    for (int i = 1; i <= n; i++) {
        a[i] = lower_bound(c.begin(), c.end(), a[i]) - c.begin();
    }
}

void add(int idx) {
    // TODO: add value at idx from data structure
    int x = a[idx];
    cnt[x]++;
    if (cnt[x] == 2) res++;
    if (cnt[x] == 3) res--;
}
void del(int idx) {
    // TODO: remove value at idx from data structure
    int x = a[idx];
    cnt[x]--;
    if (cnt[x] == 2) res++;
    if (cnt[x] == 1) res--;
}
int query() {
    // TODO: extract the current answer of the data structure
    return res;
}

void f() {
    int s = q[0].s, e = q[0].e;
    for (int i = s; i <= e; i++) add(i);
    ans[q[0].idx] = query();
    for (int i = 1; i < q.size(); i++) {
        while (q[i].s < s) add(--s);
        while (e < q[i].e) add(++e);
        while (s < q[i].s) del(s++);
        while (q[i].e < e) del(e--);
        ans[q[i].idx] = query();
    }
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
    sort(q.begin(), q.end());
    f();
    for (auto& i : ans) 
        cout << i << '\n';
}