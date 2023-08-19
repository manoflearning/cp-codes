// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()
#define pii pair<int, int>
#define fr first
#define sc second

const int MAXN = 1010101;
const int INF = 1e9 + 7;

int n;
string s;

// naive
ll naive() {
    ll ret = 0;
    for (int l = 0; l < n; l++) {
        for (int r = l; r < n; r++) {
            int isAns = 1;
            stack<char> stk;
            for (int i = l; i <= r; i++) {
                if (s[i] == '(' || s[i] == '{') stk.push(s[i]);
                else {
                    if (stk.empty()) { isAns = 0; break; }
                    else if (stk.top() == '(' && s[i] == '}') { isAns = 0; break; }
                    else if (stk.top() == '{' && s[i] == ')') { isAns = 0; break; }
                    stk.pop();
                }
            }
            if (sz(stk)) isAns = 0;
            ret += isAns;
        }
    }
    return ret;
}

// group3
int cnt[2 * MAXN];
int stk[MAXN], pos[MAXN];
int po = 0;
ll group3() {
    // solve
    ll ret = 0;

    int sum = MAXN;
    cnt[sum]++;
    for (int i = 0; i < n; i++) {
        if (s[i] == '(' || s[i] == '{') {
            stk[po] = i;
            pos[po] = sum;
            po++;
            sum++;
        }
        else {
            ret += (ll)cnt[sum] * (cnt[sum] - 1) / 2;
            cnt[sum] = 0;
            sum--;
            if (po == 0 || abs(s[i] - s[stk[po - 1]]) > 2) {
                for (int i = 0; i < po; i++) {
                    ret += (ll)cnt[pos[i]] * (cnt[pos[i]] - 1) / 2;
                    cnt[pos[i]] = 0;
                }
                po = 0;
            }
            else po--;
        }
        cnt[sum]++;
    }
    
    for (int i = 0; i < po; i++) {
        ret += (ll)cnt[pos[i]] * (cnt[pos[i]] - 1) / 2;
        cnt[pos[i]] = 0;
    }
    po = 0;
    ret += (ll)cnt[sum] * (cnt[sum] - 1) / 2;
    cnt[sum] = 0;

    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    srand(time(NULL));
    
    for (int tc = 0; tc < 42; tc++) {
        n = 1'000'000;
        s.clear();
        vector<char> arr = { '(', ')', '{', '}' };
        for (int i = 0; i < n; i++) {
            s.push_back(arr[rand() % 4]);
        }

        // ll x = group3(), y = naive();

        // cout << x << ' ' << y << '\n';
        // if (x != y) {
        //     cout << n << '\n' << s << '\n';
        //     cout << "group3 solution: " << x << '\n';
        //     cout << "naive solution: " << y << '\n';
        //     break;
        // }

        // cout << group3() << '\n';
    }
}