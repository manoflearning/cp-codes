#include "gap.h"
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const ll MX = 1e18;

ll T1(int N) {
    ll lb = 0, ub = MX;

    vector<ll> arr;
    stack<ll> stk;
    while (lb <= ub && sz(arr) + sz(stk) < N) {
        ll mn = -1, mx = -1;
        MinMax(lb, ub, &mn, &mx);
        if (mn == -1 && mx == -1) break;
        arr.push_back(mn);
        if (mn < mx) stk.push(mx);
        lb = mn + 1, ub = mx - 1;
    }
    
    while (!stk.empty()) {
        arr.push_back(stk.top());
        stk.pop();
    }

    ll ret = 0;
    for (int i = 0; i + 1 < sz(arr); i++) {
        ret = max(ret, arr[i + 1] - arr[i]);
    }
    return ret;
}

ll findGap(int T, int N) {
    if (T == 1) return T1(N);
    if (T == 2) return 0;
}
