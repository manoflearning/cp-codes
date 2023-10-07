#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 4040;
const int MAXK = 4040;
const int MOD =  998'244'353;

ll EplusO[MAXN], EminusO[MAXN];
ll c[MAXN];

void preprocessing() {
    EplusO[0] = 1;
    EminusO[0] = 1;
    for (int x = 1; x < MAXN; x++) {
        for (int i = 0; i + x < MAXN; i++) {
            EplusO[i + x] += EplusO[i];
            EplusO[i + x] %= MOD;
            EminusO[i + x] -= EminusO[i];
            EminusO[i + x] %= MOD;
        }
    }

    for (int i = 0; i < MAXN; i++) {
        c[i] = EplusO[i];
    }
}

struct Query { int n, idx; };
int q;
vector<Query> qu[MAXK];
vector<ll> ans;

void input() {
    cin >> q;
    ans.resize(q);
    for (int i = 0; i < q; i++) {
        int n, k;
        cin >> n >> k;
        qu[k].push_back({ n, i });
    }
}

void solve() {
    for (auto& i : qu[0]) {
        ans[i.idx] = c[i.n];
    }

    for (int k = 1; k < MAXN; k++) {
        if (qu[k].empty()) continue;

        vector<ll> F(MAXN);
        vector<ll> psum(k);

        for (int i = 0; i < k; i++) {
            F[i] = c[i];
            psum[i] = 
        }


    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    preprocessing();

    input();

    
}