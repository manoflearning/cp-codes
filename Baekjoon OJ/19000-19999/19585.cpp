// O(1000 * 1000 * log(1000))
#include <bits/stdc++.h>
using namespace std;

const char st = 'a';
const int MAXC = 'z' - 'a' + 1;
const int MAXN = 1000 * 4000 + 1;

int C, N;
set<string> nicknames;

struct trie {
	int cnt, t[MAXN][MAXC];
	bool term[MAXN];
	void clear() {
		memset(t, 0, sizeof(t));
		memset(term, 0, sizeof(term));
		cnt = 0;
	}
	void insert(string& s) {
		int here = 0;
		for (char& i : s) {
			if (!t[here][i - st]) t[here][i - st] = ++cnt;
			here = t[here][i - st];
		}
		term[here] = true;
	}
	bool find(string& s) {
		int here = 0;
        string tmp = s;
        reverse(tmp.begin(), tmp.end());
		for (int i = 0; i < s.size(); i++) {
			if (!t[here][s[i] - st]) return false;
            tmp.pop_back();
			here = t[here][s[i] - st];
			if (term[here]) {
                if (nicknames.count(tmp)) return true;
            }
		}
        return false;
	}
};
trie T;

void input() {
    cin >> C >> N;
    for (int i = 0; i < C; i++) {
        string s; cin >> s;
        T.insert(s);
    }
    for (int i = 0; i < N; i++) {
        string s; cin >> s;
        reverse(s.begin(), s.end());
        nicknames.insert(s);
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

    int Q; cin >> Q;
    while (Q--) {
        string s; cin >> s;
        if (T.find(s)) cout << "Yes\n";
        else cout << "No\n";
    }
}