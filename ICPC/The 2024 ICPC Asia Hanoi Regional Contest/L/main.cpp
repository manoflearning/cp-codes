#include <bits/stdc++.h>
using namespace std;
#define ll long long

const ll mod=998'244'353;

ll power(ll x, ll n) {
    if(n==0) return 1;
    ll ret=power(x, n/2);

    if(n&1) return (((ret*ret)%mod)*x)%mod;
    else return (ret*ret)%mod;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // int tc; cin >> tc;
    // while (tc--) {
        ll s,q;
        cin >> s >> q;

        ll sum=0;

        struct Node {
            ll x, y, z;
            bool operator<(const Node &rhs) const {
                return x * rhs.y < rhs.x * y;
            }
        };
        priority_queue<Node> pq, pq2;

        while(q--) {
            char op;
            ll a, b;
            cin >> op >> a >> b;

            ll tmp=(a*power(b, mod-2))%mod;
            ll nsz=(s*power(b, mod-2))%mod;

            if(op=='+') {
                sum=(sum+tmp)%mod;
                pq.push({s, b, nsz});
            }
            else {
                sum=(sum-tmp+mod)%mod;
                pq2.push({s, b, nsz});
            }

            while(pq.size() && pq2.size() && pq.top().z == pq2.top().z) {
                pq.pop();
                pq2.pop();
            }

            if(pq.size()) cout << (sum + pq.top().z)%mod << '\n';
            else cout << 0 << '\n';
        }
    // }
}
