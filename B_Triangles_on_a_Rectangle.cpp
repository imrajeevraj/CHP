#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        long long w, h;
        scanf("%lld %lld", &w, &h);
        long long ans = 0;
        // 4 sides: 0 -> bottom (y=0), 1 -> top (y=h), 2 -> left (x=0), 3 -> right (x=w)
        for(int i = 0; i < 4; i++){
            int k;
            scanf("%d", &k);
            long long mn = LLONG_MAX, mx = LLONG_MIN;
            for(int j = 0; j < k; j++){
                long long v;
                scanf("%lld", &v);
                mn = min(mn, v);
                mx = max(mx, v);
            }
            long long dim = (i < 2) ? h : w; // horizontal sides use h, vertical use w
            ans = max(ans, (mx - mn) * dim);
        }
        printf("%lld\n", ans);
    }
}