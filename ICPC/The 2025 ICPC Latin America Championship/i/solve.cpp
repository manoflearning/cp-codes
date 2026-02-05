#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

struct UF{
    vector<int> par;
    void init(int n) {
        par.assign(n, -1);
    }
    int find(int x) {
        if(par[x]<0) return x;
        return par[x] = find(par[x]);
    }
    void merge(int u, int v) {
        u=find(u);
        v=find(v);
        if(u==v) return;

        par[u]+=par[v];
        par[v]=u;
    }
}uf;

const int mxn=1'000'000;
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n; cin >> n;
    vector<int> arr(n);
    for(auto &a:arr) cin >> a;

    vector<int> bef(mxn*2, -1), nxt(mxn*2, -1);

    auto add_edge=[&](const int& u, const int &v) {
        nxt[u]=v;
        bef[v]=u;
    };

    for(int i=0; i<n; i++) {
        add_edge(arr[i], arr[(i+1)%n]);
    }

    int e; cin >> e;

    while(e--) {
        char qr; cin >> qr;
        if(qr == '?') {
            int k; cin >> k;
            vector<int> krr(k);
            for(auto &a:krr) cin >> a;

            uf.init(k);

            int ans=0;
            for(int i=0; i<k; i++) {
                if(bef[krr[i]] == -1 || nxt[krr[i]] == -1) continue;

                if(krr[(i-1+k)%k] == bef[krr[i]]) uf.merge((i-1+k)%k, i);

                ans=max(ans, -uf.par[uf.find(i)]);
            }

            if(ans == k && k % n == 0) cout << "*\n";
            else cout << ans << '\n';
        }
        if(qr == '-') {
            int x; cin >> x;
            add_edge(bef[x], nxt[x]);
            bef[x]=nxt[x]=-1;
            n--;
        }
        if(qr == '+') {
            int y,z; cin >> y >> z;
            add_edge(bef[z], y);
            add_edge(y, z);
            n++;
        }
    }
}
