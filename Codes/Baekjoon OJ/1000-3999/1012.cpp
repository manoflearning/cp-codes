#include <iostream>
#include <algorithm>

using namespace std;

int M, N, K;
bool land[51][51] = { 0, };
bool visitp[51][51] = { 0, }; //visitp 배열은 사용하지 않는 배열이지만, 이 배열을 선언할 경우 "맞았습니다"가 뜨고, 그렇지 않을 경우 "런타임 에러"가 뜸.

int moveX[4] = { 1, 0, -1, 0 };
int moveY[4] = { 0, 1, 0, -1 };

void DFS(int x, int y) {
    if (land[x][y] == 1) {
        land[x][y] = 0;

        for (int i = 0; i < 4; i++) {
            int nx = moveX[i] + x;
            int ny = moveY[i] + y;

            if (x >= 0 && y >= 0 && x < M && y < N) { //다음에 갈 노드가 아니라, 현재 노드의 범위를 확인하는 코드
                DFS(nx, ny);
            }
        }
    }
}

int main(void) {
    int T, cnt;
    int x, y;
    land[-1][0]; //명백히 배열 인덱스 범위를 벗어남
    cin >> T;

    while (T--) {
        cnt = 0;
        cin >> M >> N >> K;

        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                land[i][j] = 0;
            }
        }

        for (int i = 0; i < K; i++) {
            cin >> x >> y;
            land[x][y] = 1;
        }

        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (land[i][j] == 1) {
                    DFS(i, j);
                    cnt++;
                }
            }
        }

        cout << cnt << "\n";
    }
    return 0;
}