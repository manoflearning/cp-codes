// 노드 집합 V를 두 그룹 A, B로 나눈다.
// A 내부의 모든 노드를 엣지로 연결하고, B 내부의 모든 노드를 엣지로 연결하고, A의 노드 v와 B의 노드 u의 연결 여부를 질의한다.
// 1. 연결된 경우 : 그룹 A와 B를 랜덤으로 다시 만든다.
// 2. 연결되지 않은 경우 : 답은 모두 그룹 A에 속하거나, 모두 그룹 B에 속한다.
#include "findVertices.h"
#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

void dnc(vector<int> S) {
    if (sz(S) <= 1) return;
    if (sz(S) == 2) {
        if (query({}, {}, S[0], S[1])) {
            answer(S[0], S[1]);
            exit(0);
        }
        return;
    }

    int ub = (sz(S) + 1) / 2;
    vector<int> A, B;
    for (auto& i : S) {
        if (sz(A) == ub) B.push_back(i);
        else if (sz(B) == ub) A.push_back(i);
        else if (rand() % 2) A.push_back(i);
        else B.push_back(i);
    }

    vector<int> U, V;
    for (int i = 0; i + 1 < sz(A); i++) {
        U.push_back(A[i]);
        V.push_back(A[i + 1]);
    }
    for (int i = 0; i + 1 < sz(B); i++) {
        U.push_back(B[i]);
        V.push_back(B[i + 1]);
    }

    if (query(U, V, A[0], B[0])) dnc(S);
    else { dnc(A); dnc(B); }
}

void find(int N) {
    srand(time(NULL));

    vector<int> S;
    for (int i = 1; i <= N; i++) 
        S.push_back(i);
    dnc(S);
}
