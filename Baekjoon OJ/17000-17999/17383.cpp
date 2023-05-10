// 언제나 한 개 이상의 문제를 풀고 있는 최적해가 존재한다.
// 다시 말해 언제나 한 개 이상의 문제를 풀고 있어야 한다고 가정할 수 있다.
// 언제나 두 개의 문제를 풀고 있어야 하지는 않는다.

// 파라메트릭 서치
// f(x) = 최대 시간이 x 이하인 것이 가능한가?
// f(x)를 O(n)에 구할 수 있다.

#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n;
vector<ll> a;

int f(ll x) {
    int cnt1 = 0, cnt2 = 0;
    vector<ll> arr3;

    for (auto& i : a) {
        if (i <= x) cnt1++;
        else if (i <= 2 * x) cnt2++;
        else arr3.push_back(i);
    }

    if (cnt1 == 0) return 0;
    
    for (int i = 0; i < arr3.size(); i++) {
        ll y = arr3[i];
        int res = (y - 1) / x;
        if (cnt1 < res) return 0;
        cnt1 -= res;
        if (i + 1 < arr3.size()) arr3[i + 1] -= x;
    }

    return 1;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    a.resize(n);
    for (auto& i : a) cin >> i;

    ll l = 1, r = 1e9;
    while (l < r) {
        ll mid = (l + r) >> 1;
        
        if (f(mid)) r = mid;
        else l = mid + 1;
    }

    cout << l;
}