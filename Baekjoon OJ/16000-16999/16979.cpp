#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Fenwick {
    int flag;
    vector<ll> arr, t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        arr.resize(flag);
        t.resize(flag);
    }
    void add(int x, int value) {
        arr[x] += value;
        for (int i = x; i < flag; i = i | (i + 1)) t[i] += value;
    }
    ll query(int x) {
        ll ret = 0;
        for (int i = x; i >= 0; i = (i & (i + 1)) - 1) {
            ret += t[i];
        }
        return ret;
    }
    ll query(int l, int r) {
        if (l > r) return 0;
        return query(r) - (l ? query(l - 1) : 0);
    }
}fw;

int sq = 434;
struct Query { 
    int idx; int s, e;
    bool operator<(const Query& rhs) const {
        if (s / sq != rhs.s / sq) return s / sq < rhs.s / sq;
        return e < rhs.e;
    }
};
vector<Query> query;
vector<ll> ans;

int n, q;
vector<int> a, c;
ll res = 0;

void add(int x) {
    res += fw.query(x + 1, c.size() - 1);
    fw.add(x, 1);
}
void add2(int x) {
    res += fw.query(0, x - 1);
    fw.add(x, 1);
}
void del2(int x) {
    res -= fw.query(0, x - 1);
    fw.add(x, -1);
}
void del(int x) {
    res -= fw.query(x + 1, c.size() - 1);
    fw.add(x, -1);
}

void mo() {
    int s = query[0].s, e = query[0].e;
    for (int i = s; i <= e; i++) add(a[i]);
    ans[query[0].idx] = res;

    for (int i = 1; i < q; i++) {
        auto it = query[i];
        while (it.s < s) add2(a[--s]);
        while (e < it.e) add(a[++e]);
        while (s < it.s) del2(a[s++]);
        while (it.e < e) del(a[e--]);
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

    cin >> n >> q;
    a.resize(n);
    for (auto& i : a) cin >> i;

    for (auto& i : a) c.push_back(i);
    sort(c.begin(), c.end());
    c.erase(unique(c.begin(), c.end()), c.end());
    for (auto& i : a)
        i = lower_bound(c.begin(), c.end(), i) - c.begin();

    fw.build(c.size());
    
    query.resize(q);
    ans.resize(q);
    for (int i = 0; i < q; i++) {
        query[i].idx = i;
        cin >> query[i].s >> query[i].e;
        query[i].s--, query[i].e--;
    }

    sort(query.begin(), query.end());

    mo();
    
    for (auto& i : ans) 
        cout << i << '\n';
}