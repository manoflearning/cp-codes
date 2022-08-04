#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

const int dir[4][2] = { {1, 0},{0,1},{-1,0},{0,-1} };
const int WRNG = 10000;

int n, m;
char brd[10][10];

int escape(int last, int cnt, int ry, int rx, int by, int bx);

int main() {
	cin >> n >> m;

	int ry, rx, by, bx;

	for (int y = 0; y < n; y++)
		for (int x = 0; x < m; x++) {
			cin >> brd[y][x];

			if (brd[y][x] == 'R') {
				ry = y, rx = x;
				brd[y][x] = '.';
			}
			if (brd[y][x] == 'B') {
				by = y, bx = x;
				brd[y][x] = '.';
			}
		}
	//
	int ans = escape(-1, 1, ry, rx, by, bx);

	if (ans == WRNG) cout << "-1";
	else cout << ans;

	return 0;
}

int escape(int last, int cnt, int ry, int rx, int by, int bx) {
	//base case
	if (cnt > 10) return WRNG;
	//
	int ret = WRNG;

	for (int i = 0; i < 4; i++) {
		if (i == last) continue;

		int pry = ry, prx = rx, pby = by, pbx = bx;

		while (true) {
			pry += dir[i][0], prx += dir[i][1];

			if (brd[pry][prx] == '#') {
				pry -= dir[i][0], prx -= dir[i][1];
				break;
			}
			if (brd[pry][prx] == 'O') break;
		}
		while (true) {
			pby += dir[i][0], pbx += dir[i][1];

			if (brd[pby][pbx] == '#') {
				pby -= dir[i][0], pbx -= dir[i][1];
				break;
			}
			if (brd[pby][pbx] == 'O') break;
		}

		bool ESC = false;

		if (brd[pby][pbx] == 'O') {
			ESC = true;
			ret = min(ret, WRNG);
		}
		if (!ESC && brd[pry][prx] == 'O') {
			ESC = true;
			ret = min(ret, cnt);
		}

		if (!ESC) {
			if (pry == pby && prx == pbx) {
				int rlen = fabs(pry - ry) + fabs(prx - rx);
				int blen = fabs(pby - by) + fabs(pbx - bx);

				if (blen > rlen) {
					pby -= dir[i][0], pbx -= dir[i][1];
				}
				else {
					pry -= dir[i][0], prx -= dir[i][1];
				}
			}

			ret = min(ret, escape(i, cnt + 1, pry, prx, pby, pbx));
		}
	}

	return ret;
}
/*////////////////////////////////////////////////////////////////////
���� �ع�		: ����
���� ���		: 
������ ������		: ������ ��ĥ ��츦 �̵� �Ŀ� �ذ��Ѵ�. ������ ��ĥ ��� �� ������ �̵��Ÿ��� �������� �̵��Ÿ��� �� ������ �������� �ϸ� �ȴ�.
���� ����		: 1. ������ ��ġ�� ��� � ������ ���������ϴ��� �Ǻ��ϴ� if���� �߸���
				  2. 
*/////////////////////////////////////////////////////////////////////