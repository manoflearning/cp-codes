#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int MOD = 998'244'353;
constexpr int INF = 998'242'353;
constexpr int MEM_SIZE = 100'000;

constexpr int IDX[] = {
    MEM_SIZE - 1,
    MEM_SIZE - 2,
    MEM_SIZE - 3,
    MEM_SIZE - 4,
    MEM_SIZE - 5,
    MEM_SIZE - 6,
    MEM_SIZE - 7,
    MEM_SIZE - 8,
    MEM_SIZE - 9,
    MEM_SIZE - 10,
};

constexpr int D = 17;

int n, m;
struct inst {
    string op;
    int a, b, c;
};
vector<inst> ans;

void set_(int a, int b) {
    ans.push_back({"set", a, b, -1});
}
void add_(int a, int b, int c) {
    ans.push_back({"add", a, b, c});
}
void sub_(int a, int b, int c) {
    ans.push_back({"sub", a, b, c});
}
void mul_(int a, int b, int c) {
    ans.push_back({"mul", a, b, c});
}
void div_(int a, int b, int c) {
    ans.push_back({"div", a, b, c});
}

void test() {
    if (sz(ans) > (int)1e6) {
        cout << "size greater than 10^6\n";
        exit(0);
    }

    vector<ll> mem(MEM_SIZE);
    for (int i = 1; i <= n; i++) mem[i] = 9;
    mem[1] = 3;
    for (int i = n + 1; i <= n + m; i++) mem[i] = 9;
    mem[4] = 3;

    for (auto &[op, a, b, c] : ans) {
        if (op == "set") {
            mem[a] = b;
        } else if (op == "add") {
            mem[a] = mem[b] + mem[c];
            mem[a] = (mem[a] % MOD + MOD) % MOD;
            // if (b == 99991 && c == 5) cout << mem[a] << '\n';
            // if (b == 0 && c == 99995) cout << mem[c] << '\n';
        } else if (op == "sub") {
            mem[a] = mem[b] - mem[c];
            mem[a] = (mem[a] % MOD + MOD) % MOD;
            // if (b == 99996 && c == 99991) cout << mem[c] << '\n';
        } else if (op == "mul") {
            mem[a] = mem[b] * mem[c];
            mem[a] = (mem[a] % MOD + MOD) % MOD;
        } else if (op == "div") {
            if (mem[c] == 0) {
                cout << "mem[c] is 0\n";
                exit(0);
            }
            mem[a] = mem[b] / mem[c];
        }
        // cout << mem[0] << '\n';
    }

    cout << mem[0] << '\n';
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    set_(IDX[0], 100);
    set_(IDX[1], 99);
    set_(IDX[2], D);
    set_(IDX[3], 1);

    cin >> n >> m;

    int e = m;
    set_(IDX[4], 1);
    set_(IDX[5], D);
    while (e) {
        if (e & 1) {
            mul_(IDX[4], IDX[4], IDX[5]);
        }
        mul_(IDX[5], IDX[5], IDX[5]);
        e >>= 1;
    }

    set_(IDX[5], INF);

    // 1. mem[IDX[9]]에 B의 해시값을 저장하기
    for (int i = n + 1; i <= n + m; i++) {
        mul_(IDX[9], IDX[9], IDX[2]);
        add_(IDX[9], IDX[9], i);
    }

    // 2. mem[n+m+1...n+m+n+1]에 A[1...i]의 해시값을 각각 저장하기 (0 <= i <= n)
    for (int i = n + m + 2; i <= 2 * n + m + 1; i++) {
        mul_(i, i - 1, IDX[2]);
        add_(i, i, i - (n + m + 1));
    }

    // 3. 비교 연산이 필요함. but how???? 해시를 또 해..?
    // 비교 연산: mem[IDX2]

    for (int i = n + m + 2; i <= 2 * n + m + 1; i++) {
        if (i - (n + m + 1) < m) continue;

        set_(IDX[8], 0);

        add_(IDX[8], IDX[8], IDX[9]);

        sub_(IDX[8], IDX[8], i);
        
        mul_(IDX[7], i - m, IDX[4]);
        add_(IDX[8], IDX[8], IDX[7]);

        mul_(IDX[8], IDX[8], IDX[5]);

        for (int j = 0; j < 5; j++) {
            add_(IDX[8], IDX[8], IDX[1]);
            div_(IDX[8], IDX[8], IDX[0]);
        }

        sub_(IDX[6], IDX[3], IDX[8]);
        add_(0, 0, IDX[6]);
    }

    for (auto &[op, a, b, c] : ans) {
        cout << op << ' ' << a << ' ' << b << ' ';
        if (op != "set") cout << c << ' ';
        cout << '\n';
    }

    // test();
}
