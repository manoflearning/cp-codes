#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int INF = 1e9 + 7;

int find_cycle(int u, int p, vector<int>& vis, vector<pii>& cycle, vector<vector<pii>>& adj) {
    for(auto &[v,i]:adj[u]) {
        if(v==p) continue;
        int ret;
        if((ret=vis[v]) || (ret=(vis[v]=vis[u]+1, find_cycle(v,u,vis,cycle,adj)))) {
            if(vis[u]>=ret) cycle.push_back({u,i});
            return ret;
        }
    }

    return 0;
}

void sol() {
    ll n, m, x, y; cin >> n >> m >> x >> y;
    x--;
    y--;

    vector<pii> edge(m);
    vector<vector<pii>> adj(n);
    for(int i=0; i<m; i++) {
        auto &[l,r] = edge[i];
        cin >> l >> r;
        l--; r--;
        adj[l].push_back({r,i});
        adj[r].push_back({l,i});
    }

    ll xydis;
    // {
        vector<int> dis(n, INF);
        vector<int> par(n,-1);
        // priority_queue<pii> q;
        queue<int> q;

        // q.push({dis[x], x});
        q.push(x);
        dis[x]=0;

        while(sz(q)) {
            auto u=q.front(); q.pop();

            if(u==y) continue;

            for(auto &[v,i]:adj[u]) {
                if(dis[v]==INF) {
                    q.push(v);
                    dis[v]=dis[u]+1;
                    par[v]=u;
                }
            }
        }

        xydis=dis[y];
    // }

    if(xydis==1 && m==n-1) {
        cout << "No\n";
        return;
    }

    if(xydis==1) {
        pii mn{INF,-1};
        for(auto &[v,i]:adj[y]) {
            if(edge[i].first==y) swap(edge[i].first, edge[i].second);
            if(v==x) swap(edge[i].first, edge[i].second);

            if(v==x) continue;
            mn=min(mn, {dis[v], v});
        }

        if(mn.second!=-1) {
            queue<int> q; q.push(mn.second);

            vector<bool> vis(n,0);
            vis[mn.second]=1;
            vis[y]=1;

            while(sz(q)) {
                auto u=q.front(); q.pop();

                for(auto &[v,i]:adj[u]) {
                    if(vis[v]) continue;
                
                    if(edge[i].first==u) swap(edge[i].first, edge[i].second);
                    if(dis[v]+1==dis[u] && sz(q)==0) {
                        vis[v]=1;
                        q.push(v);
                    }
                }
            }
        }
        else {
            vector<pii> cycle, nc;
            vector<int> vis(n,0);

            vis[x]=1;
            find_cycle(x, -1, vis, cycle, adj);

            vis.assign(n,0);

            queue<int> q;

            int cnt=0;
            for(auto &[u,i]:cycle) {
                // if(u==edge[i].first) swap(edge[i].first, edge[i].second);
                vis[u]=++cnt;
            }

            int u=cycle[0].first;

            pii last;

            while(vis[u]<cnt) {
                array<int,3> mx{0,-1,-1};
                for(auto &[v,i]:adj[u]) {
                    if(vis[v]!=cnt || u!=cycle[0].first) mx=max(mx, {vis[v], v, i});
                    else last={v, i};
                }
        
                nc.push_back({u, mx[2]});
                u=mx[1];
            }

            nc.push_back(last);

            vis.assign(n, 0);

            for(auto &[u,i]:nc) {
                if(u==edge[i].first) swap(edge[i].first, edge[i].second);
                q.push(u);
                vis[u]=1;
            }

            while(sz(q)) {
                auto u=q.front(); q.pop();

                for(auto &[v,i]:adj[u]) {
                    if(vis[v]) continue;

                    if(u==edge[i].first) swap(edge[i].first, edge[i].second);
                    q.push(v);
                    vis[v]=1;
                }
            }
        }
    }
    else {
        for(auto &u:{x,y}){
            for(auto &[v,i]:adj[u]) {
                if(edge[i].first==u) swap(edge[i].first, edge[i].second);
            }
        }
    }
    cout << "Yes\n";
    for(auto &[l,r]:edge) cout << l+1 << ' ' << r+1 << '\n';
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    ll tc; cin >> tc;
    while(tc--) sol();
}
