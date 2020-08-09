#include <iostream>
#include <cmath>
#define pii pair<int, int>
#define xf first
#define ys second
using namespace std;

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int T; cin >> T;

	while (T--) {
		pii st, en;
		cin >> st.xf >> st.ys >> en.xf >> en.ys;

		int N; cin >> N;

		int ans = 0;
		for (int i = 0; i < N; i++) {
			int x, y, r;
			cin >> x >> y >> r;

			bool stIn = (pow(st.xf - x, 2) + pow(st.ys - y, 2) < pow(r, 2));
			bool enIn = (pow(en.xf - x, 2) + pow(en.ys - y, 2) < pow(r, 2));

			if (!(stIn && enIn) && (stIn || enIn)) ans++;
		}

		cout << ans << '\n';
	}
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 한 행성계가 출발점과 도착점 중 하나만을 포함하면 진입/이탈 횟수가 1 증가한다.
결정적 깨달음		: 
시간복잡도		: O(n)
오답 원인		: 1. 
				  2.
*/////////////////////////////////////////////////////////////////////