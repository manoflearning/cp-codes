#include <iostream>
#include <queue>
using namespace std;

const int MAX = 50;
const int MOV[4][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

int n, m;
char miro[MAX][MAX];
bool visited[(1 << 6)][MAX][MAX];

struct st {
	int y;
	int x;
	int cnt;
	int key;
};

int escape(int sy, int sx);

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	//input
	cin >> n >> m;

	int sy, sx;

	for (int i = 0; i < n; i++)
		for (int l = 0; l < m; l++) {
			cin >> miro[i][l];

			if (miro[i][l] == '0') sy = i, sx = l;
		}
	//
	cout << escape(sy, sx);

	return 0;
}

int escape(int sy, int sx) {
	queue<st> q;

	q.push({ sy, sx, 0, 0 });

	while (!q.empty()) {
		int y = q.front().y, x = q.front().x;
		int cnt = q.front().cnt, key = q.front().key;
		
		if (miro[y][x] == '1') return cnt;

		for (int i = 0; i < 4; i++) {
			int my = y + MOV[i][1], mx = x + MOV[i][0];
			
			if (visited[key][my][mx]) continue;
			if (my < 0 || n <= my || mx < 0 || m <= mx) continue;
			if (miro[my][mx] == '#') continue;
			//문을 만났는데 열쇠가 없음
			if ('A' <= miro[my][mx] && miro[my][mx] <= 'F') {
				if ((1 << miro[my][mx] - 'A') != (key & (1 << miro[my][mx] - 'A')))
					continue;
			}
			//열쇠 주움
			if ('a' <= miro[my][mx] && miro[my][mx] <= 'f') {
				visited[key][my][mx] = true;
				q.push({ my, mx, cnt + 1, key | (1 << miro[my][mx] - 'a') });
			}
			else {
				visited[key][my][mx] = true;
				q.push({ my, mx, cnt + 1, key });
			}
		}

		q.pop();
	}

	return -1;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: BFS, 비트마스크
접근 방식		: 
결정적 깨달음		: 방문 여부를 저장하는 visited 배열에 좌표값 뿐만 아니라 가진 키 정보까지 저장할 수 있다.
오답 원인		: 1. 관계형 연산자는 비트 연산자보다 우선순위가 높음
				  2. 
*/////////////////////////////////////////////////////////////////////