#include <bits/stdc++.h>
using namespace std;

const int sq = 318;
struct Query {
    int l, r, idx;
    bool operator<(const Query& rhs) const {
        if (l / sq != rhs.l / sq) return l / sq < rhs.l / sq;
        return (l / sq) & 1 ? r < rhs.r : r > rhs.r;
    }
};

int N, M, K;
int A[101010], psum[101010];

vector<Query> qu;
vector<int> ans;

void input() {
    cin >> N >> K;
    for (int i = 1; i <= N; i++) cin >> A[i];
    cin >> M;
    qu.resize(M);
    ans.resize(M);
    for (int i = 0; i < M; i++) {
        cin >> qu[i].l >> qu[i].r;
        qu[i].l--;
        qu[i].idx = i;
    }
}

void buildPsum() {
    for (int i = 1; i <= N; i++) {
        psum[i] = (A[i] + psum[i - 1]) % K;
    }
}

deque<int> dq[1010101];
int cnt[101010], res[101010 / sq];

void add(int v, int isLeft) {
    int x = psum[v];
    
    if (!dq[x].empty()) {
        cnt[dq[x].back() - dq[x].front()]--;
    }
    
    if (isLeft) dq[x].push_front(v);
    else dq[x].push_back(v);
    
    cnt[dq[x].back() - dq[x].front()]++;
}
void del(int v, int isLeft) {
    int x = psum[v];
    
    int len = dq[x].back() - dq[x].front();
    cnt[len]--;
    if (len == res[len / sq]) {
        for (int i = len / sq * sq + len - 1; i >= len / sq * sq; i--) {
            
        }
    }
    
    if (isLeft) dq[x].pop_front();
    else dq[x].pop_back();

    if (!dq[x].empty()) {
        cnt[dq[x].back() - dq[x].front()]++;
        res[]
    }
}
int query() { return seg.t[1]; }

void f() {
    int l = qu[0].l, r = qu[0].r;
    for (int i = l; i <= r; i++) add(i, 0);
    ans[qu[0].idx] = query();

    for (int i = 1; i < M; i++) {
        while (l < qu[i].l) del(l++, 1);
        while (qu[i].r < r) del(r--, 0);
        while (qu[i].l < l) add(--l, 1);
        while (r < qu[i].r) add(++r, 0);
        ans[qu[i].idx] = query();
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

    sort(qu.begin(), qu.end());

    buildPsum();

    f();

    for (auto& i : ans)
        cout << i << '\n';
}