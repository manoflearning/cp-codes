#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <vector>
#include <map>
#define fast_io() cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
using namespace std;
typedef pair<int, int> pii;

int n;
bool s_isAw[101]{0};
bool check[101]{0}, ans_c[101]{0};
vector<pair<int, vector<int>>> arr;
vector<int> ans(100,0);

int main(){
    //fast_io();
    char input[7];

    scanf("%d", &n);

    for(int i=0; i<n; i++){
        printf("at 00:00 check %d\n", i+1);
        fflush(stdout);
        scanf("%s", input);

        if(!strcmp(input, "awake")){
            s_isAw[i]=1;
        }
    }

    int now=0;

    for(int i=40; now+i<720; i--){
        now+=i;

        vector<int> tmp;

        for(int j=0; j<n; j++){
            if(check[j]) continue;
            printf("at %02d:%02d check %d\n", now/60, now%60, j+1);

            fflush(stdout);

            scanf("%s", input);

            if(!strcmp(input, "awake")){
                if(!s_isAw[j]){
                    check[j]=1;
                    tmp.push_back(j);
                }
            }else{
                if(s_isAw[j]){
                    check[j]=1;
                    tmp.push_back(j);
                }
            }
        }

        arr.push_back({now-i+1+720, tmp});
    }

    int af=now; now=720;
    vector<int> tmp;

    for(int i=0; i<n; i++){
        if(check[i]) continue;

        printf("at %02d:%02d check %d\n", now/60, now%60, i+1);

        fflush(stdout);
        scanf("%s", input);

        if(!strcmp(input, "awake")){
            if(!s_isAw[i]){
                check[i]=1;
                tmp.push_back(i);
            }
        }else{
            if(s_isAw[i]){
                check[i]=1;
                tmp.push_back(i);
            }
        }
    }

    arr.push_back({af+1+720, tmp});

    for(int i=0; i<arr.size(); i++){
        now=arr[i].first;
        while(now<1440 && (i==arr.size()-1 || (now<arr[i+1].first))){
            for(int j=0; j<arr[i].second.size(); j++){
                int np=arr[i].second[j];
                if(ans_c[np]) continue;
                printf("at %02d:%02d check %d\n", now/60, now%60, np+1);
                fflush(stdout);
                scanf("%s", input);

                if(!strcmp(input, "awake")){
                    if(s_isAw[np]){
                        ans_c[np]=1;
                        ans[np]=now-720;
                    }
                }else{
                    if(!s_isAw[np]){
                        ans_c[np]=1;
                        ans[np]=now;
                    }
                }
            }
            now++;
        }
    }

    printf("answer\n");
    for(int i=0; i<n; i++){
        if(!ans[i] && s_isAw[i]) ans[i]=720;
        printf("%02d:%02d\n", ans[i]/60, ans[i]%60);
    }
    fflush(stdout);

    return 0;
}