#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9+7;

ll power(ll b, ll e, ll m){
    b%=m; ll r=1;
    while(e>0){ if(e&1) r=r*b%m; b=b*b%m; e>>=1; }
    return r;
}

int main(){
    int t; scanf("%d",&t);
    while(t--){
        int n; scanf("%d",&n);
        vector<ll> a(n);
        for(auto &x: a) scanf("%lld",&x);
        ll m=0; int idx=0;
        while(idx<n && a[idx]==-1){ m++; idx++; }
        vector<ll> vals, sizes;
        int r = n-idx, i=idx;
        while(i<n){
            ll v=a[i], cnt=0;
            while(i<n && a[i]==v){ cnt++; i++; }
            vals.push_back(v); sizes.push_back(cnt);
        }
        int g = vals.size();
        ll cntAdj=0;
        for(int j=0;j+1<g;j++) if(vals[j+1]==vals[j]+1) cntAdj++;
        ll A,B;
        if(m==0){ A=1; B=0; }
        else { A = power(2, m-1, MOD); B = A; }
        ll pw = power(2, r-g, MOD);
        ll ans = pw * ((A + B*cntAdj) % MOD) % MOD;
        printf("%lld\n", ans);
    }
}