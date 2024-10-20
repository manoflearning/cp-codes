#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()

const int INF = 1e9 + 7;

int n;
vector<int> a;
vector<int> ans;
int ansDiff = -1;

void input() {
    cin >> n;
    a.resize(n);
    for (auto& i : a) cin >> i;
}

vector<int> f(int ub, int en) {
    vector<int> vi(n);

    stack<int> stk;
    int v = a[en];
    vi[en] = 1;
    stk.push(v);
    while (1) {
        int idx = upper_bound(all(a), v + ub) - a.begin();
        if (idx == sz(a)) break;
        idx--;
        if (vi[idx]) return { };
        vi[idx] = 1;
        v = a[idx];
        stk.push(v);
    }

    vector<int> ret;
    ret.push_back(a[0]);
    for (int i = 1; i < sz(a); i++) {
        if (!vi[i]) ret.push_back(a[i]);
    }
    while (!stk.empty()) {
        ret.push_back(stk.top());
        stk.pop();
    }
    return ret;
}

int getDiff(const vector<int>& res) {
    if (res.empty()) return INF;
    int ret = 0;
    ret = max(ret, abs(res[0] - res[n - 1]));
    for (int i = 1; i < n; i++) {
        ret = max(ret, abs(res[i] - res[i - 1]));
    }
    return ret;
}

vector<int> minDiff(int en) {
    int l = 0, r = 1000;
    while (l < r) {
        int mid = (l + r) >> 1;
        vector<int> res = f(mid, en);
        if (getDiff(res) <= mid) r = mid;
        else l = mid + 1;
    }
    return f(l, en);
}

void simul() {
    int st = a[0];
    for (int i = 1; i < n; i++) {
        vector<int> res = minDiff(i);
        int resDiff = getDiff(res);

        if (ans.empty()) {
            ans = res;
            ansDiff = resDiff;
        }
        else if (resDiff < ansDiff || (resDiff == ansDiff && res < ans)) {
            ans = res;
            ansDiff = resDiff;
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    sort(all(a));

    simul();

    for (auto& i : ans) cout << i << ' ';
}