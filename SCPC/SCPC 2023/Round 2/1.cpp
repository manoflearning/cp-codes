#pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

int N, K;
vector<int> a;

// [0, 4] = [A, B)
// [5, 9] = [B, C)
// [10, 14] = [C, D)
// [15, 19] = [D, A)
// 0 = A, 5 = B, 10 = C, 15 = D, 20 = A'

int dest[44];
ll w[44];

void init() {
    for (int i = 0; i < 44; i++)
        dest[i] = w[i] = 0;
}

void input() {
    cin >> N >> K;
    a.resize(N);
    for (auto& i : a) cin >> i;
}

void f(int st) {
    int cnt = 0, now = st;
    for (auto& i : a) {
        int nxt = now, d = i;
        if (0 <= now && now <= 4) {
            nxt += d;
        }
        else if (5 <= now && now <= 9) {
            if (now == 5) {
                nxt += 15 + d;
                if (nxt == 23) nxt = 28;
            }
            else nxt += d;
        }
        else if (10 <= now && now <= 14) {
            if (now == 10) {
                nxt += 15 + d;
            }
            else nxt += d;
        }
        else if (15 <= now && now <= 19) {
            nxt += d;
            if (20 < nxt) w[st]++, nxt = 0;
        }
        else if (now == 20) {
            w[st]++, nxt = 0;
        }
        else if (21 <= now && now <= 25) {
            nxt += d;
            if (nxt >= 26) nxt -= 11;
            else if (nxt == 23) nxt = 28;
        }
        else if (26 <= now && now <= 30) {
            nxt += d;
            if (nxt == 31) nxt = 20;
            else if (nxt > 31) w[st]++, nxt = 0;
        }
        now = nxt;
    }
    dest[st] = now;
}

void getPath() { // O(30N)
    for (int st = 0; st <= 30; st++) f(st);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        cout << "Case #" << tt << '\n';

        init();

        input();

        getPath();

        ll ans = 0;
        int now = 0;
        for (int i = 0; i < K; i++) {
            ans += w[now];
            now = dest[now];
        }

        cout << ans << '\n';
        
        cout << flush;
    }
}