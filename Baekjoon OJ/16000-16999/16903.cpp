#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first 
#define sc second
#define vt vector
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

#define EXPAND( x ) x // Use this if MS Visual Studio doesn't expand __VA_ARGS__ correctly
#define F_OR(i, a, b, s) for (int i = (a); (s) > 0 ? i < (b) : i > (b); i += (s))
#define F_OR1(e) F_OR(i, 0, e, 1)
#define F_OR2(i, e) F_OR(i, 0, e, 1)
#define F_OR3(i, b, e) F_OR(i, b, e, 1)
#define F_OR4(i, b, e, s) F_OR(i, b, e, s)
#define GET5(a, b, c, d, e, ...) e
#define F_ORC(...) EXPAND( GET5(__VA_ARGS__, F_OR4, F_OR3, F_OR2, F_OR1) )
#define FOR(...) EXPAND( F_ORC(__VA_ARGS__ )(__VA_ARGS__) )
#define EACH(x, a) for (auto& x : a)

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

const int MAXC = 2;

struct trie {
    trie* child[MAXC];
    int term, childCnt;

    trie() {
        fill(child, child + MAXC, nullptr);
        term = childCnt = 0;
    }
    ~trie() {
        for (int i = 0; i < MAXC; i++)
            if (child[i]) delete child[i];
    }

    void modify() {
        childCnt = 0;
        if (child[0]) childCnt += child[0]->childCnt;
        if (child[1]) childCnt += child[1]->childCnt;
    }

    void insert(ll bit, int key = 32) {
        if (key == 0) {
            term++;
            childCnt = term;
        }
        else {
            int next = (bit & (1 << (key - 1)) ? 1 : 0);
            if (!child[next]) child[next] = new trie;
            child[next]->insert(bit, key - 1);
            
            modify();
        }
    }

    void erase(ll bit, int key = 32) {
        if (key == 0) {
            term--;
            childCnt = term;
        }
        else {
            int next = (bit & (1 << (key - 1)) ? 1 : 0);
            child[next]->erase(bit, key - 1);
            
            modify();

            for (int i = 0; i < MAXC; i++) {
                if (child[i] && !child[i]->childCnt) {
                    delete child[i];
                    child[i] = nullptr;
                }
            }
        }
    }

    int find(ll bit, int key = 32) {
        if (key == 0) return term ? 1 : 0;
        else {
            int next = (bit & (1 << (key - 1)) ? 1 : 0);
            if (!child[next]) return 0;
            return child[next]->find(bit, key - 1);
        }
    }

    ll cal(ll bit, int key = 32) {
        if (key == 0) return bit;
        else {
            int next = (bit & (1 << (key - 1)) ? 0 : 1);
            if (!child[next]) {
                next = !next;
                if (!child[next]) return 0;
            }
            return child[next]->cal(bit ^ (next * (1 << (key - 1))), key - 1);
        }
    }
};

trie* root = new trie;

int main() {
	#ifndef ONLINE_JUDGE
	// Enter the absolute path of the local file input.txt, output.txt
	// Or just enter the "input.txt", "output.txt"
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
    
    root->insert(0);

	int m; cin >> m;
    while (m--) {
        int op; ll x;
        cin >> op >> x;

        if (op == 1) root->insert(x);
        if (op == 2) {
            root->erase(x);
            //cout << root->find(8) << '\n';
        }
        if (op == 3) cout << root->cal(x) << '\n';
    }

    delete root;

	return 0;
}