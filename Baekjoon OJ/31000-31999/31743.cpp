#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

struct Line { int x1, x2, y; };
struct Person { int x, y, idx; };

int n, m;
vector<Line> li;
vector<Person> pe;

int mxy;
vector<ll> w, pw, ans;

struct Fenwick { // 1-indexed
    int flag;
    vector<__int128_t> t;
    void build(int N) {
        flag = N;
        t.resize(flag + 1);
    }
    void modify(int l, int r, __int128_t val) { // add a val to all elements in interval [l, r]
        for (; l <= flag; l += l & -l) t[l] += val;
        for (r++; r<= flag; r += r & -r) t[r] -= val;
    }
    __int128_t query(int x) {
        __int128_t ret = 0;
        for (; x; x ^= x & -x) ret += t[x];
        return ret;
    }
}fw;

void input() {
    cin >> n;
    li.resize(n);
    for (auto& i : li) cin >> i.x1 >> i.x2 >> i.y;
    cin >> m;
    pe.resize(m);
    ans.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> pe[i].x >> pe[i].y;
        pe[i].idx = i;
    }
}

void coor_comp() {
    vector<int> yy;
    yy.push_back(0);
    for (auto& i : li) {
        yy.push_back(i.y);
    }
    for (auto& i : pe) {
        yy.push_back(i.y);
    }

    sort(all(yy));
    yy.erase(unique(all(yy)), yy.end());

    mxy = sz(yy);

    for (auto& i : li) {
        i.y = lower_bound(all(yy), i.y) - yy.begin();
    }
    for (auto& i : pe) {
        i.y = lower_bound(all(yy), i.y) - yy.begin();
    }

    w.resize(mxy);
    pw.resize(mxy);
    for (int i = 1; i < sz(yy); i++) {
        w[i] = yy[i] - yy[i - 1];
        pw[i] = w[i] + pw[i - 1];
    }
}

void solve() {
    struct PartialLine {
        int x, y, w;
        bool operator<(const PartialLine& rhs) const {
            return x > rhs.x;
        }
    };
    priority_queue<PartialLine> pq;
    for (auto& i : li) {
        pq.push({ i.x1, i.y, 1 });
        pq.push({ i.x2 + 1, i.y, -1 });
    }

    sort(all(pe), [&](const Person& p1, const Person& p2) {
        return p1.x < p2.x;
    });

    fw.build(mxy);
    for (auto& i : pe) {
        while (!pq.empty() && pq.top().x <= i.x) {
            auto it = pq.top();
            pq.pop();
            fw.modify(it.y, mxy - 1, it.w * pw[it.y]);
        }
        ans[i.idx] = fw.query(i.y) + pw[i.y];
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

    coor_comp();

    solve();

    for (int i = 0; i < m; i++)
        cout << ans[i] << '\n';
}
