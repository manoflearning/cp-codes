#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define p pair<int, int>
#define x first
#define y second

const int INF = 1e9 + 7;
const int MAXV = 1010;

struct MCMF{
	int s, t; //source, sink
	struct Edge{ int v, c, d, dual; };
	vector<Edge> g[MAXV];
	void addEdge(int s, int e, int c, int d){
		g[s].push_back({e, c, d, (int)g[e].size()});
		g[e].push_back({s, 0, -d, (int)g[s].size()-1});
	}

	int dst[MAXV], inq[MAXV];
	bool spfa(){
		memset(dst, 0x3f, sizeof dst);
		memset(inq, 0, sizeof inq);
		queue<int> q; q.push(s); inq[s] = 1; dst[s] = 0;
		while(q.size()){
			int now = q.front(); q.pop(); inq[now] = 0;
			for(auto i : g[now]){
				if(i.c && dst[i.v] > dst[now] + i.d){
					dst[i.v] = dst[now] + i.d;
					if(!inq[i.v]) inq[i.v] = 1, q.push(i.v);
				}
			}
		}
		return dst[t] < 1e9;
	}

	int chk[MAXV], work[MAXV];

	int dfs(int now, int fl){
        chk[now] = 1;
        if(now == t) return fl;
        for(; work[now] < g[now].size(); work[now]++){
            auto &i = g[now][work[now]];
            if(!chk[i.v] && dst[i.v] == dst[now] + i.d && i.c){
                int ret = dfs(i.v, min(fl, i.c));
                if(ret){
                    i.c -= ret; g[i.v][i.dual].c += ret;
                    return ret;
                }
            }
        }
        return 0;
	}
	p run(int _s, int _t){ //{cost, flow}
		s = _s, t = _t;
		int cst = 0, fl = 0;
		while(spfa()){
			memset(chk, 0, sizeof chk);
            memset(work, 0, sizeof work);
			int now = 0;
			while(now = dfs(s, 1e9)){
				cst += dst[t] * now;
				fl += now;
				memset(chk, 0, sizeof chk);
			}
		}
		return p(cst, fl);
	}
} mcmf;

int n, a[505][505];
int st = 0, en = 1001;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        mcmf.addEdge(st, i, 1, 0);
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
            mcmf.addEdge(i, 500 + j, 1, a[i][j]);
        }
        mcmf.addEdge(500 + i, en, 1, 0);
    }

    cout << mcmf.run(st, en).x;
}
