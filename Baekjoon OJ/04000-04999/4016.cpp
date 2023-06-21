// 먼저 임의의 두 장난감의 레벨 차의 최댓값이 1인지 확인한다. 그렇지 않다면 답은 -1.
// 임의의 두 장난감의 레벨 차의 최댓값이 0이라면 답은 0.
// 임의의 두 장난감의 레벨 차의 최댓값이 1이라면, 재귀적으로 문제를 풀 수 있다.

#include <bits/stdc++.h>
using namespace std;

int n, dep[101010];
int L[101010], R[101010];
int mnDep = 1e9 + 7, mxDep = -1;

int lvi0[101010], rvi0[101010];
int lvi1[101010], rvi1[101010];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    // input
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> L[i] >> R[i];

    // solve
    for (int i = 1; i <= n; i++) {
        if (L[i] != -1) dep[L[i]] = dep[i] + 1;
        if (R[i] != -1) dep[R[i]] = dep[i] + 1;
        if (L[i] == -1 || R[i] == -1) {
            mnDep = min(mnDep, dep[i] + 1);
            mxDep = max(mxDep, dep[i] + 1);
        }
    }

    if (mxDep - mnDep >= 2) {
        cout << -1; return 0;
    }

    if (mxDep - mnDep == 0) {
        cout << 0; return 0;
    }

    for (int i = n; i >= 1; i--) {
        if (L[i] == -1) {
            if (dep[i] + 1 == mnDep) lvi0[i] = 1;
            if (dep[i] + 1 == mxDep) lvi1[i] = 1;
        }
        else {
            lvi0[i] = lvi0[L[i]] || rvi0[L[i]];
            lvi1[i] = lvi1[L[i]] || rvi1[L[i]];
        }

        if (R[i] == -1) {
            if (dep[i] + 1 == mnDep) rvi0[i] = 1;
            if (dep[i] + 1 == mxDep) rvi1[i] = 1;
        }
        else {
            rvi0[i] = lvi0[R[i]] || rvi0[R[i]];
            rvi1[i] = lvi1[R[i]] || rvi1[R[i]];
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (lvi0[i] && lvi1[i] && rvi0[i] && rvi1[i]) {
            cout << -1; return 0;
        }

        if (lvi0[i] && rvi1[i]) ans++;
    }

    cout << ans;
}