// solution 1 : exchange argument + knapsack dp

// exchange argument
// 어떤 최적해에서 (k1, k2, ..., km)의 순서로 물을 먹는다고 하자.
// 이때 m은 청정수를 마실 수 있는 사람 수의 최댓값이다.
// 명제 : 모든 i에 대해서 p_ki + c_ki <= p_k{i+1} + c_k{i+1}인 최적해가 언제나 존재한다.

// 증명 : 어떤 i에 대해 p_ki + c_ki > p_k{i+1} + c_k{i+1}이라고 하자.
// i번째 사람이 물을 마시기 직전의 오염도를 si라고 하면
// si < c_ki이고, si + p_ki = s{i+1} < c_k{i+1}이다.

// 먼저 si < si + p_ki = s{i+1} < c_k{i+1}이므로, si < c_k{i+1}이다. (1)
// s{i+1} < c_k{i+1}이므로 양변에 p_k{i+1}를 더하면
// s{i+1} + p_k{i+1} < p_k{i+1} + c_k{i+1}이다.
// 가정에 의해 s{i+1} + p_k{i+1} < p_k{i+1} + c_k{i+1} < p_ki + c_ki이므로
// s{i+1} + p_k{i+1} < p_ki + c_ki이다.
// 양변에 p_ki를 빼면 si + p_k{i+1} < c_ki이다. (2)

// 따라서 ki와 k{i+1}을 교환할 수 있다.

#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second
#define all(x) (x).begin(), (x).end()

const int INF = 1e9 + 7;

int n;
vector<pii> a;
int dp[3131];

void input() {
    cin >> n;
    a.resize(n);
    for (auto& i : a) cin >> i.fr >> i.sc;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    sort(all(a), [&](const pii p1, const pii p2) {
        return p1.fr + p1.sc < p2.fr + p2.sc;
    });

    for (int i = 0; i <= 3100; i++) dp[i] = -INF;

    dp[0] = 0;
    for (auto& i : a) {
        for (int j = i.sc - 1; j >= 0; j--) {
            int k = j + i.fr;
            dp[k] = max(dp[k], 1 + dp[j]);
        }
    }

    int ans1 = 0, ans2 = 0;
    for (int i = 0; i <= 3100; i++) {
        if (ans1 < dp[i]) ans1 = dp[i], ans2 = i;
    }

    cout << ans1 << ' ' << ans2;
}

// solution 2 : priority queue
/*#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int n;
vector<pii> a;
int dp[3030];

void input() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int p, c;
        cin >> p >> c;
        a.push_back({ p, c });
    }
}

int f(int x) {
    int ret = 0;

    priority_queue<int, vector<int>, greater<int>> pq;
    int idx = sz(a) - 1;
    while (1) {
        while (0 <= idx && x < a[idx].fr + a[idx].sc) pq.push(a[idx--].fr);
        
        if (pq.empty() || (sz(pq) && x < pq.top())) break;

        if (sz(pq)) {
            x -= pq.top();
            pq.pop();
            ret++;
        }
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

    sort(all(a), [&](const auto& p1, const auto& p2) {
        return p1.fr + p1.sc < p2.fr + p2.sc;
    });

    int ans1 = 0, ans2 = 0;
    for (int x = 1; x < 3100; x++) {
        int res = f(x);
        if (ans1 < res) ans1 = res, ans2 = x;
    }

    cout << ans1 << ' ' << ans2;
}*/