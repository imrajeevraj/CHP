#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool isSquare(ll x){
    ll r = (ll)sqrtl((long double)x);
    while(r*r > x) r--;
    while((r+1)*(r+1) <= x) r++;
    return r*r == x;
}

int main(){
    int t; scanf("%d", &t);
    while(t--){
        int n; scanf("%d", &n);
        vector<ll> a(n+1);
        for(int i=1;i<=n;i++) scanf("%lld", &a[i]);
        vector<vector<int>> adj(n+1);
        for(int i=0;i<n-1;i++){
            int u,v; scanf("%d %d", &u,&v);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<int> parent(n+1,0), order; order.reserve(n);
        vector<int> sz(n+1,1);
        vector<char> visited(n+1,0);

        // iterative DFS to get order (for post-order subtree size) and parent
        vector<int> stack_; stack_.reserve(n);
        stack_.push_back(1);
        visited[1]=1;
        parent[1]=0;
        while(!stack_.empty()){
            int u = stack_.back(); stack_.pop_back();
            order.push_back(u);
            for(int v: adj[u]){
                if(!visited[v]){
                    visited[v]=1;
                    parent[v]=u;
                    stack_.push_back(v);
                }
            }
        }
        // process in reverse order (post-order) to accumulate subtree sizes
        for(int i=(int)order.size()-1;i>=0;i--){
            int u = order[i];
            if(parent[u]) sz[parent[u]] += sz[u];
        }

        // children list (just reuse adj minus parent edge)
        ll answer = 0;
        for(int x=1;x<=n;x++){
            if(!isSquare(a[x])) continue;
            ll S1=0,S2=0,S3=0;
            for(int v: adj[x]){
                ll csz;
                if(v == parent[x]) csz = (ll)n - sz[x];
                else csz = sz[v];
                S1 += csz;
                S2 += csz*csz;
                S3 += csz*csz*csz;
            }
            // S1 should equal n-1
            ll term3 = (S1*S1*S1 - 3*S1*S2 + 2*S3) / 6;
            ll term2 = (S1*S1 - S2) / 2;
            answer += term3 + term2;
        }
        printf("%lld\n", answer);
    }
}