#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    int t; scanf("%d",&t);
    while(t--){
        int n; scanf("%d",&n);
        if(n==1){ printf("1\n"); continue; }
        if(n==2){ printf("-1\n"); continue; }
        vector<ll> a = {1,2,3};
        ll val = 6;
        for(int i=4;i<=n;i++){
            a.push_back(val);
            val *= 2;
        }
        for(ll x : a) printf("%lld ", x);
        printf("\n");
    }
}