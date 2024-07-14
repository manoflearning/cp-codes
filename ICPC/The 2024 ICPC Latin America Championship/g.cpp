#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()

const int N = 101010;

int n, w[N];
int sum_w = 0;
double dp[N];

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
        sum_w += w[i];
    }
}

map<int, int> prime_div(int x) {
    map<int, int> ret;
    for (int d = 2; d * d <= x; d++) {
        int cnt = 0;
        while (x % d == 0) {
            x /= d; cnt++;
        }
        if (cnt > 0) ret[x] = cnt;
    }
    if (x > 1) ret[x] = 1;
    return ret;
}

map<int, int> res_lb, res_ub;

int bt(map<int, int>::iterator it_lb, map<int, int>::iterator it_ub) {
    int ret = 1;
    
}

void bottomup() {
    for (int now = n; now >= 1; now--) {
        auto mp = prime_div(now);        

        for (int i = 2; i * now <= n; i++) {
            res_lb = res_ub = prime_div(i);

            for (auto& it : mp) {
                if (res_ub.count(it.fr)) {
                    res_lb[it.fr] += it.sc;
                    res_ub[it.fr] += it.sc;
                }
                else {
                    res_lb[it.fr] = 0;
                    res_ub[it.fr] = it.sc;
                }
            }

            int sum_d = 0;


        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();


}