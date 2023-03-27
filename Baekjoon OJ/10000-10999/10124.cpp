// solution 1 : persistent segment tree
#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

struct PST { // 1-indexed
    int flag; // array size
    struct Node { int l, r, val; };
    vector<Node> t;
    vector<int> root;

    void addNode() { t.push_back({ -1, -1, 0 }); };
    void build(int l, int r, int n) {
        if (l == r) return;
        addNode();
        t[n].l = sz(t) - 1;
        addNode();
        t[n].r = sz(t) - 1;

        int mid = (l + r) >> 1;
        build(l, mid, t[n].l);
        build(mid + 1, r, t[n].r);
    }
    void build(int Flag) {
        addNode();
        root.push_back(sz(t) - 1);
        flag = Flag;
        build(1, flag, root[0]);
    }
    void modify(int p, int l, int r, int n1, int n2) {
        if (p < l || r < p) { t[n2] = t[n1]; return; }
        if (l == r) { t[n2].val = t[n1].val + 1; return; }

        int mid = (l + r) >> 1;
        if (p <= mid) {
            t[n2].r = t[n1].r;
            addNode();
        }
    }
    void modify(int p) {
        addNode();
        root.push_back(sz(t) - 1);
        modify(p, 1, flag, root[sz(root) - 2], root[sz(root) - 1]);
    }
}pst;

int n, m;
int a[505050];

void input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();


}

// solution 2 : random
/*#include <bits/stdc++.h>
#include <random>
using namespace std;
#define all(x) (x).begin(), (x).end()

int n, m;
int a[505050];
vector<int> arr[505050];

int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    srand(time(NULL));

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        arr[a[i]].push_back(i);
    }

    while (m--) {
        int l, r;
        cin >> l >> r;

        int len = (r - l + 1);
        int ans = 0;
        for (int i = 0; i < 24; i++) {
            int idx = rand() % len + l;
            int v = a[idx];
            int cnt = lower_bound(all(arr[v]), r + 1) - lower_bound(all(arr[v]), l);
            if (cnt >= len / 2 + 1) ans = v;
        }
        cout << ans << '\n';
    }
}*/