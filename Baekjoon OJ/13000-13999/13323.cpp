#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define sz(x) (int)(x).size()

// PROBLEM: You are given the array containing n integers.
// At one turn you can pick any element and increase or decrease it by 1. 
// The goal is the make the array strictly increasing by making the minimum possible number of operations.
// TIME COMPLEXITY: O(n log(n))
ll slope_trick(vector<ll> a) {
    ll ret = 0;
    priority_queue<ll> pq;
    for (int i = 0; i < sz(a); i++) {
        a[i] -= i; // Change strictly increasing condition to non-decreasing condition
        pq.push(a[i]);

        if (pq.top() > a[i]) {
            ret += pq.top() - a[i];
            pq.pop();
            pq.push(a[i]);
        }
    }
    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int n; cin >> n;
    vector<ll> a(n);
    for (auto &i : a) cin >> i;

    cout << slope_trick(a);
}