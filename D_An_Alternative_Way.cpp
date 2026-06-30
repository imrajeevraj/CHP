#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        int n;
        scanf("%d", &n);
        vector<long long> a(n), b(n);
        for(auto &x:a) scanf("%lld",&x);
        for(auto &x:b) scanf("%lld",&x);
        long long sum = 0;
        bool ok = true;
        for(int i=0;i<n;i++){
            sum += b[i]-a[i];
            if(sum < 0){ ok = false; break; }
        }
        puts(ok ? "YES" : "NO");
    }
}