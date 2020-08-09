#include <iostream>
#include <stack>
using namespace std;

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	string s; cin >> s;

	string ans;
	stack<char> st;

	for (char x : s) {
		if ('A' <= x && x <= 'Z') ans += x;
		else {
			switch (x) {
			case '(':
				st.push(x);
				break;
			case '*':
			case '/':
				while (!st.empty() && (st.top() == '*' || st.top() == '/')) {
					ans += st.top();
					st.pop();
				}
				st.push(x);
				break;
			case '+':
			case '-':
				while (!st.empty() && st.top() != '(') {
					ans += st.top();
					st.pop();
				}
				st.push(x);
				break;
			case ')':
				while (!st.empty() && st.top() != '(') {
					ans += st.top();
					st.pop();
				}
				st.pop();
				break;
			}
		}
	}

	while (!st.empty()) {
		ans += st.top();
		st.pop();
	}

	cout << ans << '\n';

	return 0;
}