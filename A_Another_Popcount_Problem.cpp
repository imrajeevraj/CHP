#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    scanf("%d", &t);
    while (t--) {
        long long n, k;
        scanf("%lld %lld", &n, &k);

        long long L = 0;
        
        while (k * ((1LL << (L + 1)) - 1) <= n) L++;

        long long used = k * ((1LL << L) - 1);
        long long rem = n - used;
        long long step = 1LL << L;
        long long cnt = rem / step;
        if (cnt > k) cnt = k;

        long long ans = k * L + cnt;
        printf("%lld\n", ans);
    }
    return 0;
}