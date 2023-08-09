// 가설 1 : N이 짝수인 경우
// mid := N / 2에 대해서,
// A에서 [1, mid]에 속하는 값들을 모두 B에서 [mid + 1, N]에 속하는 값들과 매칭시키면 maximum difference sum을 구할 수 있다.

// 가설 2 : N이 홀수인 경우
// mid := (n + 1) / 2에 대해서, 
// 1. A에서 [1, mid]에 속하는 값들을 모두 B에서 [mid, N]에 매칭시키는 경우.
// 2. A에서 [1, mid - 1]에 속하는 값들을 모두 B에서 [mid + 1, N]에 매칭시키는 경우.
// 1 또는 2를 만족시키도록 원소들을 이동시키면 답을 구할 수 있다.

// n = 3인 경우를 관찰하자
// 3
// 1 2 3
// 1 2 3 (sum = 0)
// 3
// 1 2 3
// 1 3 2 (sum = 2)
// 3
// 1 2 3
// 2 1 3 (sum = 2)
// 3
// 1 2 3
// 2 3 1 (sum = 4)
// 3
// 1 2 3
// 3 1 2 (sum = 4)
// 3
// 1 2 3
// 3 2 1 (sum = 4)

#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n;
vector<int> a, b;

void input() {
    cin >> n;
    a.resize(n);
    b.resize(n);
    for (auto& i : a) cin >> i;
    for (auto& i : b) cin >> i;
}

// ll getMaxDiffSum(int n) {
//     ll ret = 0;
//     int x = 1, y = n;
//     while (x <= n) {
//         ret += abs(x - y);
//         x++, y--;
//     }
//     return ret;
// }

ll solve(int al, int ar, int bl, int br) {
    queue<int> qa, qb;
    for (int i = 0; i < n; i++) {
        if (al <= a[i] && a[i] <= ar) qa.push(i);
        if (bl <= b[i] && b[i] <= br) qb.push(i);
    }

    ll ret = 0;
    while (!qa.empty()) {
        ret += abs(qa.front() - qb.front());
        qa.pop();
        qb.pop();
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    if (n & 1) {
        int mid = (n + 1) / 2;
        cout << min(solve(1, mid - 1, mid + 1, n), solve(1, mid, mid, n));
    }
    else cout << solve(1, n / 2, n / 2 + 1, n);
}