#include <bits/stdc++.h>
#include "art.h"
using namespace std;

int a[4040];

void solve(int N) {
    vector<int> order;
    for (int i = 1; i <= N; i++)
        order.push_back(i);
    
    for (int i = 1; i <= N; i++) {
        a[i] = publish(order);
        order.push_back(i);
        order.erase(order.begin());
    }
    
    vector<int> ans(N);
    for (int i = 1; i <= N; i++) {
        int x = a[i], y = (i == N ? a[1] : a[i + 1]);
        // x = z + c, y = (N - 1 - z) + c
        // x - y = 2 * z - N + 1
        assert((x - y + N - 1) % 2 == 0);
        int diff = (x - y + N - 1) / 2;
        assert(0 <= diff && diff < N);
        assert(ans[diff] == 0);
        ans[diff] = i;
    }

    answer(ans);
}