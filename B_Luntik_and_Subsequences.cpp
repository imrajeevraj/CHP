# include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;

    while(t--){
        int n, count_one = 0, count_zero = 0; 
        cin>>n;
        
        for(int i = 0; i < n; i++){
            int x;
            cin>>x;
            if (x == 1){
                count_one++;
            }
            if(x == 0){
                count_zero++;
            }
        }
        long long ans = count_one * pow(2, count_zero);
        cout<<ans<<"\n";
    }
    return 0;
}