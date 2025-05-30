#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

int m, n, k;
vector<int> a;
int rem[10101];

int totalSize = 0;
queue<int> q[10101];
queue<int> notRemoved;

int fl, fr;
stack<int> stk;

void init() {
    a.clear();
    memset(rem, 0, sizeof(rem));
    totalSize = 0;
    for (int i = 0; i < 10101; i++) {
        while (sz(q[i])) q[i].pop();
    }
    while (sz(notRemoved)) notRemoved.pop();

    fl = 0, fr = 0;
    while (sz(stk)) stk.pop();
}

void input() {
    cin >> m >> n >> k;
    a.resize(n);
    for (auto& i : a) { cin >> i; rem[i]++; }
}

void add(int p) {
    totalSize++;
    q[a[p]].push(p);
    notRemoved.push(p);
}

void keep() {
    int v = notRemoved.front();
    notRemoved.pop();
    
    if (a[v] <= fr) return;
    
    q[a[v]].pop();
    stk.push(a[v]);
    totalSize--;
}

void del(int x) { rem[x]--; }

void delAll(int x) {
    totalSize -= sz(q[x]);
    rem[x] -= sz(q[x]);
    while (sz(q[x])) q[x].pop();
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        fl = 1, fr = k;

        int p = 0;
        while (p < n) {
            while (p < n && totalSize < k) {
                if (fl <= a[p] && a[p] <= fr) {
                    del(a[p++]);
                }
                else if (fr < a[p]) add(p++);
            }

            while (totalSize == k && rem[fl] > 0) keep();
            
            while (fr < m && rem[fl] == 0) {
                fl++, fr++;
                delAll(fr);
            }
        }

        int ans = 1;
        while (sz(stk)) {
            int x = stk.top();
            stk.pop();
            if (x <= fr) del(x);
            else { ans = 0; break; }
            while (fr < m && rem[fl] == 0) {
                fl++, fr++;
            }
        }

        cout << (ans ? "YES" : "NO") << '\n';
    }
}