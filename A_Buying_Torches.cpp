# include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
        long long x, y, k;
        cin>>x>>y>>k;
        long long need = k * y + k -1;
        long long gain_Trades = (need + (x - 2))/ (x - 1);
        cout<<gain_Trades + k<<"\n";
    }
    return 0;
}