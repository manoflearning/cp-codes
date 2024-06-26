#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second

const int MAXM = 121;

int N, M;
ll X[MAXM], Y[MAXM], A, B;

void input() {
    cin >> N >> M;
    for (int i = 1; i <= M; i++) cin >> X[i] >> Y[i];
    cin >> A >> B;
}

ll gcd(ll x, ll y) {
    if (!y) return x;
    return gcd(y, x % y);
}
ll minv(ll x, ll y) {
    if (x == 0 && y == 1) return 0;
    if (x == 1) return 1;
    return y - minv(y % x, x) * y / x;
}
pll crt(pll U, pll V) {
    if (U.sc == -1 || V.sc == -1) return { -1, -1 };
    if (U.sc == 1) return V;
    if (V.sc == 1) return U;
    ll g = gcd(U.sc, V.sc), l = U.sc * V.sc / g;
    if ((V.fr - U.fr) % g) return { -1, -1 };

    ll u = U.sc / g, v = V.sc / g;
    ll mul = (V.fr - U.fr) / g;
    mul = mul * minv(u % v, v) % v;

    pll ret = { mul * U.sc + U.fr, l };
    ret.fr %= ret.sc, ret.fr = (ret.fr + ret.sc) % ret.sc;
    return ret;
}

vector<int> adj[MAXM];
void buildGraph() {
    for (int i = 1; i <= M; i++) {
        for (int j = i + 1; j <= M; j++) {
            pll res = crt({ X[i] % Y[i], Y[i] }, { X[j] % Y[j], Y[j] });
            if (res.fr == -1) continue;

            for (int d = 30; d >= 0; d--) {
                if (res.fr + (1ll << d) * res.sc < max(X[i], X[j])) {
                    res.fr += (1ll << d) * res.sc;
                }
            }
            if (res.fr < max(X[i], X[j])) res.fr += res.sc;

            if (res.fr <= N) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }
}

vector<int> dist(MAXM, -1);

void bfs() {
    queue<int> q;
    for (int i = 1; i <= M; i++) {
        if (X[i] <= A && (A - X[i]) % Y[i] == 0) {
            dist[i] = 0;
            q.push(i);
        }
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (auto& i : adj[v]) {
            if (dist[i] == -1) {
                dist[i] = dist[v] + 1;
                q.push(i);
            }
        }
    }
}

void printAnswer() {
    int v = -1;
    for (int i = 1; i <= M; i++) {
        if (dist[i] == -1) continue;
        if (X[i] <= B && (B - X[i]) % Y[i] == 0) {
            if (v == -1 || dist[i] < dist[v]) v = i;
        }
    }
    
    if (v == -1) {
        cout << -1;
        exit(0);
    }

    cout << dist[v] + 1 << '\n';
    stack<int> stk;
    stk.push(v);
    while (dist[v] > 0) {
        for (auto& i : adj[v]) {
            if (dist[i] + 1 == dist[v]) {
                v = i;
                break;
            }
        }
        stk.push(v);
    }

    while (!stk.empty()) {
        cout << stk.top() << '\n';
        stk.pop();
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    buildGraph();

    bfs();

    printAnswer();
}