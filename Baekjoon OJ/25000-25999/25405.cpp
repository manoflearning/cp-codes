#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define pll pair<ll, ll>
#define fr first
#define sc second

const int INF = 1e9 + 7;

int n, k;
ll lev[101010], m, x, curr;
priority_queue<ll> A;
ll B1 = 0, B2 = 0;
priority_queue<ll, vector<ll>, greater<ll>> C;

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> lev[i];
    cin >> m >> k;
}

pll f(ll ts) {
    return { ts / (B1 + B2), ts % (B1 + B2) };
}

void f2(ll at, ll ct) {
    pll res = f(min(at, ct) * (k - sz(A)));
    x += res.fr;
    if (res.sc < B1) {
        B1 -= res.sc;
        B2 += res.sc;
    }
    else if (B1 <= res.sc) {
        x++;
        ll sum = B1 + B2;
        B2 = res.sc - B1;
        B1 = sum - B2;
    }
    curr += min(at, ct);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    sort(lev + 1, lev + n + 1);

    x = lev[k];
    for (int i = 1; i <= n; i++) {
        if (lev[i] < x) A.push(lev[i]);
        else if (lev[i] == x) B1++;
        else if (lev[i] == x + 1) B2++;
        else C.push(lev[i]);
    }

    while (sz(A) || sz(C)) {
        ll at = INF, ct = INF;

        if (sz(A)) {
            ll l = 0, r = m + 1;
            while (l < r) {
                ll mid = (l + r) >> 1;

                pll res = f(mid * (k - sz(A)));
                ll nx = x + res.fr + (B1 <= res.sc ? 1 : 0);

                if (nx <= A.top() + curr + mid) r = mid;
                else l = mid + 1;
            }

            at = l;
        }
        if (sz(C)) {
            ll l = 0, r = m + 1;
            while (l < r) {
                ll mid = (l + r) >> 1;

                pll res = f(mid * (k - sz(A)));
                ll nx = x + res.fr + (B1 <= res.sc ? 1 : 0);
                
                if (C.top() <= nx + 1) r = mid;
                else l = mid + 1;
            }
            
            ct = l;
        }

        if (m - curr < at && m - curr < ct) break;
        
        f2(at, ct);
        
        if (at == ct) {
            B1++, B2++;
            A.pop(); C.pop();
        }
        else if (at < ct) {
            B1++; A.pop();
        }
        else if (at > ct) {
            B2++; C.pop();
        }
    }
    f2(m - curr, m - curr);

    vector<ll> ans;
    while (sz(A)) {
        ans.push_back(A.top() + m);
        A.pop();
    }
    while (sz(C)) {
        ans.push_back(C.top());
        C.pop();
    }
    while (B1--) ans.push_back(x);
    while (B2--) ans.push_back(x + 1);

    sort(ans.begin(), ans.end());

    for (auto& i : ans)
        cout << i << ' ';
}