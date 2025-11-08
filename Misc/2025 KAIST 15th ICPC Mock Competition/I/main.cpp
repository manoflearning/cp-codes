#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int QUE_CAP = 200;
struct fuck_queue {
    int st{}, en{}, siz{};
    vector<int> arr;
    void build() {
        arr.resize(QUE_CAP);
    }
    void push(int x) {
        arr[en] = x;
        en = (en + 1) % QUE_CAP;
        siz++;
    }
    int front() {
        return arr[st];
    }
    int at(int i) {
        return arr[(st + i) % QUE_CAP];
    }
    void pop() {
        st = (st + 1) % QUE_CAP;
        siz--;
    }
};

vector<pii> ans;

void print_op(int a_idx, int b_idx) {
    ans.push_back({a_idx, b_idx});
    // cout << a_idx << ' ' << b_idx << '\n';
}

void distr(int n, fuck_queue &a, fuck_queue &b) {
    vector<int> cnta(n + 1), cntb(n + 1);
    int cnta2 = 0, cntb2 = 0;
    for (int i = 0; i < a.siz; i++) {
        cnta[a.arr[i]]++;
        if (cnta[a.arr[i]] == 2) cnta2++;
    }
    for (int i = 0; i < b.siz; i++) {
        cntb[b.arr[i]]++;
        if (cntb[b.arr[i]] == 2) cntb2++;
    }

    while (cnta2 > 0 || cntb2 > 0) {
        if (a.siz >= n) {
            while (1) {
                int x = a.front();
                if (cnta[x] == 2) {
                    a.pop();
                    b.push(x);
                    cnta[x]--, cntb[x]++;
                    cnta2--;
                    print_op(1, 2);
                    break;
                } else {
                    a.pop();
                    a.push(x);
                    print_op(1, 1);
                }
            }
        } else {
            while (1) {
                int x = b.front();
                if (cntb[x] == 2) {
                    b.pop();
                    a.push(x);
                    cntb[x]--, cnta[x]++;
                    cntb2--;
                    print_op(2, 1);
                    break;
                } else {
                    b.pop();
                    b.push(x);
                    print_op(2, 2);
                }
            }
        }
    }
}

void op1(int i, fuck_queue &a, fuck_queue &b, int a_idx, int b_idx) {
    int cnt1 = i, cnt2 = a.siz - i - 1;
    while (cnt1--) {
        int x = a.front();
        a.pop(); a.push(x);
        print_op(a_idx, a_idx);
    }
    {
        int x = a.front();
        a.pop();
        b.push(x);
        print_op(a_idx, b_idx);
    }
    while (cnt2--) {
        int x = a.front();
        a.pop(); a.push(x);
        print_op(a_idx, a_idx);
    }
}

void op2(int i, fuck_queue &a, fuck_queue &b, int a_idx, int b_idx) {
    int cnt = b.siz - 1;
    while (cnt--) {
        int x = b.front();
        b.pop(); b.push(x);
        print_op(b_idx, b_idx);
    }

    int cnt1 = i, cnt2 = a.siz - i;
    while (cnt1--) {
        int x = a.front();
        a.pop(); a.push(x);
        print_op(a_idx, a_idx);
    }
    {
        int x = b.front();
        b.pop();
        a.push(x);
        print_op(b_idx, a_idx);
    }
    while (cnt2--) {
        int x = a.front();
        a.pop(); a.push(x);
        print_op(a_idx, a_idx);
    }
}

void solve(int n, fuck_queue &a, fuck_queue &b, int a_idx, int b_idx) {
    for (int i = n; i >= 1; i--) {
        if (a.at(i - 1) == i) continue;

        for (int j = 0; j < i; j++) {
            if (a.at(j) == i) {
                op1(j, a, b, a_idx, b_idx);
                op2(i - 1, a, b, a_idx, b_idx);
                break;
            }
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    int n; cin >> n;

    fuck_queue a, b;
    a.build();
    b.build();

    {
        int na, nb;
        cin >> na;
        assert(na <= n + 1);
        while (na--) {
            int x; cin >> x;
            a.push(x);
        }
        cin >> nb;
        assert(nb <= n + 1);
        while (nb--) {
            int x; cin >> x;
            b.push(x);
        }
    }

    distr(n, a, b);
    // cout << "after distr\n";
    solve(n, a, b, 1, 2);
    solve(n, b, a, 2, 1);

    // for (int i = 0; i < n; i++) {
    //     cout << a.at(i) << ' ';
    // }
    // cout << '\n';
    // for (int i = 0; i < n; i++) {
    //     cout << b.at(i) << ' ';
    // }
    // cout << '\n';

    assert(sz(ans) <= 200'000);
    cout << sz(ans) << '\n';
    for (auto &[i, j] : ans) cout << i << ' ' << j << '\n';
}
