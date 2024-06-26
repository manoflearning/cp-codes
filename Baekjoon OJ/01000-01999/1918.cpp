#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>

const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1 };
const int dx[] = { 1, -1, 0, 0 };

string s;
stack<char> st;

void input() {
    cin >> s;
}

int f2(char a, char b) {
    if ((a == '*' || a == '/') && (b == '+' || b == '-')) return 1;
    else return 0;
}

void f() {
    for (auto c : s) {
        if ('A' <= c && c <= 'Z') cout << c;
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (1) {
                if (st.empty()) break;
                else if (st.top() == '(') break;
                else if (f2(c, st.top())) break;
                cout << st.top();
                st.pop();
            }
            st.push(c);
        }
        else if (c == '(') st.push(c);
        else if (c == ')') {
            while (st.top() != '(') {
                cout << st.top();
                st.pop();
            }
            //cout << st.top();
            st.pop();
        }
    }
    while (!st.empty()) {
        cout << st.top();
        st.pop();
    }
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	input();
	
	f();
	
	return 0;
}
